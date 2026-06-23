#include <stdio.h>
#include <string.h>
char str[200];
int main()
{
    fgets(str, 200, stdin);
    int point = 0, num = -1, j = 0;
    for (int i = 0; i < strlen(str) - 1; i++)
    {
        if (num == -1 && str[i] != '.' && str[i] != '0')
        {
            num = i;
            str[j++] = str[i];
        }
        else if (str[i] == '.')
            point = i;
        else if (num != -1)
            str[j++] = str[i];
    }
    str[j] = '\0';
    if (point > num)
        printf("%c.%se%d", str[0], str + 1, point - num - 1);
    else if (strlen(str) == 1)
        printf("%ce%d", str[0], point - num);
    else
        printf("%c.%se%d", str[0], str + 1, point - num);
    return 0;
}
