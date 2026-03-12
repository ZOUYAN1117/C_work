#include<stdio.h>
#include<math.h>
int x[13],y[13],r[13];
double distance(int a,int b){
    return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}
double area(int a,int b)
{
    const double pi=acos(-1.0);
    double d=distance(a,b);
    double ra=r[a],rb=r[b];
    if(d>=ra+rb) return 0.0;                 // separate
    if(d==0) return pi*ra*ra<pi*rb*rb?pi*ra*ra:pi*rb*rb; // same center
    if(d<=fabs(ra-rb)) return pi*(ra<rb?ra*ra:rb*rb);    // one inside another
    double alpha=acos((ra*ra+d*d-rb*rb)/(2*ra*d));
    double beta =acos((rb*rb+d*d-ra*ra)/(2*rb*d));
    double term=(-d+ra+rb)*(d+ra-rb)*(d-ra+rb)*(d+ra+rb);
    if(term<0) term=0;
    return ra*ra*alpha+rb*rb*beta-0.5*sqrt(term);
}
int main(){
    double pi=acos(-1);
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        double sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&x[i],&y[i],&r[i]);
            sum+=pi*r[i]*r[i];
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++){
                sum-=area(i,j);
            }
        }
        printf("%.4lf\n",sum);
    }
}
