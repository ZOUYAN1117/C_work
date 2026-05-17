#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 最大字符串长度，包含末尾可能的换行和'\0'。题目要求不超过512，这里取515留有余量 */
#define MAX_LEN 515

/* 定义一个操作结构体，用于记录历史操作以支持撤销(Undo)功能 */
typedef struct
{
    int type;          // 操作类型：1 表示插入操作(insert)，2 表示删除操作(delete)
    int pos;           // 操作发生的起始位置
    char str[MAX_LEN]; // 涉及的字符串：若是插入操作则是被插入的串；若是删除操作则是被删掉的串
} Operation;

/* 声明一个足够大的栈，用于依次存放历史上执行过的每一次编辑操作 */
Operation stack[10000];
int top = 0; // 栈顶指针，指向下一个即将写入的空位

/*
 * 在指定位置插入字符串
 * @param text: 正在编辑的当前文本串
 * @param pos: 输入要插入的位置 (0表示最开头)
 * @param str: 将要被插入的字符串内容
 */
void insert_str(char *text, int pos, const char *str)
{
    int len = strlen(text);
    int slen = strlen(str);

    // 步骤1：将从pos位置开始的原有字符向后平移slen个位置，给新串腾出空间
    for (int i = len; i >= pos; i--)
    {
        text[i + slen] = text[i];
    }

    // 步骤2：把需要插入的字符串str逐个字符拷贝到腾出的空间中
    for (int i = 0; i < slen; i++)
    {
        text[pos + i] = str[i];
    }
}

/*
 * 从指定位置删除一定数量的字符，并将被删除的字符保存下来
 * @param text: 正在编辑的当前文本串
 * @param pos: 删除操作的起始位置
 * @param n: 企图删除的字符个数
 * @param deleted: 用于保存实际被删除掉的子串的缓冲区(服务于撤销功能)
 */
void delete_str(char *text, int pos, int n, char *deleted)
{
    int len = strlen(text);

    // 题目要求：若要删除的字符个数多于已有字符个数，则按实际剩下字符数删除
    if (pos + n > len)
    {
        n = len - pos;
    }

    // 步骤1：将被删除的这些字符备份存入deleted中，以便将来撤销时恢复
    for (int i = 0; i < n; i++)
    {
        deleted[i] = text[pos + i];
    }
    deleted[n] = '\0'; // 为备份的子串加上字符串结束符

    // 步骤2：将后面的剩余字符整体向前平移n个位置，覆盖掉被删除的部分
    for (int i = pos + n; i <= len; i++)
    {
        text[i - n] = text[i];
    }
}

int main()
{
    char text[MAX_LEN];
    // 读取第一行：已经历过 n 步操作后的现阶段文本串
    fgets(text, sizeof(text), stdin);
    int len = strlen(text);

    // 去除使用fgets带来的多余换行符('\n'或'\r')
    if (text[len - 1] == '\n' || text[len - 1] == '\r')
    {
        text[len - 1] = '\0';
        len--;
    }
    // 兼容Windows平台的CRLF格式('\r\n')
    if (text[len - 1] == '\r')
    {
        text[len - 1] = '\0';
    }

    int n;
    // 读取历史操作的记录数 n
    scanf("%d", &n);

    // 依序读取 n 条历史记录，并将它们直接送入操作记录栈
    // 此时不需要执行它们，因为初始文本已经是执行过这 n 步的模样了
    for (int i = 0; i < n; i++)
    {
        int type, pos;
        char str[MAX_LEN];
        scanf("%d %d %s", &type, &pos, str);
        stack[top].type = type;
        stack[top].pos = pos;
        strcpy(stack[top].str, str);
        top++; // 栈顶游标自增
    }

    int op;
    // 循环不断读取最新的命令，直到读入s-1标记为结束
    while (scanf("%d", &op), op != -1)
    {
        if (op == 1) // 1表示执行插入操作
        {
            int pos;
            char str[MAX_LEN];
            scanf("%d %s", &pos, str); // 读入要插入的位置和具体字符串内容

            insert_str(text, pos, str); // 1. 真实更新到文本中

            // 2. 将本次插入操作包装妥当后入栈，以备后期撤销
            stack[top].type = 1;
            stack[top].pos = pos;
            strcpy(stack[top].str, str);
            top++;
        }
        else if (op == 2) // 2表示执行删除操作
        {
            int pos, num;
            scanf("%d %d", &pos, &num); // 读入需删除的起始位置和待删除字符数量
            char deleted[MAX_LEN];

            delete_str(text, pos, num, deleted); // 1. 实现在文本中删除字符，同时获取被删留下的子串

            // 2. 将本次删除操作（及其被删除的内容）包装入栈。通过记录"被删除的内容"，才能对其撤销
            stack[top].type = 2;
            stack[top].pos = pos;
            strcpy(stack[top].str, deleted);
            top++;
        }
        else if (op == 3) // 3表示执行撤销(undo)操作
        {
            if (top > 0) // 防御：当栈里确有历史可以撤销时才能执行
            {
                top--; // 弹出最近的一次操作记录
                Operation last = stack[top];

                if (last.type == 1)
                {
                    // 若刚才是"插入"操作(type 1)：其逆操作是对着此插入的位置再把新塞进去的字符删了
                    char temp[MAX_LEN];
                    delete_str(text, last.pos, strlen(last.str), temp);
                }
                else if (last.type == 2)
                {
                    // 若刚才是"删除"操作(type 2)：其逆操作是再把当时拿掉的内容从同个位置插回去
                    insert_str(text, last.pos, last.str);
                }
            }
        }
    }
    // 所有操作结束之后，直接把编辑器当前的残存纯文本输出
    printf("%s\n", text);
    return 0;
}
