// 排列数和组合数，确保输入的m>=n>0
int anm(int n, int m) {
  if (m == 0)
    return 1;
  int a = 1;
  for (int i = m; i > m - n; i--)
    a *= i;
  return a;
}
int cnm(int n, int m) {
  int c;
  if (n > (m ^ 1) / 2)
    n = m - n;
  return anm(n, m) / anm(n, n);
}

// 通过二重循环递推预处理组合数（推荐）i是下面的
long long comb[1008][1008];
const long long P = 998442353;
for (int i = 0; i <= n; i++) {
  for (int j = 0; j <= i; j++) {
    if (j == 0 || j == i) { // 边界条件
      comb[i][j] = 1;
    } else { // 递推式（组合恒等式）
      comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % P;
    }
  }
}