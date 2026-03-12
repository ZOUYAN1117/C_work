#include <stdio.h>
#include <string.h>
char str[1000] = {},f[1000] = {};
int num1[1000] = {}, num2[1000] = {};
int main() {
  fgets(str, 1000, stdin);
  int j = 0, k = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] != ' ')
      str[j++] = str[i];
  }
  str[j] = '\0';
  j = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      num1[j] *= 10;
      num1[j] += str[i] - '0';
    } else {
      f[k++] = str[i];
      j++;
    }
  }
  f[k] = '\0';
  int sum = 0, a, num;
  char b;
  a=num1[0];
  k=0;
  while (f[k] != '=') {
    num=num1[++k];
    if (f[k-1] == '*') {
      a *= num;
    } else if (f[k-1] == '/') {
      a /= num;
    } else if (f[k-1] == '+') {
      sum += a;
      a = num;
    } else if (f[k-1] == '-') {
      sum += a;
      a = -num;
    }
  }
  printf("%d\n", sum + a);
  return 0;

}