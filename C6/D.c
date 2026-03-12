#include <stdio.h>
#include <string.h>
int main() {
  int n;
  scanf("%d", &n);
  char str[2000005];
  while (n--) {
    scanf("%s", str);
    int len = strlen(str);
    int base;
    char last = str[len - 1];
    if (last >= '2' && last <= '9')
      base = last - '0';
    else
      base = last - 'a' + 10;
    long long result = 0;
    for (int i = 0; i < len - 1; i++) {
      int q;
      if (str[i] >= '0' && str[i] <= '9')
        q = str[i] - '0';
      else
        q = str[i] - 'a' + 10;
      result = result * base + q;
    }
    printf("%lld\n", result);
  }
  return 0;
}