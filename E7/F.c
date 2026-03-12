#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *a[3000] = {NULL};
int main() {
  int n, q = 1;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int op;
    char s[10005];
    scanf("%d", &op);
    if (op == 1) {
      scanf("%s", s);
      if (q == 1) {
        a[q] = malloc(strlen(s) + 1);
        strcpy(a[q], s);
        printf("Delicious!\n");
        q++;
        continue;
      }
      for (int i = 1; i < q; i++) {
        if (a[i] != NULL) {
          int result = strcmp(a[i], s);
          if (result == 0) {
            printf("Not Applicable\n");
            break;
          }
        }
        if (i == q - 1) {
          a[q] = malloc(strlen(s) + 1);
          strcpy(a[q], s);
          q++;
          printf("Delicious!\n");
          break;
        }
      }
    } else if (op == 2) {
      scanf("%s", s);
      for (int i = 1; i < q; i++) {
        if (a[i] != NULL) {
          int result = strcmp(a[i], s);
          if (result == 0) {
            free(a[i]);
            a[i] = NULL;
          }
        }
      }
    } else {
      char s1[10005];
      scanf("%s %s", s, s1);
      for (int i = 1; i < q; i++) {
        if (a[i] && strcmp(a[i], s) == 0) {
          char *tmp = realloc(a[i], strlen(a[i]) + strlen(s1) + 1);
          a[i] = tmp;
          strcat(a[i], s1);
        }
      }
    }
  }
}