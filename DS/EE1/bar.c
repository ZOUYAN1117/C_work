#include <stdio.h>
#include <string.h>
int main() {
  int sum[26] = {0}, max=0;
  char str[1000000]={};
  while (scanf("%s", str) != EOF) {
    for (int i = 0; i < strlen(str); i++) {
      sum[str[i] - 'a']++;
      if (sum[str[i] - 'a'] > max) {
        max = sum[str[i] - 'a'];
      }
    }
  }
  for (int i = max; i > 0; i--) {
    for (int j = 0; j < 26; j++) {
      if (sum[j] == i) {
        printf("*");
        sum[j]--;
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("%s", "abcdefghijklmnopqrstuvwxyz\n");
}