/**
 * 文件: 单链表.c
 * 描述: 单向链表与双向链表的基本操作，包含结点的创建、头尾部插入、指定位置操作、查找、反序及销毁。
 */

#include <stdio.h>
#include <stdlib.h>

/* ==================== Part A：单链表 ==================== */

/**
 * 结构体: node - 单向链表结点结构定义
 * 成员：
 * - n: 存储结点的整型数值
 * - link: 指向下一个链表结点的指针
 */
struct node {
    int n;
    struct node *link;
};

/**
 * 创建一个新的单链表结点
 * 参数：
 * - value: 新结点的整型数值
 * 返回值：指向新结点的指针；分配失败返回 NULL
 */
struct node *newNode(int value)
{
    // 分配新结点内存空间
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL)
        return NULL;
    
    // 初始化数据及链接指针
    p->n = value;
    p->link = NULL;
    return p;
}

/**
 * 初始化空单链表
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * 返回值：无
 */
void initList(struct node **head)
{
    // 头指针初始化置为空
    *head = NULL;
}

/**
 * 判断单链表是否为空
 * 参数：
 * - head: 单链表头结点指针
 * 返回值：1 表示为空，0 表示非空
 */
int listIsEmpty(const struct node *head)
{
    return head == NULL;
}

/**
 * 计算单链表的长度 (节点个数)
 * 参数：
 * - head: 单链表头结点指针
 * 返回值：结点的个数
 */
int listLength(const struct node *head)
{
    int len = 0;
    const struct node *p = head;

    // 循环向后移动指针计数
    while (p != NULL) {
        len++;
        p = p->link;
    }
    return len;
}

/**
 * 在单链表头部插入新的数值 (头插法)
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * - value: 新的元素值
 * 返回值：1 表示插入成功，0 表示失败 (内存不足)
 */
int listInsertHead(struct node **head, int value)
{
    // 创建新节点
    struct node *p = newNode(value);
    if (p == NULL)
        return 0;
    
    // 新结点指向原头结点，并更新头指针
    p->link = *head;
    *head = p;
    return 1;
}

/**
 * 在单链表尾部追加新的数值 (O(n) 时间复杂度，无尾指针时使用)
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * - value: 新的元素值
 * 返回值：1 表示追加成功，0 表示失败
 */
int listInsertTail(struct node **head, int value)
{
    struct node *p, *q;

    // 创建新结点
    q = newNode(value);
    if (q == NULL)
        return 0;
    
    // 如果链表为空，直接将头指针指向该新结点
    if (*head == NULL) {
        *head = q;
        return 1;
    }
    
    // 遍历到链表末尾，并挂载新结点
    p = *head;
    while (p->link != NULL)
        p = p->link;
    p->link = q;
    return 1;
}

/**
 * 在有尾指针维护的单链表尾部追加新数值 (O(1) 时间复杂度)
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * - tail: 指向单链表尾结点指针的指针地址
 * - value: 新的元素值
 * 返回值：1 表示追加成功，0 表示失败
 */
int listInsertTailFast(struct node **head, struct node **tail, int value)
{
    // 创建新结点
    struct node *q = newNode(value);
    if (q == NULL)
        return 0;
    
    // 首次插入，同时更新 head 和 tail；否则在当前 tail 之后挂接新结点并更新 tail
    if (*head == NULL) {
        *head = q;
        *tail = q;
    } else {
        (*tail)->link = q;
        *tail = q;
    }
    return 1;
}

/**
 * 在单链表的指定下标位置 pos 插入新的元素
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * - pos: 插入的目标下标位置 (pos 从 0 开始)
 * - value: 新的元素值
 * 返回值：1 表示插入成功，0 表示失败 (pos越界或内存不足)
 */
int listInsertAt(struct node **head, int pos, int value)
{
    struct node *p, *q;
    int i;

    // 检查越界
    if (pos < 0)
        return 0;
    
    // 若 pos 为 0，等同于头插
    if (pos == 0)
        return listInsertHead(head, value);
    
    // 寻找第 pos-1 个结点
    p = *head;
    for (i = 0; i < pos - 1 && p != NULL; i++)
        p = p->link;
    
    // 未找到前驱节点，即越界
    if (p == NULL)
        return 0;
    
    // 创建新节点并修正指针关系
    q = newNode(value);
    if (q == NULL)
        return 0;
    q->link = p->link;
    p->link = q;
    return 1;
}

/**
 * 删除单链表中指定下标位置 pos 的结点
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * - pos: 待删除结点的下标位置 (pos 从 0 开始)
 * - out: 指针，用于输出被删除结点的值
 * 返回值：1 表示删除成功，0 表示失败 (下标越界)
 */
