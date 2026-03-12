#include<stdio.h>
int main()
{
	char c;
	int s=0;
	while(scanf("%c",&c)!=EOF)
	{
		if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='A'||c=='E'||c=='I'||c=='O'||c=='U')
		s++;
	}
	printf("%d",s);
	return 0;
}
