#include<stdio.h>
int main()
{
	long long a,b,n,u,m;
	int d[100]={0};
	scanf("%lld%lld%lld",&a,&b,&n);
	u=a/b;
	m=a%b;
	for(int i=1;i<=n;i++)
	{
		m*=10;
		d[i]=m/b;
		m=m%b;
	}
	if(m*2>=b) d[n]++;
	for(int i=n;i>=2;i--)
	{
		if(d[i]==10)
		{
			d[i-1]++;
			d[i]-=10;
		}
	}
	if(d[1]==10)
	{
		d[1]-=10;
		u++;
	}
	printf("%lld.",u);
	for(int i=1;i<=n;i++)
	{
		printf("%d",d[i]);
	}
	return 0;
}