#include <stdio.h>
#include <string.h>
int main() {
  int n;
  scanf("%d", &n);
  while (n--) {
    int m, k;
    long long sum = 0, t = 1;
    char s[100005];
    scanf("%d %d ", &m, &k);
    gets(s + 1);
    int len = strlen(s+1);
    for (int i = len; i >= 1; i--) {
      sum = (sum + t * (s[i] - '0')) % k;
      t = (t * m) % k;
    }
    printf("%lld\n", sum);
  }
}