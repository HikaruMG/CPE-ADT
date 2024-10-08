#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

typedef struct heap {
int *data;
int last_index;
} heap_t;

void init_heap(heap_t *heap,int n) {
    heap->data = (int *)malloc(n * sizeof(int)); //กำหนดขนาดของ heap
    heap->last_index = 0; //จำนวน node ที่อยู่ใน heap
}

void move_up(int *a, int *b) { //a สลับ b
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void maxpercolation_up(heap_t *heap, int k) { //จัดเรียงข้อมูลใน heap เมืื่อมีค่าใหม่เพิ่มจาก left
    // if(k==0){
    //     return;
    // }
    int parent = (k - 1) / 2;
    while(k>0 && heap->data[parent] < heap->data[k]) {
        move_up(&heap->data[parent], &heap->data[k]);
        k = parent;
        parent = (k - 1) / 2;
    }
    // if(heap->data[parent] < heap->data[k]) { //ค่า parent น้อยกว่าค่าใหม้ช่อง k
    //     move_up(&heap->data[parent], &heap->data[k]); //สลับค่า parent กับ k
    //     maxpercolation_up(heap, parent); //Recursion ต่อที่ parent
    // }
}

void maxpercolation_down(heap_t *heap, int k) { //จัดเรียงข้อมูลใน heap เมื่อลบค่าจาก Root
    while(1){
        int left_child = 2 * k + 1;
        int right_child = 2 * k + 2;
        int max = k;
        if(left_child < heap->last_index && heap->data[left_child] > heap->data[max] ) { // ช่อง left ต้องน
            max = left_child;
        }

        if(right_child < heap->last_index && heap->data[right_child] > heap->data[max] ) {
            max = right_child;
        }
        if(max==k) break;

        move_up(&heap->data[max], &heap->data[k]);
        k = max;
    }
    // int left_child = 2 * k + 1;
    // int right_child = 2 * k + 2;
    // if(left_child < heap->last_index && heap->data[left_child] > heap->data[k] ) { // ช่อง left ต้องน
    //     move_up(&heap->data[left_child], &heap->data[k]);
    //     maxpercolation_down(heap, left_child);
    // }

    // if(right_child < heap->last_index && heap->data[right_child] > heap->data[k] ) {
    //     move_up(&heap->data[right_child], &heap->data[k]);
    //     maxpercolation_down(heap, right_child);
    // }
}

void minpercolation_up(heap_t *heap, int k) {
    int parent = (k - 1) / 2;
    while (k>0 && heap->data[parent] > heap->data[k]){
        move_up(&heap->data[parent], &heap->data[k]);
        k = parent;
        parent = (k - 1) / 2;
    }

    // if(k==0){
    //     return;
    // }
    // int parent = (k - 1) / 2;
    // if(heap->data[parent] > heap->data[k]) {
    //     move_up(&heap->data[parent], &heap->data[k]);
    //     minpercolation_up(heap, parent);
    // }
}

void minpercolation_down(heap_t *heap, int k) {
    while(1){
        int left_child = 2 * k + 1;
        int right_child = 2 * k + 2;
        int min = k;
        if(left_child < heap->last_index && heap->data[left_child] < heap->data[min] ) {
            min = left_child;
        }
        if(right_child < heap->last_index && heap->data[right_child] < heap->data[min] ) {
            min = right_child;
        }
        if(min == k) break;
        move_up(&heap->data[min], &heap->data[k]);
        k = min;
    }
    // int left_child = 2 * k + 1;
    // int right_child = 2 * k + 2;
    // if(left_child < heap->last_index && heap->data[left_child] < heap->data[k] ) {
    //     move_up(&heap->data[left_child], &heap->data[k]);
    //     minpercolation_down(heap, left_child);
    // }

    // if(right_child < heap->last_index && heap->data[right_child] < heap->data[k] ) {
    //     move_up(&heap->data[right_child], &heap->data[k]);
    //     minpercolation_down(heap, right_child);
    // }
}

void maxinsert(heap_t *heap, int n) {
    heap->data[heap->last_index] = n;
    heap->last_index++;
    maxpercolation_up(heap, heap->last_index-1);
}

void mininsert(heap_t *heap, int n) {
    heap->data[heap->last_index] = n;
    heap->last_index++;
    minpercolation_up(heap, heap->last_index-1);
}

int maxdelete(heap_t *heap) {
    int maxval = heap->data[0];
    heap->data[0] = heap->data[heap->last_index-1];
    heap->last_index--;
    maxpercolation_down(heap, 0);
    return maxval;
}

int mindelete(heap_t *heap) {
    int minval = heap->data[0];
    heap->data[0] = heap->data[heap->last_index-1];
    heap->last_index--;
    minpercolation_down(heap, 0);
    return minval;
}

int main() {
    heap_t max, min;
    int n,j;
    scanf("%d", &n);

    init_heap(&max,n);
    init_heap(&min,n);

    scanf("%d", &j);
    maxinsert(&max, j);
    printf("%.1f\n", (float)j);

    for(int i = 1; i < n; i++) {
        scanf("%d", &j);

        if(j <= max.data[0]) {
            maxinsert(&max, j);
        }else{
            mininsert(&min, j);
        }

        if(max.last_index > min.last_index +1) {
            mininsert(&min, maxdelete(&max));
        }else if(min.last_index > max.last_index) {
            maxinsert(&max, mindelete(&min));
        }

        if(max.last_index == min.last_index) {
            printf("%.1f\n", (float)(max.data[0] + min.data[0]) / 2); 
        }
        else{
            printf("%.1f\n", (float)max.data[0]);
        }

    }
    return 0;
}