#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    int state;
    struct node *next_sibling;
    struct node *first_child;
    struct node *before;
} node_t;

typedef node_t tree_t;

tree_t *create_node(int value, int state) {
    tree_t *new_node = (tree_t *)malloc(sizeof(tree_t));
    new_node->value = value;
    new_node->state = state;
    new_node->first_child = NULL;
    new_node->next_sibling = NULL;
    new_node->before = NULL;
    return new_node;
}

tree_t *attach(tree_t *t, int p, int c, int robber, tree_t **node_map) {
    tree_t *child_node = create_node(c, robber);

    if (t == NULL) {  // Initialize the root
        t = create_node(p, 0);
        t->first_child = child_node;
        child_node->before = t;
        node_map[p] = t;
        node_map[c] = child_node;
        return t;
    }

    tree_t *parent_node = node_map[p];  // Fast lookup using node_map

    if (parent_node == NULL) {
        return t;
    }

    if (parent_node->first_child == NULL) {
        parent_node->first_child = child_node;
        child_node->before = parent_node;  // Before = parent
    } else {
        tree_t *sibling = parent_node->first_child;
        while (sibling->next_sibling != NULL) {
            sibling = sibling->next_sibling;
        }
        sibling->next_sibling = child_node;
        child_node->before = sibling;  // Before = older sibling
    }

    node_map[c] = child_node;  // Store child node in the map
    return t;
}

int traverse(tree_t *t, int money) {
    if (t == NULL) return 0;

    int count = 0;

    // If current node is a robber
    if (t->state == 1) {
        if (money <= 0) {
            return count;  
        } else {
            money -= 1;  
            count++;  
        }
    } else if (t->value != 0) {  
        count++;  
    }

    tree_t *child = t->first_child;

    // Traverse all children
    while (child != NULL) {
        count += traverse(child, money);
        child = child->next_sibling;
    }
    
    return count;
}


int main(void) {
    int n, money, p, c, robber;
    tree_t *t = NULL;

    
    tree_t **node_map = (tree_t **)calloc(100001, sizeof(tree_t *));  

    
    scanf("%d %d", &n, &money);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &p, &c, &robber);
        t = attach(t, p, c, robber, node_map);
    }

    printf("%d\n", traverse(t, money));

    return 0;
}