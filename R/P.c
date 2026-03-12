#include <stdio.h>
#include <string.h>
long long a[1005];
char s[10];
int main() {
  int m, n, max = 0;
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= m; i++) {
    int a0 = 1, b0 = 1;
    scanf("%d", &a0);
    if (getchar() == '\n')
      continue;
    if (getchar() == '\n') {
      if (n == 1)
        a[0] += a0;
      continue;
    }
    scanf("%d", &b0);
    if (n <= b0) {
      long long p = a0;
      for (int j = 0; j < n; j++) {
        p *= (b0 - j);
      }
      a[b0 - n] += p;
      if (max < b0 - n)
        max = b0 - n;
    }
  }
  int flag = -1;
  for (int i = 0; i <= max; i++) {
    if (a[i] != 0) {
      flag = i;
      break;
    }
  }
  if (flag == -1)
    printf("0");
  else {
    for (int i = max; i > flag; i--) {
      if (a[i] == 0)
        continue;
      else if (i != 1) {
        if (a[i] == 1)
          printf("x^%d+", i);
        else
          printf("%lldx^%d+", a[i], i);
      } else {
        if (a[i] == 1)
          printf("x+");
        else
          printf("%lldx+", a[i]);
      }
    }
    if (flag > 1) {
      if (a[flag] == 1)
        printf("x^%d", flag);
      else
        printf("%lldx^%d", a[flag], flag);
    } else if (flag == 1) {
      if (a[flag] == 1)
        printf("x");
      else
        printf("%lldx", a[flag]);
    } else if (flag == 0) {
      printf("%lld", a[flag]);
    }
  }
}