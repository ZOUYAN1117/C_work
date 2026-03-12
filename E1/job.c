#include<stdio.h>
int main()
{
	long long n,m;
	scanf("%lld %lld",&n,&m);
	if(m==0) printf("%lld",n);
	else printf("%lld",n%m);
	return 0;
}
