#include <math.h>
#include <stdio.h>

double x[1005], y[1005];
int main() {
  int n;
  double xb = 0, yb = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lf", &x[i]);
    xb += x[i];
  }
  for (int i = 1; i <= n; i++) {
    scanf("%lf", &y[i]);
    yb += y[i];
  }
  xb /= n;
  yb /= n;
  double sumx = 0, sumy = 0, sum = 0;
  for (int i = 1; i <= n; i++) {
    double tempx = 0, tempy = 0;
    tempx = x[i] - xb;
    tempy = y[i] - yb;
    sum += tempx * tempy;
    sumx += tempx * tempx;
    sumy += tempy * tempy;
  }
  sumx = sqrt(sumx);
  sumy = sqrt(sumy);
  double q=sum/sumx/sumy;
  printf("%.2lf",q);
}