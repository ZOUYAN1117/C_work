#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		unsigned int a;
		scanf("%u",&a);
		for(int j=31;j>=0;j--)
		{
			unsigned int b=a;
			b=((b >> (j)) & 1);
			if(b==1)
			printf("%u ",(1<<j));
		}
		printf("\n");
	}
	return 0;
}
