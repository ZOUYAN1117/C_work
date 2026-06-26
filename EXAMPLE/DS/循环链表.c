/**
 * 文件: 循环链表.c
 * 描述: 循环单链表与循环双链表的操作，包括入队/插入、长度计算、指定节点及位置删除与销毁。
 */

#include <stdio.h>
#include <stdlib.h>

/* ==================== Part A：循环单链表 ==================== */

/**
 * 结构体: node - 循环单链表节点结构定义
 * 成员：
 * - n: 存储结点的整型数值
 * - link: 指向后继结点的指针 (尾结点的 link 指向头结点)
 */
struct node {
    int n;
    struct node *link;
};

/**
 * 创建一个新的循环单链表结点
 * 参数：
 * - value: 新节点的数值
 * 返回值：新节点指针；分配失败返回 NULL
 */
struct node *clistNewNode(int value)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL)
        return NULL;
    p->n = value;
    p->link = NULL;
    return p;
}

/**
 * 初始化空循环链表指针 (设为 NULL)
 * 参数：
 * - head: 指向循环链表头指针的指针地址
 * - tail: 指向循环链表尾指针的指针地址
 * 返回值：无
 */
void clistMakeEmpty(struct node **head, struct node **tail)
{
    *head = NULL;
    *tail = NULL;
}

/**
 * 将已有的单向链表 (已知尾指针) 首尾相连转化为循环链表
 * 参数：
 * - head: 指向链表头指针的指针地址
 * - tail: 指向链表尾指针的指针地址
 * 返回值：无
 */
void clistBuild(struct node **head, struct node **tail)
{
    // 如果头部和尾部都不为空，让尾部指向头部成环
    if (*head != NULL && *tail != NULL)
        (*tail)->link = *head;
}

/**
 * 在循环单链表尾部追加插入新元素数值
 * 参数：
 * - head: 指向链表头指针的指针地址
 * - tail: 指向链表尾指针的指针地址
 * - value: 待追加的新数据值
 * 返回值：1 成功，0 失败 (内存分配失败)
 */
int clistInsertTail(struct node **head, struct node **tail, int value)
{
    struct node *q = clistNewNode(value);
    if (q == NULL)
        return 0;
    
    // 如果为空表，自己环绕自己；否则将 q 插入尾部并修改成环指向
    if (*head == NULL) {
        *head = q;
        *tail = q;
        q->link = q;          /* 指向自身成环 */
    } else {
        q->link = *head;
        (*tail)->link = q;
        *tail = q;
    }
    return 1;
}

/**
 * 判断循环单链表是否为空
 * 参数：
 * - head: 链表头指针
 * 返回值：1 为空，0 非空
 */
int clistIsEmpty(const struct node *head)
{
    return head == NULL;
}

/**
 * 求循环单链表的长度 (节点数)
 * 参数：
 * - head: 链表头指针
 * 返回值：循环单链表当前节点个数
 */
int clistLength(const struct node *head)
{
    const struct node *p;
    int len = 0;

    if (head == NULL)
        return 0;
    
    // 经典 do-while 绕环遍历
    p = head;
    do {
        len++;
        p = p->link;
    } while (p != head);
    return len;
}

/**
 * 按顺序打印循环单链表 (从 head 开始绕一圈，空格分隔)
 * 参数：
 * - head: 链表头指针
 * 返回值：无
 */
void clistPrint(const struct node *head)
{
    const struct node *p;
    int first = 1;

    if (head == NULL) {
        printf("\n");
        return;
    }
    
    p = head;
    do {
        if (!first)
            printf(" ");
        printf("%d", p->n);
        first = 0;
        p = p->link;
    } while (p != head);
    printf("\n");
}

/**
 * 删除循环单链表中指定下标位置 pos 的节点
 * 参数：
 * - head: 指向链表头指针的指针地址
 * - tail: 指向链表尾指针的指针地址
 * - pos: 待删除节点的下标 (0-indexed)
 * - out: 用于输出删除节点的值
 * 返回值：1 成功，0 失败 (越界)
 */
