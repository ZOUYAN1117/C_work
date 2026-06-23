#include <math.h>
#include <stdio.h>

double dis(double x1, double y1, double z1, double x2, double y2, double z2) {
  return (double)sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) +
                      (z1 - z2) * (z1 - z2));
}
int main() {
  double xa, ya, za, xb, yb, zb, xc, yc, zc;
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf", &xa, &ya, &za, &xb, &yb, &zb, &xc, &yc,
          &zc);
    double bc = dis(xb, yb, zb, xc, yc, zc);
    double ab = dis(xa, ya, za, xb, yb, zb);
    double x = ((xa - xb) * (xc - xb) + (ya - yb) * (yc - yb) +
                (za - zb) * (zc - zb)) /
               (ab * bc);
    printf("%.5lf\n", (double)acos(x));
  }
}