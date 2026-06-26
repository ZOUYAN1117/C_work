/**
 * 文件: 查找.c
 * 描述: 包含各种基础及高级查找算法模板。包括整型数组二分查找、边界二分检索、单词表顺序检索、折半检索、字母索引查找、散列（哈希）查找及整型数组线性查找。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_MAX 21   /* 单词最大长度（含 '\0'） */
#define DICT_MAX 3500 /* 字典最大单词数 */
#define NHASH 3001    /* 散列表长度 */
#define HASH_MULT 37  /* 散列乘数 */

/**
 * 结构体: HashNode - 链地址法散列表结点结构体
 * 成员：
 * - word: 存储的单词字符串
 * - link: 指向冲突链中下一个结点的指针
 */
typedef struct HashNode
{
    char word[WORD_MAX];
    struct HashNode *link;
} HashNode;

// 静态数组用于 run_boundary_search_demo
static int boundary_arr[500005];

/**
 * 递归实现经典的二分查找算法 (适用于无重复元素的有序长整型数组)
 * 参数：
 * - b: 有序的 long long 数组首地址
 * - key: 待查找的目标值键值
 * - low: 检索区间的低位边界下标
 * - high: 检索区间的高位边界下标
 * 返回值：查找到目标值时的下标位置；未找到则返回 -1
 */
int rec_bin_find(long long b[], int key, int low, int high) {
    int mid;
    // 递归终止边界，未找到
    if (low > high)
        return -1;
    
    mid = (low + high) / 2;
    // 匹配成功
    if (key == b[mid])
        return mid;
    // 往左半区递归
    else if (key < b[mid])
        return rec_bin_find(b, key, low, mid - 1);
    // 往右半区递归
    else
        return rec_bin_find(b, key, mid + 1, high);
}

/**
 * 演示如何使用二分查找在包含重复元素的升序数组中查找目标的左右边界
 * 参数：无
 * 返回值：0
 */
int run_boundary_search_demo(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    // 输入升序排列的数组
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &boundary_arr[i]) != 1) break;
    }
    
    int x;
    if (scanf("%d", &x) != 1) return 0;

    // 1. 查找左边界（即第一个值等于 x 的元素下标位置）
    int l = -1, r = n;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (boundary_arr[mid] < x)
            l = mid;
        else
            r = mid;
    }
    int lft = r;
    
    // 2. 查找右边界（即第一个值大于 x 的元素下标位置）
    l = -1, r = n;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (boundary_arr[mid] <= x)
            l = mid;
        else
            r = mid;
    }
    int rt = r;
    
    // 输出重复元素 x 的个数 (右边界 - 左边界)
    printf("%d\n", rt - lft);
    return 0;
}

/**
 * 在已按字典序排好序的单词表中做顺序查找，遇到相同或第一个比 key 大的单词即停止
 * 参数：
 * - words: 二维字符数组单词表
 * - n: 单词表中的单词个数
 * - key: 待检索的目标单词
 * - cmpCount: 指针，用于返回 strcmp 的比较次数
 * 返回值：1 找到，0 未找到
 */
int searchSeqSorted(const char words[][WORD_MAX], int n,
                    const char *key, int *cmpCount)
{
    int i, cond;

    *cmpCount = 0;
    for (i = 0; i < n; i++)
    {
        cond = strcmp(words[i], key);
        (*cmpCount)++;
        if (cond == 0)
            return 1;
        if (cond > 0)
            return 0;
    }
    return 0;
}

/**
 * 在已排序单词表中做折半查找 (二分查找)
 * 参数：
 * - words: 二维字符数组单词表
 * - n: 单词表中的单词个数
 * - key: 待检索的目标单词
 * - cmpCount: 指针，用于返回 strcmp 的比较次数
 * 返回值：1 找到，0 未找到
 */
