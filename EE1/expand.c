#include <stdio.h>
#include <string.h>
char str[1000] = {},a[1000]={};
int main() {
  scanf("%s", str);
  int j = 0;
  for (int i = 0; i < strlen(str); i++) {
      if (str[i + 1] == '-' && str[i] < str[i + 2] && ((str[i] >= 'a' && str[i+2] <= 'z') || (str[i] >= 'A' && str[i+2] <= 'Z') || (str[i] >= '0' && str[i+2] <= '9'))) {
        for (char c = str[i],d=str[i+2]; c < d; c++) {
          a[j++] = c;
        }
        i++;
      }
     else
      a[j++] = str[i];
  }
  a[j] = '\0';
  printf("%s\n", a);
}