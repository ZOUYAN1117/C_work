#include <stdio.h>
#include <stdlib.h>
int a[500005][2];
int x(const int *a1, const int *a2) {
  if (a1[1] < a2[1])
    return -1;
  else if (a1[1] > a2[1])
    return 1;
  else if (a1[0] < a2[0])
    return -1;
  else if (a1[0] > a2[0])
    return 1;
  else
    return 0;
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i][0]);
    unsigned int t = a[i][0];
    for (int j = 0; j <= 31; j++) {
      a[i][1] += (j + 1) * ((t >> j) & 1);
    }
  }
  qsort(a, n, 2 * sizeof(int), x);
  for (int i = n - 1; i >= 0; i--) {
    printf("%d\n", a[i][0]);
  }
}