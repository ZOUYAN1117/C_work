#include <stdint.h>
#include <stdio.h>

int hash_ll(long long key) {
  const uint64_t mul = 11400714819323198485ULL;
  uint64_t x = (uint64_t)key;
  x *= mul;
  return (int)(x >> 32);
}
int main() {
  int n;
  long long x;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &x);
    int h = hash_ll(x);
    printf("%d\n", h);
  }
}