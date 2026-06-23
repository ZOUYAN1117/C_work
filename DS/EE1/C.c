#include <stdio.h>
int n, a[10], used[11];
void combine(int k)
{
    if (k == n)
    {
        for (int i = 0; i < n; i++)
        {
            if (i > 0)
            {
                printf(" ");
            }
            printf("%d", a[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
        {
            used[i] = 1;
            a[k] = i;
            combine(k + 1);
            used[i] = 0;
        }
    }
}

int main()
{
    scanf("%d", &n);
    combine(0);
    return 0;
}
