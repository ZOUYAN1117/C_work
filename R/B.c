#include<stdio.h>
int main(){
    unsigned int x;
    scanf("%u",&x);
    for(int i=0;i<=31;i++){
        if((x >> i) & 1)
        printf("%u ",1<<i);
    }
}