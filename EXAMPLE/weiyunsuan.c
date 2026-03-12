// 这里默认最后一位是第0位
// 对 long long 做位运算：1ll << k
(x >> k) & 1;  // 取第 k 位（0/1）
x | (1 << k);  // 把第 k 位设为 1
x & ~(1 << k); // 把第 k 位设为 0
x ^ (1 << k);  // 把第 k 位取反
x & 1;         // 只看最低位(判断奇偶)
x >> 1;        // 删除最低位，相当于 /2 向下取整（对非负数）
x << 1;        // 在末尾补 0，相当于 *2
(x << 1) + 1;  // 在末尾补 1
x &(x - 1);    // 删掉“最低位的那个 1”
x & ((1 << k) - 1); // 取后k位
x | ((1 << k) - 1); // 把后 k 位全变为 1
x ^ ((1 << k) - 1); // 仅把后 k 位全部取反
x & -x; // （题解也常用）只保留最低位的那个 1，其余清零

// 统计二进制中 1 的个数
int count_ones(int x) {
  int cnt = 0;
  while (x) {
    x &= (x - 1); // 每次去掉一个最低位的 1
    cnt++;
  }
  return cnt;
}

// 判断是否是 2 的幂
int is_power_of_two(int n) { return n > 0 && (n & (n - 1)) == 0; }

// 把一个数拆成若干个 2 的幂之和
void print_pows(unsigned int n) {
  for (int i = 29; i >= 0; --i) { // 根据题目范围调 i
    if ((n >> i) & 1) {
      printf("%d ", 1 << i); // i就是第几位，可以直接用
    }
  }
}

// 加法器
int add_no_plus(int a, int b) {
  while (b != 0) {
    int sum = a ^ b; // 不考虑进位的和（0+0,1+1→0; 0+1,1+0→1）
    int carry = (a & b) << 1; // 进位：只有 1+1 才产生进位，左移一位放到高位
    a = sum;
    b = carry;
  }
  return a;
}

// 给 N、M 和 i、j，让 N 的第 i~j 位变成 M 的第 i~j 位（M 从 i 位开始对齐）
int update_bits(int n, int m, int i, int j) {
  for (int pos = i; pos <= j; ++pos) {
    n &= ~(1 << pos); // 把第 pos 位清 0
  }
  return n | (m << i); // 左移后或进去
}

// 输出反转其 32 位补码后的对应的数
unsigned int reverse_bits(unsigned int x) {
  unsigned int res = 0;
  for (int i = 0; i < 32; ++i) {
    res <<= 1;
    res |= (x >> i) & 1;
  }
  return res;
}

// 把i,j的n位二进制数（有前导0）错位拼在一起 eg.i=010100 j=110000 res=011100100000
for (int k = 0; k < n; k++) {
  res |= ((i >> k & 1) * 2 + (j >> k & 1)) << (k * 2);
}