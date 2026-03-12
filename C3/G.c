#include<stdio.h>
int main()
{
	int n,a,s=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		s^=a;
	}
	printf("%d",s);
	return 0;
}
