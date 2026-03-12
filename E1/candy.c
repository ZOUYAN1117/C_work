#include<stdio.h>
int main()
{
	int T,n;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		scanf("%d",&n);
		if(n%4==1||n%4==3) printf("Alice\n");
		else  printf("Bob\n");
	}
	return 0;
}
