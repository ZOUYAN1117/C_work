#include<stdio.h>
int main()
{
	int n;
	double sum=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		if(i%2==0) sum+=1.0/(2*i+1);
		else sum-=1.0/(2*i+1);
	}
	sum*=4;
	printf("%.9f",sum);
}
