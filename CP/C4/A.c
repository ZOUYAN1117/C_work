#include<stdio.h>
#define V1 7900
#define V2 11200
#define V3 16700
int main()
{
	int a,b,c;
	while(scanf("%d%d",&a,&b)!=EOF)
	{
		c=a*b;
		if(c<V1) printf("<1\n");
		else if(c>=V1&&c<V2) printf("1\n");
		else if(c>=V2&&c<V3) printf("2\n");
		else if(c>=V3) printf("3\n");
	}
}
