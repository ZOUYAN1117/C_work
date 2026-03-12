//查找数（多个重复）
#include <stdio.h>
int a[500005];
int main(void) {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) { // 第一个数是第0位，保证输入升序
    scanf("%d", &a[i]);
  }
  int x;
  scanf("%d", &x);

  int l = -1, r = n;
  while (r - l > 1) { // 查找左边界（第一个是x的数）
    int mid = (l + r) / 2;
    if (a[mid] < x)
      l = mid;
    else
      r = mid;
  }
  int lft = r;
  l = -1, r = n;
  while (r - l > 1) { // 查找右边界（第一个比x大的数）
    int mid = (l + r) / 2;
    if (a[mid] <= x)
      l = mid;
    else
      r = mid;
  }
  int rt = r;
  printf("%d\n", rt - lft);
}

//简单二分查找（不重复）
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