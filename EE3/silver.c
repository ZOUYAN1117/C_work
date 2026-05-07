#include <stdio.h>
#include <stdlib.h>
struct node
{
    int m;
    struct node *link;
};
struct node *insert_sorted(struct node *list, int a)
{
    // 1. 创建并初始化新节点
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->m = a;
    p->link = NULL;

    // 2. 如果链表为空，或者新数字比头节点还小（或相等）
    // 那么新节点就应该作为新的头节点
    if (list == NULL || list->m >= a)
    {
        p->link = list;
        return p;
    }

    // 3. 寻找中间或末尾的插入位置
    struct node *q = list;
    // 当下一个节点不为空，且下一个节点的值小于要插入的值时，指针后移
    while (q->link != NULL && q->link->m < a)
    {
        q = q->link;
    }

    // 4. 将新节点插入到找到的节点 q 的后面
    p->link = q->link;
    q->link = p;

    // 头指针没变，返回原来的头
    return list;
}
int main()
{
    struct node *list = NULL;
    int a = 0, sum = 0;
    while (1)
    {
        scanf("%d", &a);
        if (a == 999999)
            break;
        if (a > 0)
        {
            sum += a;
            list = insert_sorted(list, a);
        }
        else if (a < 0)
        {
            a = -a;
            if (a > sum)
                continue;
            sum -= a;
            while (list != NULL && a > 0)
            {
                if (a >= list->m)
                {
                    a -= list->m;
                    // 正确移除节点并释放内存
                    struct node *temp = list;
                    list = list->link;
                    free(temp);
                }
                else
                {
                    // a 不够扣掉整个节点，只扣部分，然后 a 归零
                    list->m -= a;
                    a = 0;
                }
            }
        }
        else
        {
            int t = 0;
            // 只要头部节点存在且小于 10，就累加并移除
            while (list != NULL && list->m < 10)
            {
                t += list->m;
                struct node *temp = list;
                list = list->link;
                free(temp);
            }

            // 如果确实提取到了小于 10 的值（t > 0），才重新把它当成一个完整的红包/数值放回链表
            if (t > 0)
            {
                list = insert_sorted(list, t);
            }
        }
    }
    while (list != NULL)
    {
        printf("%d ", list->m);
        struct node *temp = list;
        list = list->link;
        free(temp);
    }
}
