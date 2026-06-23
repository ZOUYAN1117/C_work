#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
struct node
{
    char c;
    struct node *link;
};

int main()
{
    FILE *in, *out;
    char raw[1000] = {0}, key[100] = {0}, line[1000] = {0};
    fgets(raw, 1000, stdin);
    in = fopen("in.txt", "r");
    out = fopen("in_crpyt.txt", "w");
    int j = 0, a[100] = {0};
    for (int i = 0; raw[i] != '\n'; i++)
    {
        if (a[(int)raw[i] - 32] == 0)
        {
            key[j] = raw[i];
            a[(int)raw[i] - 32] = 1;
            j++;
        }
    }
    key[j] = '\0';
    struct node *list = NULL, *tail = NULL, *p;
    for (int i = 0; key[i] != '\0'; i++)
    {
        p = (struct node *)malloc(sizeof(struct node));
        p->c = key[i];
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
    for (char c = 32; c <= 126; c++)
    {
        if (a[c - 32] == 0)
        {
            p = (struct node *)malloc(sizeof(struct node));
            p->c = c;
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
    }
    tail->link = list;
    const char c = list->c;
    int q = list->c;
    tail->link = list->link;
    list = list->link;
    while (list != list->link)
    {
        int n = q;
        while (--n)
        {
            list = list->link;
            tail = tail->link;
        }
        key[q - 32] = list->c;
        q = list->c;
        tail->link = list->link;
        list = list->link;
    }
    key[list->c - 32] = c;
    while (fgets(line, 1000, in) != NULL)
    {
        int i = 0;
        while (line[i] != '\0')
        {
            if (line[i] >= 32 && line[i] <= 126)
                fputc(key[line[i] - 32], out);
            else
                fputc(line[i], out);
            i++;
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
