#include <stdio.h>
#include <string.h>
char a[100005], b[5000005];
int main() {
  int n, p, q, t = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", a);
    int j = 0;
    for (; a[j] != '\0'; j++) {
      b[t] = a[j];
      t++;
    }
  }
  scanf("%d%d", &p, &q);
  char temp;
  temp = b[p - 1];
  b[p - 1] = b[q - 1];
  b[q - 1] = temp;
  for (int i = 0; b[i] != '\0'; i++) {
    printf("%c", b[i]);
  }
}