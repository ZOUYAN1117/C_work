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
    for (int i = 0, j = 0; raw[i] != '\0'; i++)
    {
        if (a[tolower((unsigned char)raw[i]) - 'a'] == 0)
        {
            key[j] = tolower((unsigned char)raw[i]);
            a[tolower((unsigned char)raw[i]) - 'a'] = 1;
            j++;
        }
    }
    for (char c =)
        in = fopen("filein.txt", "r");
    out = fopen("fileout.txt", "w");
    while (fgets(line, 1000, in) != NULL)
    {
    }
    fclose(in);
    fclose(out);
    return 0;
}
