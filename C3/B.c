#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
	{
		int sum=0,a=i;
		while(a!=0)
		{
			if(a%2==1) sum++;
			a/=2;
		}
		printf("%d ",sum);
	}
	return 0;
}
