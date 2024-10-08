#include <stdio.h>

void SelectionSortArr(int arr[], int n) {
    int i,j,low;
    for(i = 0; i < n - 1; i++) {
        low = i;
        for(j = i + 1; j < n; j++) {
            if(arr[j] < arr[low]) {
                low = j;
            }
        }
        if (low != i) {
            int temp = arr[i];
            arr[i] = arr[low];
            arr[low] = temp;
        }
    }
}
 

void sumthreenum(int arr[], int n, int p, int q[], int idx,int current) {
    if(idx ==3){
        if (p == q[0] + q[1] + q[2]) {
            printf("%d %d %d\n",q[0],q[1],q[2]);
        }
        return;
    }

    for(int i = current; i < n; i++) {
        if(i>current && arr[i] == arr[i-1]) continue;
        q[idx] = arr[i];
        sumthreenum(arr,n,p,q,idx+1,i+1);
    }
}


int main() {
    int n,p;
    int q[3];
    scanf("%d %d",&n,&p);
    int arr[n];
    for(int i = 0; i < n; i++) {
        scanf("%d",&arr[i]);
    }

    SelectionSortArr(arr,n);
    sumthreenum(arr,n,p,q,0,0);
    return 0;
}
