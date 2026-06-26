/**
 * 文件: 位运算与进制转换.c
 * 描述: 十进制与任意进制相互转换、打印二进制表达形式，以及位运算常用操作。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 十进制转任意进制输出 (仅支持 16 进制及以下，输出不含前导 0)
 * 参数：
 * - num: 待转换输出的十进制整数数值
 * - base: 转换的目标进制 (2 <= base <= 16)
 * 返回值：无
 */
void print_num_base(int num, int base) {
    if (num < 0) {
        putchar('-');
        num = -num;
    }
    if (num / base > 0) // 利用递归实现反向输出
        print_num_base(num / base, base);
    printf("%x", num % base); // 如果想要大写字母则使用 %X
}

/**
 * 打印任意长度的二进制数 (带前导 0)
 * 参数：
 * - num: 待转换输出的十进制整数数值
 * - len: 需输出打印的二进制数长度
 * 返回值：无
 */
void print_bin(int num, int len) {
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    putchar('\n');
}

/**
 * 打印 64 位长整型 (long long) 的二进制形式 (每 4 位加一个空格，方便阅读)
 * 参数：
 * - x: 待转换输出的长整型数值
 * 返回值：无
 */
void print_bin_ll(long long x) {
    for (int i = 63; i >= 0; --i) {
        putchar(((x >> i) & 1) + '0');
        if (i % 4 == 0)
            putchar(' '); // 每 4 位加个空格，方便看
    }
    putchar('\n');
}

/**
 * 任意进制字符串形式转为十进制长整型数值
 * 参数：
 * - base: 原数字符串的进制基数
 * - number_str: 任意进制的整数字符串
 * 返回值：转换后的十进制长整型数值
 */
long long base_to_dec(int base, const char *number_str) {
    int l = strlen(number_str);
    long long *a = malloc(l * sizeof(long long));
    for (int i = 0; i < l; i++) {
        if (number_str[i] >= '0' && number_str[i] <= '9')
            a[i] = number_str[i] - '0';
        else if (number_str[i] >= 'a' && number_str[i] <= 'z')
            a[i] = number_str[i] - 'a' + 10;
        else
            a[i] = number_str[i] - 'A' + 10;
    }
    long long ans = 0, p = 1;
    for (int i = l - 1; i >= 0; i--) {
        ans += p * a[i];
        p *= base;
    }
    free(a);
    return ans;
}

/**
 * 统计一个整型数的二进制表达中 1 的个数
 * 参数：
 * - x: 待统计的整型数值
 * 返回值：二进制中 1 的个数
 */
int count_ones(int x) {
    int cnt = 0;
    while (x) {
        x &= (x - 1); // 每次去掉一个最低位的 1
        cnt++;
    }
    return cnt;
}

/**
 * 判断一个整数是否为 2 的幂
 * 参数：
 * - n: 待判断的整型数值
 * 返回值：1 表示是，0 表示否
 */
int is_power_of_two(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

/**
 * 将一个数拆解为若干个 2 的幂之和并进行打印输出
 * 参数：
 * - n: 待拆解的无符号整型数值
 * 返回值：无
 */
void print_power_components(unsigned int n) {
    for (int i = 29; i >= 0; --i) { // 根据题目范围调整 i
        if ((n >> i) & 1) {
            printf("%d ", 1 << i);
        }
    }
    putchar('\n');
}

/**
 * 不使用任何算术加号实现两个整数相加 (全加器原理)
 * 参数：
 * - a: 加数 a
 * - b: 加数 b
 * 返回值：相加得到的和
 */
int add_no_plus(int a, int b) {
    while (b != 0) {
        int sum = a ^ b; // 不考虑进位的和
        int carry = (a & b) << 1; // 进位：只有 1+1 才产生进位
        a = sum;
        b = carry;
    }
    return a;
}

/**
 * 位段更新操作 (将 n 的第 i 到 j 位替换为 m 的对应低位，并左移对齐)
 * 参数：
 * - n: 待更新的原始整型值
 * - m: 目标覆写值
 * - i: 更新位域的起始下标
 * - j: 更新位域的终止下标
 * 返回值：更新后的数值
 */
int update_bits(int n, int m, int i, int j) {
    for (int pos = i; pos <= j; ++pos) {
        n &= ~(1 << pos); // 把第 pos 位清 0
    }
    return n | (m << i); // 左移后或进去
}

/**
 * 反转 32 位无符号整型数的二进制补码表达
 * 参数：
 * - x: 待反转的无符号整型值
 * 返回值：反转二进制后对应的新数值
 */
unsigned int reverse_bits(unsigned int x) {
    unsigned int res = 0;
    for (int i = 0; i < 32; ++i) {
        res <<= 1;
        res |= (x >> i) & 1;
    }
    return res;
}

/**
 * 将两个 n 位的二进制数 i 和 j 各个二进制位交叉拼装在一起 (错位拼接)
 * 参数：
 * - i: 第一个无符号整型值
 * - j: 第二个无符号整型值
 * - n: 操作的有效二进制位数
 * 返回值：交叉组装后的整型新数值
 */
unsigned int interleave_bits(unsigned int i, unsigned int j, int n) {
    unsigned int res = 0;
    for (int k = 0; k < n; k++) {
        res |= (((i >> k) & 1) * 2 + ((j >> k) & 1)) << (k * 2);
    }
    return res;
}
