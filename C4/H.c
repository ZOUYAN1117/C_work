#include<stdio.h>
int a[20]={0};
int main()
{
	long long n;
	while(scanf("%lld",&n)!=EOF)
	{
		int i=1;
		for(int j=1;j<=20;j++) a[j] = 0;
		while(n!=0)
		{
			a[i]=n%9;
			n/=9;
			i++;
		}
		int flag=0;
		for(int i=20;i>=1;i--)
		{
			if(a[i]>0||flag==1)
			{
				flag=1;
				if(a[i]>=5) printf("%d",a[i]+1);
				else printf("%d",a[i]);
			}
		}
		printf("\n");
	}
}
