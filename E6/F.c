#include <stdio.h>
int d[1000005];
int main() {
  int n, m, t;
  scanf("%d%d%d", &n, &m, &t);
  for (int i = 1; i <= n; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    d[l]++;
    d[r + 1]--;
  }
  int flag = 0, sum = 0, ansl = 0, anst = 0, templ, tempt;
  for (int i = 0; i <= t; i++) {
    sum += d[i];
    if (sum <= m && i != t) {
      if (flag == 0) {
        tempt = i - 1;
        templ = 1;
        flag = 1;
      } else {
        templ++;
      }
    } else {
      flag = 0;
      if (templ > ansl) {
        anst = tempt;
        ansl = templ;
      }
    }
  }
  if (anst == -1)
    anst = 0;
  printf("%d", anst);
}