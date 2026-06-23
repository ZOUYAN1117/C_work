#include <stdio.h>
#include <string.h>
char a[100], b[100];
void delete(char *a)
{
    int i = 0, p = 0;
    for (int j = 0; a[j] != '\0'; j++)
    {
        if (a[j] != '0' || p != 0)
        {
            p = 1;
            a[i++] = a[j];
        }
    }
    a[i] = '\0';
}
int main()
{
    scanf("%s", a);
    scanf("%s", b);
    delete(a);
    delete(b);
    long long lena = strlen(a), lenb = strlen(b);
    if (lena < lenb)
    {
        int n = lenb - lena;
        memmove(a + n, a, lena + 1);
        for (int i = 0; i < n; i++)
            a[i] = '0';
        for (int i = strlen(a) - 1; i >= 0; i--)
        {
            if (b[i] < a[i])
            {
                b[i] += 10;
                b[i - 1]--;
            }
            b[i] -= a[i] - '0';
        }
        delete(b);
        printf("-%s", b);
    }
    else if (lena > lenb)
    {
        int n = lena - lenb;
        memmove(b + n, b, lenb + 1);
        for (int i = 0; i < n; i++)
            b[i] = '0';
        for (int i = strlen(a) - 1; i >= 0; i--)
        {
            if (a[i] < b[i])
            {
                a[i] += 10;
                a[i - 1]--;
            }
            a[i] -= b[i] - '0';
        }
        delete(a);
        printf("%s", a);
    }
    else if (strcmp(a, b) < 0)
    {
        int n = lenb - lena;
        memmove(a + n, a, lena + 1);
        for (int i = 0; i < n; i++)
            a[i] = '0';
        for (int i = strlen(a) - 1; i >= 0; i--)
        {
            if (b[i] < a[i])
            {
                b[i] += 10;
                b[i - 1]--;
            }
            b[i] -= a[i] - '0';
        }
        delete(b);
        printf("-%s", b);
    }
    else if (strcmp(a, b) > 0)
    {
        int n = lena - lenb;
        memmove(b + n, b, lenb + 1);
        for (int i = 0; i < n; i++)
            b[i] = '0';
        for (int i = strlen(a) - 1; i >= 0; i--)
        {
            if (a[i] < b[i])
            {
                a[i] += 10;
                a[i - 1]--;
            }
            a[i] -= b[i] - '0';
        }
        delete(a);
        printf("%s", a);
    }
    else
    {
        printf("0");
        return 0;
    }
}
