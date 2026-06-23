#include<stdio.h>
long long a[1000001],b[1000001];
int main()
{
	scanf("%lld %lld",&a[0],&b[0]);
	for(int i=1;i<=a[0];i++)
	scanf("%lld",&a[i]);
	a[a[0]+1]=a[a[0]];
	for(int j=1;j<=b[0];j++)
	scanf("%lld",&b[j]);
	b[b[0]+1]=b[b[0]];
	int i=1,j=1;
	while(i!=a[0]+1||j!=b[0]+1)
	{
		if(i==a[0]+1)
		{
			printf("%lld ",b[j]);
			j++;
		}
		else if(j==b[0]+1)
		{
			printf("%lld ",a[i]);
			i++;
		}
		else if(a[i]>=b[j])
		{
			printf("%lld ",b[j]);
			j++;
		}
		else
		{
			printf("%lld ",a[i]);
			i++;
		}
	}
}
