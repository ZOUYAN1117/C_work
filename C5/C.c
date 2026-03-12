#include <stdio.h>
long long a[50] = {2, 1};
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 2; i < 51; i++) {
    a[i] = a[i - 1] + a[i - 2];
  }
  for (int i = 0; i < n; i++) {
    int b;
    scanf("%d", &b);
    printf("%lld\n", a[b]);
  }
}