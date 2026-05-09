#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char word[200];

int istype(char a)
{
    if (isalpha(a))
    {
        return 1;
    }
    else if (a >= '0' && a <= '9')
    {
        return 2;
    }
    else
        return 0;
}

int main()
{
    int c, flag = 0, end = 0;
    while ((c = getchar()) != EOF)
    {
        flag = istype(c);
        if (flag) // 1/2
        {
            if (istype(word[end]) == '\0')
            {
                word[end] = c;
                continue;
            }
            if (flag == istype(word[end]))
            {
                end++;
                word[end] = c;
            }
            else
            {
                for (int i = end; i >= 0; i--)
                    printf("%c", word[i]);
                end = 0;
                word[0] = c;
            }
        }
        else
        { // 为0直接输出
            if (word[0] != '\0')
            {
                for (int i = end; i >= 0; i--)
                    printf("%c", word[i]);
                end = 0;
                word[0] = '\0';
            }
            printf("%c", c);
        }
    }
}
