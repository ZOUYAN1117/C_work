#include <stdio.h>
unsigned int f(unsigned int a) {
  unsigned int sum;
  sum = a * (a + 2) + 9;
  return sum;
}
unsigned int g(unsigned int b) {
  unsigned int sum = 0;
  sum = f(b) + f(2 * f(b + 3)) + 3 * b;
  return sum;
}
unsigned int h(unsigned int c, unsigned int d) {
  unsigned int sum = 0;
  sum = g(f(c) + d) + f(3 * g(4 * c + d)) + g(f(f(c - d)));
  return sum;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    unsigned int x, y;
    scanf("%u %u", &x, &y);
    unsigned int res = h(x, y);
    printf("%u\n", res);
  }
  return 0;
}