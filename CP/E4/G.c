#include<stdio.h>
int main()
{
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		long long n,k,a,t=1;
		long long s=1;
		int flag=1;
		scanf("%lld %lld",&n,&k);
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&a);
			if(a<0)
			{
				t*=-1;
			}
			if(a==0)
			{
				s=0;
				for(int x=j+1;x<=n;x++) 
				scanf("%lld",&a);
				break;
			}
			if(flag)
			{
				if(a<0) a=-a;
				s*=a;
				if(s>=1000000000)
				{
					s=1000000000;
					flag=0;
				}
			}
		}
		s*=t;
		if(s<k) printf("<\n");
        else if(s==k) printf("=\n");
        else printf(">\n");
	}
}
