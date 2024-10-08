#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    int land;
    struct node *parent;
    struct node *next_sibling;
    struct node *first_child;
} node_t;

typedef node_t tree_t;

int cost(tree_t *t, int money);
tree_t *new_node(int data, int land);
tree_t *attach(tree_t *t, int p, int c,int r, tree_t **route);


int main() {
    tree_t *t = NULL;
    tree_t **route = (tree_t **)calloc(100001, sizeof(tree_t *));
    int city,money,p,c,r;
    scanf("%d %d", &city, &money);
    for (int i = 0; i < city; i++) {
        scanf("%d %d %d", &p, &c, &r);
        t = attach(t, p, c,r, route);
    }
    printf("%d\n", cost(t, money));
    return 0;
}

tree_t *new_node(int data, int land) {
    tree_t *tmp = (tree_t *)malloc(sizeof(tree_t));
    tmp->data = data;
    tmp->land = land;
    tmp->parent = NULL;
    tmp->first_child = NULL;
    tmp->next_sibling = NULL;
    return tmp;
}
int cost(tree_t *t, int money) {
    tree_t *tmp = t->first_child;
    int d = 0;
    if(t==NULL){
        return 0;
    }
    if(t->land==1){
        if(money<= 0){
            return d;
        }
        else{
            money -=1;
            d++;
        }
    }
    else if (t->data != 0)
    {
        d++;
    }
    while (tmp!=NULL)
    {
        d+= cost(tmp, money);
        tmp = tmp->next_sibling;
    }
    return d;
}
tree_t *attach(tree_t *t, int p, int c,int r, tree_t **route) {
    tree_t *tmp = new_node(c,r);
    if(t==NULL){
        t = new_node(p,0);
        t->first_child = tmp;
        tmp->parent = t;
        route[p]=t;
        route[c]=tmp;
        return t;
    }
    tree_t *parent = route[p];
    if(parent==NULL){
        return t;
    }
    if(parent->first_child==NULL){
        parent->first_child = tmp;
        tmp->parent = parent;
    }else{
        tree_t *sibling = parent->first_child;
        while(sibling->next_sibling!=NULL){
            sibling = sibling->next_sibling;
        }
        sibling->next_sibling = tmp;
        tmp->parent = sibling;
    }
    route[c]=tmp;
    return t;
}