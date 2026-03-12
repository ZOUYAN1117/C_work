#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  int months[14] = {0,  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 30}; // 定义每月天数
  int temp;
  int y, mon, d;
  int tempday;
  while((scanf("%d", &temp))!=EOF){
    y = temp / 10000;
    mon = temp % 10000 / 100;
    d = temp % 100;
    d +=99;
    tempday = months[mon] + (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && mon == 2);
    while (d > tempday) // 如果天数超过该月份的天数
    {
      d -= tempday;
      mon++; // 天数减去该月天数，月份加一
      if(((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)){
        y += (mon - 1) / 13;
      mon = (mon - 1) % 13 + 1;
      }
      else {
        y += (mon - 1) / 12;
      mon = (mon - 1) % 12 + 1;
      }
      tempday = months[mon] + (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && (mon == 2));
    }
    printf("%04d%02d%02d\n", y, mon, d);
  }
  return 0;
}

// scanf("%",&);
// printf("%",);
// for(int i=1;i<=n;i++)