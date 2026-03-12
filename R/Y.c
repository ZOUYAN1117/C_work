#include <stdio.h>
long long a[3005];
int main() {
  int n;
  long long m;
  scanf("%d%lld", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%lld", &a[i]);
  if (a[n] + a[n - 1] + a[n - 2] < m || a[1] + a[2] + a[3] > m) {
    printf("0");
    return 0;
  }
  long long i1 = m / 3 + 1, i2 = m / 2 + 1;
  long long sum = 0;
  for (int i = 1; a[i] <= i1 && i <= n - 2; i++)
    for (int j = i + 1, k = n; j < k && j <= n - 1; j++) {
      if (a[i] + 2 * a[j] > m)
        break;
      while (j < k && a[i] + a[j] + a[k] > m)
        k--;
      if (a[i] + a[j] + a[k] < m)
        continue;
      if (a[j] == a[k]) {
        sum += (k - j + 1) * (k - j) / 2;
        break;
      }
      int j0=1,k0=1;
      while(a[j+1]==a[j]){
        j0++;
        j++;
      }
      while(a[k-1]==a[k]){
        k0++;
        k--;
      }
      sum+=j0*k0;
    }
  printf("%lld", sum);
}