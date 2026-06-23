#include<stdio.h>
int main()
{
	int n,a,l[10001]={0}; 
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		int s=0;
		for(int j=1;j<=n;j++)
		{
			if(l[j]==0) s++;
			if(s==a+1)
			{
				l[j]=i;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)
	printf("%d ",l[i]);
    return 0;
}
