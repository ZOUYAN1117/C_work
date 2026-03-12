#include<stdio.h>
int main()
{
	int h,f,t,s,y;
	scanf("%d%d%d",&h,&f,&t);
	if(h<=5)
	{
		y=2000;
		if(f*(1<<(2+h))<2000)
		y=f*(1<<(2+h));
	}
	else if(h==6||h==7) y=3000;
	else if(h==8||h==9||h==10) y=4000;
	else if(h==11||h==12) y=6000;
	else y=8000;
	s=4*y+t;
	printf("%d",s);
}
