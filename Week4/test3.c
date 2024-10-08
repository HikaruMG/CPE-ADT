// O(mlogm) 
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a,const void *b){
    int int_a = *(int*)a;
    int int_b = *(int*)b;
    if (int_a<int_b){
        return 1;
    }else if(int_a>int_b){
        return -1;
    }else{
        return 0;
    }
}
int main(void){
    int m,v,c=0,temp;
    scanf("%d",&m);
    int price[m];
    for(int i =0;i<m;i++){ //<- O(m)
        scanf("%d",&price[i]);
    }
    int n = sizeof(price)/sizeof(price[0]);
    qsort(price, n, sizeof(int), compare); //<- O(mlog(m)) <-(qsort)
    scanf("%d",&v);
    int tempv = v;
    for(int i = 0;i<m;i++){ //<- O(m)
        if(tempv>=price[i]){
            temp = tempv/price[i];
            printf("Temp:%d\n",temp);
            c += temp;
            tempv -= temp*price[i];
        }
    }
    printf("%d",c);
    
    //  for (int i = 0; i < n; i++) {
    //      printf("%d ", price[i]);
    //  }
    //  printf("\n");
      return 0;
}