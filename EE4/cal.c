#include <stdio.h>
#include <stdlib.h>

/* 数字栈：使用 float 存储计算值 */
float numstack[100];
int numtop = -1; /* 数字栈顶索引，-1 表示空 */

/* 操作符栈：存放 '+','-','*','/','(',')' 等 */
char opstack[100];
int optop = -1; /* 操作符栈顶索引，-1 表示空 */

/* 将数字入栈（简单边界检查） */
void pushnum(float x)
{
    if (numtop == 99)
    {
        printf("error\n"); /* 栈溢出处理（仅打印） */
        return;
    }
    numstack[++numtop] = x;
}

/* 将操作符入栈（简单边界检查） */
void pushop(char c)
{
    if (optop == 99)
    {
        printf("error\n"); /* 栈溢出处理（仅打印） */
        return;
    }
    opstack[++optop] = c;
}

/* 弹出数字（空栈时打印 error 并返回 0） */
float popnum()
{
    if (numtop == -1)
    {
        printf("error\n");
        return 0;
    }
    return numstack[numtop--];
}

/* 弹出操作符（空栈时打印 error 并返回 0） */
char popop()
{
    if (optop == -1)
    {
        printf("error\n");
        return 0;
    }
    return opstack[optop--];
}

/* 返回操作符优先级：+,- ->1 ; *,/ ->2 ; 其他 ->0 */
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

/* 对 a 和 b 应用操作符 op，注意顺序是 a op b */
float calculate(float a, float b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b; /* 未检查除以 0 的情况 */
    return 0;
}

int main()
{
    int op, x;
    int c;
    /* 逐字符读取输入直到 EOF */
    while ((c = getchar()) != EOF)
    {
        if (c >= '0' && c <= '9')
        {
            /* 遇到数字字符：把它放回输入流，用 scanf 读取完整的整数 */
            ungetc(c, stdin);
            scanf("%d", &x); /* 只接受整数（多位整数也可以） */
            pushnum(x);      /* 将读取到的整数以 float 入栈 */
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            /* 遇到二元运算符：在运算符栈中弹出所有优先级 >= 当前运算符的操作并计算 */
            while (optop != -1 && precedence(opstack[optop]) >= precedence(c))
            {
                op = popop();
                float b = popnum();
                float a = popnum();
                pushnum(calculate(a, b, op));
            }
            /* 将当前操作符入栈，等待后面的数或更高优先级的运算 */
            pushop(c);
        }
        else if (c == ' ')
        {
            continue; /* 跳过空格 */
        }
        else if (c == '(')
        {
            /* 左括号直接入栈，作为分隔符，阻止外层运算符弹出 */
            pushop(c);
        }
        else if (c == ')')
        {
            /* 右括号：弹出直到遇到左括号 '('，对中间表达式求值 */
            while (optop != -1 && opstack[optop] != '(')
            {
                op = popop();
                float b = popnum();
                float a = popnum();
                pushnum(calculate(a, b, op));
            }
            popop(); /* 弹出并丢弃左括号 '(' */
        }
        else if (c == '=')
        {
            /* 遇到 '='：将栈中剩余操作符全部计算完，输出结果并结束 */
            while (optop != -1)
            {
                op = popop();
                float b = popnum();
                float a = popnum();
                pushnum(calculate(a, b, op));
            }
            printf("%.2f\n", popnum()); /* 输出两位小数结果 */
            return 0;
        }
        /* 其他字符未显式处理（会被忽略或导致行为未定义） */
    }
}
