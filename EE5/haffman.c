// 文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode
{ // Huffman树结构
    char c;
    int weight; // 树节点权重，叶节点为字符和它的出现次数
    struct tnode *left, *right;
};
int Ccount[128] = {0};            // 存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数
struct tnode *Root = NULL;        // Huffman树的根节点
char HCode[128][MAXSIZE] = {{0}}; // 字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式）
int Step = 0;                     // 实验步骤
FILE *Src, *Obj;

void statCount();   // 步骤1：统计文件中字符频率
void createHTree(); // 步骤2：创建一个Huffman树，根节点为Root
void makeHCode();   // 步骤3：根据Huffman树生成Huffman编码
void atoHZIP();     // 步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();                // 输出步骤1的结果
void print2(struct tnode *p); // 输出步骤2的结果
void print3();                // 输出步骤3的结果
void print4();                // 输出步骤4的结果

int main()
{
    if ((Src = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "%s open failed!\n", "input.txt");
        return 1;
    }
    if ((Obj = fopen("output.txt", "w")) == NULL)
    {
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d", &Step); // 输入当前实验步骤

    statCount();                           // 实验步骤1：统计文件中字符出现次数（频率）
    (Step == 1) ? print1() : 1;            // 输出实验步骤1结果
    createHTree();                         // 实验步骤2：依据字符频率生成相应的Huffman树
    (Step == 2) ? print2(Root) : 2;        // 输出实验步骤2结果
    makeHCode();                           // 实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
    (Step == 3) ? print3() : 3;            // 输出实验步骤3结果
    (Step >= 4) ? atoHZIP(), print4() : 4; // 实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果

    fclose(Src);
    fclose(Obj);
    return 0;
}

// 【实验步骤1】开始
void statCount()
{
    int c;
    while ((c = fgetc(Src)) != EOF)
        Ccount[c]++;
    Ccount[0] = 1; // 设定NUL字符出现次数为1，保证Huffman树的根节点不为NULL
}

// 【实验步骤1】结束

// 【实验步骤2】开始
struct tnode *F[256];
int F_size = 0;

void sortF()
{
    for (int i = 0; i < F_size - 1; i++)
    {
        for (int j = 0; j < F_size - 1 - i; j++)
        {
            if (F[j]->weight > F[j + 1]->weight ||
                (F[j]->weight == F[j + 1]->weight && F[j]->c > F[j + 1]->c))
            {
                struct tnode *temp = F[j];
                F[j] = F[j + 1];
                F[j + 1] = temp;
            }
        }
    }
}

void insertF(struct tnode *p)
{
    int i = F_size - 1;
    while (i >= 0 && F[i]->weight > p->weight)
    {
        F[i + 1] = F[i];
        i--;
    }
    F[i + 1] = p;
    F_size++;
}

void createHTree()
{
    F_size = 0;
    for (int i = 0; i < 128; i++)
    {
        if (Ccount[i] > 0)
        {
            struct tnode *p = (struct tnode *)malloc(sizeof(struct tnode));
            p->c = i;
            p->weight = Ccount[i];
            p->left = p->right = NULL;
            F[F_size++] = p;
        }
    }
    sortF();

    while (F_size > 1)
    {
        struct tnode *T0 = F[0];
        struct tnode *T1 = F[1];
        struct tnode *T_prime = (struct tnode *)malloc(sizeof(struct tnode));
        T_prime->c = 0;
        T_prime->weight = T0->weight + T1->weight;
        T_prime->left = T0;
        T_prime->right = T1;
        for (int i = 2; i < F_size; i++)
        {
            F[i - 2] = F[i];
        }
        F_size -= 2;
        insertF(T_prime);
    }

    if (F_size == 1)
    {
        Root = F[0];
    }
}
// 【实验步骤2】结束

// 【实验步骤3】开始
void visitHTree(struct tnode *p, char *path, int len)
{
    if (p != NULL)
    {
        if (p->left == NULL && p->right == NULL)
        {
            path[len] = '\0';
            strcpy(HCode[(unsigned char)p->c], path);
        }
        else
        {
            path[len] = '0';
            visitHTree(p->left, path, len + 1);
            path[len] = '1';
            visitHTree(p->right, path, len + 1);
        }
    }
}

void makeHCode()
{
    char path[MAXSIZE];
    if (Root != NULL)
    {
        visitHTree(Root, path, 0);
    }
}

// 【实验步骤4】开始
void atoHZIP()
{
    fseek(Src, 0, SEEK_SET); // 重新定位到文件开头，因为之前步骤1已经读到文件末尾了
    int c;
    unsigned char hc = 0;
    int bit_count = 0;
    // 1. 读取原文件每个字符加入到压缩码
    while ((c = fgetc(Src)) != EOF)
    {
        char *s = HCode[c];
        for (int i = 0; s[i] != '\0'; i++)
        {
            hc = (hc << 1) | (s[i] - '0');
            bit_count++;
            if (bit_count == 8)
            {
                fputc(hc, Obj);
                printf("%x", hc);
                hc = 0;
                bit_count = 0;
            }
        }
    }

    // 2. 将输入结束符的 Huffman 码 (HCode[0]) 放到最后
    char *s0 = HCode[0];
    for (int i = 0; s0[i] != '\0'; i++)
    {
        hc = (hc << 1) | (s0[i] - '0');
        bit_count++;

        if (bit_count == 8)
        {
            fputc(hc, Obj);
            printf("%x", hc);
            hc = 0;
            bit_count = 0;
        }
    }

    // 3. 处理最后不足8位的情况，需要左移并补0
    if (bit_count > 0)
    {
        hc = hc << (8 - bit_count);
        fputc(hc, Obj);
        printf("%x", hc);
    }
}
// 【实验步骤4】结束

void print1()
{
    int i;
    printf("NUL:1\n");
    for (i = 1; i < 128; i++)
        if (Ccount[i] > 0)
            printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
    if (p != NULL)
    {
        if ((p->left == NULL) && (p->right == NULL))
            switch (p->c)
            {
            case 0:
                printf("NUL ");
                break;
            case ' ':
                printf("SP ");
                break;
            case '\t':
                printf("TAB ");
                break;
            case '\n':
                printf("CR ");
                break;
            default:
                printf("%c ", p->c);
                break;
            }
        print2(p->left);
        print2(p->right);
    }
}

void print3()
{
    int i;

    for (i = 0; i < 128; i++)
    {
        if (HCode[i][0] != 0)
        {
            switch (i)
            {
            case 0:
                printf("NUL:");
                break;
            case ' ':
                printf("SP:");
                break;
            case '\t':
                printf("TAB:");
                break;
            case '\n':
                printf("CR:");
                break;
            default:
                printf("%c:", i);
                break;
            }
            printf("%s\n", HCode[i]);
        }
    }
}

void print4()
{
    long int in_size, out_size;

    fseek(Src, 0, SEEK_END);
    fseek(Obj, 0, SEEK_END);
    in_size = ftell(Src);
    out_size = ftell(Obj);

    printf("\n原文件大小：%ldB\n", in_size);
    printf("压缩后文件大小：%ldB\n", out_size);
    printf("压缩率：%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}
