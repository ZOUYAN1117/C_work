#include <stdio.h>
#include <string.h>
char s[1005], str[1005];
int substr_equal(const char *s, int len, int l1, const char *t, int l2) {
  for (int i = 0; i < len; ++i) {
    if (s[l1 + i] != t[l2 + i])
      return 0;
  }
  return 1;
}
int main() {
  while (scanf("%s", s) != EOF) {
    int sum = 0;
    scanf("%s", str);
    int len0 = strlen(s), len1 = strlen(str);
    for (int i = 0; i < len0; i++) {
      if (substr_equal(s, len1, i, str, 0))
        sum++;
    }
    printf("%d\n", sum);
  }
}