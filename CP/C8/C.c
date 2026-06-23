#include<stdio.h>
#include<string.h>
char a[1005][10005];
int main(){
    int i=1;
    while(scanf("%s",a[i])!=EOF){
        int len=strlen(a[i]),sum=0;
        if(len%2==0){
            for(int j=0;j<len/2;j++){
                if(a[i][j]!=a[i][len-1-j])
                sum++;
            }
        }else {
            for(int j=0;j<len/2;j++){
                if(a[i][j]!=a[i][len-1-j])
                sum++;
            }
        }
        i++;
        printf("%d\n",sum);
    }
}