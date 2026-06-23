#include<stdio.h>
long long a[21]={1};
int main()
{
	for(int i=1;i<=20;i++)
	{
		a[i]=a[i-1]*i;
	}
	int N,M,n;
	scanf("%d %d %d",&N,&M,&n);
	for(int i=0;i<=n;i++)
	{
		double s=0.0;
		if(i>M||N-M-n+i<0||n<i) 
		{
			printf("%.4lf ",s);
			continue;
		}
		else
		{
			s=1.0*a[M]/a[N]*a[N-M]/a[i]*a[n]/a[M-i]*a[N-n]/a[n-i]/a[N-M-n+i];
			printf("%.4lf ",s);
		}
	}
}
