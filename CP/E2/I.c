#include<stdio.h>
int main()
{
	int n,q,a[1001],op,x,y;
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=1;i<=q;i++)
	{
		scanf("%d %d %d",&op,&x,&y);
		if(op==1)
		a[x]=a[y];
		else if(op==2)
		{
			int t;
			t=a[x];
			a[x]=a[y];
			a[y]=t;
		}
		else if(op==3)
		a[x]+=y;
		else if(op==4)
		a[x]=y;
		else if(op==5)
		printf("%d\n",a[x]-a[y]);
		else
		{
			long long sum=0;
			for(int j=x;j<=y;j++)
			sum+=a[j];
			printf("%d\n",sum);
		}
	}
	return 0;
} 
