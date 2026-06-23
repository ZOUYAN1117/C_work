#include <stdio.h>
int rec_bin_find(long long b[], int key, int low, int high) {
  int mid;
  if (low > high)
    return -1;
  mid = (low + high) / 2;
  if (key == b[mid])
    return mid;
  else if (key < b[mid])
    return rec_bin_find(b, key, low, mid - 1);
  else
    return rec_bin_find(b, key, mid + 1, high);
}
long long b[100005];
char s[100005][22];
int main() {
  int m, n;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &b[i]);
    getchar();
    scanf("%s", s[i]);
  }
  for (int i = 1; i <= m; i++) {
    long long temp;
    scanf("%lld", &temp);
    int t = rec_bin_find(b, temp, 0, n - 1);
    if (t == -1) {
      printf("Not find!\n");
    } else
      printf("%s\n", s[t]);
  }
}