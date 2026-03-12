#include <stdio.h>
#include <string.h>
char s[105];
int main() {
  int num = 0;
  while (scanf("%s", s) != EOF) {
    int len = strlen(s);
    int flag = 1;
    if (len == 2 && s[0] == '<' && s[len - 1] == '>') {
      printf("Not an Arrow\n");
      continue;
    }
    if (s[0] != '<' && s[len - 1] != '>') {
      printf("Not an Arrow\n");
      continue;
    }
    if (s[0] == '=' && s[len - 1] == '=') {
      printf("Not an Arrow\n");
      continue;
    }
    for (int i = 1; i <= len - 2; i++) {
      if (s[i] != '=') {
        printf("Not an Arrow\n");
        flag--;
        break;
      }
    }
    if (flag == 0) {
      continue;
    }
    if (s[0] == '<' && s[len - 1] == '=') {
      printf("Left Arrow\n");
    } else if (s[0] == '=' && s[len - 1] == '>') {
      printf("Right Arrow\n");
    } else if (s[0] == '<' && s[len - 1] == '>') {
      printf("Bidirectional Arrow\n");
    } else
      printf("Not an Arrow\n");
  }
}