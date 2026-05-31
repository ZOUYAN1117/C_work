/*
 * 循环单链表 + 循环双链表
 *
 * Part A：struct node { int n; struct node *link; }，尾结点 link 指向头。
 * Part B：struct cdnode { int n; prior; link; }，首尾相接且 prior 成环。
 *
 * 遍历注意：用 do-while，从 head 出发绕一圈，避免死循环。
 */

#include <stdio.h>
#include <stdlib.h>

/* ========== 循环链表：结点定义 ========== */

struct node {
    int n;
    struct node *link;
};

/* ========== 循环链表：结点创建 ========== */

struct node *clistNewNode(int value)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL)
        return NULL;
    p->n = value;
    p->link = NULL;
    return p;
}

/* ========== 循环链表：初始化 ========== */

/*
 * 功能：初始化空循环链表
 * 参数：head、tail 均置 NULL
 *
 * 使用示例：
 *   struct node *head = NULL, *tail = NULL;
 *   clistMakeEmpty(&head, &tail);
 */
void clistMakeEmpty(struct node **head, struct node **tail)
{
    *head = NULL;
    *tail = NULL;
}

/*
 * 功能：将已有单链表（尾指针 tail 已知）接成循环链表
 *       若 head 为 NULL 则不做任何事
 * 返回：无
 *
 * 使用示例：
 *   // 先用尾插建好单链表 head、tail，再：
 *   clistBuild(&head, &tail);
 */
void clistBuild(struct node **head, struct node **tail)
{
    if (*head != NULL && *tail != NULL)
        (*tail)->link = *head;
}

/* ========== 循环链表：尾插 ========== */

/*
 * 功能：在循环链表尾部插入结点，并自动保持成环
 * 返回：1 成功，0 失败
 *
 * 使用示例：
 *   clistInsertTail(&head, &tail, 10);
 *   clistInsertTail(&head, &tail, 20);
 */
int clistInsertTail(struct node **head, struct node **tail, int value)
{
    struct node *q = clistNewNode(value);
    if (q == NULL)
        return 0;
    if (*head == NULL) {
        *head = q;
        *tail = q;
        q->link = q;          /* 只有一个结点时指向自己 */
    } else {
        q->link = *head;
        (*tail)->link = q;
        *tail = q;
    }
    return 1;
}

/* ========== 循环链表：遍历与长度 ========== */

/*
 * 功能：判断循环链表是否为空
 * 返回：1 空，0 非空
 */
int clistIsEmpty(const struct node *head)
{
    return head == NULL;
}

/*
 * 功能：求循环链表结点个数
 * 返回：结点个数
 *
 * 使用示例：
 *   int len = clistLength(head);
 */
int clistLength(const struct node *head)
{
    const struct node *p;
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

/*
 * 功能：按顺序打印循环链表（从 head 起绕一圈）
 * 返回：无
 *
 * 使用示例：
 *   clistPrint(head);
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

/* ========== 循环链表：删除 ========== */

/*
 * 功能：删除下标 pos 处的结点（pos 从 0 起）
 * 参数：若删后链表为空，*head 与 *tail 均置 NULL
 * 返回：1 成功，0 失败
 *
 * 使用示例：
 *   int x;
 *   clistDeleteAt(&head, &tail, 0, &x);
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

    if (len == 1) {
        if (out != NULL)
            *out = (*head)->n;
        free(*head);
        *head = NULL;
        *tail = NULL;
        return 1;
    }

    if (pos == 0) {
        q = *head;
        if (out != NULL)
            *out = q->n;
        *head = q->link;
        (*tail)->link = *head;
        free(q);
        return 1;
    }

    p = *head;
    for (i = 0; i < pos - 1; i++)
        p = p->link;
    q = p->link;
    if (out != NULL)
        *out = q->n;
    p->link = q->link;
    if (q == *tail)
        *tail = p;
    free(q);
    return 1;
}

/*
 * 功能：删除指定结点指针 target（须确为表中结点）
 * 返回：1 成功，0 失败
 *
 * 使用示例：
 *   clistDeleteNode(&head, &tail, p);
 */
int clistDeleteNode(struct node **head, struct node **tail, struct node *target)
{
    struct node *p;
    int pos = 0, len, i;

    if (*head == NULL || target == NULL)
        return 0;
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

/* ========== 循环链表：销毁 ========== */

/*
 * 功能：先断开环，再释放所有结点
 * 返回：无
 *
 * 使用示例：
 *   clistDestroy(&head, &tail);
 */
void clistDestroy(struct node **head, struct node **tail)
{
    struct node *p, *q;

    if (*head == NULL)
        return;

    if (*head == *tail) {
        free(*head);
        *head = NULL;
        *tail = NULL;
        return;
    }

    (*tail)->link = NULL;     /* 先断环，变单链表 */
    p = *head;
    while (p != NULL) {
        q = p->link;
        free(p);
        p = q;
    }
    *head = NULL;
    *tail = NULL;
}

/* ========== Part B：循环双链表 ========== */

struct cdnode {
    int n;
    struct cdnode *prior;
    struct cdnode *link;
};

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

void cdlistMakeEmpty(struct cdnode **head, struct cdnode **tail)
{
    *head = NULL;
    *tail = NULL;
}

int cdlistInsertTail(struct cdnode **head, struct cdnode **tail, int value)
{
    struct cdnode *q = cdlistNewNode(value);
    if (q == NULL)
        return 0;
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

int cdlistIsEmpty(const struct cdnode *head)
{
    return head == NULL;
}

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

int cdlistDeleteNode(struct cdnode **head, struct cdnode **tail, struct cdnode *target)
{
    if (*head == NULL || target == NULL)
        return 0;
    if (*head == *tail) {
        free(target);
        *head = NULL;
        *tail = NULL;
        return 1;
    }
    target->prior->link = target->link;
    target->link->prior = target->prior;
    if (target == *head)
        *head = target->link;
    if (target == *tail)
        *tail = target->prior;
    free(target);
    return 1;
}

int cdlistDeleteAt(struct cdnode **head, struct cdnode **tail, int pos, int *out)
{
    struct cdnode *p;
    int i, len;

    if (*head == NULL || pos < 0)
        return 0;
    len = cdlistLength(*head);
    if (pos >= len)
        return 0;
    p = *head;
    for (i = 0; i < pos; i++)
        p = p->link;
    if (out != NULL)
        *out = p->n;
    return cdlistDeleteNode(head, tail, p);
}

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
