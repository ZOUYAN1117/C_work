// 用字符串前记得加上
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *memcpy(void *__restrict__ _Dst, const void *__restrict__ _Src,
             size_t _Size);

// 将字符串全部转成小写（原地修改）
void str_to_lower(char *s) {
  for (int i = 0; s[i] != '\0'; ++i) {
    s[i] = (char)tolower((unsigned char)s[i]);
  }
}

// 将字符串全部转成大写（原地修改）
void str_to_upper(char *s) {
  for (int i = 0; s[i] != '\0'; ++i) {
    s[i] = (char)toupper((unsigned char)s[i]);
  }
}

// 每个“单词”首字母大写，其余保持原样（换行输出）
int main() {
  char name[110];
  while (scanf("%s", name) != EOF) {
    name[0] = toupper(name[0]);
    printf("%s\n", name);
  }
  return 0;
}

// 判断字符串是否为回文（忽略大小写，全部按小写比较）
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

// 计算把串变成回文至少要改多少对字符（考虑大小写的不同）
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

/* 高效拼接多个字符串（手写 strcat，避免重复遍历）
 * 把 src 拼接到 dest 后面，使用外部维护的长度 *plen：
 *   char ans[5000005] = {0};
 *   int len = 0;
 *   append_string(ans, &len, "abc");    注意&！！！！
 *   append_string(ans, &len, "xyz");
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

// 正确的 swap（按指针传参）
void swap_int(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void swap_ll(long long *a, long long *b) {
  long long tmp = *a;
  *a = *b;
  *b = tmp;
}

// 统计数组 a[0..n-1] 中所有 int 的所有字节里，数值等于 114 的字节个数。
int count_114_bytes_in_ints(const int *a, int n) {
  int total = 0;
  for (int i = 0; i < n; ++i) {
    unsigned char *p = (unsigned char *)&a[i]; // 关键
    for (int j = 0; j < 4; ++j) {
      if (p[j] == 114)
        ++total;
    }
  }
  return total;
}

// 比较两个连续区间 s[l1..r1-1], t[l2..r2-1] 是否完全相等
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

// 去掉字符串末尾所有空白字符（空格 / '\n' / '\t' 等）
void rstrip(char *s) {
  int len = (int)strlen(s);
  while (len > 0 && isspace((unsigned char)s[len - 1])) {
    s[--len] = '\0';
  }
}

// 去掉字符串开头和末尾的空白字符，结果放回原串
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

/*
 * 统计某个字符在字符串中出现的次数
 * 示例：统计 '1' 的个数，用于很多二进制/位运算 + 字符串题：
 *   char s[1000005];
 *   scanf("%s", s);
 *   int ones = count_char(s, '1');
 */
int count_char(const char *s, char ch) {
  int cnt = 0;
  for (int i = 0; s[i] != '\0'; ++i) {
    if (s[i] == ch)
      ++cnt;
  }
  return cnt;
}

// 化为字符串标准型（如果是偶数，求两个子串标准型。按照字典序排列，将字典序小放前面，拼接在一起）
void cal(char *s, int len, char *result) {
  if (len % 2 == 1) {
    memcpy(result, s, len);
    result[len] = '\0';
    return;
  }
  int mid = len / 2;
  cal(s, mid, result);
  cal(s + mid, mid, result + mid);
  int cmp = strncmp(result, result + mid, mid);
  if (cmp <= 0) {
    result[len] = '\0';
  } else { // 左右交换
    char temp[2005];
    memcpy(temp, result + mid, mid);
    memcpy(temp + mid, result, mid);
    temp[len] = '\0';
    memcpy(result, temp, len + 1);
  }
}

/*
 * 功能：在原字符串 s1 中屏蔽敏感词 key（用 '*' 覆盖），忽略大小写。
 * 要求：s2 是 s1 的“全小写副本”，长度与 s1 一样，且以 '\0' 结尾。
 */
void mask_sensitive(char s1[], const char s2[], const char key[]) {
  char lower_key[64];
  int keylen = strlen(key);
  for (int i = 0; i < keylen; ++i) // 把关键词也转成小写，保证忽略大小写匹配
    lower_key[i] = (char)tolower((unsigned char)key[i]);
  lower_key[keylen] = '\0';
  const char *p = s2; // 在小写串 s2 里找
  while ((p = strstr(p, lower_key)) != NULL) {
    int pos = (int)(p - s2); // 关键字在 s2 中的起始下标
    for (int i = 0; i < keylen; ++i)
      s1[pos + i] = '*'; // 在原串 s1 中对应位置改成 '*'
    p++;                 // 从下一个字符继续找，避免死循环
  }
}