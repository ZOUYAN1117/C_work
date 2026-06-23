#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct node
{
    int a;
    long long n;
    struct node *link;
};

long long sum;

struct node *delete_node(struct node *list, struct node *p)
{
    // 如果要删除的是头节点 (即第一个节点就是 p)
    if (list == p)
        return list->link; // 返回新的头节点
    // 如果要删除的是中间节点或尾节点，需要找到 p 的前驱节点
    struct node *prev = list;
    while (prev->link != p)
    {
        prev = prev->link;
    }
    // 已经找到了 p 节点（即 prev->link == p），不用验证是否存在
    prev->link = p->link; // 将 p 的前驱节点直接指向 p 的后一个节
    // 返回原来的头节点
    return list;
}

struct node *insert_sorted(struct node *list, int a, long long n)
{
    // 1. 创建并初始化新节点
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->a = a;
    p->n = n;
    p->link = NULL;

    // 2. 如果链表为空，或者新数字比头节点还大
    // 那么新节点就应该作为新的头节点
    if (list == NULL || list->n < n)
    {
        if (list != NULL)
            sum++;
        p->link = list;
        return p;
    }

    if (list->n == n)
    {
        sum++;
        list->a += a;
        if (list->a == 0)
            list = list->link;
        free(p);
        return list;
    }

    // 3. 寻找中间或末尾的插入位置
    struct node *q = list;
    // 当下一个节点不为空，且下一个节点的值小于要插入的值时，指针后移
    while (q->link != NULL && q->link->n >= n)
    {
        q = q->link;
        sum++;
    }
    if (q->n == n)
    {
        sum++;
        q->a += a;
        if (q->a == 0)
            delete_node(list, q);
        free(p);
        return list;
    }
    else
    {
        sum++;
        if (q->link != NULL)
            sum++;
        p->link = q->link;
        q->link = p;
    }
    // 头指针没变，返回原来的头
    return list;
}

int main()
{
    struct node *list = NULL;
    while (1)
    {
        int a;
        long long n;
        scanf("%d %lld", &a, &n);
        if (n == -1)
            break;
        list = insert_sorted(list, a, n); // 插入
    }
    while (list != NULL)
    {
        struct node *temp = list;
        printf("%d %lld\n", list->a, list->n);
        list = list->link;
        free(temp);
    }
    printf("%lld", sum);
}
