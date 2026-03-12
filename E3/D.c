#include<stdio.h>
long long n[7500001]={1,1};
int main()
{
	int T;
	for(int i=1;i<=7500000;i++)
	n[i]=(n[i-1]*i)%998244353;
	scanf("%lld",&T);
	for(int i=1;i<=T;i++)
	{
		long long m;
		scanf("%lld",&m);
		printf("%lld\n",n[m]);
	}
	return 0;
}
