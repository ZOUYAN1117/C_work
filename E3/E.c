#include<stdio.h>
#include<math.h>
double a[100001]={1},b[100001]={1};
int main()
{
	int T,n;
	scanf("%d",&T);
	for(int i=1;i<=100000;i++)
	{
		if(i%2==0)
		a[i]=a[i-1]+1.0/(2*i+1);
		else a[i]=a[i-1]-1.0/(2*i+1);
		b[i]=b[i-1]+1.0/(2*i+1.0)/(2*i+1.0);
	}
	for(int i=1;i<=T;i++)
	{
		scanf("%d",&n);
		double sum=0;
		sum=fabs(sqrt(8*b[n-1])-4*a[n-1]);
		printf("%0.6f\n",sum);
	}
	return 0;
}
