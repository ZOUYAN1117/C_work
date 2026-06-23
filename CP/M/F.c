#include <stdio.h>
#include <stdlib.h>
char s[100005];
int sum[27][2];
int a[26];
char b[26] = {"ETAOINSHRDLCUMWFGYPBVKJXQZ"};
int x(const int *a1, const int *a2) {
  if (a1[0] < a2[0])
    return 1;
  else if (a1[0] > a2[0])
    return -1;
  else
    return 0;
}
int main() {
  int n = 0;
  while ((s[n] = getchar()) != EOF) {
    if (s[n] >= 'a' && s[n] <= 'z') {
      sum[s[n] - 'a'][0]++;
    } else if (s[n] >= 'A' && s[n] <= 'Z') {
      sum[s[n] - 'A'][0]++;
    }
    n++;
  }
  for (int i = 0; i <= 25; i++) {
    sum[i][1] = i;
  }
  qsort(sum, 26, 2 * sizeof(int), x);
  for (int i = 0; i <= 25; i++) {
    a[sum[i][1]] = b[i] - 'A';
  }
  for (int i = 0; i < n; i++) {
    if (s[i] >= 'a' && s[i] <= 'z') {
      printf("%c", 'a' + a[s[i] - 'a']);
    } else if (s[i] >= 'A' && s[i] <= 'Z') {
      printf("%c", 'A' + a[s[i] - 'A']);
    } else
      printf("%c", s[i]);
  }
}