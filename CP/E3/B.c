#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=n;i>=1;i--)
	{
		if(i>=3)
		printf("%d bottles of beer on the wall,\n%d bottles of beer.\nTake one down and pass it around,\nnow there's %d more bottles of beer on the wall!\n",i,i,i-1);
		else if(i==2)
		printf("2 bottles of beer on the wall,\n2 bottles of beer.\nTake one down and pass it around,\nnow there's 1 more bottle of beer on the wall!\n");
		else if(i==1)
		printf("1 bottle of beer on the wall,\n1 bottle of beer.\nTake one down and pass it around,\nthere's no more bottles of beer on the wall!\n");
	}
	return 0;
}
