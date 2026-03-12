#include <stdio.h>
int main() {
  int n, a;
  long long sum = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a);
    unsigned char *p = (unsigned char *)&a;
    for (int i = 0; i < 4; i++)
      if (p[i] == 114)
        sum++;
  }
  printf("%lld", sum);
}