#include <stdio.h>
unsigned int a[1005];
int main() {
  int m, n;
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= n; i++) {
    unsigned int t;
    scanf("%u", &t);
    int p = t % m;
    int j = 0;
    do {
      if (!a[p + j]) {
        a[p + j] = t;
        break;
      }
      if (j == m - 1 - p) {
        j = -p - 1;
      }
      j++;
    } while (j != 0);
  }
  for (int i = 0; i <= m - 1; i++) {
    printf("%u ", a[i]);
  }
}