//高精度除法
#include <stdio.h>
long long ans[105];
int main() {
  long long a, b, n;
  scanf("%lld%lld%lld", &a, &b, &n);
  ans[0] = a / b;
  ans[1] = (a % b) * 10;
  for (int i = 1; i <= n + 1; i++) {
    ans[i + 1] = (ans[i] % b) * 10;
    ans[i] = ans[i] / b;
  }
  if (ans[n + 1] >= 5) // 四舍五入
  {
    ans[n] += 1;
    for (int i = n; i > 0; i--) // 对每一位小数进行进位处理
    {
      ans[i - 1] += ans[i] / 10; // 第 i 位满10，第 i-1 位加一
      ans[i] %= 10;              // 第 i 位进一后对 10 取模
    }
  }
  printf("%lld.", ans[0]);
  for (int i = 1; i <= n; i++)
    printf("%lld", ans[i]);
  return 0;
}