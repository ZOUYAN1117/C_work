#include <stdio.h>
int no5(int x) {
  if (x == 0)
    return 1;
  if (x % 10 == 5)
    return 0;
  return no5(x / 10);
}
int main() {
  int n, sum = 0;
  scanf("%d", &n);
  for (int i = 0; i <= n / 3; i++) {
    for (int j = i; j <= n / 2; j++) {
        if (i + j + j > n)
          break;
      for (int k = j; k <= n; k++) {
        if (i + j + k == n && no5(i) && no5(j) && no5(k)) {
          sum++;
        }
        if (i + j + k > n)
          break;
      }
    }
  }
  printf("%d\n", sum);
}