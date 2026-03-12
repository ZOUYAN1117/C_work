// 求最大公约数
// 方法一：递归高效
int gcd(int a, int b) {
  if (b == 0) // 达到基本情况，递归结束
    return a;
  return gcd(b, a % b);
}

// 方法二：非递归，可负数
long long gcd(long long a, long long b) // 辗转相除求最大公约数
{
  long long r;
  if (b == 0)
    return a < 0 ? -a : a;
  while ((r = a % b) != 0) // 相当于r=a%b&&a%b!=0同时进行赋值和判断
  {
    a = b;
    b = r;
  }
  return b < 0 ? -b : b;
}

// 求最大公倍数
long long lcm(long long a1, long long b1) {
  long long temp, a = a1, b = b1;
  while (a % b != 0) {
    temp = a % b;
    a = b;
    b = temp;
  }
  return a1 / b * b1;
}