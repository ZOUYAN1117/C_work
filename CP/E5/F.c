#include <stdio.h>
void div(int n){
    if(n==1){
        printf("1");
    }else{
        if(n%2==0){
            printf("(");
            div(n/2);
            printf("+");
            div(n/2);
            printf(")");
        }
        else{
            printf("(");
            div((n-1)/2);
            printf("+1+");
            div((n-1)/2);
            printf(")");
        }
    }
}
int main(){
    int a,n;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&a);
        div(a);
        printf("\n");
    }
}