#include <stdio.h>
#include <string.h>
char l[6], n[55];
long long len;
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int p, g, m, k, b;
    scanf("%[^ ]", l);
    scanf(" %[^[]", n);
    scanf("[%lld]", &len);
    scanf("%s", n);
    if (strcmp(l+1, "char") == 0)
      p = 1;
    else if (strcmp(l+1, "short") == 0)
      p = 2;
    else if (strcmp(l+1, "int") == 0)
      p = 4;
    else
      p = 8;
    len *= p;
    if (len / 1073741824 > 0) {
      g = len / 1073741824;
      len %= 1073741824;
      printf("%dGB ", g);
    }
    if (len / 1048576 > 0) {
      m = len / 1048576;
      len %= 1048576;
      printf("%dMB ", m);
    }
    if (len / 1024 > 0) {
      k = len / 1024;
      len %= 1024;
      printf("%dKB ", k);
    }
    b = len;
    if(b>0)
    printf("%dB", b);
    printf("\n");
  }
}