#include <math.h>
#include <stdio.h>
#define eps 1e-8
int a[10005];
int main() {
  int n, q;
  double p, np;
  scanf("%d", &n);
  scanf("%lf", &p);
  np = n * p;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n - 1; i++) {
    for (int j = 1; j <= n - i; j++) {
      if (a[j] > a[j + 1]) {
        int t = a[j];
        a[j] = a[j + 1];
        a[j + 1] = t;
      }
    }
  }
  if (fabs(round(np) - np) < eps) {
    q = (int)round(np);
    printf("%.1f", (a[q] + a[q + 1]) / 2.0);
  } else {
    q = (int)floor(np) + 1;
    printf("%.1f", (double)a[q]);
  }
}