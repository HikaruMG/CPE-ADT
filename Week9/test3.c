#include <stdio.h>
#include <stdlib.h>
#define __bin_tree__
#include <week9.h>
#ifndef __bin_tree__
typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t tree_t;
#endif
int inorderBST(node_t* t, int n) {
    if (t == NULL)
        return 1;
    if (!inorderBST(t->left, n))
        return 0;
    if (t->data <= n)
        return 0;
    n = t->data;
    return inorderBST(t->right, n);
}
int is_bst(node_t* t) {
    int n = -1000;  
    return inorderBST(t, n);
}

int height(node_t* t) {
    if (t == NULL){
        return 0;
    }
    int h_left = height(t->left);
    int h_right = height(t->right);
    return (h_left > h_right ? h_left : h_right)+1;
}

int is_avl(node_t* t) {
    if (t == NULL){
        return 1;
    }
    int h_left = height(t->left);
    int h_right = height(t->right);
    if (abs(h_left - h_right) > 1){
        return 0;
    }
    return is_bst(t) && is_avl(t->left) && is_avl(t->right) ;
}

// Write your code here
// ** Note that the attach() function has
// been implemented already and included
// in the week9.h header
// ...
int main(void) {
tree_t *t = NULL;
int n, i;
int parent, child;
int branch; // 0 root, 1 left, 2 right
scanf("%d", &n);
for (i=0; i<n; i++) {
scanf("%d %d %d", &parent, &child,
&branch);
t = attach(t, parent, child, branch);
}
printf("%d %d\n", is_bst(t), is_avl(t));
return 0;
}