/**
 * 文件: 约瑟夫环.c
 * 描述: 约瑟夫环问题的单向循环链表实现模板，仅保留循环链表的节点追加、约瑟夫环定位删除与最后一节点状态判定。
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 结构体: node - 约瑟夫环链表节点结构体
 * 成员：
 * - c: 存储结点的字符型数据
 * - link: 指向下一个链表节点的指针
 */
struct node
{
    char c;
    struct node *link;
};

/**
 * 在单链表尾部追加节点 (供构建初始约瑟夫环链表使用)
 * 参数：
 * - list: 指向链表头节点指针的指针地址
 * - tail: 指向链表尾节点指针的指针地址
 * - data: 写入新节点的字符数据值
 * 返回值：无
 */
void append_node(struct node **list, struct node **tail, char data)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL)
        return;
    p->c = data;
    p->link = NULL;

    if (*list == NULL)
    {
        *list = p;
        *tail = p;
    }
    else
    {
        (*tail)->link = p;
        *tail = p;
    }
}

/**
 * 约瑟夫环节点删除 (在循环链表中向后走 step 步并摘除且释放该节点)
 * 参数：
 * - list: 指向当前节点指针的指针地址 (删除后将向后移动指向下一节点)
 * - tail: 指向当前节点前驱指针的指针地址 (在循环链表中即前一个节点)
 * - step: 待前进跨越的步数 (比如 step 传 1 时，删除当前节点)
 * 返回值：被移除节点的内部字符数据 char
 */
char pop_josephus_node(struct node **list, struct node **tail, int step)
{
    char result_data;

    // 只有一个节点了
    if (*list == (*list)->link)
    {
        result_data = (*list)->c;
        free(*list);
        *list = NULL;
        *tail = NULL;
        return result_data;
    }

    // 走 step - 1 次跨越
    while (--step > 0)
    {
        *list = (*list)->link;
        *tail = (*tail)->link;
    }

    // 摘除当前节点 (*list)
    struct node *temp = *list;
    result_data = temp->c;

    // 前驱节点指向后继节点，修复断链
    (*tail)->link = temp->link;

    // 移动当前节点指针到下一个节点
    *list = temp->link;

    free(temp); // 释放摘除节点的内存

    return result_data;
}

/**
 * 判断循环单链表是否仅剩最后一个节点
 * 参数：
 * - list: 链表当前节点指针
 * 返回值：1 表示只剩最后一个节点，0 表示多于一个节点或为空
 */
int is_last_node(struct node *list)
{
    return (list != NULL && list == list->link);
}

/**
 * 约瑟夫环求解完整调用框架演示 (以输入字符串构建环，每次走 step 步删除为例)
 * 参数：
 * - key: 用于构建环的字符数组
 * - step: 每次跨越的步数
 * 返回值：无
 */
void run_josephus_demo(const char *key, int step)
{
    struct node *list = NULL;
    struct node *tail = NULL;

    // 1. 构建初始链表
    for (int i = 0; key[i] != '\0'; i++)
    {
        append_node(&list, &tail, key[i]);
    }

    // 2. 将链表首尾连接成环
    if (tail != NULL)
    {
        tail->link = list;
    }

    // 3. 循环弹出并打印约瑟夫环节点
    while (list != NULL)
    {
        char deleted_char = pop_josephus_node(&list, &tail, step);
        printf("%c ", deleted_char);
    }
    printf("\n");
}
