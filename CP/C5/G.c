#include <math.h>
#include <stdio.h>
long long b(long long y) {
  long long n = 0;
  if (y == 1)
    return 0;
  if (y == 2)
    return 1;
  while (pow(2, n) < y)
    n++;
  return n;
}
long long c(long long y) {
  if (b(y) == 0 || b(y) == 1)
    return 1;
  return y - pow(2, b(y) - 1);
}
long long a(long long x, long long y) {
  if (x == 0)
    return 0;
  if (x == 1)
    return 1;
  return x + a(b(y), c(y));
}
int main() {
  long long n;
  scanf("%lld", &n);
  n++;
  printf("%lld", a(b(n), c(n)));
  return 0;
}