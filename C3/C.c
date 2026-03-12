#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		unsigned long long a;
		scanf("%llu",&a);
		for(int j=64;j>=1;j--)
		{
			unsigned long long b=a;
			b=((b >> (j-1)) & 1);
			printf("%llu",b);
			if(j%4==1&&j!=1) printf(" ");
		}
		printf("\n");
	}
	return 0;
}
