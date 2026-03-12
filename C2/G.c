#include<stdio.h>
int main()
{
    int n,h0,m0,s0,t0;
    scanf("%d",&n);
    scanf("%d:%d:%d",&h0,&m0,&s0);
    t0=h0*3600+m0*60+s0;
    for(int i=1;i<=n;i++)
    {
    	int h1,m1,s1,h2,m2,s2,t;
    	scanf("%d:%d:%d",&h1,&m1,&s1);
    	scanf("%d:%d:%d",&h2,&m2,&s2);
    	t=(h2-h1)*3600+(m2-m1)*60+(s2-s1);
    	if(t>=t0) printf("%02d:%02d:%02d Yes!\n",t/3600,t%3600/60,t%60);
    	else printf("%02d:%02d:%02d No~555~\n",t/3600,t%3600/60,t%60);
	}
    return 0;
}
