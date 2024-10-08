#include <stdio.h>
    int main(void){
    int m,n;
    int c,a,b;
    scanf("%d %d",&m,&n);
    c = (m*m)+(n*n);
    a = (m*m)-(n*n);
    b = 2*(m*n);
    printf("%d %d %d",a,b,c);
    return 0;
}