#include <stdio.h>
int a[1005];
int main() {
  int n, x;
  scanf("%d%d", &n, &x);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  a[0] = a[n];
  for (int i = 1; i <= n; i++) {
    if (a[i] == x) {
      printf("%d", a[i - 1]);
      break;
    }
    if (i == n)
      printf("-1");
  }
}