#include <stdio.h>
int a, b, c;
int win(int x, int y) {
  if ((x == 2 && y == 1) || (x == 1 && y == 0) || (x == 0 && y == 2))
    return 1;
  else
    return 0;
}
int main() {
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    int a1, a2, a3;
    scanf("%d%d%d", &a1, &a2, &a3);
    if ((a1 == a2 && a2 == a3) || (a1 != a2 && a2 != a3 && a3 != a1))
      continue;
    else if (a1 == a2) {
      if (win(a1, a3)) {
        a++;
        b++;
      } else
        c++;
    } else if (a2 == a3) {
      if (win(a2, a1)) {
        b++;
        c++;
      } else
        a++;
    } else if (a3 == a1) {
      if (win(a1, a2)) {
        c++;
        a++;
      } else
        b++;
    }
  }
  printf("%d %d %d", a, b, c);
}