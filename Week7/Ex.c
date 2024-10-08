#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *parent;
    struct node *next_sibling;
    struct node *first_child;
} node_t;
typedef node_t tree_t;
//Queue
typedef struct node2 {
    int data;
    struct node2 *prev;
    struct node2 *next;
} node2_t;

typedef struct queue {
    node2_t *front;
    node2_t *rear;
} queue_t;

// Function prototypes
void equeue(queue_t *q, int data);
int dequeue(queue_t *q);
tree_t *search_node(tree_t *t,int v);
tree_t *attach (tree_t *t,int p,int c);
tree_t *detach (tree_t *t,int v);
int search (tree_t *t,int v);
int degree (tree_t *t,int v);
int is_root (tree_t *t,int v);
int is_leaf(tree_t *t, int v);
void descendant(tree_t *t, int v);
void ancestor(tree_t *t, int v);
void siblings(tree_t *t, int v);
int depth(tree_t *t, int v);
int for_print(tree_t *start, tree_t *end);
int path_length(tree_t *t, int start, int end);
void print_path(tree_t *t, int start, int end);
void bfs(tree_t *t);
void dfs(tree_t *t);
void for_print_tree(tree_t *t, int depth);
void print_tree(tree_t *t);

int main(void) {
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d %d", &parent, &child);
                t = attach(t, parent, child);
                break;
            case 2:
                scanf("%d", &node);
                t = detach(t, node);
                break;
            case 3:
                scanf("%d", &node);
                printf("%d\n", search(t, node));
                break;
            case 4:
                scanf("%d", &node);
                printf("%d\n", degree(t, node));
                break;
            case 5:
                scanf("%d", &node);
                printf("%d\n", is_root(t, node));
                break;
            case 6:
                scanf("%d", &node);
                printf("%d\n", is_leaf(t, node));
                break;
            case 7:
                scanf("%d", &node);
                siblings(t, node);
                break;
            case 8:
                scanf("%d", &node);
                printf("%d\n", depth(t, node));
                break;
            case 9:
                scanf("%d %d", &start, &end);
                print_path(t, start, end);
                break;
            case 10:
                scanf("%d %d", &start, &end);
                printf("%d\n", path_length(t, start, end));
                break;
            case 11:
                scanf("%d", &node);
                ancestor(t, node);
                break;
            case 12:
                scanf("%d", &node);
                descendant(t, node);
                break;
            case 13:
                bfs(t);
                break;
            case 14:
                dfs(t);
                break;
            case 15:
                print_tree(t);
                break;
        }
    }
    return 0;
}

// Function implementations
tree_t *search_node(tree_t *t, int v) {
    if (t == NULL) {
        return NULL;
    }
    if (t->value == v) {
        return t;
    }
    tree_t *pos = search_node(t->first_child, v);
    if (pos != NULL) {
        return pos;
    }
    else{
        return search_node(t->next_sibling, v);
    }
}

tree_t *attach(tree_t *t, int p, int c) {
    tree_t *new_node = (tree_t *)malloc(sizeof(tree_t));
    new_node->value = c;
    new_node->parent = NULL;
    new_node->first_child = NULL;
    new_node->next_sibling = NULL;

    if (t == NULL) {
        return new_node;
    }

    tree_t *pos = search_node(t, p);
    if (pos == NULL) {
        free(new_node);
        return t;
    }

    if (pos->first_child == NULL) {
        pos->first_child = new_node;
        new_node->parent = pos;
        return t;
    } else {
        pos = pos->first_child;
        while (pos->next_sibling != NULL) {
            pos = pos->next_sibling;
        }
        new_node->parent = pos;
        pos->next_sibling = new_node;
        return t;
    }
}

tree_t *detach(tree_t *t, int v) {
    tree_t *pos = search_node(t, v);
    tree_t *parent = pos->parent;
    if(t==NULL){
        return t;
    }
    if(pos==NULL){
        return t;
    }
    if(parent->first_child==pos){
        parent->first_child=pos->next_sibling;
    }
    else{
        parent->next_sibling=pos->next_sibling;
    }
    if(pos->next_sibling!=NULL){
        pos->next_sibling->parent=parent;
    }
    return t;
}

