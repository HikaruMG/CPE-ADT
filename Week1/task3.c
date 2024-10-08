#include <stdio.h>
#include <math.h>
int main(void){
    int l,w =0;
    double t =0;
    double area = 0;

    printf("length(m.):");
    scanf("%d",&l);
    printf("width(m.):");
    scanf("%d",&w);

    area = (l*3.28084)*(w*3.28084);
    t = area/2;
    printf("Use %.5lf seconds.",t);
    return 0;
}