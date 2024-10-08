#include <stdio.h>
#include <stdlib.h>
typedef struct node {
int data;
struct node *next;
} node_t;
typedef node_t queue_t;

queue_t* enqueue(queue_t *q, int value) {
    node_t *tnode = (node_t*)malloc(sizeof(node_t));
    tnode->data = value;
    tnode->next = NULL;
    if (q == NULL) {
        return tnode;
    } else {
        node_t *cnode = q;
        while (cnode->next != NULL) {
              cnode = cnode->next;
        }
        cnode->next = tnode;
        return q;
    }
}

queue_t* dequeue(queue_t *q){
  if(q!=NULL){
    node_t *tmp = q;
    printf("%d\n", q->data);
      q = q->next;
      free(tmp);
    } else {
      printf("Queue is empty.\n");
    }
  return q;
}

void show(queue_t *q){
  node_t *cnode = q;
  if(cnode==NULL){
    printf("Queue is empty.\n");
    return;
  }
  while (cnode!=NULL){
    printf("%d ",cnode->data);
    cnode = cnode->next;
  }
  printf("\n");
}

void empty(queue_t *q){
  if(q==NULL){
    printf("Queue is empty.\n");
  }
  else{
    printf("Queue is not empty.\n");
  }
}

void size(queue_t *q){
  int count = 0;
  node_t *cnode = q;
  while(cnode!=NULL){
    count++;
    cnode = cnode->next;
  }
  printf("%d\n", count);
}
int main(void) {
queue_t *q = NULL;
int n, i, command, value;
scanf("%d", &n);
for (i=0; i<n; i++) {
scanf("%d", &command);
switch(command) {
case 1:
scanf("%d", &value);
q = enqueue(q, value);
break;
case 2:
q = dequeue(q);
break;
case 3:
show(q);
break;
case 4:
empty(q);
break;
case 5:
size(q);
break;
}
}
return 0;
}