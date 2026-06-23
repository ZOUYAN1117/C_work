#include <stdio.h>
long long a[2003][2003];
int main() {
    int n,m;
    scanf("%d%d", &n, &m);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+a[i][j];
        }
    }
    int q;
    scanf("%d", &q);
    while(q--) {
        int x1,y1,x2,y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        long long sum;
        sum = a[x2][y2]-a[x1-1][y2]-a[x2][y1-1]+a[x1-1][y1-1];
        printf("%lld\n", sum);
    }
    return 0;
}