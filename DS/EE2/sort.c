#include <stdio.h>
#include <string.h>
typedef struct
{
    int num;
    char name[25];
    char phone[12];
} Person;
int main()
{
    int n;
    scanf("%d", &n);
    Person a[100] = {0}, b[100] = {0}, temp = {0};
    int m = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%s %s", a[i].name, a[i].phone);
    }
    for (int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < m; j++)
        {
            if (strcmp(b[j].name, a[i].name) == 0)
            {
                if (strcmp(b[j].phone, a[i].phone) == 0)
                {
                    k = 1;
                    break;
                }
                else
                {
                    b[m].num++;
                }
            }
        }
        if (k)
        {
            continue;
        }
        strcpy(b[m].phone, a[i].phone);
        strcpy(b[m].name, a[i].name);
        m++;
    }
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < m - 1 - i; j++)
        {
            if (strcmp(b[j].name, b[j + 1].name) > 0)
            {
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
            else if (strcmp(b[j].name, b[j + 1].name) == 0)
            {
                if (b[j].num > b[j + 1].num)
                {
                    temp = b[j];
                    b[j] = b[j + 1];
                    b[j + 1] = temp;
                }
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (b[i].num > 0)
        {
            printf("%s_%d %s\n", b[i].name, b[i].num, b[i].phone);
        }
        else
            printf("%s %s\n", b[i].name, b[i].phone);
    }
    return 0;
}
