#include<stdio.h>
int main()
{
	int n,y,m,d,h,mi;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d.%d.%d %d:%d",&y,&m,&d,&h,&mi);
		h+=mi/60;
        mi%=60;
		d+=h/24;
        h%=24;
		while(1)
		{
			int j=0;
			if(m>12)
			{
				y+=(m-1)/12;
				m-=(m-1)/12*12;
			}
			if(m == 2)
            {
            	int p;
            	if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
            	p=29;
            	else p=28;
                if(d>p)
                {
                    d-=p;
                    m++;
                    j++;
                }
            }
			else if((m==1||m==3||m==5||m==7||m==8||m==10||m==12)&&d>31)
			{
				d-=31;
				m++;
				j++;
			}
			else if((m==4||m==6||m==9||m==11)&&d>30)
			{
				d-=30;
				m++;
				j++;
			}
			if(j==0) break;
		}
		if(y>=10000)
		printf("%05d.%02d.%02d %02d:%02d\n",y,m,d,h,mi);
		else printf("%04d.%02d.%02d %02d:%02d\n",y,m,d,h,mi);
	}
	return 0;
}
