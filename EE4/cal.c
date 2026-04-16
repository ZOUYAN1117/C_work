#include <stdio.h>
#include <stdlib.h>
float numstack[100];
int numtop = -1;
char opstack[100];
int optop = -1;
void pushnum(float x)
{
    if (numtop == 99)
    {
        printf("error\n");
        return;
    }
    numstack[++numtop] = x;
}
void pushop(char c)
{
    if (optop == 99)
    {
        printf("error\n");
        return;
    }
    opstack[++optop] = c;
}
float popnum()
{
    if (numtop == -1)
    {
        printf("error\n");
        return 0;
    }
    return numstack[numtop--];
}
char popop()
{
    if (optop == -1)
    {
        printf("error\n");
        return 0;
    }
    return opstack[optop--];
}
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}
float calculate(float a, float b, char op)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b;
    return 0;
}
int main()
{
    int op, x;
    int c;
    while ((c = getchar()) != EOF)
    {
        if (c >= '0' && c <= '9')
        {
            ungetc(c, stdin);
            scanf("%d", &x);
            pushnum(x);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            while (optop != -1 && precedence(opstack[optop]) >= precedence(c))
            {
                op = popop();
                float b = popnum();
                float a = popnum();
                pushnum(calculate(a, b, op));
            }
            pushop(c);
        }
        else if (c == ' ')
        {
            continue;
        }
        else if (c == '(')
        {
            pushop(c);
        }
        else if (c == ')')
        {
            while (optop != -1 && opstack[optop] != '(')
            {
                op = popop();
                float b = popnum();
                float a = popnum();
                pushnum(calculate(a, b, op));
            }
            popop();
        }
        else if (c == '=')
        {
            while (optop != -1)
            {
                op = popop();
                float b = popnum();
                float a = popnum();
                pushnum(calculate(a, b, op));
            }
            printf("%.2f\n", popnum());
            return 0;
        }
    }
}
