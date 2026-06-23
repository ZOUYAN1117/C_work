#include<stdio.h>
int main()
{
	int a,b,c;
	for(int i=100;i<=999;i++)
	{
		a=i/100;
		b=i/10%10;
		c=i%10;
		int sum=a*a*a+b*b*b+c*c*c;
		if(i%sum==0) printf("%d\n",i);
	}
}
