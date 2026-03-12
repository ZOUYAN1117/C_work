//年、月、日、时、分 转化为标准时间
#include <stdio.h>
int main() {
  int months[13] = {0,  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 定义每月天数
  int n;// 数据组数
  int y, mon, d, h, min;// 年、月、日、时、分
  int tempday;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d.%d.%d %d:%d", &y, &mon, &d, &h, &min); // 输入乱流中的时间
    h += (min / 60);
    min %= 60;
    d += (h / 24);
    h %= 24; // 计算正常的小时数、分钟数，并向天数进位
    y += (mon - 1) / 12;
    mon = (mon - 1) % 12 + 1; // 先将月份向年份进位
    tempday = months[mon] + (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && (mon == 2)); // 计算当前的y和mon对应的当月天数
    while (d > tempday) // 如果天数超过该月份的天数
    {
      d -= tempday;
      mon++; // 天数减去该月天数，月份加一
      y += (mon - 1) / 12;
      mon = (mon - 1) % 12 + 1; // 若月份大于12，则向年份进位
      tempday = months[mon] + (((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) && (mon == 2)); // 计算当前的y和mon对应的当月天数
    }
    printf("%04d.%02d.%02d %02d:%02d\n", y, mon, d, h, min);
  }
}