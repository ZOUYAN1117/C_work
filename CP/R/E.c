#include <stdio.h>
long long a, b, c, a0, b0, c0;
int main() {
  int n;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &n);
  for (int i = 1; i <= n; i++) {
    int op, k;
    scanf("%d%d", &op, &k);
    if (a == a0 || b == b0 || c == c0) {
      printf("0\n");
      continue;
    }
    if (op == 1) {
      if (k >= a0) {
        printf("%lld\n", (k - a0) * (b - b0) * (c - c0));
        a0 = k;
      } else
        printf("0\n");
    } else if (op == 2) {
      if (k >= b0) {
        printf("%lld\n", (a - a0) * (k - b0) * (c - c0));
        b0 = k;
      } else
        printf("0\n");
    } else {
      if (k >= c0) {
        printf("%lld\n", (a - a0) * (b - b0) * (k - c0));
        c0 = k;
      } else
        printf("0\n");
    }
  }
}