#include<stdio.h>
#define e 998244353
char a[1000001]={0};
int main()
{
	long long n,i=0,s=0,t=1;
	scanf("%s",&a);
	while(a[i]!='\0')
	{
		i++;
	}
	a[i]='0';
	for(int j=0;j<i;j++)
	{
		if(a[j]>='5'&&a[j]<'9') a[j]++;
		else if(a[j]>='9')
		{
			a[j]='0';
			a[j+1]++;
		}
	}
	for(int j=i-1;j>=0;j--)
	{
		s+=(a[j]-'0')*t;
		s%=e;
		t=t*9%e;
	}
	printf("%lld",s+1);
}
