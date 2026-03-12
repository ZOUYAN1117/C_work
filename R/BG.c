#include <stdio.h>
#include <string.h>
char s1[50005], s2[55];
int a[50005];
int main() {
  int t, flag = 0;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    int q = 0;
    scanf("%s", s1);
    getchar();
    scanf("%s", s2);
    int len1 = strlen(s1), len2 = strlen(s2);
    for (int j = 0; j <= len1 - len2; j++) {
      for (int m = 0; m < len2; m++) {
        if (s2[m] != '*' && s2[m] != s1[j + m])
          break;
        else if (m == len2 - 1) {
          q++;
          a[q] = j + 1;
          flag = 1;
          break;
        }
      }
    }
    if (flag == 0)
      printf("0\n");
    else{
        printf("%d\n",q);
        for(int j=1;j<=q;j++) printf("%d ",a[j]);
        printf("\n");
    }
    flag = 0;
  }
}