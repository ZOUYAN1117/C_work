#include <stdio.h>
#include <stdlib.h>
int stack[100], top = -1;
void push(int x)
{
    if (top == 99)
    {
        printf("error ");
        return;
    }
    stack[++top] = x;
}
void pop()
{
    if (top == -1)
    {
        printf("error ");
        return;
    }
    printf("%d ", stack[top]);
    top--;
}
int main()
{
    int op, x;
    while (scanf("%d", &op) != EOF)
    {
        if (op == 1)
        {
            scanf("%d", &x);
            push(x);
        }
        else if (op == 0)
        {

            pop();
        }
        else
            return 0;
    }
}
