#include<stdio.h>
int main()
{
	int n,d;
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		scanf("%d",&d);
		if(i==1) printf("M");
		if(d!=0)
		for(int j=1;j<=d;j++) printf("_");
		printf("M");
	}
	return 0;
}
