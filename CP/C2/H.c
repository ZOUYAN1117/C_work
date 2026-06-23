#include<stdio.h>
int main()
{
    long long h,p,q,n,a;
	while(scanf("%lld %lld %lld", &h,&p,&q) != EOF)
	{
		long long sum=0,s=0;
		scanf("%lld", &n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld", &a);
			h+=a;
			sum+=a;
			if(h<=p)
			{
				if(s!=1) s=-1;
			}
			else if(h>=q)
				{
					if(s!=-1) s=1;
				}
		}
		if(sum>0)
		{
			if(s!=-1) s=1;
		}
		else if(sum<0)
		{
			if(s!=1) s=-1;
		}
		if(s==1) printf("up\n");
		else if(s==-1) printf("down\n");
		else  printf("No\n");
	}
    return 0;
}
