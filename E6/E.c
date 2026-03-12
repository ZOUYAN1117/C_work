#include <stdio.h>
#include <string.h>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    char a[2005], b[2005];
    scanf("%s %s", a, b);
    int n = strlen(a);
    if (n % 2 == 1) {
      if (strcmp(a, b) == 0) {
        printf("Mocha Parfait!\n");
      } else {
        printf("qaq\n");
      }
    } else {
      char temp1[2005], temp2[2005], temp[2005];
      for (int i = 0; i < n / 2; i++) {
        temp1[i] = a[i];
        temp2[i] = a[i + n / 2];
        temp[i] = b[i];
      }
      temp1[n / 2] = '\0';
      temp2[n / 2] = '\0';
      if (strcmp(temp1, temp) == 0 || strcmp(temp2, temp) == 0) {
        printf("Mocha Parfait!\n");
      } else {
        printf("qaq\n");
      }
    }
  }
}