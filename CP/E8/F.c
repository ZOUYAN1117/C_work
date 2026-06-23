#include <stdio.h>
int main() {
  long long a, b, c;
  scanf("%lld * %lld = %lld", &a, &b, &c);
  int a1 = a / 10000, a2 = (a / 1000) % 10, a3 = (a / 100) % 10,
      a4 = (a / 10) % 10, a5 = a % 10;
  int b1 = b / 10000, b2 = (b / 1000) % 10, b3 = (b / 100) % 10,
      b4 = (b / 10) % 10, b5 = b % 10;
  int c1 = c / 1000000, c2 = (c / 100000) % 10, c3 = (c / 10000) % 10,
      c4 = (c / 1000) % 10, c5 = (c / 100) % 10, c6 = (c / 10) % 10,
      c7 = c % 10;
  for (int x = 1; x <= 9; x++) {
    for (int y = 1; y <= 9; y++) {
      for (int z = 1; z <= 9; z++) {
        int map_a[10] = {0}, map_b[10] = {0}, map_c[10] = {0};
        int inv_map[10] = {0};
        int valid = 1;
        int digits_a[] = {a1, a2, a3, a4, a5};
        int digits_b[] = {b1, b2, b3, b4, b5};
        int digits_c[] = {c1, c2, c3, c4, c5, c6, c7};
        int mapping[10] = {-1};
        if (digits_a[0] == digits_b[0] && digits_a[0] == digits_c[0]) {
          int xa = x, ya = x, za = x;
          int all_valid = 1;
          for (int i = 0; i < 5; i++) {
            if (mapping[digits_a[i]] == -1) {
              mapping[digits_a[i]] = x;
            }
          }
          if (x * y == z && all_valid) {
            printf("%d * %d = %d\n", x, y, z);
            return 0;
          }
        }
      }
    }
  }
  return 0;
}