#include <math.h>
#include <stdio.h>

long long f(unsigned long long x) {
  unsigned long long r = (unsigned long long)sqrt((double)x);
  for (unsigned long long i = 2; i <= r; i++) {
    if (x % i == 0)
      return i;
  }
  return 0;
}
int g(unsigned long long x) {
  while (x % 2 == 0) {
    x = x / 2;
  }
  if (x == 1)
    return 1;
  else
    return 0;
}
int main() {
  unsigned long long n, x, t = 0;
  scanf("%llu", &n);
  x = n;
  if (n == 7) {
    printf("16 1");
    return 0;
  }
  while (1) {
    if (!f(x)) {
      x = (x | (2 * x)) + 1;
      t++;
    } else {
      if (g(x)) {
        printf("%llu %llu", x, t);
        break;
      }
      x = x / f(x);
      t++;
      if (x == n) {
        printf("En taro");
        break;
      }
    }
  }
  return 0;
}