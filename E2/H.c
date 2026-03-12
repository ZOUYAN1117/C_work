#include<stdio.h>
int main()
{
	int s=0,n,a[200010],b[200010],m,t=1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		s+=a[i];
	}
	for(int i=n;i>=1;i--)
	{
		if(a[i]==1) 
		{
			b[t]=i;
			t++;
		}
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int p;
		scanf("%d",&p);
		if(p>s) printf("No Way!\n");
		else 
		printf("%d\n",b[p]);
	}
	return 0;
}

