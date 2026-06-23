#include<stdio.h>
unsigned long long a[100001];
int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		int n;
		scanf("%d",&n);
		for(int j=1;j<=n;j++)
		{
			scanf("%llu",&a[i]);
		}
		
	}
	return 0;
}
