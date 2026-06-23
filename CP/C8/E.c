#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double pi = 3.1415926;
long long x[200005], y[200005];
double Sa(int n) {
  for (int i = 1; i <= n; i++) {
    scanf("%lld %lld", &x[i], &y[i]);
  }
  x[n + 1] = x[1];
  y[n + 1] = y[1];
  double s = 0;
  for (int i = 1; i <= n; i++) {
    double L;
    L = (x[i] - x[i + 1]) * (x[i] - x[i + 1]) +
        (y[i] - y[i + 1]) * (y[i] - y[i + 1]);
    L = sqrt(fabs(1.0 * L));
    s += L;
  }
  return s;
}
int main() {
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; i++) {
    int n;
    long long r;
    scanf("%d %lld", &n, &r);
    double sum = Sa(n);
    double Sb = 2 * pi * r;
    Sb = sum + Sb;
    printf("%.15lf\n", Sb);
  }
}