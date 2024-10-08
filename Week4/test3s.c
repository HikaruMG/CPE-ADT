// O(m)

#include <stdio.h>
int main(void){
    int m,v,c=0,arr,tempv;
    int snackprice[100]={0};
    //  for (int i = 0; i <= 100; i++) {
    //      printf("%d ", price[i]);
    //  }
    //  printf("\n");
    scanf("%d",&m);
    for(int i = 0 ; i < m; i++){ //<-- O(m)
        scanf("%d" ,&arr);
        snackprice[arr] = 1;
    }
    scanf("%d",&v);
    tempv = v;
    for(int i = 99 ; i > 0; i--){ //<- O(1)
        if(snackprice[i] == 1 && tempv >= i){
            c+= (tempv/i);
            tempv %= i;
        }
    }
    printf("%d",c);
    return 0;
}