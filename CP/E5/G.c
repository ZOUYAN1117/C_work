#include <stdio.h>
long long t = 0;
int op, c = 0;
long long m[20] = {0};
long long f(int n) {
  t++;
  for (int i = 1; i <= c; i++) {
    printf("|   ");
  }
  printf("calculate begin f(%d)\n", n);
  c++;

  if (m[n] != 0 && op == 1) {
    c--;
    for (int i = 1; i <= c; i++) {
      printf("|   ");
    }
    printf("calculated before return f(%d) = %lld\n", n, m[n]);
    return m[n];
  }

  long long fn = 0;
  if (n == 3) {
    fn = 1;
  } else {
    for (int i = 3; i <= n; i++) {
      if (i == 3 || i == n) {
        fn += f(n - 1);
      } else {
        fn += f(n - i + 2) * f(i - 1);
      }
    }
  }
  if (op == 1) {
    m[n] = fn;
  }
  c--;
  for (int i = 1; i <= c; i++) {
    printf("|   ");
  }
  printf("calculate end return f(%d) = %lld\n", n, fn);
  return fn;
}
int main() {
  int n;
  scanf("%d%d", &op, &n);
  printf("answer f(%d) = %lld\n", n, f(n));
  printf("total function invoked count = %lld\n", t);
  return 0;
}