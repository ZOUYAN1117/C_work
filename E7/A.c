#include <stdio.h>
#include <string.h>
char a[1005];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    gets(a);
    int p = strlen(a);
    for (int i = p - n; i <= p - 1; i++)
      printf("%c", a[i]);
    printf("\n");
  }
}