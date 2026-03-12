#include <stdio.h>
int next_permutation(int j[], int n) {
  int l, r;
  for (l = n - 1; l > 0 && j[l] > j[l + 1]; l--)
    ;
  if (l == 0)
    return 0;
  for (r = n; j[r] < j[l]; r--)
    ;
  int tmp = j[l];
  j[l] = j[r];
  j[r] = tmp;
  for (l++, r = n; l < r; l++, r--) {
    tmp = j[l];
    j[l] = j[r];
    j[r] = tmp;
  }
  return 1;
}
void swap(int *a, int *b) {
  int temp;
  temp = *b;
  *b = *a;
  *a = temp;
}
long long munber(int p[], int n) {
  int sum = 0;
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
      if (p[i] > p[j])
        sum++;
  return (sum % 2 == 0) ? 1 : -1;
}
int m[10][10];
int J[10];
int main() {
  int n;
  long long sum = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      scanf("%d", &m[i][j]);
  for (int i = 1; i <= n; i++)
    J[i] = i;
  do {
    long long t = munber(J, n);
    int j = 1;
    for (int i = 1; i <= n; i++) {
      t *= m[j][J[i]];
      j++;
    }
    sum += t;
  } while (next_permutation(J, n));
  printf("%lld", sum);
  return 0;
}