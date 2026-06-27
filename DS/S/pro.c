#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[25];
    int good, bad, lv;
} Pro;

int cmp2(const void *p, const void *q)
{
    const Pro *a = (const Pro *)p;
    const Pro *b = (const Pro *)q;
    if (a->lv > b->lv)
        return -1;
    if (a->lv < b->lv)
        return 1;
    if (strcmp(a->name, b->name) < 0)
        return -1;
    if (strcmp(a->name, b->name) > 0)
        return 1;
    return 0;
}

int main()
{
    Pro pro[100];
    int n, t = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        Pro temp;
        scanf("%s %d %d", temp.name, &temp.good, &temp.bad);
        int flag = 0;
        for (int j = 0; j < t; j++)
        {
            if (strcmp(temp.name, pro[j].name) == 0)
            {
                pro[j].good += temp.good;
                pro[j].bad += temp.bad;
                pro[j].lv = 100 * pro[j].good / (pro[j].bad + pro[j].good);
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            continue;
        else
        {
            strcpy(pro[t].name, temp.name);
            pro[t].good = temp.good;
            pro[t].bad = temp.bad;
            pro[t].lv = 100 * pro[t].good / (pro[t].bad + pro[t].good);
            t++;
        }
    }
    qsort(pro, t, sizeof(Pro), cmp2);
    for (int i = 0; i < t; i++)
    {
        printf("%s %d %d%%\n", pro[i].name, pro[i].good + pro[i].bad, pro[i].lv);
    }
}
