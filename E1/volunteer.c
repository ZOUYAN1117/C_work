#include<stdio.h>
int main()
{
	int n,m,s;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&m);
		s=m%1000;
		m/=1000;
		if(m<25372)
		{
			if(s<10) printf("chuanyuan 00%d\n",s);
			else if(s<100) printf("chuanyuan 0%d\n",s);
			else  printf("chuanyuan %d\n",s);
		}
		else
		{
			if(s<10) printf("shie 00%d\n",s);
			else if(s<100) printf("shie 0%d\n",s);
			else  printf("shie %d\n",s);
		}
	}
	return 0;
}
