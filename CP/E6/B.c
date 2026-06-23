#include <stdio.h>
#include <string.h>
char a[1005][105];
int main() {
  int n = 1;
  while (scanf("%s", a[n]) != EOF) {
    if (n == 1) {
      printf("Delicious!\n");
      n++;
      continue;
    }
    for (int i = 1; i < n; i++) {
      int result = strcmp(a[i], a[n]);
      if (result == 0) {
        printf("Not Applicable\n");
        break;
      }
      if (i == n - 1)
        printf("Delicious!\n");
    }
    n++;
  }
}