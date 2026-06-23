#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 定义二叉排序树节点
struct Node
{
    char word[105];     // 存储单词
    int count;          // 出现次数
    struct Node *left;  // 左子树指针
    struct Node *right; // 右子树指针
};

// 在二叉排序树中插入单词或更新词频
struct Node *insert(struct Node *root, const char *word)
{
    if (root == NULL)
    {
        // 创建新节点
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        strcpy(newNode->word, word);
        newNode->count = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    // 比较单词字典序
    int cmp = strcmp(word, root->word);
    if (cmp == 0)
    {
        // 单词已存在，频次加 1
        root->count++;
    }
    else if (cmp < 0)
    {
        // 单词字典序小于当前节点，插入到左子树
        root->left = insert(root->left, word);
    }
    else
    {
        // 单词字典序大于当前节点，插入到右子树
        root->right = insert(root->right, word);
    }

    return root;
}

// 中序遍历二叉排序树（保证按字典序输出）
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s %d\n", root->word, root->count);
        inorder(root->right);
    }
}

// 释放二叉排序树内存
void free_tree(struct Node *root)
{
    if (root != NULL)
    {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main()
{
    // 尝试打开文件
    FILE *fp = fopen("article.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }

    struct Node *root = NULL;
    char buffer[105];
    int idx = 0;
    int c;

    // 逐字符读取文件内容
    while ((c = fgetc(fp)) != EOF)
    {
        if (isalpha(c))
        {
            // 如果是大写字母，统一转化为小写字母
            buffer[idx++] = tolower(c);
        }
        else
        {
            // 遇到非字母字符且 buffer 中有内容时，说明成功读取到一个单词
            if (idx > 0)
            {
                buffer[idx] = '\0';
                root = insert(root, buffer);
                idx = 0; // 重置 buffer 的索引
            }
        }
    }

    // 处理文件末尾可能存在的最后一个单词
    if (idx > 0)
    {
        buffer[idx] = '\0';
        root = insert(root, buffer);
    }
    fclose(fp);

    // 按照题目要求输出 root, root->right, root->right->right 节点上的单词
    if (root != NULL)
    {
        printf("%s", root->word);
        if (root->right != NULL)
        {
            printf(" %s", root->right->word);
            if (root->right->right != NULL)
            {
                printf(" %s", root->right->right->word);
            }
        }
        printf("\n");
    }

    // 中序遍历输出所有单词及词频（字典序）
    inorder(root);

    // 清理释放内存
    free_tree(root);

    return 0;
}
