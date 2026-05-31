/*
 * 单链表 + 双链表
 *
 * Part A 单链：struct node { int n; struct node *link; };
 * Part B 双链：struct dnode { int n; struct dnode *prior; struct dnode *link; };
 *
 * 使用方法：复制 #include、所需结构体及函数到你的程序中（可只抄 Part A 或 Part B）。
 * 约定：返回 1 成功，0 失败。pos 从 0 开始（第 0 个结点即头结点）。
 */

#include <stdio.h>
#include <stdlib.h>

/* ========== 单链表：结点定义 ========== */

struct node {
    int n;
    struct node *link;
};

/* ========== 单链表：结点创建 ========== */

/*
 * 功能：创建一个值为 value 的新结点
 * 返回：新结点指针；分配失败返回 NULL
 *
 * 使用示例：
 *   struct node *p = newNode(10);
 */
struct node *newNode(int value)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL)
        return NULL;
    p->n = value;
    p->link = NULL;
    return p;
}

/* ========== 单链表：初始化与状态 ========== */

/*
 * 功能：初始化空链表
 * 参数：head - 指向头指针的指针（即 main 里 struct node *list; 则传 &list）
 *
 * 使用示例：
 *   struct node *list = NULL;
 *   initList(&list);
 */
void initList(struct node **head)
{
    *head = NULL;
}

/*
 * 功能：判断链表是否为空
 * 返回：1 空，0 非空
 *
 * 使用示例：
 *   if (listIsEmpty(list)) printf("空链表\n");
 */
int listIsEmpty(const struct node *head)
{
    return head == NULL;
}

/*
 * 功能：求链表长度
 * 返回：结点个数
 *
 * 使用示例：
 *   int len = listLength(list);
 */
int listLength(const struct node *head)
{
    int len = 0;
    const struct node *p = head;

    while (p != NULL) {
        len++;
        p = p->link;
    }
    return len;
}

/* ========== 单链表：头尾插入 ========== */

/*
 * 功能：在链表头部插入结点（头插法）
 * 返回：1 成功，0 失败（内存不足）
 *
 * 使用示例：
 *   listInsertHead(&list, 10);
 *   listInsertHead(&list, 20);   // 链表变为 20 -> 10
 */
int listInsertHead(struct node **head, int value)
{
    struct node *p = newNode(value);
    if (p == NULL)
        return 0;
    p->link = *head;
    *head = p;
    return 1;
}

/*
 * 功能：在链表尾部插入结点（无 tail 指针，需遍历到末尾，O(n)）
 *       适合结点不多、第三次作业「尾插建表」类题目。
 * 返回：1 成功，0 失败
 *
 * 使用示例：
 *   listInsertTail(&list, 10);
 *   listInsertTail(&list, 20);   // 链表变为 10 -> 20
 */
int listInsertTail(struct node **head, int value)
{
    struct node *p, *q;

    q = newNode(value);
    if (q == NULL)
        return 0;
    if (*head == NULL) {
        *head = q;
        return 1;
    }
    p = *head;
    while (p->link != NULL)
        p = p->link;
    p->link = q;
    return 1;
}

/*
 * 功能：在链表尾部插入结点（维护 tail 指针，O(1) 尾插）
 * 参数：tail 传 struct node **tail，首次调用前 *tail 应为 NULL
 * 返回：1 成功，0 失败
 *
 * 使用示例：
 *   struct node *list = NULL, *tail = NULL;
 *   listInsertTailFast(&list, &tail, 10);
 *   listInsertTailFast(&list, &tail, 20);
 */
int listInsertTailFast(struct node **head, struct node **tail, int value)
{
    struct node *q = newNode(value);
    if (q == NULL)
        return 0;
    if (*head == NULL) {
        *head = q;
        *tail = q;
    } else {
        (*tail)->link = q;
        *tail = q;
    }
    return 1;
}

/* ========== 单链表：指定位置插入与删除 ========== */

/*
 * 功能：在下标 pos 处插入结点（pos==0 为头插，pos==length 为尾插）
 * 返回：1 成功，0 失败
 *
 * 使用示例：
 *   listInsertAt(&list, 1, 99);   // 插到第 2 个位置
 */
