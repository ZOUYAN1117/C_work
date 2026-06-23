#include <math.h>
#include <stdio.h>
int power(int a, int b) {
  int res = 1;
  for (int i = 1; i <= b; i++) {
    res *= a;
  }
  return res;
}
char a[6600][6600];
void c(int x, int y, int k) {
  a[x][y] = 'x';
  a[x + 1][y + 1] = '\\';
  a[x + 1][y - 1] = '/';
  a[x - 1][y + 1] = '/';
  a[x - 1][y - 1] = '\\';
  if (k == 1) {
    return;
  }
  int m = power(3, k - 1);
  c(x, y, k - 1);
  c(x + m, y + m, k - 1);
  c(x + m, y - m, k - 1);
  c(x - m, y + m, k - 1);
  c(x - m, y - m, k - 1);
}
int main() {
  int t;
  scanf("%d", &t);
  if (t == 0) {
    printf("x\n");
    return 0;
  }
  int n = pow(3, t);
  c(n / 2 + 1, n / 2 + 1, t);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (a[i][j] == 'x' || a[i][j] == '/' || a[i][j] == '\\') {
        printf("%c", a[i][j]);
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}