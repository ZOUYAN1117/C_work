// 高效判断long long素数
int isprime(long long num) {
  if (num == 2 || num == 3)
    return 1;
  if ((num & 1) == 0 || num == 1 || num % 3 == 0) // num&1==0,相当于num%2==0
    return 0;
  int i, flag;
  for (i = 5, flag = 4; 1ll * i * i <= num; i += flag) // 1LL将后面的数据强制转换为long long
  {
    flag = 6 - flag; // 步长为4，2，4，2，4......
    if (num % i == 0)
      return 0;
  }
  return 1;
}