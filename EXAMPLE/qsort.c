// 小数 升序（数组从0开始）
#include <stdio.h>
#include <stdlib.h>
double arr[2010];
int compare(const void *a, const void *b) {
  double num_a = *(double *)a;
  double num_b = *(double *)b;
  if (num_a < num_b) {
    return -1;
  } else if (num_a > num_b) {
    return 1;
  } else {
    return 0;
  }
}
int main() {
  int n = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &arr[i]);
  }
  qsort(arr, n, sizeof(double), compare);
  for (int i = 0; i < n; i++) {
    printf("%.4lf ", arr[i]);
  }
  return 0;
}

// int 升序（数组从0开始）
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

// long long 升序
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

/*
 * 字符串排序 （字典序）
 *   char s[1010][110];
 *   qsort(s, n, sizeof(s[0]), cmp_str);
 */
int cmp_str(const void *p, const void *q) {
  const char *a = (const char *)p;
  const char *b = (const char *)q;
  int t = strcmp(a, b); // 升序
  if (t < 0)
    return -1;
  if (t > 0)
    return 1;
  return 0;
}

// 两关键词排序
// int a[500005][2];
// qsort(a, n, 2 * sizeof(int), cmp2);
int cmp2(const void *p, const void *q) {
  const int *a = (const int *)p;
  const int *b = (const int *)q;
  if (a[0] < b[0]) // 先按 a[0] 升序
    return -1;
  if (a[0] > b[0])
    return 1;
  if (a[1] < b[1])
    return -1;
  if (a[1] > b[1])
    return 1;
  return 0;
}

// 编号排序（间接排序，用另外一个数组指标对待排序数组排序）
// 以len升序排序，从小到大输出原对应位置
int len[1000], id[1000];
for (int i = 0; i < n; i++)
  id[i] = i;
int cmp(const void *p, const void *q) {
  int i = *(const int *)p;
  int j = *(const int *)q;
  if (len[i] < len[j]) // 长度升序
    return -1;
  if (len[i] > len[j])
    return 1;
  return 0;
}
qsort(id, n, sizeof(int), cmp);