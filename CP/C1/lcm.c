#include<stdio.h>
int main()
{
	int a,b,c,i=0;
	scanf("%d %d %d",&a,&b,&c);
	do{
		i++;
	}while(i%a!=0||i%b!=0||i%c!=0);
	printf("%d",i);
	return 0;
}
