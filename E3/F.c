#include<stdio.h>
int a[10001]={0};
int main()
{
	int n,t;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		a[t]++;
	}
	for(int i=1;i<=10001;i++)
	if(a[i]!=0)
	printf("%d : %d\n",i,a[i]);
	return 0;
}
