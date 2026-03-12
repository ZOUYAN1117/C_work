#include<stdio.h>
#include <math.h>
#define eps 1e-9
int main()
{
	double a,b,c,d;
	scanf("%lf %lf %lf",&a,&b,&c);
	d=b*b-4*a*c;
	if(fabs(a-0)<=eps&&fabs(b-0)>eps) printf("Just one root: %.2f",-c/b);
	else if(fabs(a-0)<=eps&&fabs(b-0)<=eps&&fabs(c-0)<=eps) printf("Infroots");
	else if(fabs(a-0)<=eps&&fabs(b-0)<=eps&&fabs(c-0)>eps) printf("No Root");
	else if(fabs(d-0)<=eps) printf("The same two roots: %.2f",-b /2/a);
	else if(d>0) 
	{
		if((-b+sqrt(d))/2/a>(-b-sqrt(d))/2/a) printf("%.2f %.2f",(-b+sqrt(d))/2/a,(-b-sqrt(d))/2/a);
		else printf("%.2f %.2f",(-b-sqrt(d))/2/a,(-b+sqrt(d))/2/a);
	}
	else printf("No Root");
	return 0;
}
