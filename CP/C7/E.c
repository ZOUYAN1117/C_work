#include <stdio.h>
#include <string.h>
char s[2005], s1[2005], c[15][55];
char p[2005];
int main() {
  gets(s1);
  for (int j = 0; s1[j] != '\0'; j++) {
    if (s1[j] >= 'A' && s1[j] <= 'Z')
      s[j] = s1[j] + 'a' - 'A';
    else
      s[j] = s1[j];
  }
  int n, len[15], i = 0;
  scanf("%d", &n);
  int n0 = n;
  while (n0--) {
    scanf("%s", c[i]);
    len[i] = strlen(c[i]);
    for (int j = 0; c[i][j] != '\0'; j++) {
      if (c[i][j] >= 'A' && c[i][j] <= 'Z')
        c[i][j] = c[i][j] + 'a' - 'A';
    }
    i++;
  }
  for (i = 0; s[i] != '\0'; i++) {
    for (int j = 0; j <= n; j++) {
      if (strncmp(s + i, c[j], len[j]) == 0) {
        for (int q = 0; q < len[j]; q++)
          p[i + q] = '*';
        break;
      }
    }
  }
  for (i = 0; s[i] != '\0'; i++) {
    if (p[i] != '*')
      printf("%c", s1[i]);
    else
      printf("%c", p[i]);
  }
}