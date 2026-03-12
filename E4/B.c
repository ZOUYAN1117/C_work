#include<stdio.h>
int main()
{
	int n,k;
	scanf("%d %d",&n,&k);
	for(int i=0;i<n*k;i++)
	{
		for(int j=0;j<n*k;j++)
		{
			if((i%(2*k)<k&&j%(2*k)<k)||(i%(2*k)>=k&&j%(2*k)>=k)) printf("1");
			else printf(" ");
		}
		printf("\n");
	}
}
