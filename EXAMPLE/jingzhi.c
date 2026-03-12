// 十进制转任意进制，仅支持16进制及以下，输出不含前导0
void printnum(int num, int base) {
  if (num < 0) {
    putchar('-');
    num = -num;
  } // 取正数
  if (num / base > 0) // 利用递归实现反向输出
    printnum(num / base, base);
  printf("%x", num % base); // 如果你想要大写字母则使用%X
}

// 任意进制转十进制
#include <stdio.h>
#include <string.h>
char number[100001];
long long a[100001];
int base;
int main() {
  scanf("%d ", &base);
  gets(number);
  int l = strlen(number);
  for (int i = 0; i < l; i++) {
    if (number[i] >= '0' && number[i] <= '9')
      a[i] = number[i] - '0';
    else
      a[i] = number[i] - 'a' + 10;
  }
  long long ans = 0, p = 1;
  for (int i = l - 1; i >= 0; i--) {
    ans += p * a[i];
    p *= base;
  }
  printf("%lld\n", ans);
}

// num是你要输出的数，len是输出长度，输出是num的len位二进制码，包含前导0
void printbin(int num, int len) {
  int i;
  for (i = len - 1; i >= 0; i--) {
    printf("%d", num >> i & 1);
  }
  putchar('\n');
}

// 打印一个 long long 的二进制
void print_bin_ll(long long x) {
  for (int i = 63; i >= 0; --i) {
    putchar(((x >> i) & 1) + '0');
    if (i % 4 == 0)
      putchar(' '); // 每 4 位加个空格，方便看
  }
}