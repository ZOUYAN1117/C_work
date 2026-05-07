#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 去除前导0（如果全为0则保留一个'0'）
void remove_leading_zeros(char *str) {
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

// 传入两个纯数字符串，计算减法结果并以动态分配的字符串返回
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
    if (!result) return NULL; // 内存分配失败保护

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

// ----- 测试用例 -----
int main() {
    char num1[100], num2[100];
    if (scanf("%99s %99s", num1, num2) == 2) {
        
        char *res = subtract_strings(num1, num2);
        
        if (res) {
            printf("结果为: %s\n", res);
            free(res); // 用完后务必释放内存
        }
    }
    return 0;
}