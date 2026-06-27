#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define STACK_MAX 105
#define NAME_MAX 15
int N;
/**
 * 结构体: IntStack - 顺序栈结构定义
 * 成员：
 * - data: 静态数组，存储栈中元素
 * - top: 栈顶指针，指向栈顶元素的下一个空闲位置 (0 表示空栈)
 */
typedef struct
{
    char data[STACK_MAX][NAME_MAX];
    int top; /* 栈顶下一个空闲位置；0 表示空栈 */
} IntStack;

/**
 * 初始化空栈
 * 参数：
 * - s: 顺序栈指针
 * 返回值：无
 */
void stackInit(IntStack *s)
{
    s->top = 0;
}

/**
 * 判断栈是否为空
 * 参数：
 * - s: 顺序栈指针
 * 返回值：1 表示为空，0 表示非空
 */
int stackIsEmpty(const IntStack *s)
{
    return s->top == 0;
}

/**
 * 判断栈是否已满
 * 参数：
 * - s: 顺序栈指针
 * 返回值：1 表示已满，0 表示未满
 */
int stackIsFull(const IntStack *s)
{
    return s->top >= N;
}

/**
 * 获取栈中当前元素个数
 * 参数：
 * - s: 顺序栈指针
 * 返回值：元素个数
 */
int stackSize(const IntStack *s)
{
    return s->top;
}

/**
 * 将元素 x 压入栈顶 (入栈)
 * 参数：
 * - s: 顺序栈指针
 * - x: 待入栈的整型数值
 * 返回值：1 成功，0 失败 (栈满)
 */
int stackPush(IntStack *s, char *x)
{
    // 判断是否栈满
    if (s->top >= N)
        return 0;

    // 在当前空闲位置填值，并递增指针
    strcpy(s->data[s->top], x);
    s->top++;
    return 1;
}

/**
 * 弹出栈顶元素并获取其值 (出栈)
 * 参数：
 * - s: 顺序栈指针
 * - out: 指针，用于输出弹出的元素值
 * 返回值：1 成功，0 失败 (栈空)
 */
int stackPop(IntStack *s, char *out)
{
    // 判断是否栈空
    if (s->top == 0)
        return 0;

    // 递减指针，并在需要时传回该位置数据值
    s->top--;
    if (out != NULL)
        strcpy(out, s->data[s->top]);
    return 1;
}

/**
 * 调试输出栈内所有元素 (从栈底到栈顶方向以空格分隔打印)
 * 参数：
 * - s: 顺序栈指针
 * 返回值：无
 */
void stackPrint(const IntStack *s)
{
    int i;

    // 顺序打印静态数组中的元素
    for (i = s->top - 1; i >= 0; i--)
    {
        printf("%s\n", s->data[i]);
    }
}

int main()
{
    int sum = 0, op = 0;
    IntStack *s, *s2;
    char temp[NAME_MAX];
    s = (IntStack *)malloc(sizeof(IntStack));
    s2 = (IntStack *)malloc(sizeof(IntStack));
    stackInit(s);
    stackInit(s2);
    scanf("%d", &N);
    while (scanf("%d", &op), op != -1)
    {
        if (op == 1)
        {
            scanf("%s", temp);
            stackPush(s, temp);
        }
        else if (op == 2)
        {
            scanf("%s", temp);
            char out[NAME_MAX];
            while (stackPop(s, out))
            {
                sum++;
                if (strcmp(out, temp) == 0)
                {
                    while (stackPop(s2, out))
                        stackPush(s, out);
                    break;
                }
                stackPush(s2, out);
            }
            while (stackPop(s2, out))
            {
                stackPush(s, out);
                sum--;
            }
        }
    }
    printf("%d\n", sum);
    stackPrint(s);
}
