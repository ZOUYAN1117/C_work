#include<stdio.h>
int main()
{
	long long T,n,a,d;
	scanf("%lld",&T);
	for(int i=1;i<=T;i++)
	{
		scanf("%lld%lld%lld",&n,&a,&d);
		if(d==0) 
		{
			printf("%lld\n",a);
			continue;
		}
		long long t;
		while(d!=0)
		{
			t=a%d;
			a=d;
			d=t;
		}
		printf("%lld\n",a);
	}
}
