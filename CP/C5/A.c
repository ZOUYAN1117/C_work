#include <math.h>
#include <stdio.h>

int main() {
  int n, y;
  long long x;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld %d", &x, &y);
    double ans = (double) pow (x, 1.0 / y);
    printf("%.5f\n", ans);
  }
}