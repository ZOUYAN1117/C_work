#include<stdio.h>
char h[101][22];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=21;i++)
	{
		for(int j=1;j<=n;j++)
		h[j][i]='.';
	}
	for(int i=1;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		h[i][21-a]='_';
		for(int j=22-a;j<=22;j++)
		h[i][j]='*';
	}
	int x,y;
	scanf("%d %d",&x,&y);
	h[x][21-y]='-';
	h[x+2][21-y]='-';
	h[x+1][21-y]='o';
	for(int i=1;i<=21;i++)
	{
		for(int j=1;j<=n;j++)
		printf("%c",h[j][i]);
		printf("\n");
	}
}
