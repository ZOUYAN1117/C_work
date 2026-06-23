#include <stdio.h>
int main() {
  long long a, b, a0, b0, t, gcd, s = 0;
  scanf("%lld%lld", &a, &b);
  a0 = a;
  b0 = b;
  while (b != 0) {
    t = a % b;
    a = b;
    b = t;
  }
  gcd = a;
  s = a0 / gcd;
  s *= b0;
  printf("%lld", s);
}
