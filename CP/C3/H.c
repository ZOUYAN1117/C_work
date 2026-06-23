#include<stdio.h>
int main()
{
	unsigned long long a,b,sum=0;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%llu %llu",&a,&b);
		while (a < b)
		{
        a|=a+1;
		}
		printf("%llu\n", a);
	}
	return 0;
}
