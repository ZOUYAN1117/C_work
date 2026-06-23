#include <stdio.h>
int f1(int x) { return -~x++; }
int f2(int x) { return ~-x++; }
int main() {
  int x;
  while (scanf("%d", &x) != EOF) {
    printf("%d %d\n", f1(x), f2(x));
  }
  return 0;
}