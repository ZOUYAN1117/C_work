#include <stdio.h>
#include <string.h>
typedef struct book
{
    char name[51];
    char author[21];
    char publisher[31];
    char date[11];
} Book;
void findBook(Book books[], int sum, char str[], int index[])
{
    int m = 0;
    for (int i = 0; i < sum; i++)
        for (int j = 0; j < (int)strlen(books[i].name) - (int)strlen(str) + 1; j++)
            if (strncmp(books[i].name + j, str, strlen(str)) == 0)
            {
                index[m++] = i;
                break;
            }
    if (m == 0)
        index[0] = -1;
    return;
}
int main()
{
    FILE *in, *out;
    in = fopen("books.txt", "r");
    out = fopen("ordered.txt", "w");
    Book books[500], temp;
    int sum = 0;
    while (fscanf(in, "%s %s %s %s", books[sum].name, books[sum].author, books[sum].publisher, books[sum].date) != EOF)
    {
        sum++;
    }
    for (int i = 0; i < sum; i++)
        for (int j = 0; j < sum - 1 - i; j++)
        {
            if (strcmp(books[j].name, books[j + 1].name) > 0)
            {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    int op = 0;
    while (1)
    {
        scanf("%d", &op);
        if (op == 0)
            break;
        else if (op == 1)
        {
            scanf("%s %s %s %s", books[sum].name, books[sum].author, books[sum].publisher, books[sum].date);
            sum++;
            for (int i = sum - 1; i > 0; i--)
                if (strcmp(books[i - 1].name, books[i].name) > 0)
                {
                    temp = books[i - 1];
                    books[i - 1] = books[i];
                    books[i] = temp;
                }
                else
                    break;
        }
        else if (op == 2)
        {
            char str[50];
            scanf("%s", str);
            int index[500] = {0};
            findBook(books, sum, str, index);
            if (index[0] != -1)
            {
                printf("%-50s%-20s%-30s%-10s\n", books[index[0]].name, books[index[0]].author, books[index[0]].publisher, books[index[0]].date);
                for (int k = 1; index[k] != 0; k++)
                    printf("%-50s%-20s%-30s%-10s\n", books[index[k]].name, books[index[k]].author, books[index[k]].publisher, books[index[k]].date);
            }
        }
        else if (op == 3)
        {
            char str[50];
            scanf("%s", str);
            int index[500] = {0};
            findBook(books, sum, str, index);
            if (index[0] != -1)
            {
                for (int i = index[0]; i < sum - 1; i++)
                    books[i] = books[i + 1];
                sum--;
                for (int k = 1; index[k] != 0; k++)
                {
                    for (int i = index[k] - k; i < sum - 1; i++)
                        books[i] = books[i + 1];
                    sum--;
                }
            }
        }
        op = 0;
    }
    for (int i = 0; i < sum; i++)
        fprintf(out, "%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].publisher, books[i].date);
    fclose(in);
    fclose(out);
    return 0;
}
