#include <stdio.h>
int p[1000005];
int comb[1000005][1000005], t[1000005];
long long q[1000005] = {1};
const long long P = 998442353;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 || j == i) { // 边界条件
        comb[i][j] = 1;
      } else { // 递推式（组合恒等式）
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % P;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    q[i] = 2 * q[i - 1] % P;
  }
  long long sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &p[i]);
    t[i] = 1 * q[n - i] % P;
    for (int j = 2; j <= i; j++) {
      t[i] += comb[i - 1][j - 1] * j * q[n - i] % P;
      t[i] %= P;
    }
    sum = (sum + p[i] * t[i]) % P;
  }
  sum += q[n] * 6 % P;
  printf("%lld", sum);
}