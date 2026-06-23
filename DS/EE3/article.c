#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
struct node
{
    char word[30];
    int count;
    struct node *link;
};

int main()
{
    FILE *in;
    char raw[50] = {0}, key[30] = {0};
    struct node *list = NULL, *p;
    int ch = 0, j = 0;
    in = fopen("article.txt", "r");
    while ((ch = fgetc(in)) != EOF)
    {
        if (isalpha((unsigned char)ch))
        {
            raw[j++] = (char)tolower((unsigned char)ch);
            continue;
        }
        raw[j] = '\0';
        j = 0;
        for (int i = 0; raw[i] != '\0'; i++)
        {
            if (isalpha(raw[i]))
            {
                key[j] = tolower(raw[i]);
                j++;
            }
        }
        if (j == 0)
            continue;
        key[j] = '\0';
        if (list == NULL)
        {
            p = (struct node *)malloc(sizeof(struct node));
            strcpy(p->word, key);
            p->count = 1;
            p->link = NULL;
            list = p;
        }
        else
        {
            struct node *q = list;
            while (q != NULL)
            {
                if (strcmp(q->word, key) == 0)
                {
                    q->count++;
                    break;
                }
                q = q->link;
            }
            if (q == NULL)
            {
                q = list;
                while (q != NULL)
                {
                    if (strcmp(key, q->word) < 0)
                    {
                        p = (struct node *)malloc(sizeof(struct node));
                        strcpy(p->word, key);
                        p->link = list;
                        p->count = 1;
                        list = p;
                        break;
                    }
                    if (q->link == NULL)
                    {
                        p = (struct node *)malloc(sizeof(struct node));
                        strcpy(p->word, key);
                        q->link = p;
                        p->count = 1;
                        p->link = NULL;
                        break;
                    }
                    if (strcmp(key, q->link->word) < 0)
                    {
                        p = (struct node *)malloc(sizeof(struct node));
                        strcpy(p->word, key);
                        p->link = q->link;
                        q->link = p;
                        p->count = 1;
                        break;
                    }
                    q = q->link;
                }
            }
        }
        j = 0;
    }
    while (list != NULL)
    {
        printf("%s %d\n", list->word, list->count);
        list = list->link;
    }
    fclose(in);
    return 0;
}
