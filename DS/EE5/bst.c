#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tnode
{
    int a, h;
    struct tnode *left, *right;
};
void printLeaves(struct tnode *Root)
{
    if (Root != NULL)
    {
        if (Root->left == NULL && Root->right == NULL)
        {
            printf("%d %d\n", Root->a, Root->h);
        }
        printLeaves(Root->left);
        printLeaves(Root->right);
    }
}
int main()
{
    struct tnode *Root = NULL;
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);
        if (Root == NULL)
        {
            Root = (struct tnode *)malloc(sizeof(struct tnode));
            Root->a = a;
            Root->h = 1;
            Root->left = NULL;
            Root->right = NULL;
        }
        else
        {
            struct tnode *q = Root;
            struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
            p->a = a;
            p->h = 1;
            p->left = NULL;
            p->right = NULL;
            while (q != NULL)
            {
                if (p->a < q->a)
                {
                    if (q->left == NULL)
                    {
                        p->h++;
                        q->left = p;
                        break;
                    }
                    else
                    {
                        q = q->left;
                        p->h++;
                    }
                }
                else
                {
                    if (q->right == NULL)
                    {
                        p->h++;
                        q->right = p;
                        break;
                    }
                    else
                    {
                        q = q->right;
                        p->h++;
                    }
                }
            }
        }
    }
    printLeaves(Root);
}
