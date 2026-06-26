/**
 * 文件: 字符串处理.c
 * 描述: 包含各种字符串常用处理操作与算法模板，如大小写原地转换、回文判定、手写高效拼接、特殊子串比较、空白字符截断、敏感词掩码等。
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 将整条字符串中的英文字母全部原地修改转换为小写字母
 * 参数：
 * - s: 待转换的字符串首地址
 * 返回值：无
 */
void str_to_lower(char *s) {
    for (int i = 0; s[i] != '\0'; ++i) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
}

/**
 * 将整条字符串中的英文字母全部原地修改转换为大写字母
 * 参数：
 * - s: 待转换的字符串首地址
 * 返回值：无
 */
void str_to_upper(char *s) {
    for (int i = 0; s[i] != '\0'; ++i) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
}

/**
 * 判断指定字符串是否为回文串 (忽略字母的大小写差异)
 * 参数：
 * - s: 待判断的字符串首地址
 * 返回值：1 表示为回文，0 表示非回文
 */
int is_palindrome_ci(const char *s) {
    int len = (int)strlen(s);
    int i = 0, j = len - 1;
    while (i < j) {
        char a = (char)tolower((unsigned char)s[i]);
        char b = (char)tolower((unsigned char)s[j]);
        if (a != b)
            return 0;
        ++i;
        --j;
    }
    return 1;
}

/**
 * 计算将字符串修改为回文串，最少需要更改几个位置的字符 (区分字母大小写)
 * 参数：
 * - s: 待处理的字符串首地址
 * 返回值：需要修改的最小字符对数
 */
int min_changes_to_palindrome(const char *s) {
    int len = (int)strlen(s);
    int l = 0, r = len - 1;
    int cnt = 0;
    while (l < r) {
        if (s[l] != s[r])
            ++cnt;
        ++l;
        --r;
    }
    return cnt;
}

/**
 * 高效拼接字符串 (避免标准 strcat 每次都从头扫描目标串的低效行为)
 * 参数：
 * - dest: 目标字符数组首地址
 * - plen: 指向记录当前 dest 已存字符长度变量的指针，拼接后会被自增更新
 * - src: 待追加拼接的源字符串首地址
 * 返回值：无
 */
void append_string(char *dest, int *plen, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[*plen] = src[i];
        ++(*plen);
        ++i;
    }
    dest[*plen] = '\0';
}

/**
 * 交换两个整型数据的值
 * 参数：
 * - a: 整数 a 的指针
 * - b: 整数 b 的指针
 * 返回值：无
 */
void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * 交换两个长整型数据的值
 * 参数：
 * - a: 长整数 a 的指针
 * - b: 长整数 b 的指针
 * 返回值：无
 */
void swap_ll(long long *a, long long *b) {
    long long tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * 统计一个整型数组中，所有 int 数据拆分为字节后，数值等于 114 的单字节个数 (字节级指针访问演示)
 * 参数：
 * - a: 整型数组首地址
 * - n: 数组大小
 * 返回值：匹配到的单字节个数
 */
int count_114_bytes_in_ints(const int *a, int n) {
    int total = 0;
    for (int i = 0; i < n; ++i) {
        unsigned char *p = (unsigned char *)&a[i]; // 强转指针进行字节级访问
        for (int j = 0; j < 4; ++j) {
            if (p[j] == 114)
                ++total;
        }
    }
    return total;
}

/**
 * 比较两个字符串的特定区间子串 s[l1..r1-1] 和 t[l2..r2-1] 是否完全相等
 * 参数：
 * - s: 第一个字符串首地址
 * - l1: 区间 1 的起始下标
 * - r1: 区间 1 的终止下标 (开区间边界)
 * - t: 第二个字符串首地址
 * - l2: 区间 2 的起始下标
 * - r2: 区间 2 的终止下标 (开区间边界)
 * 返回值：1 表示区间内子序列完全相等，0 表示不等或长度不同
 */
int substr_equal(const char *s, int l1, int r1, const char *t, int l2, int r2) {
    int len1 = r1 - l1;
    int len2 = r2 - l2;
    if (len1 != len2)
        return 0;
    for (int i = 0; i < len1; ++i) {
        if (s[l1 + i] != t[l2 + i])
            return 0;
    }
    return 1;
}

/**
 * 原地截断并去除字符串尾部所有的空白字符 (如空格、制表符、回车换行等)
 * 参数：
 * - s: 待处理的字符串首地址
 * 返回值：无
 */
void rstrip(char *s) {
    int len = (int)strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }
}

/**
 * 原地去除字符串首尾两端所有的空白字符 (结果写回原字符串)
 * 参数：
 * - s: 待处理的字符串首地址
 * 返回值：无
 */
void strip(char *s) {
    int len = (int)strlen(s);
    int l = 0;
    while (l < len && isspace((unsigned char)s[l]))
        ++l;
    int r = len - 1;
    while (r >= l && isspace((unsigned char)s[r]))
        --r;
    int newlen = (r >= l) ? (r - l + 1) : 0;
    if (newlen > 0) {
        memmove(s, s + l, (size_t)newlen);
    }
    s[newlen] = '\0';
}

/**
 * 统计指定字符 ch 在字符串 s 中出现的总次数
 * 参数：
 * - s: 待统计的字符串首地址
 * - ch: 被统计的目标字符
 * 返回值：字符 ch 出现的次数值
 */
int count_char(const char *s, char ch) {
    int cnt = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == ch)
            ++cnt;
    }
    return cnt;
}

/**
 * 递归计算得到字符串的某种分治字典序标准型 (常用于分治类字符串比较题)
 * 参数：
 * - s: 输入源字符指针
 * - len: 输入的子串长度
 * - result: 指向存放标准型结果的目标字符指针
 * 返回值：无
 */
void canonize_string(char *s, int len, char *result) {
    if (len % 2 == 1) {
        memcpy(result, s, len);
        result[len] = '\0';
        return;
    }
    int mid = len / 2;
    canonize_string(s, mid, result);
    canonize_string(s + mid, mid, result + mid);
    int cmp = strncmp(result, result + mid, mid);
    if (cmp <= 0) {
        result[len] = '\0';
    } else { // 左右交换位置拼接
        char temp[2005];
        memcpy(temp, result + mid, mid);
        memcpy(temp + mid, result, mid);
        temp[len] = '\0';
        memcpy(result, temp, len + 1);
    }
}

/**
 * 在原字符串 s1 中检索特定词汇 key，并将其用 '*' 覆盖予以屏蔽 (过滤过程忽略大小写)
 * 参数：
 * - s1: 待覆写屏蔽的原字符串首地址
 * - s2: 传入的 s1 全小写形式的备份字符串首地址，长度需与 s1 相同，作导航检索用
 * - key: 待屏蔽的关键字字符串
 * 返回值：无
 */
void mask_sensitive(char s1[], const char s2[], const char key[]) {
    char lower_key[64];
    int keylen = strlen(key);
    for (int i = 0; i < keylen; ++i) // 关键词转小写
        lower_key[i] = (char)tolower((unsigned char)key[i]);
    lower_key[keylen] = '\0';
    const char *p = s2; // 在小写副本 s2 里找
    while ((p = strstr(p, lower_key)) != NULL) {
        int pos = (int)(p - s2); // 关键字在 s2 中的起始下标
        for (int i = 0; i < keylen; ++i)
            s1[pos + i] = '*'; // 将原串 s1 中对应位置覆盖为 '*'
        p++; // 继续往后匹配，避免死循环
    }
}