int clistDeleteAt(struct node **head, struct node **tail, int pos, int *out)
{
    struct node *p, *q;
    int i, len;

    if (*head == NULL || pos < 0)
        return 0;
    
    len = clistLength(*head);
    if (pos >= len)
        return 0;

    // 只有一个节点的情况，直接清空释放
    if (len == 1) {
        if (out != NULL)
            *out = (*head)->n;
        free(*head);
        *head = NULL;
        *tail = NULL;
        return 1;
    }

    // 删除头结点
    if (pos == 0) {
        q = *head;
        if (out != NULL)
            *out = q->n;
        *head = q->link;
        (*tail)->link = *head; // 保持尾部指向新的头部
        free(q);
        return 1;
    }

    // 寻找待删节点的前驱结点
    p = *head;
    for (i = 0; i < pos - 1; i++)
        p = p->link;
    q = p->link;
    
    if (out != NULL)
        *out = q->n;
    p->link = q->link;
    
    // 如果删除了尾节点，需要移动尾指针到前驱
    if (q == *tail)
        *tail = p;
    
    free(q);
    return 1;
}

/**
 * 根据具体的节点指针 target 删除循环单链表中的该节点
 * 参数：
 * - head: 指向头指针的指针地址
 * - tail: 指向尾指针的指针地址
 * - target: 待删除节点的具体指针
 * 返回值：1 成功，0 失败 (target不在链表中)
 */
int clistDeleteNode(struct node **head, struct node **tail, struct node *target)
{
    struct node *p;
    int pos = 0, len, i;

    if (*head == NULL || target == NULL)
        return 0;
    
    // 遍历匹配该指针以确定其下标位置
    p = *head;
    len = clistLength(*head);
    for (i = 0; i < len; i++) {
        if (p == target) {
            return clistDeleteAt(head, tail, pos, NULL);
        }
        p = p->link;
        pos++;
    }
    return 0;
}

/**
 * 销毁循环单链表，释放所有内存
 * 参数：
 * - head: 指向头指针的指针地址
 * - tail: 指向尾指针的指针地址
 * 返回值：无
 */
void clistDestroy(struct node **head, struct node **tail)
{
    struct node *p, *q;

    if (*head == NULL)
        return;

    // 单节点销毁
    if (*head == *tail) {
        free(*head);
        *head = NULL;
        *tail = NULL;
        return;
    }

    // 先断开环变成普通单链表，然后顺序销毁
    (*tail)->link = NULL;     /* 先断环 */
    p = *head;
    while (p != NULL) {
        q = p->link;
        free(p);
        p = q;
    }
    *head = NULL;
    *tail = NULL;
}

/* ==================== Part B：循环双链表 ==================== */

/**
 * 结构体: cdnode - 循环双向链表节点结构定义
 * 成员：
 * - n: 存储结点的整型数值
 * - prior: 指向前驱结点的指针 (首结点的 prior 指向尾)
 * - link: 指向后继结点的指针 (尾结点的 link 指向首)
 */
struct cdnode {
    int n;
    struct cdnode *prior;
    struct cdnode *link;
};

/**
 * 创建一个新的循环双向链表结点
 * 参数：
 * - value: 节点包含的整型数值
 * 返回值：新节点指针；分配失败返回 NULL
 */
struct cdnode *cdlistNewNode(int value)
{
    struct cdnode *p = (struct cdnode *)malloc(sizeof(struct cdnode));
    if (p == NULL)
        return NULL;
    p->n = value;
    p->prior = NULL;
    p->link = NULL;
    return p;
}

/**
 * 初始化循环双链表为空
 * 参数：
 * - head: 指向头指针的指针地址
 * - tail: 指向尾指针的指针地址
 * 返回值：无
 */
void cdlistMakeEmpty(struct cdnode **head, struct cdnode **tail)
{
    *head = NULL;
    *tail = NULL;
}

