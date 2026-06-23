#include<stdio.h>
int main()
{
	unsigned long long p,q,sum;
	while(scanf("%llu %llu",&p,&q)!=EOF)
	{
		sum=p&(~q);
		printf("%llu\n",sum);
	}
	return 0;
}
