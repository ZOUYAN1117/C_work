#include<stdio.h>
int main()
{
	long long c,t,y,m,d,x,w;
	while(scanf("%lld %lld",&t,&x)!=EOF)
	{
		y=t%10000;
		m=(t/10000)/100;
		d=(t/10000)%100;
		if(m<3)
		{
			y--;
			m+=12;
		}
		c=y/100;
		y=y%100;
		w=(c/4-2*c+y+y/4+(26*(m+1))/10+d-1)%7; 
		if(w < 0) 
		w+=7;
		w+=x;
		w%=7;
		switch (w)
		{
			case 0: printf("Sunday\n");
			break;
			case 1: printf("Monday\n");
			break;
			case 2: printf("Tuesday\n");
			break;
			case 3: printf("Wednesday\n");
			break;
			case 4: printf("Thursday\n");
			break;
			case 5: printf("Friday\n");
			break;
			case 6: printf("Saturday\n");
			break;
		}
	}
}
