#include<stdio.h>
int main()
{
	int n,i=0,t=1,a,b;
	scanf("%d",&n);
	while(i!=n)
	{
		a=t%10;
		b=t/10;
		if(a==7) i++;
		else if(b!=0)
		{
			a=b%10;
			b=b/10;
			if(a==7) i++;
			else if(b!=0)
				{
				a=b%10;
				b=b/10;
				if(a==7) i++;
				else if(b!=0)
					{
					a=b%10;
					b=b/10;
					if(a==7) i++;
					}
			}
		}
		t++;
	}
	printf("%d",t-1);
	return 0;
}
