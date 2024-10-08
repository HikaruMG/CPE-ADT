#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 16
#define MAX_NODE 100000

typedef struct Node {
    int f;
    char TEXT[MAX_TEXT];
    struct Node *left_child, *right_child;
} Node;

Node* createnode(int f, const char* TEXT) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->f = f;
    strcpy(node->TEXT, TEXT);
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}
// Priority Queue
Node* priorityQueue[MAX_NODE]; // สร้าง Priority Queue ขนาด MAX

// ฟังก์ชันในการสลับโหนด
void move_up(int i, int j) {
    Node* tmp = priorityQueue[i];
    priorityQueue[i] = priorityQueue[j];
    priorityQueue[j] = tmp;
}

// เพิ่มโหนดใหม่เข้าใน Priority Queue
int last_index = 0;
void insert(Node* n) {
    priorityQueue[last_index] = n;
    int i = last_index;
    last_index++;
    
    // ทำการ percolation_up ขึ้น
    while (i>0)
    {
        int parent = (i-1)/2;
        if(priorityQueue[i]->f >= priorityQueue[parent]->f) break;
        move_up(i, parent);
        i = parent;
    }
    
}

// ดึงโหนดที่มีค่าน้อยที่สุดออกจาก Priority Queue
Node* delete_Min() {
    Node* minNode = priorityQueue[0];
    last_index--;
    priorityQueue[0] = priorityQueue[last_index];
    
    int i = 0;
    
    // ทำการ heapify ลง
    while (2*i+1 < last_index) {
        int smallest = i;
        int left_child = 2*i+1;
        int right_child = 2*i+2;
        if (priorityQueue[left_child]->f < priorityQueue[smallest]->f)
            smallest = left_child;
        if (right_child < last_index && priorityQueue[right_child]->f < priorityQueue[smallest]->f)
            smallest = right_child;
        if (smallest == i)
            break;
        move_up(i, smallest);
        i = smallest;
    }
    return minNode;
}

// สร้าง Huffman Tree
Node* HuffmanTree() {
    while (last_index > 1) {
        Node* left_child = delete_Min();
        Node* right_child = delete_Min();
        
        Node* merge = createnode(left_child->f + right_child->f, "");
        merge->left_child = left_child;
        merge->right_child = right_child;
        insert(merge);
    }
    
    return delete_Min();
}

// ฟังก์ชัน DFS ในการสร้างรหัส
void dfs(Node* n_root, char* C, int depth) {
    if (n_root == NULL)
        return;
    
    // ถ้าเป็น leaf ให้แสดงคำกับรหัส
    if (n_root->left_child == NULL && n_root->right_child == NULL) {
        C[depth] = '\0';
        printf("%s: %s\n", n_root->TEXT, C);
        return;
    }

    // ไปทางซ้าย 0
    C[depth] = '0';
    dfs(n_root->left_child, C, depth + 1);
    
    // ไปทางขวา 1
    C[depth] = '1';
    dfs(n_root->right_child, C, depth + 1);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char TEXT[MAX_TEXT];
        int f;
        scanf("%s %d", TEXT, &f);
        Node* node = createnode(f, TEXT);
        insert(node);
    }
    Node* n_root = HuffmanTree();
    char C[MAX_TEXT];
    dfs(n_root, C, 0);
    return 0;
}
