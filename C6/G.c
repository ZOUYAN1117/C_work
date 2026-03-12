#include <stdio.h>
int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  long long dp[100005] = {0};
  dp[0] = 1;
  long long sum = 0;
  for (int i = 1; i <= n; i++) {
    if (i <= k)
      sum += dp[i - 1];
    else
      sum += dp[i - 1] - dp[i - k - 1];
    dp[i] = sum;
    dp[i] %= 100003;
  }
  printf("%lld\n", dp[n]);
  return 0;
}