int searchBin(const char words[][WORD_MAX], int n,
              const char *key, int *cmpCount)
{
    int low, high, mid, res;

    low = 0;
    high = n - 1;
    *cmpCount = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        (*cmpCount)++;
        res = strcmp(words[mid], key);
        if (res == 0)
            return 1;
        if (res < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;
}

/**
 * 为已排序单词表构建 26 字母索引表
 * 参数：
 * - words: 二维字符数组单词表
 * - n: 单词表中的单词个数
 * - index: 2D 索引表 (index[c-'a'][0] 为起始下标，index[c-'a'][1] 为长度)
 * 返回值：无
 */
void searchBuildLetterIndex(const char words[][WORD_MAX], int n,
                            int index[26][2])
{
    int i, k;
    char first;

    // 初始化索引表为0
    for (k = 0; k < 26; k++)
        index[k][0] = index[k][1] = 0;

    if (n == 0)
        return;

    first = 'a';
    index[first - 'a'][0] = 0;
    for (i = 0; i < n; i++)
    {
        if (words[i][0] > first)
        {
            index[first - 'a'][1] = i - index[first - 'a'][0];
            index[words[i][0] - 'a'][0] = i;
            first = words[i][0];
        }
    }
    index[first - 'a'][1] = n - index[first - 'a'][0];
}

/**
 * 在指定下标区间范围内做折半查找 (供索引查找内部使用)
 * 参数：
 * - words: 二维字符数组单词表
 * - low: 区间下界
 * - high: 区间上界
 * - key: 待检索的目标单词
 * - cmpCount: 指针，用于返回 strcmp 的比较次数
 * 返回值：1 找到，0 未找到
 */
int searchBinRange(const char words[][WORD_MAX], int low, int high,
                   const char *key, int *cmpCount)
{
    int mid, res;

    *cmpCount = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        (*cmpCount)++;
        res = strcmp(words[mid], key);
        if (res == 0)
            return 1;
        if (res < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;
}

/**
 * 结合 26 字母索引表与折半查找算法进行高效单词检索
 * 参数：
 * - words: 二维字符数组单词表
 * - index: 构建完毕的 2D 字母索引表
 * - key: 待检索的目标单词
 * - cmpCount: 指针，用于返回 strcmp 的比较次数
 * 返回值：1 找到，0 未找到
 */
int searchByIndex(const char words[][WORD_MAX], int index[26][2],
                  const char *key, int *cmpCount)
{
    int low, high;

    // 查索引表得到该首字母对应的起始范围
    low = index[key[0] - 'a'][0];
    high = index[key[0] - 'a'][0] + index[key[0] - 'a'][1] - 1;
    return searchBinRange(words, low, high, key, cmpCount);
}

/**
 * 计算字符串的散列 hash 值 (作业给定多项式乘数取模算法)
 * 参数：
 * - str: 字符串指针
 * 返回值：计算得到的散列值，范围在 0 .. NHASH-1 之间
 */
unsigned int hashStr(const char *str)
{
    unsigned int h = 0;
    const char *p;

    for (p = str; *p != '\0'; p++)
        h = HASH_MULT * h + (unsigned char)*p;
    return h % NHASH;
}

/**
 * 向哈希链表的指定冲突桶链的尾部追加插入单词节点
 * 参数：
 * - table: 哈希表数组 (元素为链表头节点指针)
 * - word: 待插入的单词
 * 返回值：无
 */
void hashInsertTail(HashNode *table[], const char *word)
{
    HashNode *p, *q;
    unsigned int k;

    k = hashStr(word);
    p = (HashNode *)malloc(sizeof(HashNode));
    if (p == NULL) return;
    strcpy(p->word, word);
    p->link = NULL;
    
    // 链首为空直接挂接，否则移动至链尾进行追加
    if (table[k] == NULL)
        table[k] = p;
    else
    {
        q = table[k];
        while (q->link != NULL)
            q = q->link;
        q->link = p;
    }
}

/**
 * 在链地址法哈希表中检索特定的单词 key (顺序扫描桶中冲突链表)
 * 参数：
 * - table: 哈希表数组
 * - key: 待查找的单词
 * - cmpCount: 指针，用于返回 strcmp 的比较次数
 * 返回值：1 找到，0 未找到
 */
int searchHashChain(HashNode *table[], const char *key, int *cmpCount)
{
    HashNode *p;
    int cond;

    *cmpCount = 0;
    p = table[hashStr(key)];
    while (p != NULL)
    {
        cond = strcmp(p->word, key);
        (*cmpCount)++;
        if (cond == 0)
            return 1;
        if (cond > 0) // 链表中元素是有序的，一旦当前位置字典序大于 key 即可判定未找到
            return 0;
        p = p->link;
    }
    return 0;
}

/**
 * 释放哈希链表中所分配的所有动态节点内存
 * 参数：
 * - table: 哈希表数组
 * 返回值：无
 */
void hashFreeAll(HashNode *table[])
{
    int i;
    HashNode *p, *q;

    // 循环遍历每一个冲突桶并逐个释放节点
    for (i = 0; i < NHASH; i++)
    {
        p = table[i];
        while (p != NULL)
        {
            q = p->link;
            free(p);
            p = q;
        }
        table[i] = NULL;
    }
}

/**
 * 在一维整型数组中进行顺序线性检索
 * 参数：
 * - arr: 待检索的整型数组首地址
 * - n: 数组长度
 * - key: 待查找的目标值
 * 返回值：找到时返回其下标，未查找到则返回 -1
 */
int searchLinearInt(const int arr[], int n, int key)
{
    int i;

    for (i = 0; i < n; i++)
        if (arr[i] == key)
            return i;
    return -1;
}
