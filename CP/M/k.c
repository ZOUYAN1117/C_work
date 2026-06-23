#include<stdio.h>
#include<stdlib.h>
int cmp(const void *p1,const void *p2)
{
	int *m=(int *)p1;
	int *n=(int *)p2;
	return *m-*n;
}
int main()
{
	int a[10]={2,6,8,3,5,9,0,4,2,6};
	qsort(a,10,4,cmp);
	for(int i=0;i<10;i++)
	{
		printf("%d ",a[i]);
	}
}
