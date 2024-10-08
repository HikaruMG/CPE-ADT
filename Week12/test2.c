#include <stdio.h>

void quick_sort(int arr[],int low, int high) {
    int pivot;
    if (low< high){
        pivot = partition(arr,low,high);
        quick_sort(arr,low,pivot-1);
        quick_sort(arr,pivot+1,high);
    }
}

int medianofthree(int arr[],int low,int mid, int high) {
    if ((arr[low] > arr[mid]) != (arr[low] > arr[high])){
        return low;
    }
    else if ((arr[mid] > arr[low]) != (arr[mid] > arr[high])) {
        return mid;
    }
    else {
        return high;
    }
}

int partition(int arr[],int low, int high) {
    int mid = low + (high-low)/2;
    int median = medianofthree(arr,low,mid,high);

    int tmp = arr[median];
    arr[median] = arr[high];
    arr[high] = tmp;
    int pivot = arr[high];

    int i = low - 1;
    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int tmp2 = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = tmp2;
    return i+1;
}

void sumthreenum(int arr[], int n, int p) {
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue;
        }
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            if (sum == p) {
                printf("%d %d %d\n", arr[i], arr[left], arr[right]);
                while (left < right && arr[left] == arr[left + 1]) {
                    left++;
                }
                while (left < right && arr[right] == arr[right - 1]){
                    right--;
                }
                right--;
                left++;
            } else if (sum < p) {
                left++;
            } else {
                right--;
            }
        }
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

    quick_sort(arr, 0, n - 1);
    sumthreenum(arr,n,p);
    return 0;
}
