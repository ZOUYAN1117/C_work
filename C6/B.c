#include <stdio.h>
int main(){
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        int m1=0,m2=0,m3=0;
        scanf("%d",&n);
        while(n--){
            int a;
            scanf("%d",&a);
            if(a%3==1) m1++;
            else if(a%3==2) m2++;
            else m3++;
        }
        if(m1+m2>=m3-1&&m1+m3>=m2-1&&m2+m3>=m1-1)
            printf("YES\n");
        else
            printf("NO\n");
    }
}