/**
 * 在循环双链表尾部插入新数据值
 * 参数：
 * - head: 指向头指针的指针地址
 * - tail: 指向尾指针的指针地址
 * - value: 待追加的值
 * 返回值：1 成功，0 失败
 */
int cdlistInsertTail(struct cdnode **head, struct cdnode **tail, int value)
{
    struct cdnode *q = cdlistNewNode(value);
    if (q == NULL)
        return 0;
    
    // 空链表自己首尾自联；否则连接 tail 和新节点并在最前端成环
    if (*head == NULL) {
        *head = *tail = q;
        q->link = q;
        q->prior = q;
    } else {
        q->link = *head;
        q->prior = *tail;
        (*tail)->link = q;
        (*head)->prior = q;
        *tail = q;
    }
    return 1;
}

/**
 * 判断循环双链表是否为空
 * 参数：
 * - head: 链表头指针
 * 返回值：1 为空，0 非空
 */
int cdlistIsEmpty(const struct cdnode *head)
{
    return head == NULL;
}

/**
 * 计算循环双链表的节点数
 * 参数：
 * - head: 链表头指针
 * 返回值：节点总数
 */
int cdlistLength(const struct cdnode *head)
{
    const struct cdnode *p;
    int len = 0;

    if (head == NULL)
        return 0;
    
    p = head;
    do {
        len++;
        p = p->link;
    } while (p != head);
    return len;
}

/**
 * 在循环双链表中摘除并销毁指定的节点指针 target
 * 参数：
 * - head: 指向头指针的指针地址
 * - tail: 指向尾指针的指针地址
 * - target: 待摘除的节点指针
 * 返回值：1 成功，0 失败
 */
int cdlistDeleteNode(struct cdnode **head, struct cdnode **tail, struct cdnode *target)
{
    if (*head == NULL || target == NULL)
        return 0;
    
    // 只有一个节点直接清除
    if (*head == *tail) {
        free(target);
        *head = NULL;
        *tail = NULL;
        return 1;
    }
    
    // 绕开 target 建立前后节点的双向连接
    target->prior->link = target->link;
    target->link->prior = target->prior;
    
    // 维护头尾指针位置
    if (target == *head)
        *head = target->link;
    if (target == *tail)
        *tail = target->prior;
    
    free(target);
    return 1;
}

/**
 * 删除循环双链表中指定下标位置 pos 的节点
 * 参数：
 * - head: 指向头指针的指针地址
 * - tail: 指向尾指针的指针地址
 * - pos: 下标位置 (0-indexed)
 * - out: 用于输出删除节点的值
 * 返回值：1 成功，0 失败 (越界)
 */
int cdlistDeleteAt(struct cdnode **head, struct cdnode **tail, int pos, int *out)
{
    struct cdnode *p;
    int i, len;

    if (*head == NULL || pos < 0)
        return 0;
    
    len = cdlistLength(*head);
    if (pos >= len)
        return 0;
    
    // 寻找到待删节点并执行销毁
    p = *head;
    for (i = 0; i < pos; i++)
        p = p->link;
    if (out != NULL)
        *out = p->n;
    return cdlistDeleteNode(head, tail, p);
}

/**
 * 销毁循环双向链表，释放内存并将头尾置 NULL
 * 参数：
 * - head: 指向头指针的指针地址
 * - tail: 指向尾指针的指针地址
 * 返回值：无
 */
void cdlistDestroy(struct cdnode **head, struct cdnode **tail)
{
    struct cdnode *p, *q;

    if (*head == NULL)
        return;
    if (*head == *tail) {
        free(*head);
        *head = NULL;
        *tail = NULL;
        return;
    }
    
    // 断环，变普通双链表后顺序销毁
    (*head)->prior->link = NULL;
    (*tail)->link = NULL;
    p = *head;
    while (p != NULL) {
        q = p->link;
        free(p);
        p = q;
    }
    *head = NULL;
    *tail = NULL;
}
