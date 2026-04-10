#include <stdio.h>
#include <stdlib.h>
struct node
{
    int x, y;
    struct node *link;
};
int main()
{
    int n, t = 0, num[100] = {0};
    struct node *list[100] = {NULL}, *tail[100] = {NULL};
    scanf("%d", &n);
    while (n-- > 0)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        list[t] = (struct node *)malloc(sizeof(struct node));
        tail[t] = (struct node *)malloc(sizeof(struct node));
        list[t]->link = tail[t];
        tail[t]->link = NULL;
        list[t]->x = x1;
        list[t]->y = y1;
        tail[t]->x = x2;
        tail[t]->y = y2;

        for (int i = 0; i < t; i++)
        {
            if ((list[t]->x == tail[i]->x) && (list[t]->y == tail[i]->y))
            {
                tail[i]->link = list[t]->link;
                tail[i] = list[t];
            }
            if (tail[t]->x == list[i]->x && tail[t]->y == list[i]->y)
            {
                tail[t]->link = list[i]->link;
                tail[t] = list[i];
            }
        }
        t++;
    }
    for (int i = 0; i < t; i++)
    {
        struct node *p = list[i];
        while (p->link != NULL)
        {
            p = p->link;
            num[i]++;
        }
        num[i]++;
    }
    int max = 0;
    for (int i = 0; i < t; i++)
    {
        if (num[max] < num[i])
            max = i;
    }
    printf("%d %d %d", num[max] - 1, list[max]->x, list[max]->y);
    return 0;
}
