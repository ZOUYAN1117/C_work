/**
 * 文件: 栈.c
 * 描述: 顺序存储结构（静态数组）实现的整型栈基本操作，包含初始化、状态判断、入栈、出栈及读栈顶。
 */

#include <stdio.h>

/**
 * 结构体: IntStack - 顺序栈结构定义
 * 成员：
 * - data: 静态数组，存储栈中元素
 * - top: 栈顶指针，指向栈顶元素的下一个空闲位置 (0 表示空栈)
 */
#define STACK_MAX 100

typedef struct {
    int data[STACK_MAX];
    int top;           /* 栈顶下一个空闲位置；0 表示空栈 */
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
    return s->top >= STACK_MAX;
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
 * 清空栈 (即将栈顶指针置 0)
 * 参数：
 * - s: 顺序栈指针
 * 返回值：无
 */
void stackClear(IntStack *s)
{
    s->top = 0;
}

/**
 * 将元素 x 压入栈顶 (入栈)
 * 参数：
 * - s: 顺序栈指针
 * - x: 待入栈的整型数值
 * 返回值：1 成功，0 失败 (栈满)
 */
int stackPush(IntStack *s, int x)
{
    // 判断是否栈满
    if (s->top >= STACK_MAX)
        return 0;
    
    // 在当前空闲位置填值，并递增指针
    s->data[s->top] = x;
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
int stackPop(IntStack *s, int *out)
{
    // 判断是否栈空
    if (s->top == 0)
        return 0;
    
    // 递减指针，并在需要时传回该位置数据值
    s->top--;
    if (out != NULL)
        *out = s->data[s->top];
    return 1;
}

/**
 * 读取栈顶元素的值 (不出栈)
 * 参数：
 * - s: 顺序栈指针
 * - out: 指针，用于输出栈顶元素值
 * 返回值：1 成功，0 失败 (栈空)
 */
int stackPeek(const IntStack *s, int *out)
{
    // 判断是否栈空
    if (s->top == 0)
        return 0;
    
    // 获取当前栈顶元素 (位于 top - 1 处)
    if (out != NULL)
        *out = s->data[s->top - 1];
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
    for (i = 0; i < s->top; i++) {
        printf("%d", s->data[i]);
        if (i < s->top - 1)
            printf(" ");
    }
    printf("\n");
}
