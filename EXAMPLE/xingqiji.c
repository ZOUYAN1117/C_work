//判断星期几
#include <stdio.h>
// 输入格式yyyymmdd
// eg：20241025
void printweek(int);
int getweek(int);
int main() {
  int timee;
  scanf("%d", &timee);
  if (!(timee >= 101 && timee <= 99991231)) {
    printf("wrong");
    return 0; 
  } //判断输入是否合法
  int w = getweek(timee);
  printweek(w);
  return 0;
}

int getweek(int ttime) {
  int year = ttime / 10000;          // 哪年
  int month = (ttime % 10000) / 100; // 哪月
  int day = ttime % 100;             // 哪日
  if (month < 3) {
    month += 12;
    year--;
  }
  int y = year % 100;
  int c = year / 100;
  int w =
      (y + (y / 4) + (c / 4) - 2 * c + (13 * (month + 1)) / 5 + day - 1) % 7;
  if (w < 0) {
    w += 7;
  }
  return w;
}

void printweek(int w) {
  switch (w) {
  case 0:
    printf("Sunday\n"); 
    break;
  case 1:
    printf("Monday\n"); 
    break;
  case 2:
    printf("Tuesday\n"); 
    break;
  case 3:
    printf("Wednesday\n");
    break;
  case 4:
    printf("Thursday\n"); 
    break;
  case 5:
    printf("Friday\n"); 
    break;
  case 6:
    printf("Saturday\n"); 
    break;
  }
}