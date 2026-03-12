#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		unsigned int a,sum=0;
		scanf("%u",&a);
		for(int j=0;j<=31;j++)
		{
			unsigned int b=a;
			b=((b >> (j)) & 1);
			sum+=(b << (31-j));
		}
		printf("%u\n",sum);
	}
	return 0;
}
