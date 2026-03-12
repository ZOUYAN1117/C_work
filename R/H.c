#include <stdio.h>
#include <string.h>
char s[10005];
int main() {
  scanf("%s", s);
  int len = strlen(s), sum = 1;
  char flag = s[0];
  for (int i = 1; i <= len; i++) {
    if (flag != s[i] && sum <= 1) {
      sum = 1;
      printf("%c", flag);
      flag = s[i];
    } else if (flag != s[i] && sum > 1) {
      printf("%c%d", flag, sum);
      sum = 1;
      flag = s[i];
    } else
      sum++;
  }
}