int listInsertAt(struct node **head, int pos, int value)
{
    struct node *p, *q;
    int i;

    if (pos < 0)
        return 0;
    if (pos == 0)
        return listInsertHead(head, value);
    p = *head;
    for (i = 0; i < pos - 1 && p != NULL; i++)
        p = p->link;
    if (p == NULL)
        return 0;
    q = newNode(value);
    if (q == NULL)
        return 0;
    q->link = p->link;
    p->link = q;
    return 1;
}

/*
 * 功能：删除下标 pos 处的结点
 * 返回：1 成功，0 失败
 *
 * 使用示例：
 *   int x;
 *   listDeleteAt(&list, 0, &x);
 */
int listDeleteAt(struct node **head, int pos, int *out)
{
    struct node *p, *q;
    int i;

    if (*head == NULL || pos < 0)
        return 0;
    if (pos == 0) {
        q = *head;
        if (out != NULL)
            *out = q->n;
        *head = q->link;
        free(q);
        return 1;
    }
    p = *head;
    for (i = 0; i < pos - 1 && p->link != NULL; i++)
        p = p->link;
    if (p->link == NULL)
        return 0;
    q = p->link;
    if (out != NULL)
        *out = q->n;
    p->link = q->link;
    free(q);
    return 1;
}

/* ========== 单链表：按值查找与删除 ========== */

/*
 * 功能：查找值 value 第一次出现的下标
 * 返回：1 找到，0 未找到
 *
 * 使用示例：
 *   int idx;
 *   if (listFind(list, 10, &idx)) printf("在下标 %d\n", idx);
 */
int listFind(const struct node *head, int value, int *index)
{
    const struct node *p = head;
    int i = 0;

    while (p != NULL) {
        if (p->n == value) {
            if (index != NULL)
                *index = i;
            return 1;
        }
        p = p->link;
        i++;
    }
    return 0;
}

/*
 * 功能：删除第一个值为 value 的结点
 * 返回：1 成功，0 失败（未找到）
 *
 * 使用示例：
 *   listDeleteValue(&list, 10);
 */
int listDeleteValue(struct node **head, int value)
{
    struct node *p, *q;

    if (*head == NULL)
        return 0;
    if ((*head)->n == value) {
        q = *head;
        *head = q->link;
        free(q);
        return 1;
    }
    p = *head;
    while (p->link != NULL && p->link->n != value)
        p = p->link;
    if (p->link == NULL)
        return 0;
    q = p->link;
    p->link = q->link;
    free(q);
    return 1;
}

/*
 * 功能：读取下标 pos 处结点的值
 * 返回：1 成功，0 失败
 *
 * 使用示例：
 *   int x;
 *   listGetAt(list, 2, &x);
 */
int listGetAt(const struct node *head, int pos, int *out)
{
    const struct node *p = head;
    int i;

    if (out == NULL)
        return 0;
    for (i = 0; i < pos && p != NULL; i++)
        p = p->link;
    if (p == NULL)
        return 0;
    *out = p->n;
    return 1;
}

/* ========== 单链表：遍历与反序 ========== */

/*
 * 功能：按顺序打印链表所有元素（调试用）
 * 返回：无
 *
 * 使用示例：
 *   listPrint(list);   // 输出：10 20 30
 */
void listPrint(const struct node *head)
{
    const struct node *p = head;
    int first = 1;

    while (p != NULL) {
        if (!first)
            printf(" ");
        printf("%d", p->n);
        first = 0;
        p = p->link;
    }
    printf("\n");
}

/*
 * 功能：原地反转链表（头插法思路）
 * 返回：无
 *
 * 使用示例：
 *   listReverse(&list);   // 实现反序输出效果
 */
void listReverse(struct node **head)
{
    struct node *new_head = NULL;
    struct node *p, *q;

    p = *head;
    while (p != NULL) {
        q = p->link;
        p->link = new_head;
        new_head = p;
        p = q;
    }
    *head = new_head;
}

/* ========== 单链表：销毁 ========== */

/*
 * 功能：释放整条链表，头指针置 NULL
 * 返回：无
 *
 * 使用示例：
 *   listDestroy(&list);
 */
void listDestroy(struct node **head)
{
    struct node *p, *q;

    p = *head;
    while (p != NULL) {
        q = p->link;
        free(p);
        p = q;
    }
    *head = NULL;
}

/* ========== Part B：双链表 ========== */

