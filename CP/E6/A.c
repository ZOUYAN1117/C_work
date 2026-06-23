#include <stdio.h>
int a[105][105];
int main() {
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= m; j++) {
      printf("%lld ", (long long)(a[j][i]) + a[i][j]);
    }
    printf("\n");
  }
  return 0;
}