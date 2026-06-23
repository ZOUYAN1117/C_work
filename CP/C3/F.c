#include<stdio.h>
unsigned int F[14000001];
int main()
{
	int n,q,a;
	scanf("%d %u %d",&n,&F[0],&q);
	for(int i=1;i<=n;i++)
	{
    	unsigned int x = F[i-1];
   		x ^= x << 13;
    	x ^= x >> 17;
    	x ^= x << 5;
    	F[i] = x;
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&a);
		printf("%u\n",F[a]);
	}
	return 0;
}
