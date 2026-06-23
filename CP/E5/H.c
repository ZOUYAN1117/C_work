#include <math.h>
#include <stdio.h>
#include <stdlib.h>
long long x[100001], y[100001];
int main() {
  int n;
  scanf("%d\n", &n);
  for (int i = 1; i < n; i++) {
    scanf("(%lld,%lld)\n", &x[i], &y[i]);
  }
  scanf("(%lld,%lld)", &x[n], &y[n]);
  long long area = 0;
  for (int i = 3; i <= n; i++) {
    area += llabs((x[i - 1] - x[1]) * (y[i] - y[1]) - (x[i] - x[1]) * (y[i - 1] - y[1]));
  }
  if(area % 2 == 0)
    printf("%lld.0\n", area / 2);
  else
    printf("%lld.5\n", area / 2);
}