#include <stdio.h>
int s[102] = {0}, d[102] = {0};
int main() {
  int n, m, n0;
  scanf("%d %d", &n, &m);
  n0 = n;
  int l = 1, num = 0, t = 1;
  while (n) {
    if (!s[l]) {
      num++;
      if (num == m) {
        s[l] = 1;
        if (l == 0)
          d[t] = n0;
        else
          d[t] = l;
        t++;
        num = 0;
        n--;
      }
    }
    l = (l + 1) % n0;
  }
  for (int i = 1; i <= n0; i++) {
    printf("%d ", d[i]);
  }
}