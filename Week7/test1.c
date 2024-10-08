#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int value;
    struct node *next_sibling;
    struct node *first_child;
} node_t;
typedef node_t tree_t;
tree_t* pos; 

tree_t* searchx(tree_t *t, int v) {
    if (t == NULL || t->value == v){
        return t;
    }
    pos = searchx(t->first_child, v);
    if (pos != NULL) {
        return pos;
    } else {
        return searchx(t->next_sibling, v);
    }
}

int search(tree_t *t, int node_value) {\
    if(searchx(t, node_value) != NULL) {
        return 1;
    }else{
        return 0;
    }
}

tree_t* attach(tree_t *t, int parent, int child) {
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = child;
    new_node->first_child = NULL;
    new_node->next_sibling = NULL;

    pos = searchx(t, parent);
    if (pos->first_child == NULL) {
        pos->first_child = new_node;
    }else {
        pos = pos->first_child;
        while (pos->next_sibling != NULL) {
            pos = pos->next_sibling;
        }
        pos->next_sibling = new_node;
    }
    return t;
}

// tree_t* detach(tree_t *t, int node_value) {
//     if (t == NULL) return NULL;
//     if (t->value == node_value) {
//         tree_t *new_root = t->first_child;
//         free(t);
//         return new_root;
//     }

//     tree_t *parent = NULL;
//     tree_t *current = t;
//     while (current != NULL) {
//         tree_t *child = current->first_child;
//         if (child != NULL && child->value == node_value) {
//             parent = current;
//             break;
//         }
//         while (child != NULL) {
//             if (child->value == node_value) {
//                 parent = current;
//                 break;
//             }
//             child = child->next_sibling;
//         }
//         if (parent != NULL) break;
//         current = current->next_sibling;
//     }

//     if (parent == NULL) return t;

//     tree_t *to_detach = parent->first_child;
//     if (to_detach->value == node_value) {
//         parent->first_child = to_detach->next_sibling;
//     } else {
//         tree_t *prev_child = to_detach;
//         tree_t *curr_child = to_detach->next_sibling;
//         while (curr_child != NULL && curr_child->value != node_value) {
//             prev_child = curr_child;
//             curr_child = curr_child->next_sibling;
//         }
//         if (curr_child != NULL) {
//             prev_child->next_sibling = curr_child->next_sibling;
//             to_detach = curr_child;
//         }
//     }
//     free(to_detach);
//     return t;
// }

// int degree(tree_t *t, int v) {
//     pos = searchx(t, v);
//     int count = 0;
//     while(pos->first_child != NULL) {
//         count++;
//         pos = pos->next_sibling;
//     }
//     return count;
// }

// int is_root(tree_t *t, int v) {
//     if(t!=NULL && t->value == v) {
//         return 1;
//     }
//     else {
//         return 0;
//     }
// }

// int is_leaf(tree_t *t, int v) {
//     pos = searchx(t, v);
//     if(pos->first_child == NULL) {
//         return 1;
//     }
//     else {
//         return 0;
//     }
// }

// void siblings(tree_t *t, int v) {
//     pos = searchx(t, v);
//     while (pos->next_sibling != NULL)
//     {
//         printf("%d ", pos->next_sibling->value);
//         pos = pos->next_sibling;
//     }

// }

// int find_depth(tree_t *t, int v,int deph) {
//     if(t->value == v) {
//         return deph;
//     }
//     int val = find_depth(t->first_child, v, deph+1);
//     if(val != -1) {
//         return val;
//     }
//     return find_depth(t->next_sibling, v, deph);
// }
// int depth(tree_t *t, int v) {
//     return find_depth(t, v, 0);
// }

// int find_path(tree_t *t, int start, int end, int path[], int *path_len) {
// if (t == NULL) return 0;
//     path[*path_len] = t->value;
//     (*path_len)++;
//     if (t->value == start) {
//         if (searchx(t, end)) return 1;
//         (*path_len)--;
//         return 0;
//     }
//     if (find_path(t->first_child, start, end, path, path_len)) return 1;
//     if (find_path(t->next_sibling, start, end, path, path_len)) return 1;
//     (*path_len)--;
//     return 0;
// }
// void print_path(tree_t *t, int start, int end) {
//     int path[100]; // Arbitrary large size for path
//     int path_len = 0;
//     find_path(t, start, end, path, &path_len);
//     for (int i = 0; i < path_len; i++) {
//         printf("%d ", path[i]);
//     }
//     printf("\n");
// }

