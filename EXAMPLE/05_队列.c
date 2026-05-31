/*
 * 队列（两种实现，按题目选抄其一即可）
 *
 * A. 普通顺序队列：front 为队头下标，rear 为队尾下一空位，size 记录个数
 *    适合第四次作业「银行排队」等，写法直观。
 *
 * B. 循环队列：front/rear 下标取模，count 记录个数，空间利用率高。
 *
 * 约定：返回 1 成功，0 失败。
 */

#include <stdio.h>

/* ========== 普通队列：结构体定义 ========== */

#define QUEUE_MAX 10000   /* 可按题目改小 */

typedef struct {
    int data[QUEUE_MAX];
    int front;         /* 队头元素下标 */
    int rear;          /* 队尾下一空位下标 */
    int size;          /* 当前元素个数 */
} IntQueue;

/* ========== 普通队列：初始化与状态 ========== */

/*
 * 功能：初始化空队列
 * 返回：无
 *
 * 使用示例：
 *   IntQueue q;
 *   queueInit(&q);
 */
void queueInit(IntQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

/*
 * 功能：判断队列是否为空
 * 返回：1 空，0 非空
 */
int queueIsEmpty(const IntQueue *q)
{
    return q->size == 0;
}

/*
 * 功能：判断队列是否已满
 * 返回：1 满，0 未满
 */
int queueIsFull(const IntQueue *q)
{
    return q->size >= QUEUE_MAX;
}

/*
 * 功能：返回队列元素个数
 * 返回：元素个数
 */
int queueSize(const IntQueue *q)
{
    return q->size;
}

/*
 * 功能：清空队列
 * 返回：无
 */
void queueClear(IntQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

/* ========== 普通队列：入队、出队、读队头 ========== */

/*
 * 功能：元素 x 入队（加到队尾）
 * 返回：1 成功，0 失败（队满）
 *
 * 使用示例：
 *   queueEnqueue(&q, 10);
 *   queueEnqueue(&q, 20);
 */
int queueEnqueue(IntQueue *q, int x)
{
    if (q->size >= QUEUE_MAX)
        return 0;
    q->data[q->rear] = x;
    q->rear++;
    q->size++;
    return 1;
}

/*
 * 功能：队头元素出队
 * 返回：1 成功（值写入 *out），0 失败（队空）
 *
 * 使用示例：
 *   int x;
 *   if (!queueDequeue(&q, &x)) printf("队列为空\n");
 */
int queueDequeue(IntQueue *q, int *out)
{
    if (q->size == 0)
        return 0;
    if (out != NULL)
        *out = q->data[q->front];
    q->front++;
    q->size--;
    return 1;
}

/*
 * 功能：读取队头元素但不出队
 * 返回：1 成功，0 失败（队空）
 *
 * 使用示例：
 *   int x;
 *   queuePeek(&q, &x);
 */
int queuePeek(const IntQueue *q, int *out)
{
    if (q->size == 0)
        return 0;
    if (out != NULL)
        *out = q->data[q->front];
    return 1;
}

/* ========== 普通队列：辅助输出 ========== */

/*
 * 功能：从队头到队尾打印（调试用）
 * 返回：无
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

/* ========================================================================
 * 循环队列（与上面普通队列二选一即可）
 * ======================================================================== */

/* ========== 循环队列：结构体定义 ========== */

typedef struct {
    int data[QUEUE_MAX];
    int front;         /* 队头元素下标 */
    int rear;          /* 队尾下一空位下标 */
    int count;         /* 当前元素个数，用 count 判空满更直观 */
} IntCQueue;

/* ========== 循环队列：初始化与状态 ========== */

/*
 * 功能：初始化空循环队列
 * 返回：无
 *
 * 使用示例：
 *   IntCQueue cq;
 *   cqueueInit(&cq);
 */
void cqueueInit(IntCQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

/*
 * 功能：判断循环队列是否为空
 * 返回：1 空，0 非空
 */
int cqueueIsEmpty(const IntCQueue *q)
{
    return q->count == 0;
}

/*
 * 功能：判断循环队列是否已满
 * 返回：1 满，0 未满
 */
int cqueueIsFull(const IntCQueue *q)
{
    return q->count >= QUEUE_MAX;
}

/*
 * 功能：返回循环队列元素个数
 * 返回：元素个数
 */
int cqueueSize(const IntCQueue *q)
{
    return q->count;
}

/*
 * 功能：清空循环队列
 * 返回：无
 */
void cqueueClear(IntCQueue *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

/* ========== 循环队列：入队、出队、读队头 ========== */

/*
 * 功能：元素 x 入队
 * 返回：1 成功，0 失败（队满）
 *
 * 使用示例：
 *   cqueueEnqueue(&cq, 10);
 */
int cqueueEnqueue(IntCQueue *q, int x)
{
    if (q->count >= QUEUE_MAX)
        return 0;
    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % QUEUE_MAX;
    q->count++;
    return 1;
}

/*
 * 功能：队头元素出队
 * 返回：1 成功，0 失败（队空）
 *
 * 使用示例：
 *   int x;
 *   cqueueDequeue(&cq, &x);
 */
int cqueueDequeue(IntCQueue *q, int *out)
{
    if (q->count == 0)
        return 0;
    if (out != NULL)
        *out = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_MAX;
    q->count--;
    return 1;
}

/*
 * 功能：读取队头元素但不出队
 * 返回：1 成功，0 失败（队空）
 */
int cqueuePeek(const IntCQueue *q, int *out)
{
    if (q->count == 0)
        return 0;
    if (out != NULL)
        *out = q->data[q->front];
    return 1;
}

/* ========== 循环队列：辅助输出 ========== */

/*
 * 功能：从队头到队尾打印（调试用）
 * 返回：无
 */
void cqueuePrint(const IntCQueue *q)
{
    int i, idx;

    for (i = 0; i < q->count; i++) {
        idx = (q->front + i) % QUEUE_MAX;
        printf("%d", q->data[idx]);
        if (i < q->count - 1)
            printf(" ");
    }
    printf("\n");
}
