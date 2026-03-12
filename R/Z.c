#include <stdio.h>
int a[3000005];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int temp;
    scanf("%d", &temp);
    a[temp]++;
  }
  if (a[n] == 0) {
    printf("0");
    return 0;
  }
  int sum = 0;
  long long t = 1;
  for (int i = 1; i <= n; i++) {
    long long q = 1;
    for (int j = i - sum; j > i - sum - a[i]; j--)
      q = q * j % 993244853;
    if (a[i] == 0)
      q = 1;
    t = t * q % 993244853;
    sum += a[i];
    if (sum > i) {
      printf("0");
      return 0;
    }
  }
  printf("%lld", t);
}