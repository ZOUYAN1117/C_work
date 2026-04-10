#include <stdio.h>
#include <stdlib.h>
struct code
{
    int space, memery;
    struct code *link;
};
int main()
{
    int n = 0;
    scanf("%d", &n);
    struct code *list = NULL, *tail = NULL, *p;
    for (int i = 0; i < n; i++)
    {
        p = (struct code *)malloc(sizeof(struct code));
        scanf("%d%d", &p->space, &p->memery);
        p->link = NULL;
        if (list == NULL)
        {
            list = p;
            tail = p;
        }
        else
        {
            tail->link = p;
            tail = p;
        }
    }
    tail->link = list;
    scanf("%d", &n);
    while (n != -1)
    {
        int num = -1;
        p = list;
        while (1)
        {
            if (n == list->memery)
            {
                // printf("%d %d\n", list->space, list->memery);
                if (list == tail)
                    return 0;
                tail->link = list->link;
                list = list->link;
                p = list;
                break;
            }
            else if (n < list->memery)
            {
                if (num > list->memery - n || num == -1)
                    num = list->memery - n;
            }
            if (list->link == p)
            {
                if (num == -1)
                {
                    list = list->link;
                    tail = tail->link;
                    break;
                }
                else
                {
                    list = list->link;
                    tail = tail->link;
                    while (list->memery != n + num)
                    {
                        list = list->link;
                        tail = tail->link;
                    }
                    // printf("%d %d\n", list->space, n);
                    list->memery = num;
                    p = list;
                    break;
                }
            }
            list = list->link;
            tail = tail->link;
        }
        scanf("%d", &n);
    }
    p = list;
    while (p->link != list)
    {
        printf("%d %d\n", p->space, p->memery);
        p = p->link;
    }
    printf("%d %d\n", p->space, p->memery);
    return 0;
}
