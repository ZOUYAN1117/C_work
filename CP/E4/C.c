#include<stdio.h>
int a[13]={0,31,0,31,30,31,30,31,31,30,31,30,31};
int main()
{
	long long T;
	scanf("%lld",&T);
	for(int i=1;i<=T;i++)
	{
		int y,m,d,s=0;
		scanf("%d%d%d",&y,&m,&d);
		if((y%4==0&&y%100!=0)||y%400==0) a[2]=29;
		else a[2]=28;
		for(int j=1;j<m;j++)
		s+=a[j];
		s+=d;
		printf("%d\n",s);
	}
}
