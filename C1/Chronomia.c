#include<stdio.h>
int main()
{
	long long n,i=1,j=1,s=0,p=998244353,a=0,b=0,a1=0,b1=0;
	scanf("%lld",&n);
	a=(((n%p)*((n+1)%p))%p);
	a=a*a%p;
	b=2*n+1;
	s=(a*b)%p;
	s=(s*7)%p;
	printf("%lld",s);
	return 0;
}
