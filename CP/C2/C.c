#include<stdio.h>
int main()
{
	int n;
	double r,C;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%lf",&r);
		C=2*3.14159265358979*r;
		printf("%.4f\n",C);
	}
    return 0;
}