int listDeleteAt(struct node **head, int pos, int *out)
{
    struct node *p, *q;
    int i;

    // 判空与负数判断
    if (*head == NULL || pos < 0)
        return 0;
    
    // 删除头结点
    if (pos == 0) {
        q = *head;
        if (out != NULL)
            *out = q->n;
        *head = q->link;
        free(q);
        return 1;
    }
    
    // 寻找被删结点的前驱结点
    p = *head;
    for (i = 0; i < pos - 1 && p->link != NULL; i++)
        p = p->link;
    
    // 越界保护
    if (p->link == NULL)
        return 0;
    
    // 摘除结点并释放内存
    q = p->link;
    if (out != NULL)
        *out = q->n;
    p->link = q->link;
    free(q);
    return 1;
}

/**
 * 在单链表中查找指定元素值 value 第一次出现的下标
 * 参数：
 * - head: 单链表头结点指针
 * - value: 待查找的数值
 * - index: 指针，用于返回该元素的下标位置
 * 返回值：1 表示查找成功，0 表示未找到
 */
int listFind(const struct node *head, int value, int *index)
{
    const struct node *p = head;
    int i = 0;

    // 循环遍历查找对应的值
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

/**
 * 删除单链表中第一个数据值等于 value 的结点
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * - value: 待删除的数值
 * 返回值：1 表示删除成功，0 表示失败 (未找到或链表为空)
 */
int listDeleteValue(struct node **head, int value)
{
    struct node *p, *q;

    if (*head == NULL)
        return 0;
    
    // 若头结点就是要删除的目标值
    if ((*head)->n == value) {
        q = *head;
        *head = q->link;
        free(q);
        return 1;
    }
    
    // 寻找对应值的结点的前驱
    p = *head;
    while (p->link != NULL && p->link->n != value)
        p = p->link;
    
    // 未找到该数值
    if (p->link == NULL)
        return 0;
    
    // 摘除并释放该节点
    q = p->link;
    p->link = q->link;
    free(q);
    return 1;
}

/**
 * 获取单链表中指定下标位置 pos 结点的值
 * 参数：
 * - head: 单链表头结点指针
 * - pos: 下标位置 (0-indexed)
 * - out: 指针，用于输出读取到的元素值
 * 返回值：1 表示获取成功，0 表示失败 (下标越界)
 */
int listGetAt(const struct node *head, int pos, int *out)
{
    const struct node *p = head;
    int i;

    if (out == NULL)
        return 0;
    
    // 移位遍历到 pos 结点
    for (i = 0; i < pos && p != NULL; i++)
        p = p->link;
    
    if (p == NULL)
        return 0;
    
    *out = p->n;
    return 1;
}

/**
 * 按顺序打印单链表所有元素 (空格分隔，换行结尾)
 * 参数：
 * - head: 单链表头结点指针
 * 返回值：无
 */
void listPrint(const struct node *head)
{
    const struct node *p = head;
    int first = 1;

    // 顺序循环打印
    while (p != NULL) {
        if (!first)
            printf(" ");
        printf("%d", p->n);
        first = 0;
        p = p->link;
    }
    printf("\n");
}

/**
 * 原地反转单链表 (借助头插法思想实现逆序)
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * 返回值：无
 */
void listReverse(struct node **head)
{
    struct node *new_head = NULL;
    struct node *p, *q;

    p = *head;
    // 顺次摘除节点作为新链表的头部插入
    while (p != NULL) {
        q = p->link;
        p->link = new_head;
        new_head = p;
        p = q;
    }
    *head = new_head;
}

/**
 * 销毁单链表，释放其所有节点内存，头指针置 NULL
 * 参数：
 * - head: 指向单链表头结点指针的指针地址
 * 返回值：无
 */
void listDestroy(struct node **head)
{
    struct node *p, *q;

    p = *head;
    // 依次遍历释放所有结点
    while (p != NULL) {
        q = p->link;
        free(p);
        p = q;
    }
    *head = NULL;
}

/* ==================== Part B：双链表 ==================== */

/**
 * 结构体: dnode - 双向链表结点结构定义
 * 成员：
 * - n: 存储结点的整型数值
 * - prior: 指向前驱结点的指针
 * - link: 指向后继结点的指针
 */
struct dnode {
    int n;
    struct dnode *prior;
    struct dnode *link;
};

/**
 * 创建一个新的双向链表结点
 * 参数：
 * - value: 新结点的整型数值
 * 返回值：新结点指针；内存分配失败返回 NULL
 */
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

/**
 * 初始化空双向链表
 * 参数：
 * - head: 指向双链表头结点指针的指针地址
 * 返回值：无
 */
void dinitList(struct dnode **head)
{
    *head = NULL;
}

/**
 * 判断双向链表是否为空
 * 参数：
 * - head: 双链表头结点指针
 * 返回值：1 为空，0 非空
 */
int dlistIsEmpty(const struct dnode *head)
{
    return head == NULL;
}

/**
 * 求双向链表的长度
 * 参数：
 * - head: 双链表头指针
 * 返回值：节点个数
 */
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

/**
 * 在双向链表头部插入新的数值 (头插法)
 * 参数：
 * - head: 指向双链表头指针的指针地址
 * - value: 新元素值
 * 返回值：1 成功，0 失败 (内存不足)
 */
int dlistInsertHead(struct dnode **head, int value)
{
    struct dnode *q = dnewNode(value);
    if (q == NULL)
        return 0;
    
    // 更新前驱和后继指针关系
    q->link = *head;
    if (*head != NULL)
        (*head)->prior = q;
    *head = q;
    return 1;
}

/**
 * 在双链表表尾追加新的数值 (O(n) 复杂度)
 * 参数：
 * - head: 指向双链表头指针的指针地址
 * - value: 新元素值
 * 返回值：1 成功，0 失败
 */
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
    // 遍历到链表最后一个节点
    while (p->link != NULL)
        p = p->link;
    p->link = q;
    q->prior = p;
    return 1;
}

