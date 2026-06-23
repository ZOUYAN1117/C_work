#include <stdio.h>
int a[19] = {0, 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
char b[19] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
int main() {
  int n;
  scanf("%d", &n);
  getchar();
  for (int i = 1; i <= n; i++) {
    int sum = 0;
    for (int j = 1; j <= 17; j++) {
      char t = getchar();
      sum += (t - '0') * a[j];
    }
    sum %= 11;
    if (b[sum] == getchar()) {
      printf("YES\n");
    } else
      printf("NO\n");
    getchar();
  }
}