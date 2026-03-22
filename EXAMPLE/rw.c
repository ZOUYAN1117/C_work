#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    FILE *in, *out;
    char line[1000];
    in = fopen("filein.txt", "r");
    out = fopen("fileout.txt", "w");
    while (fgets(line, 1000, in) != NULL)
    {
    }
    fclose(in);
    fclose(out);
    return 0;
}
