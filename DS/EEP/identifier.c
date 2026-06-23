#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main()
{
    char *key[100] = {};
    char word[32];
    int c = '\0', num = 0, t = 0;
    while ((c = getchar()) != '\n')
    {
        if (isalpha(c) || c == '_' || (num > 0 && isdigit(c)))
        {
            word[num++] = c;
        }
        else
        {
            if (num > 0)
            {
                word[num] = '\0';
                key[t] = malloc(num + 1);
                strcpy(key[t], word);
                t++;
                num = 0;
            }
        }
    }
    for (int i = 0; i < t; i++)
        for (int j = i + 1; j < t; j++)
        {
            if (strcmp(key[i], key[j]) == 0)
            {
                free(key[j]);
                for (int k = j; k < t - 1; k++)
                    key[k] = key[k + 1];
                t--;
                j--;
            }
            if (strcmp(key[i], key[j]) > 0)
            {
                char *temp = key[i];
                key[i] = key[j];
                key[j] = temp;
            }
        }
    for (int i = 0; i < t; i++)
    {
        printf("%s\n", key[i]);
        free(key[i]);
    }
    return 0;
}
