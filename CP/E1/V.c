#include<stdio.h>
int main()
{
	int x0,y0,vx,vy,t;
	scanf("%d %d",&x0,&y0);
	scanf("%d %d",&vx,&vy);
	scanf("%d",&t);
	printf("%d %d",x0+vx*t,y0+vy*t);
	return 0;
}
