#include<stdio.h>
int main()
{
	int sumboy=0,sumgirl=0,a,b,ib=0,ig=0;
	do
	{
		scanf("%d %d",&a,&b);
		if(a!=-1)
		{
			if(a==0)
			{
				sumboy+=b;
				ib++;
			}
			else{
				sumgirl+=b;
				ig++;
			}
			
		}
	}
	while(a!=-1);
	printf("%d\n",(sumboy+sumgirl)/(ib+ig));
	if(ib==0)
	{
		printf("No boy\n");
	}
	else printf("%d\n",sumboy/ib);
	if(ig==0)
	{
		printf("No girl");
	}
	else printf("%d",sumgirl/ig);
	return 0;
}
