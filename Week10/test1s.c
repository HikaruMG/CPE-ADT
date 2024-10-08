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
void move_up(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void percolation_up(heap_t *heap, int k) {
    int parent = (k-1) / 2;
    if(heap->data[k] > heap->data[parent]) {
        move_up(&heap->data[k], &heap->data[parent]);
        percolation_up(heap, parent);
    }
}

void percolation_down(heap_t *heap, int k) {
    int left_child = (2 * k) + 1 ;    
    int right_child = (2 * k) + 2;

    if(left_child <= heap->last_index && heap->data[k] <= heap->data[left_child] ) {
        move_up(&heap->data[k], &heap->data[left_child]);
        percolation_down(heap, left_child);
    }

    if(right_child <= heap->last_index && heap->data[k] <= heap->data[right_child] ) {
        move_up(&heap->data[k], &heap->data[right_child]);
        percolation_down(heap, right_child);
    }
}

void update_key(heap_t *heap, int old_key, int new_key) {
    int index = -1;
    for (int i = 0; i <= heap->last_index; i++) {
        if (heap->data[i] == old_key) {
            index = i;
            break;
        }
    }
    heap->data[index] = new_key;
    if (new_key > old_key) {
    percolation_up(heap, index);
    } else if (new_key < old_key) {
        percolation_down(heap, index);
    }
}

int find_max(heap_t *heap) {
    if (heap->last_index < 0) {
        return -1;
    }
    return heap->data[0];
}
void insert(heap_t *heap, int value) {
    heap->last_index++;
    heap->data[heap->last_index] = value;
    percolation_up(heap, heap->last_index);
}

void delete_max(heap_t *heap) {
    heap->data[0] = heap->data[heap->last_index];
    heap->last_index--;
    percolation_down(heap, 0);
}

void bfs(heap_t *heap) {
    for (int i = 0; i <= heap->last_index; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main(void) {
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;
    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                insert(max_heap, data);
                break;
            case 2:
                delete_max(max_heap);
                break;
            case 3:
                printf("%d\n", find_max(max_heap));
                break;
            case 4:
                scanf("%d %d", &old_key, &new_key);
                update_key(max_heap, old_key,
                new_key);
                break;
            case 5:
                bfs(max_heap);
                break;
        }
    }
    return 0;
}