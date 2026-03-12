#include <stdio.h>
int qpow(int a, long long b, int p) {
  int ans = 1;
  int base = a;
  while (b > 0) {
    if (b & 1) {
      ans = ans * (long long)base % p;
    }
    base = (long long)base * base % p;
    b >>= 1;
  }
  return ans;
}
int main(){
    long long a,b,p;
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%lld%lld%lld",&a,&b,&p);
        printf("%d\n",qpow(a,b,p));
    }
}