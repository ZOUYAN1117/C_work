// 高效率判断日期是否合法 输入：yyyymmdd
int dayof[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int isleapyear(int n) { return (n % 400 == 0 || (n % 100 != 0 && n % 4 == 0)); } // 二月是否多一天（判断闰年）
int checkdate(int x) // 判断x是不是合法的日期
{
  int y = x / 10000;
  int m = x / 100 % 100;
  int d = x % 100;
  if (m <= 0 || m >= 13)
    return 0;
  int day = dayof[m];
  if (m == 2 && isleapyear(y))
    day++;
  if (d <= 0 || d > day)
    return 0;
  return 1;
}