#include <stdio.h>
#include <string.h>
#include <ctype.h>
int match(char s[], char t[])
{
    for (int i = 0; t[i] != '\0'; i++)
        if (s[i] == '\0' || tolower((unsigned char)s[i]) != tolower((unsigned char)t[i]))
            return 0;
    return 1;
}
int main()
{
    FILE *in, *out;
    char oldstr[1000], newstr[1000], line[1000];
    scanf("%s", oldstr);
    scanf("%s", newstr);
    int len = strlen(oldstr);
    in = fopen("filein.txt", "r");
    out = fopen("fileout.txt", "w");
    while (fgets(line, 1000, in) != NULL)
    {
        for (int i = 0; line[i] != '\0';)
        {
            if (match(&line[i], oldstr))
            {
                fputs(newstr, out);
                i += len;
            }
            else
            {
                fputc(line[i], out);
                i++;
            }
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
