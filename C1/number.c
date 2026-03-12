#include<stdio.h>
int main()
{
	int n,a,d;
	scanf("%d %d %d",&n,&a,&d);
	for(int i=1;i<=n;i++)
	{
		printf("%d",a+(i-1)*d);
		if(i<=n-1) printf(" ");
	}
	return 0;
}
