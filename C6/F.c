#include <stdio.h>
int lower_bound(int b[], int n, int key) {
  int low = 0, high = n;
  while (low < high) {
    int mid = (low + high) / 2;
    if (b[mid] < key)
      low = mid + 1;
    else
      high = mid;
  }
  return low;
}
int upper_bound(int b[], int n, int key) {
  int low = 0, high = n;
  while (low < high) {
    int mid = (low + high) / 2;
    if (b[mid] <= key)
      low = mid + 1;
    else
      high = mid;
  }
  return low;
}
int main() {
  int n;
  int a[500005];
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int key;
    scanf("%d", &key);
    int l = lower_bound(a, n, key);
    int r = upper_bound(a, n, key);
    printf("%d\n", r - l);
  }
  return 0;
}