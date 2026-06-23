#include<stdio.h>
int main()
{
	int n;
	long long a[1001];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=n;i>=2;i--)
	{
		printf("%lld ",a[i]);
	}
	printf("%lld",a[1]);
    return 0;
}
