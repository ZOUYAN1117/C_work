/**
 * 文件: 队列.c
 * 描述: 顺序队列与循环队列的实现，包含队列的初始化、入队、出队、读队头与打印操作。
 */

#include <stdio.h>

/* ==================== Part A：普通顺序队列 ==================== */

/**
 * 结构体: IntQueue - 普通顺序队列结构定义 (不循环取模)
 * 成员：
 * - data: 静态数组，存储队列元素
 * - front: 队头元素下标位置
 * - rear: 队尾下一个空闲下标位置
 * - size: 当前队列的元素个数
 */
#define QUEUE_MAX 10000   /* 最大队列容量 */

typedef struct {
    int data[QUEUE_MAX];
    int front;         /* 队头元素下标 */
    int rear;          /* 队尾下一空位下标 */
    int size;          /* 当前元素个数 */
} IntQueue;

/**
 * 初始化普通顺序队列
 * 参数：
 * - q: 队列结构指针
 * 返回值：无
 */
void queueInit(IntQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

/**
 * 判断普通顺序队列是否为空
 * 参数：
 * - q: 队列结构指针
 * 返回值：1 为空，0 非空
 */
int queueIsEmpty(const IntQueue *q)
{
    return q->size == 0;
}

/**
 * 判断普通顺序队列是否已满
 * 参数：
 * - q: 队列结构指针
 * 返回值：1 已满，0 未满
 */
int queueIsFull(const IntQueue *q)
{
    return q->size >= QUEUE_MAX;
}

/**
 * 获取普通顺序队列的元素个数
 * 参数：
 * - q: 队列结构指针
 * 返回值：元素个数
 */
int queueSize(const IntQueue *q)
{
    return q->size;
}

/**
 * 清空普通顺序队列
 * 参数：
 * - q: 队列结构指针
 * 返回值：无
 */
void queueClear(IntQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

/**
 * 元素 x 入队 (追加到队尾)
 * 参数：
 * - q: 队列结构指针
 * - x: 待入队的元素值
 * 返回值：1 成功，0 失败 (队满)
 */
int queueEnqueue(IntQueue *q, int x)
{
    if (q->size >= QUEUE_MAX)
        return 0;
    
    // 写入尾部并递增尾指针及计数
    q->data[q->rear] = x;
    q->rear++;
    q->size++;
    return 1;
}

/**
 * 队头元素出队
 * 参数：
 * - q: 队列结构指针
 * - out: 用于输出弹出的元素值
 * 返回值：1 成功，0 失败 (队空)
 */
int queueDequeue(IntQueue *q, int *out)
{
    if (q->size == 0)
        return 0;
    
    // 传回头部值，并增加头指针、减少计数
    if (out != NULL)
        *out = q->data[q->front];
    q->front++;
    q->size--;
    return 1;
}

/**
 * 读取队头元素 (不出队)
 * 参数：
 * - q: 队列结构指针
 * - out: 用于输出队头元素值
 * 返回值：1 成功，0 失败 (队空)
 */
int queuePeek(const IntQueue *q, int *out)
{
    if (q->size == 0)
        return 0;
    if (out != NULL)
        *out = q->data[q->front];
    return 1;
}

/**
 * 从队头到队尾打印普通顺序队列所有元素 (空格分隔，换行结尾)
 * 参数：
 * - q: 队列结构指针
 * 返回值：无
 */
void queuePrint(const IntQueue *q)
{
    int i, idx;

    for (i = 0; i < q->size; i++) {
        idx = q->front + i;
        printf("%d", q->data[idx]);
        if (i < q->size - 1)
            printf(" ");
    }
    printf("\n");
}

/* ==================== Part B：循环队列 ==================== */

/**
 * 结构体: IntCQueue - 循环队列结构定义
 * 成员：
 * - data: 静态数组，存储队列元素
 * - front: 队头元素下标位置
 * - rear: 队尾下一个空闲下标位置
 * - count: 当前队列元素个数 (循环取模场景以此判满判空更直观)
 */
typedef struct {
    int data[QUEUE_MAX];
    int front;         /* 队头元素下标 */
    int rear;          /* 队尾下一空位下标 */
    int count;         /* 当前元素个数 */
} IntCQueue;

/**
 * 初始化循环队列
 * 参数：
 * - q: 循环队列结构指针
 * 返回值：无
 */
void cqueueInit(IntCQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

/**
 * 判断循环队列是否为空
 * 参数：
 * - q: 循环队列结构指针
 * 返回值：1 为空，0 非空
 */
int cqueueIsEmpty(const IntCQueue *q)
{
    return q->count == 0;
}

/**
 * 判断循环队列是否已满
 * 参数：
 * - q: 循环队列结构指针
 * 返回值：1 已满，0 未满
 */
int cqueueIsFull(const IntCQueue *q)
{
    return q->count >= QUEUE_MAX;
}

/**
 * 获取循环队列当前元素个数
 * 参数：
 * - q: 循环队列结构指针
 * 返回值：元素个数
 */
int cqueueSize(const IntCQueue *q)
{
    return q->count;
}

/**
 * 清空循环队列
 * 参数：
 * - q: 循环队列结构指针
 * 返回值：无
 */
void cqueueClear(IntCQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

/**
 * 元素 x 进入循环队列
 * 参数：
 * - q: 循环队列结构指针
 * - x: 待入队的元素值
 * 返回值：1 成功，0 失败 (队满)
 */
int cqueueEnqueue(IntCQueue *q, int x)
{
    if (q->count >= QUEUE_MAX)
        return 0;
    
    // 写入尾部并实现尾指针环绕环形数组自增
    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % QUEUE_MAX;
    q->count++;
    return 1;
}

/**
 * 循环队列队头元素出队
 * 参数：
 * - q: 循环队列结构指针
 * - out: 用于输出弹出的元素值
 * 返回值：1 成功，0 失败 (队空)
 */
int cqueueDequeue(IntCQueue *q, int *out)
{
    if (q->count == 0)
        return 0;
    
    // 传回头部值，实现头部指针环绕环形数组自增并缩减计数
    if (out != NULL)
        *out = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_MAX;
    q->count--;
    return 1;
}

/**
 * 读取循环队列队头元素 (不出队)
 * 参数：
 * - q: 循环队列结构指针
 * - out: 用于输出队头元素值
 * 返回值：1 成功，0 失败 (队空)
 */
int cqueuePeek(const IntCQueue *q, int *out)
{
    if (q->count == 0)
        return 0;
    if (out != NULL)
        *out = q->data[q->front];
    return 1;
}

/**
 * 从队头到队尾打印循环队列所有元素 (空格分隔，换行结尾)
 * 参数：
 * - q: 循环队列结构指针
 * 返回值：无
 */
void cqueuePrint(const IntCQueue *q)
{
    int i, idx;

    // 每次计算环形偏移下标并打印
    for (i = 0; i < q->count; i++) {
        idx = (q->front + i) % QUEUE_MAX;
        printf("%d", q->data[idx]);
        if (i < q->count - 1)
            printf(" ");
    }
    printf("\n");
}