/**
 * 在有尾指针维护的双向链表表尾追加数值 (O(1) 复杂度)
 * 参数：
 * - head: 指向双链表头指针的指针地址
 * - tail: 指向双链表尾指针的指针地址
 * - value: 新元素值
 * 返回值：1 成功，0 失败
 */
int dlistInsertTailFast(struct dnode **head, struct dnode **tail, int value)
{
    struct dnode *q = dnewNode(value);
    if (q == NULL)
        return 0;
    
    // 空链表初始化，否则在 tail 处双向挂接并更新 tail 指针
    if (*head == NULL) {
        *head = *tail = q;
    } else {
        q->prior = *tail;
        (*tail)->link = q;
        *tail = q;
    }
    return 1;
}

// 声明双向链表特定节点删除函数，供其他函数调用
int dlistDeleteNode(struct dnode **head, struct dnode *target, int *out);

/**
 * 在双链表指定下标位置 pos 插入新数值
 * 参数：
 * - head: 指向头指针的指针地址
 * - pos: 下标位置 (0-indexed)
 * - value: 插入的值
 * 返回值：1 成功，0 失败
 */
int dlistInsertAt(struct dnode **head, int pos, int value)
{
    struct dnode *p, *q;
    int i;

    if (pos < 0)
        return 0;
    if (pos == 0)
        return dlistInsertHead(head, value);
    
    // 寻找第 pos-1 个结点作为插入前驱
    p = *head;
    for (i = 0; i < pos - 1 && p != NULL; i++)
        p = p->link;
    if (p == NULL)
        return 0;
    
    // 重新连接新旧邻居节点的 prior 和 link 指针
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

/**
 * 删除双链表中指定位置 pos 的结点
 * 参数：
 * - head: 指向头指针的指针地址
 * - pos: 待删除下标 (0-indexed)
 * - out: 用于输出删除的节点值
 * 返回值：1 成功，0 失败
 */
int dlistDeleteAt(struct dnode **head, int pos, int *out)
{
    struct dnode *q;
    int i;

    if (*head == NULL || pos < 0)
        return 0;
    
    // 删除头结点
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
    
    // 遍历到目标待删除节点
    q = *head;
    for (i = 0; i < pos && q != NULL; i++)
        q = q->link;
    if (q == NULL)
        return 0;
    return dlistDeleteNode(head, q, out);
}

/**
 * 核心功能：删除双向链表中的特定节点指针 target
 * 参数：
 * - head: 指向头指针的指针地址
 * - target: 待删除的节点指针
 * - out: 用于输出删除节点的值
 * 返回值：1 成功，0 失败
 */
int dlistDeleteNode(struct dnode **head, struct dnode *target, int *out)
{
    if (*head == NULL || target == NULL)
        return 0;
    if (out != NULL)
        *out = target->n;
    
    // 重新链接前后节点，绕过 target
    if (target->prior != NULL)
        target->prior->link = target->link;
    else
        *head = target->link;
    
    if (target->link != NULL)
        target->link->prior = target->prior;
    
    free(target);
    return 1;
}

/**
 * 获取双向链表指定下标 pos 的节点数值
 * 参数：
 * - head: 头节点指针
 * - pos: 查找下标
 * - out: 用于返回节点值
 * 返回值：1 成功，0 失败 (越界)
 */
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

/**
 * 在双链表中查找特定数值 value 第一次出现的下标
 * 参数：
 * - head: 双链表头指针
 * - value: 被寻找的值
 * - index: 指针，用于返回下标
 * 返回值：1 找到，0 未找到
 */
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

/**
 * 打印双向链表的所有元素数值
 * 参数：
 * - head: 双链表头指针
 * 返回值：无
 */
void dlistPrint(const struct dnode *head)
{
    const struct dnode *p = head;

    while (p != NULL) {
        printf("%d ", p->n);
        p = p->link;
    }
    printf("\n");
}

/**
 * 销毁双向链表并释放所有节点内存
 * 参数：
 * - head: 指向头指针的指针地址
 * 返回值：无
 */
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
