#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  int k;
  while ((scanf("%d", &k)) != EOF) {
    switch (k) {
    case 1:
      printf("Life cannot possibly bear splendid flowers from lies.\n");
      break;
    case 2:
      printf("Where is there dignity unless there is honesty?\n");
      break;
    case 3:
      printf("If one loses honesty, he(she) is going to lose everything.\n");
      break;
    case 4:
      printf("I promise I won't cheat in the exam.\n");
      break;
    }
  }
  return 0;
}

// scanf("%",&);
// printf("%",);
// for(int i=1;i<=n;i++)