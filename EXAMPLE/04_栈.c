/*
 * 顺序栈
 *
 * 与第四次作业「栈操作」一致：容量 100，top 表示栈顶下一个空闲位置。
 *   top == 0        栈空
 *   top == STACK_MAX 栈满
 *   栈顶元素在 data[top-1]
 *
 * 使用方法：复制结构体及需要的函数到你的 stack.c 等文件中。
 */

#include <stdio.h>

/* ========== 栈：结构体定义 ========== */

#define STACK_MAX 100

typedef struct {
    int data[STACK_MAX];
    int top;           /* 栈顶下一个空闲位置；0 表示空栈 */
} IntStack;

/* ========== 栈：初始化与状态 ========== */

/*
 * 功能：初始化空栈
 * 返回：无
 *
 * 使用示例：
 *   IntStack s;
 *   stackInit(&s);
 */
void stackInit(IntStack *s)
{
    s->top = 0;
}

/*
 * 功能：判断栈是否为空
 * 返回：1 空，0 非空
 *
 * 使用示例：
 *   if (stackIsEmpty(&s)) printf("error ");
 */
int stackIsEmpty(const IntStack *s)
{
    return s->top == 0;
}

/*
 * 功能：判断栈是否已满
 * 返回：1 满，0 未满
 *
 * 使用示例：
 *   if (stackIsFull(&s)) printf("error");
 */
int stackIsFull(const IntStack *s)
{
    return s->top >= STACK_MAX;
}

/*
 * 功能：返回栈中元素个数
 * 返回：元素个数
 *
 * 使用示例：
 *   int n = stackSize(&s);
 */
int stackSize(const IntStack *s)
{
    return s->top;
}

/*
 * 功能：清空栈
 * 返回：无
 *
 * 使用示例：
 *   stackClear(&s);
 */
void stackClear(IntStack *s)
{
    s->top = 0;
}

/* ========== 栈：入栈、出栈、读栈顶 ========== */

/*
 * 功能：元素 x 入栈
 * 返回：1 成功，0 失败（栈满）
 *
 * 使用示例：
 *   stackPush(&s, 10);
 *   stackPush(&s, 20);
 */
int stackPush(IntStack *s, int x)
{
    if (s->top >= STACK_MAX)
        return 0;
    s->data[s->top] = x;
    s->top++;
    return 1;
}

/*
 * 功能：栈顶元素出栈
 * 返回：1 成功（值写入 *out），0 失败（栈空）
 *
 * 使用示例：
 *   int x;
 *   if (!stackPop(&s, &x)) printf("error ");
 *   else printf("%d ", x);
 */
int stackPop(IntStack *s, int *out)
{
    if (s->top == 0)
        return 0;
    s->top--;
    if (out != NULL)
        *out = s->data[s->top];
    return 1;
}

/*
 * 功能：读取栈顶元素但不出栈
 * 返回：1 成功，0 失败（栈空）
 *
 * 使用示例：
 *   int x;
 *   if (stackPeek(&s, &x)) printf("栈顶是 %d\n", x);
 */
int stackPeek(const IntStack *s, int *out)
{
    if (s->top == 0)
        return 0;
    if (out != NULL)
        *out = s->data[s->top - 1];
    return 1;
}

/* ========== 栈：辅助输出 ========== */

/*
 * 功能：从栈底到栈顶打印（调试用）
 * 返回：无
 *
 * 使用示例：
 *   stackPrint(&s);
 */
void stackPrint(const IntStack *s)
{
    int i;

    for (i = 0; i < s->top; i++) {
        printf("%d", s->data[i]);
        if (i < s->top - 1)
            printf(" ");
    }
    printf("\n");
}
