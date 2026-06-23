#include <stdio.h>
int main() {
  int n;
  double a[2002];
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &a[i]);
  }
  int i, j, swapFlag;
  double hold;
  for (i = 1; i < n; i++) {
    swapFlag = 0;
    for (j = 0; j < n - i; j++) {
      if (a[j] > a[j + 1]) {
        swapFlag = 1;
        hold = a[j];
        a[j] = a[j + 1];
        a[j + 1] = hold;
      }
    }
    if (swapFlag == 0)
      break;
  }
  for (i = 0; i < n; i++) {
    printf("%.4f ", a[i]);
  }
  return 0;
}