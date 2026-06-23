#include <stdio.h>
#include <string.h>
char s;
int main() {
  int n;
  scanf("%d\n", &n);
  while (n--) {
    int num = 0;
    while (1) {
      scanf("%c", &s);
      if (s == '\n')
        break;
      if (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u') {
        num++;
      }
    }
    if (num != 0)
      printf("Turing Complete!\n");
    else
      printf("Ex Machina\n");
  }
}