#include <stdio.h>
#include <string.h>
char a[505][505];
int sa[505];
int main() {
  char c[505];
  scanf("%s", c);
  int n = strlen(c);
  for (int i = 0; i < n; i++) {
    int t = 0;
    for (int j = i; j < n; j++) {
      a[i][t] = c[j];
      t++;
    }
    a[i][t] = '\0';
    sa[i] = i;
  }
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (strcmp(a[sa[j]], a[sa[j + 1]]) > 0) {
        int t = sa[j];
        sa[j] = sa[j + 1];
        sa[j + 1] = t;
      }
    }
  }
  for (int i = 0; i < n; i++)
    printf("%d ", sa[i] + 1);
}