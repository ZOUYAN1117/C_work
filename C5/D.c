#include <math.h>
#include <stdio.h>
int f(long long x) {
  if (x < 2)
    return 0;
  long long r = (long long)sqrt((double)x);
  for (long long i = 2; i <= r; i++) {
    if (x % i == 0)
      return 0;
  }
  return 1;
}

int main() {
  int T;
  long long n;
  scanf("%d", &T);
  while (T--) {
    scanf("%lld", &n);
    while (!f(n)) {
      n++;
    }
    printf("%lld\n", n);
  }
  return 0;
}