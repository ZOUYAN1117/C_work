#include<stdio.h>
int main()
{
	int b;
	while(scanf("%d",&b)!=EOF)
	{
		char a=b;
		if((a>='A'&&a<='Z')||(a>='a'&&a<='z')||(a>='0'&&a<='9'))
		{
			printf("Lingliang likes %c!\n",a);
		}
		else printf("Ewww\n");
	}
    return 0;
}
