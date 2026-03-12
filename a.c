#include <stdio.h>
int s = 24;
const int MOD = 998244853;
int main() {
  int n, t;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &t);
    s = (s + t * (i + 1)) % MOD;
  }
  for (int i = 3; i <= n; i++)
    s = (s * 2) % MOD;
  printf("%d\n", n == 1 ? t + 12 : s);
  return 0;
}