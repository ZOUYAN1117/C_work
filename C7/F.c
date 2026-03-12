#include <stdio.h>
#include <string.h>
char a[65536], s[1030];
int main() {
  int prt = 0, i = 0;
  gets(s);
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    switch (s[i]) {
    case '>':
      prt++;
      break;
    case '<':
      prt--;
      break;
    case '+':
      a[prt]++;
      break;
    case '-':
      a[prt]--;
      break;
    case '.':
      putchar(a[prt]);
      break;
    case ',':
      a[prt] = getchar();
      break;
    case '[':
      if (a[prt] == 0) {
        int nest = 1;
        while (nest > 0 && ++i < len) {
          if (s[i] == '[')
            nest++;
          else if (s[i] == ']')
            nest--;
        }
      }
      break;
    case ']':
      if (a[prt] != 0) {
        int nest = 1;
        while (nest > 0 && --i >= 0) {
          if (s[i] == ']')
            nest++;
          else if (s[i] == '[')
            nest--;
        }
      }
      break;
    }
  }
}