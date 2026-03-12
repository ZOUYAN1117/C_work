#include<stdio.h>
int main()
{
	int a,b,c,d,p0,q0;
	scanf("%d %d",&a,&b);
	scanf("%d %d",&c,&d);
	p0=a*d-b*c;
	q0=b*d;
	int p=p0,q=q0,t=1,g;
	if(p<0) p-=2*p;
	while(q!=0)
	{
		t=p%q;
		p=q;
		q=t;
	}
	g=p;
	p0/=g;
	q0/=g; 
	if(p0==q0||p0==-q0||p0==0||q0==1) printf("%d",p0);
	else printf("%d/%d",p0,q0);
	return 0;
}
