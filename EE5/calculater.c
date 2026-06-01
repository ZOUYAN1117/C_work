#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 表达式树的节点结构
struct node
{
    int is_op;                 // 标记是否为操作符（1表示操作符，0表示操作数）
    int val;                   // 存储具体的值，可能为字符（操作符如 '+'）或整数（操作数）
    struct node *left, *right; // 左子节点和右子节点指针
};

// 后缀表达式的词法单元结构
struct token
{
    int is_op; // 标记是否为操作符（1表示操作符，0表示操作数）
    int val;   // 存储具体的值
};

// 获取操作符的优先级：乘除优先级为2，加减优先级为1，其余为0
int precedence(int op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// 递归计算表达式树的函数（后序遍历机制）
int eval(struct node *root)
{
    if (!root)
        return 0; // 空节点返回0
    if (!root->is_op)
        return root->val; // 如果是叶子节点(操作数)，直接返回其值

    // 递归计算左右子树的值
    int l = eval(root->left);
    int r = eval(root->right);

    // 根据根节点的操作符类型进行计算并返回
    if (root->val == '+')
        return l + r;
    if (root->val == '-')
        return l - r;
    if (root->val == '*')
        return l * r;
    if (root->val == '/')
        return l / r; // C语言的整数除法，自带向下取整特性
    return 0;
}

int main()
{
    struct token postfix[1005]; // 存储转换后的后缀表达式
    int p_idx = 0;              // 后缀表达式数组的索引

    int op_stack[1005]; // 操作符栈，用于中缀转后缀调度算法 (Shunting-yard algorithm)
    int op_top = 0;     // 操作符栈顶指针

    int num = 0;    // 当前解析的多位数字的具体值
    int in_num = 0; // 标识当前是否正在连续读取一个数字

    int c;
    // 1. 中缀表达式转后缀表达式
    while ((c = getchar()) != EOF)
    {
        if (c == '=')
        {
            // 遇到 '=' 表示表达式结束。如果前面还有解析到一半的数字，需要先保存到后缀表达式中。
            if (in_num)
            {
                postfix[p_idx].is_op = 0;
                postfix[p_idx].val = num;
                p_idx++;
                in_num = 0;
            }
            break;
        }
        if (isdigit(c))
        {
            // 解析多位数字：累乘十进制权值
            num = num * 10 + (c - '0');
            in_num = 1;
        }
        else
        {
            // 如果上一个解析的是数字，遇到符号/空格需要将该完整数字推入后缀表达式数组中
            if (in_num)
            {
                postfix[p_idx].is_op = 0;
                postfix[p_idx].val = num;
                p_idx++;
                in_num = 0;
                num = 0;
            }

            // 忽略空格和空白字符
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
            {
                continue;
            }

            // 下面就是经典的调度场算法核心逻辑
            if (c == '(')
            {
                // 左括号直接压入操作符栈
                op_stack[op_top++] = c;
            }
            else if (c == ')')
            {
                // 遇到右括号，将操作符栈中的符号不断弹出压入后缀表达式，直到遇到左括号 '(' 为止
                while (op_top > 0 && op_stack[op_top - 1] != '(')
                {
                    postfix[p_idx].is_op = 1;
                    postfix[p_idx].val = op_stack[--op_top];
                    p_idx++;
                }
                if (op_top > 0)
                    op_top--; // 将左括号 '(' 从栈中弹出并丢弃
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                // 遇到四则运算符：将优先级大于或等于当前运算符的其他栈顶运算符弹出，加入后缀表达式中
                while (op_top > 0 && op_stack[op_top - 1] != '(' && precedence(op_stack[op_top - 1]) >= precedence(c))
                {
                    postfix[p_idx].is_op = 1;
                    postfix[p_idx].val = op_stack[--op_top];
                    p_idx++;
                }
                // 最后把当前运算符压栈
                op_stack[op_top++] = c;
            }
        }
    }

    // 如果字符串结束前刚好在一个数字状态中，将其压入
    if (in_num)
    {
        postfix[p_idx].is_op = 0;
        postfix[p_idx].val = num;
        p_idx++;
    }
    // 将栈中剩余的操作符全部输出到后缀表达式数组中
    while (op_top > 0)
    {
        postfix[p_idx].is_op = 1;
        postfix[p_idx].val = op_stack[--op_top];
        p_idx++;
    }

    // 2. 根据后缀表达式建立表达式树 (Expression Tree)
    struct node *stack[1005]; // 指针栈，存放树节点
    int top = 0;

    for (int i = 0; i < p_idx; i++)
    {
        // 分配新节点内存并初始化
        struct node *n = (struct node *)malloc(sizeof(struct node));
        n->is_op = postfix[i].is_op;
        n->val = postfix[i].val;
        n->left = n->right = NULL;

        if (n->is_op)
        {
            // 如果遇到操作符，从栈顶弹出两棵子树（因为是后缀，先弹出的T1在右，后弹出的T2在左）
            struct node *T1 = stack[--top]; // 右子节点
            struct node *T2 = stack[--top]; // 左子节点
            n->left = T2;
            n->right = T1;
            // 将以此操作符为根的新连好的子树重新压回栈中
            stack[top++] = n;
        }
        else
        {
            // 如果是操作数，也就是叶节点，直接压入树节点栈中
            stack[top++] = n;
        }
    }

    if (top == 0)
        return 0;
    struct node *root = stack[0]; // 栈中唯一的最后元素正是整个表达式树的根节点

    // 3. 题目要求的输出：首先输出表达式树根、左子节点及右子节点上的运算符或操作数
    if (root)
    {
        if (root->is_op)
            printf("%c", root->val);
        else
            printf("%d", root->val);

        if (root->left)
        { // 若有左节点则输出
            printf(" ");
            if (root->left->is_op)
                printf("%c", root->left->val);
            else
                printf("%d", root->left->val);
        }

        if (root->right)
        { // 若有右节点则输出
            printf(" ");
            if (root->right->is_op)
                printf("%c", root->right->val);
            else
                printf("%d", root->right->val);
        }
        printf("\n"); // 完毕后跟随回车
    }

    // 4. 递归计算整棵表达式树的结果并按要求进行输出
    int res = eval(root);
    printf("%d\n", res);

    return 0;
}
