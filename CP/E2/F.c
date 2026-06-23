#include<stdio.h>
int main()
{
	int n,q,d,b,e;
	long long a[100010]={0};
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&d);
		a[i]=a[i-1]+d+190;
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d %d",&b,&e);
		printf("%lld\n",a[e]-a[b]);
	}
	return 0;
}
