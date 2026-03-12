#include <stdio.h>
#include <string.h>
char s[22];
int main() {
  int n;
  scanf("%d", &n);
  while (n--) {
    scanf(" ");
    gets(s);
    for (int i = 2; i <= 20; i++) {
      if (i != 6 && i != 11 && i != 16) {
        int temp;
        if (s[i] >= '0' && s[i] <= '9') {
          temp = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
          temp = s[i] - 'a' + 10;
        }
        if (temp / 8 == 1) {
          printf("1");
          temp -= 8;
        } else
          printf("0");
        if (temp / 4 == 1) {
          printf("1");
          temp -= 4;
        } else
          printf("0");
        if (temp / 2 == 1) {
          printf("1");
          temp -= 2;
        } else
          printf("0");
        if (temp == 1) {
          printf("1");
        } else
          printf("0");
        printf(" ");
      }
    }
    printf("\n");
  }
}