#include <stdio.h>
#include <stdlib.h>
#include <C:/Users/ASUS/Desktop/Elab/Git/CPE-ADT/Week8/Week8.h>
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
int pathSum(tree_t *t, int s) {
    int count = 0;
    if(t==NULL) {
        return 0;
    }
    if(t->data == s) {
        count++;
    }
    count += pathSum(t->left, s-t->data);
    count += pathSum(t->right, s-t->data);
    return count;
}
int countPathsWithSum(tree_t *t, int s) {
    if(t==NULL) {
        return 0;
    }
    return pathSum(t, s) + countPathsWithSum(t->left, s) + countPathsWithSum(t->right, s);
}
int main(void) {
    tree_t *t = NULL;
    int n, s, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d %d", &n, &s);
    for (i=0; i<n; i++) {
        scanf("%d %d %d", &parent, &child,
        &branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d\n", countPathsWithSum(t, s));
    return 0;
}