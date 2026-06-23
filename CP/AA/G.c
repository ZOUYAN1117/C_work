#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const double eps = 0.000000001;
double rad[300005], len[300005];
int id[300005];
int x[300005], y[300005];
int cmp(const void *p, const void *q) {
  int i = *(const int *)p;
  int j = *(const int *)q;
  if (fabs(rad[i] - rad[j]) <= eps) {
    if (fabs(len[i] - len[j]) <= eps)
      return 0;
    else {
      if (len[i] < len[j]) // 距离升序
        return -1;
      if (len[i] > len[j])
        return 1;
    }
  } else {
    if (rad[i] < rad[j]) // 角度升序
      return -1;
    if (rad[i] > rad[j])
      return 1;
  }
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &x[i], &y[i]);
    id[i] = i;
    // 求len
    len[i] = hypot(x[i], y[i]);
    // 求rad
    if (y[i] > 0)
      rad[i] = acos(1.0 * x[i] / len[i]);
    if (y[i] < 0)
      rad[i] = acos((-1.0) * x[i] / len[i]) + acos(-1);
    if (y[i] == 0) {
      if (x[i] > 0)
        rad[i] = 0;
      else
        rad[i] = acos(-1);
    }
  }
  qsort(id + 1, n, sizeof(int), cmp);
  for (int i = 1; i <= n; i++) {
    printf("(%d, %d)\n", x[id[i]], y[id[i]]);
  }
  return 0;
}