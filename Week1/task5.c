#include <stdio.h>
#include <stdlib.h>
int main(void){
    char a , b;
    int num1 = a;
    int num2 = b;
    int dis = 0;
    scanf("%c %c",&a,&b);
    dis = abs(a-b);
    printf("%d",dis);
    return 0;
}