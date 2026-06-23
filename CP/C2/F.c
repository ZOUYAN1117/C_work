#include<stdio.h>
int main()
{
    char c; 
    while(scanf("%c", &c) != EOF)
    {
        if(c<='z'&&c>='a')
        printf("%c",'Z'+'a'-c);
        else if(c<='Z'&&c>='A')
        printf("%c",'z'+'A'-c);
        else printf("%c",c);
    }
    return 0;
}
