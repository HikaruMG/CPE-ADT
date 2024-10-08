//O((log m)*(log n))
#include<stdio.h>
#include<math.h>
int area(int m){ //<-- O(log(m))
    int n = 1;
    while (n <= m) {
        n *= 2;
    }
    return n / 2;
}
void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int dividearea(int m,int n){ //<-- O(log(m)*log(n))
    if (m==0||n==0){
        return 0;
    }
    if (n<m){
        swap(&m,&n);
    }
    
    int s = area(m);

    if(m==1){
        return n;
    }
    if(m==s && s==n){
        return 1;
    }
    if(s==m){
        return 1+dividearea(m,n-s);
    }
    return 1+dividearea(m-s,n)+dividearea(s,n-s);
}
int main(void) {
  int m, n ;
  scanf("%d %d",&m,&n);
  printf("%d",dividearea(m,n));
  return 0;
}
