#include<stdio.h>
int main()
{
	int n,x,a[101],rank=0;
	scanf("%d %d",&n,&x);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(x<a[i]) rank++;
	}
	printf("%d",rank+1);
    return 0;
}
