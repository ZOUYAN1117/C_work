#include<stdio.h>
int main()
{
	unsigned int a,b,s1,s2,s3,s4,s5,s6,n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%u%u",&a,&b);
		s1=~a;
		s2=a&b;
		s3=a|b;
		s4=a^b;
		s5=a<<b;
		s6=a>>b;
		printf("%u %u %u %u %u %u\n",s1,s2,s3,s4,s5,s6);
	}
	return 0;
}
