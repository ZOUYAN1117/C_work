#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char type;
    int date;
    int rank;
    char name[110];
} News;

int cmp2(const void *p, const void *q)
{
    const News *a = (const News *)p;
    const News *b = (const News *)q;
    if (a->type > b->type)
        return -1;
    if (a->type < b->type)
        return 1;
    if (a->date < b->date)
        return -1;
    if (a->date > b->date)
        return 1;
    if (a->rank < b->rank)
        return -1;
    if (a->rank > b->rank)
        return 1;
    return 0;
}

News news[100], temp;

int main()
{
    int t = 0, i = 0;
    while ((temp.type = getchar()) != 'E')
    {
        if (temp.type == 'R')
        {
            qsort(news, t, sizeof(News), cmp2);
            int outn;
            scanf("%d\n", &outn);
            for (int j = t - 1; j >= t - outn; j--)
            {
                printf("%c %d %s\n", news[j].type, news[j].date, news[j].name);
                news[j].type = '\0';
                news[j].date = 0;
                news[j].rank = 0;
                strcpy(news[j].name, "\0");
            }
            t -= outn;
        }
        else
        {
            scanf("%d %s\n", &temp.date, temp.name);
            news[t].type = temp.type;
            news[t].date = temp.date;
            strcpy(news[t].name, temp.name);
            news[t].rank = i;
            t++;
            i++;
        }
    }
    qsort(news, t, sizeof(News), cmp2);
    for (int j = t - 1; j >= 0; j--)
        printf("%c %d %s\n", news[j].type, news[j].date, news[j].name);
}
