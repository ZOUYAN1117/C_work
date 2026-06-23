#include <stdio.h>
#include <string.h>
#define MAXSIZE 1000
#define MAXLEN 20 // 限制每个单词的最大长度
char stack[MAXSIZE][MAXLEN];
char line[MAXSIZE][10][MAXLEN];
int top = -1;
int isEmpty()
{
    return top == -1;
}
void push(char item[])
{
    top++;
    strcpy(stack[top], item);
}
void pop()
{
    if (isEmpty())
        printf("Empty Stack!");
    else
        top--;
}
int main()
{
    char word[20], fuc[400][20];
    int a = 0, t = 0;
    scanf("%d", &a);
    scanf("%s", word);
    strcpy(fuc[t++], word);
    push(word);
    int x = 0;
    while (!isEmpty())
    {
        scanf("%d", &a);
        if (a == 8)
        { // push
            scanf("%s", word);
            strcpy(fuc[t++], word);
            push(word);
        }
        else
        { // pop
            int flag = 0, q = 0;
            for (int i = 0; i < x; i++)
            {
                if (strcmp(line[i][0], stack[top - 1]) == 0)
                {
                    int j = 0;
                    while (line[i][j][0] != '\0')
                    {
                        if (strcmp(line[i][j], stack[top]) == 0)
                        {
                            q = 1;
                            pop();
                            break;
                        }
                        j++;
                    }
                    if (q == 1)
                        break;
                    strcpy(line[i][j], stack[top]);
                    pop();
                    flag = 1;
                }
            }
            if (q == 1)
                continue;
            if (flag == 0)
            {
                strcpy(line[x][0], stack[top - 1]);
                strcpy(line[x][1], stack[top]);
                x++;
                pop();
            }
        }
    }
    int q[100] = {};
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; line[j][0][0] != '\0'; j++)
            if (q[j] == 0 && strcmp(line[j][0], fuc[i]) == 0)
            {
                printf("%s:%s", line[j][0], line[j][1]);
                for (int t = 2; line[j][t][0] != '\0'; t++)
                    printf(",%s", line[j][t]);
                printf("\n");
                q[j] = 1;
                break;
            }
    }
}