int search(tree_t *t, int v) {
    return search_node(t, v) != NULL ? 1 : 0;
}

int degree(tree_t *t, int v) {
    tree_t *pos = search_node(t, v);
    int count = 0;
    pos = pos->first_child;
    while ( pos != NULL) {
        count++;
        pos = pos->next_sibling;
    }
    return count;
}

int is_root(tree_t *t, int v) {
    if (t != NULL && t->value == v) {
        return 1;
    }
    else {
        return 0;
    }
}

int is_leaf(tree_t *t, int v) {
    tree_t *pos = search_node(t, v);
    if (pos->first_child == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

void siblings(tree_t *t, int v){
    tree_t *pos = search_node(t, v);
    tree_t *tmp = pos;
    if(pos == NULL||pos->parent == NULL|| (pos == pos->parent->first_child && pos->next_sibling == NULL)){
        printf("\n");
    }
    else{
        while (tmp->parent->first_child != tmp){
           tmp = tmp->parent;
        }
        if(tmp->parent->first_child == tmp){
            while(tmp != pos){
                printf("%d ", tmp->value);
                tmp = tmp->next_sibling;
            }
        }
        while (pos->next_sibling != NULL){
            printf("%d ", pos->next_sibling->value);
            pos = pos->next_sibling;
        }
        printf("\n");
    }
}

int depth(tree_t *t, int v) {
    tree_t *pos = search_node(t, v);
    int count = 0;
    if(pos == NULL||pos==t){
        return 0;
    }
    else{
        while (pos!=t)
        {
            if(pos->parent->first_child == pos){
                count++;
            }
            pos = pos->parent;
        }
        return count;

    }
}

int for_print(tree_t *start, tree_t *end) {
    tree_t *tmp = end;
    if(start == end){
        printf("%d ", start->value);
        return start->value;
    }
    while (end->parent!=NULL&&end->parent->first_child!=end){
        end = end->parent;
    }
    for_print(start, end->parent);
    printf("%d ", tmp->value);
    return tmp->value;
}

void print_path(tree_t *t, int start, int end) {
    tree_t *startX = search_node(t, start);
    tree_t *endX = search_node(t, end);
    for_print(startX, endX);
    printf("\n");
}

int path_length(tree_t *t, int start, int end) {
    return depth(t, end) - depth(t, start) +1;
}

void ancestor(tree_t *t, int v) {
    print_path(t,t->value, v);
}

void enqueue(queue_t *q, int data){
  node2_t *new_node = (node2_t *)malloc(sizeof(node2_t));
  new_node->data = data;
  new_node->next = NULL;
  new_node->prev = NULL;
  if(q->rear == NULL){
    q->front = new_node;
    q->rear = new_node;
  }
  else{
    q->rear->next = new_node;
    new_node->prev = q->rear;
    q->rear = new_node;
  }
}

int dequeue(queue_t *q){
  node2_t *tmp = q->front;
  int data = q->front->data;
  q->front = q->front->next;
  if (q->front == NULL) {
      q->rear = NULL;
  } else {
      q->front->prev = NULL;
  }
  free(tmp);
  return data;
}


void dfs(tree_t *t){//#14
    if (t == NULL){
        return ;
    }
    printf("%d ", t->value);
    dfs(t->first_child);
    dfs(t->next_sibling);
}
void bfs(tree_t *t){
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    q->front = q->rear = NULL;
    enqueue(q,t->value);
    while(q->front!=NULL){
        int val = q->front->data;
        tree_t *pos = search_node(t, val);
        tree_t *child = pos->first_child;
        while(child!=NULL){
        enqueue(q,child->value);
        child = child->next_sibling;
        }
        printf("%d ", dequeue(q));
    }
}

void for_print_tree(tree_t *t, int depth){
  if (t == NULL){
      return ;
  }
  for (int i = 0; i < depth; i++) {
      printf("    ");
  }
  printf("%d\n", t->value);
  for_print_tree(t->first_child, depth + 1);
  for_print_tree(t->next_sibling, depth);
}

void print_tree(tree_t *t){
  for_print_tree(t, 0);
}

void descendant(tree_t *t , int v){//#12
    bfs(search_node(t, v));
    printf("\n");
}
