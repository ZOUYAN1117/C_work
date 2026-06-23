#include <stdio.h>
void f(int n, int k, int j, int p) {
  if (n == 1) {
    printf("Electromagnet move disk 1 from %d to %d\n", k, j);
  } else {
    f(n - 1, k, p, j);
    printf("Electromagnet move disk %d from %d to %d\n", n, k, j);
    f(n - 1, p, j, k);
  }
}
int main() {
  int a, k, j, p;
  scanf("%d %d %d %d", &a, &k, &j, &p);
  f(a, k, j, p);
}