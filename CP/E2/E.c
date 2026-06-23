#include<stdio.h>
int main()
{
	int n,k,a[1000]={0},t;
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&t);
		a[t]=0;
	}
	for(int i=1;i<=n;i++)
	printf("%d ",a[i]);
	return 0;
}
