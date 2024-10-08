#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t bst_t;
// Write your code here
// ...
node_t* newnode(int data) {
    node_t *t = (node_t*)malloc(sizeof(node_t));
    t->data = data;
    t->left = NULL;
    t->right = NULL;
    return t;
}
node_t* insert(bst_t *t, int data) {
    if(t==NULL){
        return newnode(data);
    }
    if(t->data>data){
        t->left = insert(t->left, data);
    }
    else{
        t->right = insert(t->right, data);
    }
    return t;
}

node_t* searchnode(bst_t *t, int data) {
    if(t==NULL){
        return NULL;
    }
    if(t->data==data){
        return t;
    }
    if(data < t->data){
        return searchnode(t->left, data);
    }
    else{
        return searchnode(t->right, data);
    }
}

node_t* minnode(bst_t *t) {
    while (t->left!=NULL)
    {
        t = t->left;
    }
    return t;
    
}
node_t* delete(bst_t *t, int data) {
    if(t==NULL){
        return NULL;
    }

    if(t->data>data){
        t->left = delete(t->left, data);
    }
    else if (t->data<data){
        t->right = delete(t->right, data);
    }
    else{
        if(t->left==NULL&&t->right==NULL){
            free(t);
            return NULL;
        }
        else if(t->left==NULL){
            node_t *tmp = t->right;
            free(t);
            return tmp;
        }
        else if(t->right==NULL){
            node_t *tmp = t->left;
            free(t);
            return tmp;
        }
        else{
            node_t *tmp = minnode(t->right);
            t->data = tmp->data;
            t->right = delete(t->right, tmp->data);
        }
    }
    return t;
}

int find(bst_t *t, int data) {
    if(t==NULL){
        return 0;
    }
    if(t->data==data){
        return 1;
    }
    if(t->data>data){
        return find(t->left, data);
    }
    else{
        return find(t->right, data);
    }
}

int find_min(bst_t *t) {
    if(t->left==NULL){
        return t->data;
    }
    return find_min(t->left);
}

int find_max(bst_t *t) {
    if(t->right==NULL){
        return t->data;
    }
    return find_max(t->right);
}
void inorder(node_t *t, int k, int *n, int *ans) {
    if(t==NULL || *n>=k){
        return ;
    }
    inorder(t->left, k, n, ans);
    (*n)++;
    if(*n==k){
        *ans = t->data;
    }
    inorder(t->right, k, n, ans);
}
int find_k_th(bst_t *t, int k) {
    int ans = 0;
    int n = 0;
    inorder(t, k, &n, &ans);
    return ans;
}




int main(void) {
    bst_t *t = NULL;
    int n, i;
    int command, data, k;
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
            scanf("%d", &data);
            printf("%d\n", find(t, data));
            break;
        case 4:
            printf("%d\n", find_min(t));
            break;
        case 5:
            printf("%d\n", find_max(t));
            break;
        case 6:
            scanf("%d", &k);
            printf("%d\n", find_k_th(t, k));
            break;
        }
    }
    return 0;
}