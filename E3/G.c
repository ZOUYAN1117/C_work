#include<stdio.h>
char a;
int main()
{
	int n,m,x0,y0,x,y;
	scanf("%d %d",&n,&m);
	scanf("%d %d",&x0,&y0);
	scanf("%d %d",&x,&y);
	for(int i=x-2;i<=x+2;i++)
	{
		for(int j=y-2;j<=y+2;j++)
		{
			if(j==y0&&i==x0) a='+';
			else if(i==x0) a='-';
			else if(j==y0) a='|';
			else if(j>y0&&i+j<x0+y0) a='A';
			else if(j>y0&&i+j==x0+y0) a='/';
			else if(i<x0&&i+j>x0+y0) a='B';
			else if(i>x0&&j-i>y0-x0) a='C';
			else if(j>y0&&j-i==y0-x0) a='\\';
			else if(j>y0&&j-i<y0-x0) a='D';
			else if(j<y0&&i+j>x0+y0) a='E';
			else if(j<y0&&i+j==x0+y0) a='/';
			else if(i>x0&&i+j<x0+y0) a='F';
			else if(i<x0&&j-i<y0-x0) a='G';
			else if(i<x0&&j-i==y0-x0) a='\\'; 
			else if(j<y0&&j-i>y0-x0) a='H';
			printf("%c",a);
		}
		printf("\n");
	}
	return 0;
}
