#include<stdio.h>
int main()
{
	int a[1001]={0};
	int n,m,t;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&t);
		if(t==1) a[n]=!a[n];
		else a[t-1]=!a[t-1];
		a[t]=!a[t];
		if(t==n) a[1]=!a[1];
		else a[t+1]=!a[t+1];
	}
	for(int i=1;i<=n;i++)
	printf("%d ",a[i]);
	return 0;
}