// int path_length(tree_t *t, int start, int end) {
//     int path[100];
//     int path_len = 0;
//     if (find_path(t, start, end, path, &path_len)) {
//         return path_len - 1;
//     }
//     return -1; // Return -1 if path is not found
// }

// void ancestor(tree_t *t, int v) {
//     pos = searchx(t, v);
//     while(pos != NULL) {
//         printf("%d ", pos->value);
//         pos = searchx(t, pos->value);
//     }
//     printf("\n");
// }
// void find_descendants(tree_t *t) {
//     tree_t* first = t->first_child;
//     while(first != NULL) {
//         printf("%d ", first->value);
//         find_descendants(first);
//         first = first->next_sibling;
//     }
// }
// void descendant(tree_t *t, int v) {
//     pos = searchx(t, v);
//     find_descendants(pos);
//     printf("\n");
// }

// void bfs(tree_t *t) {
//     tree_t *q[10000];
//     int front = 0, rear = 0;
//     q[rear++] = t;
//     while(front < rear) {
//         pos = q[front++];
//         printf("%d ", pos->value);
//         tree_t* first = pos->first_child;
//         while(first != NULL) {
//             q[rear++] = first;
//             first = first->next_sibling;
//         }    
//     }
//     printf("\n");
// }

// void print_tree_recursive(tree_t *t, int level) {
//     if (t == NULL) return;

//     for (int i = 0; i < level; i++) {
//         printf("    ");
//     }
//     printf("%d\n", t->value);

//     tree_t *child = t->first_child;
//     while (child != NULL) {
//         print_tree_recursive(child, level + 1);
//         child = child->next_sibling;
//     }
// }

// void print_tree(tree_t *t) {
//     print_tree_recursive(t, 0);
// }

// void dfs(tree_t *t) {
//     tree_t *stack[10000];
//     int top = -1;
//     stack[++top] = t;
//     while(top >= 0) {
//         pos = stack[top--];
//         printf("%d ", pos->value);
//         tree_t* first = pos->first_child;
//         while(first != NULL) {
//             stack[++top] = first;
//             first = first->next_sibling;
//         }
//     }
//     printf("\n");
// }
int main(void) {
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d %d", &parent, &child);
                t = attach(t, parent, child);
                break;
            // case 2:
            //     scanf("%d", &node);
            //     t = detach(t, node);
            //     break;
            case 3:
                scanf("%d", &node);
                printf("%d\n", search(t, node));
                break;
            // case 4:
            //     scanf("%d", &node);
            //     printf("%d\n", degree(t, node));
            //     break;
            // case 5:
            //     scanf("%d", &node);
            //     printf("%d\n", is_root(t, node));
            //     break;
            // case 6:
            //     scanf("%d", &node);
            //     printf("%d\n", is_leaf(t, node));
            //     break;
            // case 7:
            //     scanf("%d", &node);
            //     siblings(t, node);
            //     break;
            // case 8:
            //     scanf("%d", &node);
            //     printf("%d\n", depth(t, node));
            //     break;
            // case 9:
            //     scanf("%d %d", &start, &end);
            //     print_path(t, start, end);
            //     break;
            // case 10:
            //     scanf("%d %d", &start, &end);
            //     printf("%d\n",
            //     path_length(t, start, end));
            //     break;
            // case 11:
            //     scanf("%d", &node);
            //     ancestor(t, node);
            //     break;
            // case 12:
            //     scanf("%d", &node);
            //     descendant(t, node);
            //     break;
            // case 13:
            //     bfs(t);
            // break;
            //     case 14:
            //     dfs(t);
            //     break;
            // case 15:
            //     print_tree(t);
            //     break;
        }
    }
    return 0;
}