#include<stdio.h>
int main()
{
	int n,a[200001]={0,1,2,3},p=998244353,t;
	scanf("%d",&n);
	for(int i=4;i<=n;i++)
	{
		a[i]=a[i-1]+a[i-2];
		a[i]%=p;
	}
	t=2*(a[n]+a[n-1])%p;
	printf("%d",t);
	return 0;
} 
