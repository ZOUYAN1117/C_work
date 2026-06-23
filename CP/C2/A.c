#include<stdio.h>
int main()
{
	printf("#include<stdio.h>\n");
	printf("int main() {\n    ");
	printf("int a, b, sum;\n    ");
	printf("scanf(");
	printf("%c",'"'); 
	printf("%%d%%d");
	printf("%c",'"'); 
	printf(", &a, &b);\n    ");
	printf("sum = a + b;\n    ");
	printf("printf(");
	printf("%c",'"'); 
	printf("%%d + %%d = %%d");
	printf("%c",'"');
	printf(",");
	printf(" a, b, sum);\n    return 0;\n}");
	return 0;
}
