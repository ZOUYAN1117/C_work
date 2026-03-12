#include <stdio.h>
#include <string.h>

char s1[15], s2[15];
int main() {
  while ((scanf("%s%s", &s1, &s2)) != EOF) {
    int len1 = strlen(s1), len2 = strlen(s2);
    if (len1 == len2) {
      if (strcmp(s1, s2) < 0)
        printf("%s\n", s1);
      else
        printf("%s\n", s2);
    } else if (strcmp(s1, s2) < 0)
      printf("%s\n", s2);
    else
      printf("%s\n", s1);
  }
  return 0;
}

// scanf("%",&);
// printf("%",);
// for(int i=1;i<=n;i++)