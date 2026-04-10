#include <stdio.h>
#include <stdlib.h>
struct node
{
    int base, power;
    struct node *link;
};
int main()
{
    int base, power;
    struct node *list = NULL, *tail = NULL, *p, *list1 = NULL, *tail1 = NULL, *list2 = NULL;
    char c;
    // 第一条链
    while (1)
    {
        scanf("%d%d%c", &base, &power, &c);
        p = (struct node *)malloc(sizeof(struct node));
        p->power = power;
        p->base = base;
        p->link = NULL;
        if (list == NULL)
            list = tail = p;
        else
        {
            tail->link = p;
            tail = p;
        }
        if (c == '\n')
            break;
    }
    // 第二条链
    while (scanf("%d%d", &base, &power) == 2)
    {
        p = (struct node *)malloc(sizeof(struct node));
        p->power = power;
        p->base = base;
        p->link = NULL;
        if (list1 == NULL)
            list1 = tail1 = p;
        else
        {
            tail1->link = p;
            tail1 = p;
        }
    }
    // 相乘之后插入
    struct node *pa, *pb;
    for (pa = list; pa != NULL; pa = pa->link)
    {
        for (pb = list1; pb != NULL; pb = pb->link)
        {
            int nb = pa->base * pb->base;
            int np = pa->power + pb->power;
            // 从大到小插入
            p = (struct node *)malloc(sizeof(struct node));
            p->power = np;
            p->base = nb;
            p->link = NULL;
            if (list2 == NULL)
            {
                list2 = p;
                continue;
            }
            struct node *t = list2;
            while (t != NULL)
            {
                if (t->power < p->power)
                {
                    p->link = t;
                    break;
                }
                if (t->link == NULL)
                {
                    p->link = t->link;
                    t->link = p;
                    break;
                }
                if (t->link->power < p->power)
                {
                    p->link = t->link;
                    t->link = p;
                    break;
                }
                if (t->link->power == p->power)
                {
                    t->link->base += p->base;
                    break;
                }
                t = t->link;
            }
        }
    }
    p = list2;
    while (p != NULL)
    {
        printf("%d %d ", p->base, p->power);
        p = p->link;
    }
    return 0;
}
