/**
 * 文件: 高精度计算.c
 * 描述: 高精度大数基本运算，包含支持正负结果的大数减法与生成任意位数的除法小数结果。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 辅助函数：清除大数字符串结果中的前导 0
 * 参数：
 * - str: 待处理的大数字符串首地址
 * 返回值：无
 */
static void remove_leading_zeros(char *str) {
    int i = 0, p = 0;
    for (int j = 0; str[j] != '\0'; j++) {
        if (str[j] != '0' || p != 0) {
            p = 1;
            str[i++] = str[j];
        }
    }
    if (i == 0) {
        str[i++] = '0';
    }
    str[i] = '\0';
}

/**
 * 传入两个整型数字字符串，计算其减法差值结果 (str1 - str2)，并以动态分配的字符串返回
 * 参数：
 * - str1: 被减数字符串
 * - str2: 减数字符串
 * 返回值：指向动态分配的结果字符串的首地址指针；使用完毕后必须用 free() 释放内存
 */
char* subtract_strings(const char *str1, const char *str2) {
    char a[1000], b[1000];
    strcpy(a, str1);
    strcpy(b, str2);

    remove_leading_zeros(a);
    remove_leading_zeros(b);

    int lena = strlen(a);
    int lenb = strlen(b);

    // 分配结果内存：最大长度 + 符号位长度(1) + 终止符长度(1)
    int max_len = (lena > lenb ? lena : lenb) + 2;
    char *result = (char *)malloc(max_len);
    if (!result) return NULL; // 内存分配保护

    char *larger, *smaller;
    int is_negative = 0;

    // 比较大小以决定谁减谁，并设置正负号
    if (lena > lenb || (lena == lenb && strcmp(a, b) > 0)) {
        larger = a;
        smaller = b;
    } else if (lena < lenb || (lena == lenb && strcmp(a, b) < 0)) {
        larger = b;
        smaller = a;
        is_negative = 1;
    } else {
        strcpy(result, "0");
        return result;
    }

    int L = strlen(larger);
    int S = strlen(smaller);
    int n = L - S;

    // 将较短的字符串后移补0对齐
    memmove(smaller + n, smaller, S + 1);
    for (int i = 0; i < n; i++) {
        smaller[i] = '0';
    }

    // 核心竖式减法模拟
    for (int i = L - 1; i >= 0; i--) {
        if (larger[i] < smaller[i]) {
            larger[i] += 10;
            larger[i - 1]--;
        }
        larger[i] -= smaller[i] - '0';
    }

    // 去除减法结果生成的前导0
    remove_leading_zeros(larger);

    // 拼接结果到返回字符串中
    if (is_negative) {
        sprintf(result, "-%s", larger);
    } else {
        strcpy(result, larger);
    }

    return result;
}

/**
 * 高精度除法，计算 a / b 的商并保留输出 n 位小数结果 (带四舍五入进位)
 * 参数：
 * - a: 被除数 (long long)
 * - b: 除数 (long long)
 * - n: 需要保留的小数点后有效位数
 * 返回值：无
 */
void high_precision_div(long long a, long long b, int n) {
    long long *ans = calloc(n + 5, sizeof(long long));
    if (!ans) return;
    
    // 模拟除法并记录每一位数值
    ans[0] = a / b;
    ans[1] = (a % b) * 10;
    for (int i = 1; i <= n + 1; i++) {
        ans[i + 1] = (ans[i] % b) * 10;
        ans[i] = ans[i] / b;
    }
    
    // 判断第 n+1 位的值是否需要进位并处理
    if (ans[n + 1] >= 5) { // 四舍五入进位
        ans[n] += 1;
        for (int i = n; i > 0; i--) { // 对每一位小数进行进位处理
            ans[i - 1] += ans[i] / 10; // 第 i 位满 10，第 i-1 位加一
            ans[i] %= 10;              // 第 i 位进一后对 10 取模
        }
    }
    
    // 输出整数部分与小数部分
    printf("%lld.", ans[0]);
    for (int i = 1; i <= n; i++) {
        printf("%lld", ans[i]);
    }
    printf("\n");
    
    free(ans);
}
