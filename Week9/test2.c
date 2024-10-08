#include <stdio.h>
#include <stdlib.h>
#define __avl_tree__
#include <C:/Users/ASUS/Desktop/Elab/Git/CPE-ADT/Week9/week9.h>
#ifndef __avl_tree__
typedef struct node {
int data;
int height;
struct node *left;
struct node *right;
} node_t;
typedef node_t avl_t;
#endif
// Write your code here
// ** Note that the print_tree() function
// has been implemented already and
// included in the week9.h header
// ...

node_t* newnode(int data) {
    node_t *t = (node_t*)malloc(sizeof(node_t));
    t->data = data;
    t->left = NULL;
    t->right = NULL;
    return t;
}

int height(avl_t *t) {
    if (t == NULL) {
        return 0;
    }
    return t->height;
}

int find_max(int a, int b) {
    if (a>b){
        return a;
    }
    else{
        return b;
    }
}

node_t* SRR(avl_t *t) {
    avl_t* tmp1 = t->left;
    avl_t* tmp2 = tmp1->right;

    tmp1->right = t;
    t->left = tmp2;
    t->height = find_max(height(t->left), height(t->right)) + 1;
    tmp1->height = find_max(height(tmp1->left), height(tmp1->right)) + 1;
    return tmp1;
}

node_t* SLR(avl_t *t) {
    avl_t *tmp1 = t->right;
    avl_t *tmp2 = tmp1->left;

    tmp1->left = t;
    t->right = tmp2;
    t->height = find_max(height(t->left), height(t->right)) + 1;
    tmp1->height = find_max(height(tmp1->left), height(tmp1->right)) + 1;
    return tmp1;
}

int checkbl(avl_t *t) {
    if(t == NULL) {
        return 0;
    }
    return height(t->left) - height(t->right);
}
int find_min(node_t *t) {
    if(t->left==NULL){
        return t->data;
    }
    return find_min(t->left);
}
node_t* insert(avl_t *t, int data) {
    if (t == NULL) {1 
        t = newnode(data);
    }
    if (data < t->data) {
        t->left = insert(t->left, data);
    }
    else if (data > t->data) {
        t->right = insert(t->right, data);
    }
    else {
        return t;
    }
    t->height = find_max(height(t->left), height(t->right)) + 1;
    if(checkbl(t) > 1 && data < t->left->data) {
        return SRR(t);
    }
    if(checkbl(t) < -1 && data > t->right->data) {
        return SLR(t);
    }
    if(checkbl(t) > 1 && data > t->left->data) {
        t->left = SLR(t->left);
        return SRR(t);
    }
    if(checkbl(t) < -1 && data < t->right->data) {
        t->right = SRR(t->right);
        return SLR(t);
    }
    return t;
}

node_t* delete(avl_t *t, int data) {
    if (t == NULL) {
        return t;
    }
    if (data < t->data) {
        t->left = delete(t->left, data);
    }
    else if (data > t->data) {
        t->right = delete(t->right, data);
    }
    else {
        if((t->left == NULL) || (t->right == NULL)) {
            node_t *tmp = t->left ? t->left : t->right;
            if(tmp == NULL) {
                tmp = t;
                t = NULL;
            }
            else {
                *t = *tmp;
            }
        }
            else{
                node_t* tmp = find_min(t->right);
                t->data = tmp->data;
                t->right = delete(t->right, tmp->data);
            }
            }
            if(t==NULL){
                return t;
            }

            t->height = find_max(height(t->left), height(t->right)) + 1;
            int check = checkbl(t);
            if(check > 1 && checkbl(t->left) >= 0) {
                return SRR(t);
            }
            if(check > 1 && checkbl(t->left) < 0) {
                t->left = SLR(t->left);
                return SRR(t);
            }
            if(check < -1 && checkbl(t->right) <= 0) {
                return SLR(t);
            }
            if(check < -1 && checkbl(t->right) > 0) {
                t->right = SRR(t->right);
                return SLR(t);
            }
            return t;
        }
int main(void) {
    avl_t *t = NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                t = insert(t, data);
                break;
            case 2:
                scanf("%d", &data);
                t = delete(t, data);
                break;
            case 3:
                print_tree(t);
                break;
        }
    }
return 0;
}