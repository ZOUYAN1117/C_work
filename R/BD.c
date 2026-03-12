#include <stdio.h>
char a = '0', t;
int main() {
  while ((t = getchar()) != EOF) {
    if (a == '%') {
      switch (t) {
      case '%':
        printf("%%\n");
        a = '0';
        break;
      case 'd':
        printf("int\n");
        a = '0';
        break;
      case 'f':
        printf("float\n");
        a = '0';
        break;
      case 's':
        printf("char[]\n");
        a = '0';
        break;
      case 'c':
        printf("char\n");
        a = '0';
        break;
      default:
        printf("FORMAT STRING ERR0R");
        return 0;
        break;
      }
    } else if (a == '\\') {
      switch (t) {
      case '\\':
        printf("\\\n");
        a = '0';
        break;
      case '\"':
        printf("\"\n");
        a = '0';
        break;
      case 'n':
      case 't':
        printf("space\n");
        a = '0';
        break;
      default:
        printf("FORMAT STRING ERR0R");
        return 0;
        break;
      }
    } else {
      if (t == '%') {
        a = '%';
        continue;
      }
      if (t == '\\') {
        a = '\\';
        continue;
      }
      if (t == ' ') {
        printf("space\n");
        continue;
      }
      printf("%d\n", (int)t);
    }
  }
}