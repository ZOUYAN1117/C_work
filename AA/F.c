#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[200005];
int is_palindrome_ci(const char *s) {
  int len = (int)strlen(s);
  int i = 0, j = len - 1;
  while (i <= j) {
    char a = s[i];
    char b = s[j];
    if(i==j){
        if (a != 'o' && a != 'v' && a != 'x' && a != 'w') 
        return 0;
    }
    if (a != 'b' && a != 'd' && a != 'p' && a != 'q') {
      if (a != b)
        return 0;
    }
    switch (a) {
    case 'b':
      if (b != 'd')
        return 0;
      break;
    case 'd':
      if (b != 'b')
        return 0;
      break;
    case 'p':
      if (b != 'q')
        return 0;
      break;
    case 'q':
      if (b != 'p')
        return 0;
      break;
    }
    ++i;
    --j;
  }
  return 1;
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    if (is_palindrome_ci(s))
      printf("yes\n");
    else
      printf("no\n");
  }
  return 0;
}

// scanf("%",&);
// printf("%",);
// for(int i=1;i<=n;i++)