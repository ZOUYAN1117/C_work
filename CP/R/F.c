#include <stdio.h>
int max(int a, int b, int c) {
  if (a >= b) {
    if (a >= c)
      return a;
    else
      return c;
  } else {
    if (b >= c)
      return b;
    else
      return c;
  }
}
int a[135][135];
int main() {
  int m, n;
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= m / 3; i++) {
    for (int t = 1; t <= 3; t++) {
      for (int j = 1; j <= n / 3; j++) {
        int a1, a2, a3;
        scanf("%d%d%d", &a1, &a2, &a3);
        a1 = max(a1, a2, a3);
        if (t == 1)
          a[i][j] = a1;
        else if (a1 >= a[i][j])
          a[i][j] = a1;
      }
    }
  }
  for (int i = 1; i <= m / 3; i++) {
    for (int j = 1; j <= n / 3; j++)
      printf("%d ", a[i][j]);
    printf("\n");
  }
}