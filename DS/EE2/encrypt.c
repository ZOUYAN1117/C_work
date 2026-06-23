#include <stdio.h>
#include <string.h>
#include <ctype.h>
int a[26];
char raw[60], key[26];
int main()
{
    FILE *in, *out;
    char line[1000];
    scanf("%s", raw);
    int j = 0;
    for (int i = 0; raw[i] != '\0'; i++)
    {
        if (a[(int)raw[i] - 'a'] == 0)
        {
            key[j] = raw[i];
            a[(int)raw[i] - 'a'] = 1;
            j++;
        }
    }
    for (char c = 'z'; c >= 'a'; c--)
    {
        if (a[c - 'a'] == 0)
        {
            key[j] = c;
            j++;
        }
    }
    in = fopen("encrypt.txt", "r");
    out = fopen("output.txt", "w");
    while (fgets(line, 1000, in) != NULL)
    {
        int i = 0;
        while (line[i] != '\0')
        {
            if (isalpha(line[i]))
                fputc(key[line[i] - 'a'], out);
            else
                fputc(line[i], out);
            i++;
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
