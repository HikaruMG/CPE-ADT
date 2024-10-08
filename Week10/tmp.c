#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int *data;
    int last_index;
} heap_t;

heap_t *init_heap(int s) {
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (int *)malloc(s * sizeof(int));
    heap->last_index = -1; 
    return heap;
}

void free_heap(heap_t *heap) {
    free(heap->data); // คืนพื้นที่หน่วยความจำของ data
    free(heap); // คืนพื้นที่หน่วยความจำของ heap
}

int main() {
    int size = 10;
    heap_t *my_heap = init_heap(size);

    // ตัวอย่างการเพิ่มข้อมูลลงในฮีป
    for (int i = 0; i < size; i++) {
        my_heap->data[++my_heap->last_index] = i * 10; // เพิ่มค่าในฮีป
    }

    // แสดงค่าที่อยู่ในฮีป
    for (int i = 0; i <= my_heap->last_index; i++) {
        printf("index = %d | Data = %d\n", i,my_heap->data[i]);
    }
    printf("\n");

    // คืนพื้นที่หน่วยความจำเมื่อไม่ใช้งาน
    free_heap(my_heap);

    return 0;
}
