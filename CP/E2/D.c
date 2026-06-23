#include<stdio.h>
int main()
{
	char c,a[100010];
	int t=0,m=1;
	while(scanf("%c",&c)!=EOF)
	{
		if(t!=1||c!='r')
		{
			if(t==1) t=0;
			if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u') t=1;
			a[m]=c;
			m++;
		}
		else
		{
			if(t==1) t=0;
			if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u') t=1;
		}
	}
	for(int i=1;i<=m;i++)
	printf("%c",a[i]);
	return 0;
}
