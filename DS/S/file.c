#include <stdio.h>
#include <string.h>
#include <stdlib.h>
long long space;
int N;
typedef struct
{
    char name[25], parentName[25];
    int type, byte;
} File;
int main()
{
    FILE *in;
    // 打开输入文件（只读 + 错误检查）
    if ((in = fopen("input.txt", "r")) == NULL)
    {
        printf("Can't open file input.txt!\n");
        return 1;
    }
    // 读取
    fscanf(in, "%lld %d", &space, &N);
    File temp;
    for (int i = 1; i <= N; i++)
    {
        fscanf(in, "%s %s %d %d\n", temp.name, temp.parentName, &temp.type, &temp.byte);
    }
    fclose(in);
    return 0;
}
