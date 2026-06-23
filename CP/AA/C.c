#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
double a, b;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lf%lf", &a, &b);
    if (a > b) {
      double c = sqrt(a * a - b * b);
      printf("%.3lf ", c);
    } else if (a < b) {
      double c = sqrt(b * b - a * a);
      printf("%.3lf ", c);
    }
    printf("%.3lf\n", hypot(a,b));
  }
  return 0;
}

// scanf("%",&);
// printf("%",);
// for(int i=1;i<=n;i++)