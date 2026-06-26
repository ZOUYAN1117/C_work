/**
 * 文件: 快速排序与自定义比较器.c
 * 描述: C 标准库 qsort 的各种常见数据类型 (int, double, long long, 字符串, 双关键字, 间接编号) 的自定义比较器模板。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 浮点数升序比较器 (double 类型)
 * 参数：
 * - a: 元素 a 指针
 * - b: 元素 b 指针
 * 返回值：-1 表示 a < b，1 表示 a > b，0 表示相等
 */
int compare_double_asc(const void *a, const void *b) {
    double num_a = *(const double *)a;
    double num_b = *(const double *)b;
    if (num_a < num_b) {
        return -1;
    } else if (num_a > num_b) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 整型升序比较器 (int 类型)
 * 参数：
 * - p1: 元素 1 指针
 * - p2: 元素 2 指针
 * 返回值：-1 (a < b), 1 (a > b), 0 (相等)
 */
int cmp_int_asc(const void *p1, const void *p2) {
    int a = *(const int *)p1;
    int b = *(const int *)p2;
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}

/**
 * 长整型升序比较器 (long long 类型)
 * 参数：
 * - p1: 元素 1 指针
 * - p2: 元素 2 指针
 * 返回值：-1 (a < b), 1 (a > b), 0 (相等)
 */
int cmp_ll_asc(const void *p1, const void *p2) {
    long long a = *(const long long *)p1;
    long long b = *(const long long *)p2;
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}

/**
 * 字符串字典序升序比较器
 * 参数：
 * - p: 字符串数组第一个元素指针 (一般为二维字符数组一行的首地址)
 * - q: 字符串数组第二个元素指针
 * 返回值：strcmp 的比较结果 (-1, 1, 0)
 * 用法：
 *   char s[1010][110];
 *   qsort(s, n, sizeof(s[0]), cmp_str);
 */
int cmp_str(const void *p, const void *q) {
    const char *a = (const char *)p;
    const char *b = (const char *)q;
    return strcmp(a, b);
}

/**
 * 双关键字整型排序比较器 (先按第一列升序，若相等则按第二列升序)
 * 参数：
 * - p: 指向包含两个整型数据的一维数组首地址的指针
 * - q: 指向包含两个整型数据的一维数组首地址的指针
 * 返回值：根据优先级决定的比较结果
 * 用法：
 *   int a[500005][2];
 *   qsort(a, n, 2 * sizeof(int), cmp_double_keyword);
 */
int cmp_double_keyword(const void *p, const void *q) {
    const int *a = (const int *)p;
    const int *b = (const int *)q;
    if (a[0] < b[0]) // 第一关键字升序
        return -1;
    if (a[0] > b[0])
        return 1;
    if (a[1] < b[1]) // 第二关键字升序
        return -1;
    if (a[1] > b[1])
        return 1;
    return 0;
}

// 模拟用全局数组，用于间接编号排序示例
static int demo_len[1000];

/**
 * 间接编号排序比较器 (以另外一个数组的值来决定当前编号数组的顺序)
 * 参数：
 * - p: 指向待排编号的指针 1
 * - q: 指向待排编号的指针 2
 * 返回值：根据外部数值比较决定的结果 (-1, 1, 0)
 * 用法示例：
 *   int id[1000];
 *   for (int i = 0; i < n; i++) id[i] = i;
 *   qsort(id, n, sizeof(int), cmp_indirect);
 */
int cmp_indirect(const void *p, const void *q) {
    int i = *(const int *)p;
    int j = *(const int *)q;
    if (demo_len[i] < demo_len[j]) // 以 demo_len 数组中对应位置的大小关系升序排序
        return -1;
    if (demo_len[i] > demo_len[j])
        return 1;
    return 0;
}