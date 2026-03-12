#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a[1005][1005];
int main() {
  int t, n, x, y;
  scanf("%d", &t);
  while (t--) {
    long long sum = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        scanf("%d", &a[i][j]);
        if (a[i][j] == 2) {
          x = i;
          y = j;
        }
      }
    int x0 = x, y0 = y;
    while (a[x0 + 1][y0 + 1] == 0&& x0 + 1<= n && x0 + 1>= 1 && y0 + 1<= n && y0 + 1>= 1) {
      sum++;
      x0++;
      y0++;
    }
    x0 = x, y0 = y;
    while (a[x0 + 1][y0] == 0&& x0 + 1<= n && x0 + 1>= 1 && y0<= n && y0>= 1) {
      sum++;
      x0++;
    }
    x0 = x, y0 = y;
    while (a[x0][y0 + 1] == 0&& x0<= n && x0>= 1 && y0 + 1<= n && y0 + 1>= 1) {
      sum++;
      y0++;
    }
    x0 = x, y0 = y;
    while (a[x0 - 1][y0 + 1] == 0&& x0 - 1<= n && x0 - 1>= 1 && y0 + 1<= n && y0 + 1>= 1) {
      sum++;
      x0--;
      y0++;
    }
    x0 = x, y0 = y;
    while (a[x0 - 1][y0] == 0&& x0 - 1<= n && x0 - 1>= 1 && y0<= n && y0>= 1) {
      sum++;
      x0--;
    }
    x0 = x, y0 = y;
    while (a[x0 - 1][y0 - 1] == 0&& x0 - 1<= n && x0 - 1>= 1 && y0 - 1<= n && y0 - 1>= 1) {
      sum++;
      x0--;
      y0--;
    }
    x0 = x, y0 = y;
    while (a[x0][y0 - 1] == 0&& x0<= n && x0>= 1 && y0 - 1<= n && y0 - 1>= 1) {
      sum++;
      y0--;
    }
    x0 = x, y0 = y;
    while (a[x0 + 1][y0 - 1] == 0 && x0 + 1<= n && x0 + 1>= 1 && y0 - 1<= n && y0 - 1>= 1) {
      sum++;
      x0++;
      y0--;
    }
    printf("%lld\n", sum);
  }
  return 0;
}

// scanf("%",&);
// printf("%",);
// for(int i=1;i<=n;i++)