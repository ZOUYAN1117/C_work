#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[5];
    int cnt, price;
} Dish;

int cmp2(const void *p, const void *q)
{
    const Dish *a = (const Dish *)p;
    const Dish *b = (const Dish *)q;
    if (a->cnt * a->price < b->cnt * b->price)
        return -1;
    if (a->cnt * a->price > b->cnt * b->price)
        return 1;
    if (a->cnt < b->cnt)
        return -1;
    if (a->cnt > b->cnt)
        return 1;
    return 0;
}

int main()
{
    Dish dish[100];
    int n, t = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int place;
        Dish temp;
        scanf("%d %s %d %d", &place, temp.name, &temp.cnt, &temp.price);
        int flag = 0;
        for (int j = 0; j < t; j++)
        {
            if (strcmp(temp.name, dish[j].name) == 0)
            {
                dish[j].cnt += temp.cnt;
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            continue;
        else
        {
            strcpy(dish[t].name, temp.name);
            dish[t].cnt = temp.cnt;
            dish[t].price = temp.price;
            t++;
        }
    }
    qsort(dish, t, sizeof(Dish), cmp2);
    long long sum = 0;
    for (int i = 0; i < t; i++)
    {
        printf("%s %d %d\n", dish[i].name, dish[i].cnt, dish[i].cnt * dish[i].price);
        sum += dish[i].cnt * dish[i].price;
    }
    printf("%lld", sum);
}