struct dnode {
    int n;
    struct dnode *prior;
    struct dnode *link;
};

struct dnode *dnewNode(int value)
{
    struct dnode *p = (struct dnode *)malloc(sizeof(struct dnode));
    if (p == NULL)
        return NULL;
    p->n = value;
    p->prior = NULL;
    p->link = NULL;
    return p;
}

void dinitList(struct dnode **head)
{
    *head = NULL;
}

int dlistIsEmpty(const struct dnode *head)
{
    return head == NULL;
}

int dlistLength(const struct dnode *head)
{
    int len = 0;
    const struct dnode *p = head;

    while (p != NULL) {
        len++;
        p = p->link;
    }
    return len;
}

int dlistInsertHead(struct dnode **head, int value)
{
    struct dnode *q = dnewNode(value);
    if (q == NULL)
        return 0;
    q->link = *head;
    if (*head != NULL)
        (*head)->prior = q;
    *head = q;
    return 1;
}

int dlistInsertTail(struct dnode **head, int value)
{
    struct dnode *p, *q = dnewNode(value);
    if (q == NULL)
        return 0;
    if (*head == NULL) {
        *head = q;
        return 1;
    }
    p = *head;
    while (p->link != NULL)
        p = p->link;
    p->link = q;
    q->prior = p;
    return 1;
}

int dlistInsertTailFast(struct dnode **head, struct dnode **tail, int value)
{
    struct dnode *q = dnewNode(value);
    if (q == NULL)
        return 0;
    if (*head == NULL) {
        *head = *tail = q;
    } else {
        q->prior = *tail;
        (*tail)->link = q;
        *tail = q;
    }
    return 1;
}

int dlistDeleteNode(struct dnode **head, struct dnode *target, int *out);

int dlistInsertAt(struct dnode **head, int pos, int value)
{
    struct dnode *p, *q;
    int i;

    if (pos < 0)
        return 0;
    if (pos == 0)
        return dlistInsertHead(head, value);
    p = *head;
    for (i = 0; i < pos - 1 && p != NULL; i++)
        p = p->link;
    if (p == NULL)
        return 0;
    q = dnewNode(value);
    if (q == NULL)
        return 0;
    q->link = p->link;
    q->prior = p;
    if (p->link != NULL)
        p->link->prior = q;
    p->link = q;
    return 1;
}

int dlistDeleteAt(struct dnode **head, int pos, int *out)
{
    struct dnode *q;
    int i;

    if (*head == NULL || pos < 0)
        return 0;
    if (pos == 0) {
        q = *head;
        if (out != NULL)
            *out = q->n;
        *head = q->link;
        if (*head != NULL)
            (*head)->prior = NULL;
        free(q);
        return 1;
    }
    q = *head;
    for (i = 0; i < pos && q != NULL; i++)
        q = q->link;
    if (q == NULL)
        return 0;
    return dlistDeleteNode(head, q, out);
}

int dlistDeleteNode(struct dnode **head, struct dnode *target, int *out)
{
    if (*head == NULL || target == NULL)
        return 0;
    if (out != NULL)
        *out = target->n;
    if (target->prior != NULL)
        target->prior->link = target->link;
    else
        *head = target->link;
    if (target->link != NULL)
        target->link->prior = target->prior;
    free(target);
    return 1;
}

int dlistGetAt(const struct dnode *head, int pos, int *out)
{
    const struct dnode *p = head;
    int i;

    for (i = 0; i < pos && p != NULL; i++)
        p = p->link;
    if (p == NULL)
        return 0;
    if (out != NULL)
        *out = p->n;
    return 1;
}

int dlistFind(const struct dnode *head, int value, int *index)
{
    const struct dnode *p = head;
    int i = 0;

    while (p != NULL) {
        if (p->n == value) {
            if (index != NULL)
                *index = i;
            return 1;
        }
        p = p->link;
        i++;
    }
    return 0;
}

void dlistPrint(const struct dnode *head)
{
    const struct dnode *p = head;

    while (p != NULL) {
        printf("%d ", p->n);
        p = p->link;
    }
    printf("\n");
}

void dlistDestroy(struct dnode **head)
{
    struct dnode *p, *q;

    p = *head;
    while (p != NULL) {
        q = p->link;
        free(p);
        p = q;
    }
    *head = NULL;
}
