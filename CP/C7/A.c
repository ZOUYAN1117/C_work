#include <stdio.h>
char a[5003][103];
int main() {
  int i = 1;
  while (scanf("%s", a[i] + 1) != EOF)
    i++;
  for (int j = 1; j <= i; j++) {
    if (a[j][1] >= 'a' && a[j][1] <= 'z')
      a[j][1] = a[j][1] - 'a' + 'A';
    printf("%s\n", a[j] + 1);
  }
}