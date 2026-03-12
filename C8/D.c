#include <stdio.h>
int main() {
  int n;
  scanf("%d\n", &n);
  for (int i = 1; i <= n; i++) {
    char X, L;
    scanf("\n");
    scanf("%c~%c", &X, &L);
    if (L == 'B') {
      double x, y;
      scanf("(%lf,%lf)", &x, &y);
      double E = x * y, D = x * y * (1 - y);
      printf("E(%c)=%.4lf,D(%c)=%.4lf\n", X, E, X, D);
    } else if (L == 'P') {
      double x;
      scanf("(%lf)", &x);
      double E = x, D = x;
      printf("E(%c)=%.4lf,D(%c)=%.4lf\n", X, E, X, D);
    } else if (L == 'G') {
      double x;
      scanf("(%lf)", &x);
      double E = 1.0 / x, D = (1 - x) / x / x;
      printf("E(%c)=%.4lf,D(%c)=%.4lf\n", X, E, X, D);
    } else if (L == 'U') {
      double x, y;
      scanf("(%lf,%lf)", &x, &y);
      double E = (x + y) / 2, D = (y - x) * (y - x) / 12;
      printf("E(%c)=%.4lf,D(%c)=%.4lf\n", X, E, X, D);
    } else {
      double x, y;
      scanf("(%lf,%lf)", &x, &y);
      double E = x, D = y;
      printf("E(%c)=%.4lf,D(%c)=%.4lf\n", X, E, X, D);
    }
  }
}