#include <stdio.h>
unsigned int a[1024];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    long long temp;
    scanf("%lld", &temp);
    int t = 0;
    while (temp) {
      t |= 1 << (temp % 10);
      temp /= 10;
    }
    a[t]++;
  }
  long long sum = 0;
  for (int i = 0; i <= 1022; i++)
    for (int j = i + 1; j <= 1023; j++)
      if ((i | j) == 1023)
        sum += 1ll * a[i] * a[j];
  sum += 1ll * a[1023] * (a[1023] - 1) / 2;
  printf("%lld", sum);
}