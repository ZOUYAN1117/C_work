#include<stdio.h>
int main()
{
	int n,d;
	scanf("%d",&n);
	if(n==0)
	printf("0");
	if(n<0)
	{
		printf("-");
		n-=2*n;
	}
	do
	{
		if(n%10!=0)
		printf("%d",n%10);
		n/=10;
	}while(n>=1);
	return 0;
}
