#include<stdio.h>
int main()
{
	int n;
    long long a,s=0,m=1,t[200010]={0,1,2};
    const long long p=998244353;
	scanf("%d",&n);
	for(int i=3;i<=n;i++)
	{
		t[i]=t[i-1]*3%p;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a);
		m*=a;
		m%=p;
		s+=m*t[n-i+1];
		s%=p;
	}
	printf("%lld",s);
    return 0;
}
