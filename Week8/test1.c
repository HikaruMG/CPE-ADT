#include <stdio.h>
#include <stdlib.h>
#include <C:/Users/ASUS/Desktop/Elab/Git/CPE-ADT/Week8/Week8.h>
#include <math.h>
#ifndef __bin_tree__
typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t tree_t;
#endif
// Write your code here
// ** Note that the attach() function has
// been implemented already and included
// in the week8.h header
// ...
int height(tree_t *t) {
    if (t == NULL) {
        return -1; 
    }
    int leftHeight = height(t->left);
    int rightHeight = height(t->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int count_nodes(tree_t *t) {
    if(t==NULL){
        return 0;
    }
    return 1 + count_nodes(t->left) + count_nodes(t->right);
}
int is_full(tree_t *t) {
    if(t==NULL){
        return 1;
    }
    if(t->left==NULL && t->right==NULL){
        return 1;
    }
    if(t->left!=NULL && t->right!=NULL){
        return is_full(t->left) && is_full(t->right);
    }
    return 0;
}

int is_perfect(tree_t *t) {
    if (t == NULL) {
        return 1;
    }
    int n = count_nodes(t);
    // printf("%d\n",n);
    int d = height(t);
    // printf("%d\n",d);
    int h = (int)pow(2, d + 1) - 1;;
    // printf("%d\n",h);
    return n == h;
}

int is_complete(tree_t *t) {
    int n = count_nodes(t);
    return is_completeX(t,0,n);
}
int is_completeX(tree_t *t,int pos,int n) {
    if(t==NULL){
        return 1;
    }
    if(pos>=n){
        return 0;
    }
    return is_completeX(t->left,2*pos+1,n) && is_completeX(t->right,2*pos+2,n);
}

int is_degenerate(tree_t *t) {
    if(t==NULL){
        return 1;
    }
    if(t->left!=NULL && t->right!=NULL){
        return 0;
    }
    if(t->left){
        return is_degenerate(t->left);
    }else{
        return is_degenerate(t->right);
    }
}

int rightSK(tree_t *t) {
    if(t==NULL){
        return 1;
    }
    if(t->left!=NULL){
        return 0;
    }
    return rightSK(t->right);
}

int leftSK(tree_t *t) {
    if(t==NULL){
        return 1;
    }
    if(t->right!=NULL){
        return 0;
    }
    return leftSK(t->left);
}

int is_skewed(tree_t *t) {
    return rightSK(t) || leftSK(t);
}
int main(void) {
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d %d", &parent, &child,&branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d %d %d %d %d\n", is_full(t),is_perfect(t), is_complete(t),is_degenerate(t), is_skewed(t));
    return 0;
}