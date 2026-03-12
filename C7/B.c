#include <stdio.h>
int h[43][43], s[43][43], a[43][43];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      scanf("%d", &h[i][j]);
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= m; j++)
      scanf("%d", &s[i][j]);
  for (int i = 1; i <= m - n + 1; i++)
    for (int j = 1; j <= m - n + 1; j++) {
      int sum = 0;
      for (int p = 1; p <= n; p++)
        for (int q = 1; q <= n; q++)
          sum += h[p][q] * s[i + p - 1][j + q - 1];
      a[i][j] = sum;
    }
  for (int i = 1; i <= m - n + 1; i++) {
    for (int j = 1; j <= m - n + 1; j++) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}