#include<stdio.h>
int main()
{
	int n,m,i,j=0;
	scanf("%d %d",&n,&m);
	for(i=0;i<=n;i++)
	{
		if(i*10+(n-i)*8==m)
		{
			printf("%d",i);
			j=1;
		}
	}
	if(j==0)
	printf("ERR0R");
	return 0;
}
