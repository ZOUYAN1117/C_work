#include<stdio.h>
int main()
{
	int n,s;
	scanf("%d",&n);
	while(n>=5)
	{
		s+=n/5;
		n=n/5+n%5;
	}
	printf("%d",s);
	return 0;
}
