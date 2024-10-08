#include <stdio.h>
int main(void){
    int a,b,h = 0;
    float area =0;

    printf("a:");
    scanf("%d",&a);
    printf("b:");
    scanf("%d",&b);
    printf("h:");
    scanf("%d",&h);
    
    area = 0.5*(a+b)*h;
    printf("Area is %.1f",area);
    return 0;
}