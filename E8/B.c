#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char s[10005][1005];
int cmp(const void *a, const void *b) {
  const char(*sa)[1005] = a;
  const char(*sb)[1005] = b;
  return strcmp(*sa, *sb);
}
int main() {
  int n;
  if (scanf("%d", &n) != 1)
    return 0;
  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
  }
  qsort(s, n, sizeof(s[0]), cmp);
  for (int i = 0; i < n; i++) {
    printf("%s\n", s[i]);
  }
  return 0;
}