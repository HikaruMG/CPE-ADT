//ลูปจะทำงานจนถึงแค่ sqrt(n) จะได้ว่า O(sqrt(n))
#include <stdio.h>
#include <math.h>
int checkprime(int n){
    if(n<=1){ //<--O(1)
        return 0;
    }
    for(int i = 2;i<=sqrt(n);i++){ //<--Loop (O(sqrt(n)))
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}
int main(void) {
    int n;
    scanf("%d",&n);
    printf("%d",checkprime(n));
    return 0;
}