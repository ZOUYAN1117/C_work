/**
 * 文件: 常用数学算法.c
 * 描述: 包含排列组合计算、最大公约数 (GCD) 与最小公倍数 (LCM)、快速幂、素数判定及斜边计算等数论与几何算法。
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * 计算排列数 A_m^n (确保输入的 m >= n > 0)
 * 参数：
 * - n: 排列数的上标
 * - m: 排列数的下标
 * 返回值：排列数值
 */
int anm(int n, int m) {
    if (m == 0)
        return 1;
    int a = 1;
    for (int i = m; i > m - n; i--)
        a *= i;
    return a;
}

/**
 * 计算组合数 C_m^n
 * 参数：
 * - n: 组合数的上标
 * - m: 组合数的下标
 * 返回值：组合数值
 */
int cnm(int n, int m) {
    if (n > (m ^ 1) / 2)
        n = m - n;
    return anm(n, m) / anm(n, n);
}

// 静态数组与常量，用于二重循环递推组合数预处理
#define MAX_COMB 1008
static long long comb[MAX_COMB][MAX_COMB];
static const long long P = 998442353;

/**
 * 通过二重循环递推预处理组合数，防止大数组越界和溢出 (推荐用于多次查询且需要取模的场景)
 * 参数：
 * - limit: 预处理的最大行数限制 (不应超过 MAX_COMB)
 * 返回值：无
 */
void precompute_combinations(int limit) {
    for (int i = 0; i <= limit && i < MAX_COMB; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) { // 边界条件
                comb[i][j] = 1;
            } else { // 递推式（组合恒等式）
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % P;
            }
        }
    }
}

/**
 * 递归高效求取最大公约数 (GCD)
 * 参数：
 * - a: 整数 a
 * - b: 整数 b
 * 返回值：最大公约数
 */
int gcd(int a, int b) {
    if (b == 0) // 达到基本情况，递归结束
        return a;
    return gcd(b, a % b);
}

/**
 * 非递归、支持负数的最大公约数 (GCD) 算法 (long long 版)
 * 参数：
 * - a: 长整型数 a
 * - b: 长整型数 b
 * 返回值：最大公约数绝对值
 */
long long gcd_ll(long long a, long long b) {
    long long r;
    if (b == 0)
        return a < 0 ? -a : a;
    while ((r = a % b) != 0) {
        a = b;
        b = r;
    }
    return b < 0 ? -b : b;
}

/**
 * 求取两个数的最小公倍数 (LCM)
 * 参数：
 * - a1: 长整型数 a1
 * - b1: 长整型数 b1
 * 返回值：最小公倍数数值
 */
long long lcm(long long a1, long long b1) {
    long long temp, a = a1, b = b1;
    while (a % b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a1 / b * b1;
}

/**
 * 快速幂算法，计算 a^n % mod 结果
 * 参数：
 * - a: 底数
 * - n: 指数
 * - mod: 模数
 * 返回值：计算后的幂模值
 */
int qpow(int a, long long n, int mod) {
    int ans = 1;
    int base = a;
    while (n > 0) {
        if (n & 1) { // 找到n的二进制的哪些位是1
            ans = ans * (long long)base % mod;
        }
        base = (long long)base * base % mod; // 快速幂的自我叠加相乘
        n >>= 1; // 下一次while循环查找下一位二进制
    }
    return ans;
}

/**
 * 高效判断一个较大的长整型数是否为素数
 * 参数：
 * - num: 待判断的长整型数值
 * 返回值：1 表示为素数，0 表示非素数
 */
int isprime(long long num) {
    if (num == 2 || num == 3)
        return 1;
    if ((num & 1) == 0 || num == 1 || num % 3 == 0) // 过滤偶数、1、3的倍数
        return 0;
    int i, flag;
    for (i = 5, flag = 4; 1ll * i * i <= num; i += flag) {
        flag = 6 - flag; // 步长在 4 和 2 之间交替 (即只检查 6k±1 的数)
        if (num % i == 0)
            return 0;
    }
    return 1;
}

/**
 * 计算直角三角形的斜边长度 (调用 C 标准 math 库的 hypot)
 * 参数：
 * - x: 直角边 x 的长度
 * - y: 直角边 y 的长度
 * 返回值：斜边长度数值
 */
double get_hypot(double x, double y) {
    return hypot(x, y);
}
