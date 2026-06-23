#include <stdio.h>
void optiBubSort(long long a[], int n) {
  int i, j, swapFlag, q = 0;
  long long hold;
  for (i = 1; i < n; i++) {
    swapFlag = 0;
    for (j = q; j < n - i; j++) {
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
}
long long a[1000005];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  optiBubSort(a, n);
  for (int i = 0; i < n; i++) {
    if (a[i] != a[i-1])
      printf("%lld ", a[i]);
  }
}