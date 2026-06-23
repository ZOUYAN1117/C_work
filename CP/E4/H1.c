#include <stdio.h>
#include <string.h>
#define MOD 998244353
#define M 1000005
char n[M];
long long pow9[M];
int main() {
  long long ans = 0;
  int L, i, d, r, c;
  scanf("%s", n);
  L = strlen(n);
  pow9[0] = 1;
  for (i = 1; i <= L; i++) {
    pow9[i] = pow9[i - 1] * 9 % MOD;
  }
  for (i = 0; i < L; i++) {
    d = n[i] - '0';
    r = L - i - 1;
    c = d;
    if (d > 5)
      c--;
    if (c > 0) {
      ans = (ans + c * pow9[r]) % MOD;
    }
    if (d == 5) {
      printf("%lld\n", ans % MOD);
      return 0;
    }
  }
  ans = (ans + 1) % MOD;
  printf("%lld\n", ans);
  return 0;
}