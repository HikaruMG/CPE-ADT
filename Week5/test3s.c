#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
int n,m;
bool cdigi(int number, int k) {
    while (number > 0) {
        if (number % 10 == k) {
            return true;
        }
        number /= 10;
    }
    return false;
}

typedef struct node {
  int data;
  int number;
  struct node *next;
}node_t;

void show(node_t *h){
  node_t *t = h;
  while(t->next!=h){
    printf("%d ",t->data);
    t = t->next;
  }
  printf("%d\n",t->data);

  t = t->next;
  while(t->next!=h){
    printf("%d ",t->number);
    t = t->next;
  }
  printf("%d ",t->number);
  printf("\n");
}

void delete(node_t *to){
  node_t *tmp = to->next;
  if(to->next->next->data==-1) delete(to->next);
  to->next = to->next->next;
  free(tmp);
}

void play(node_t *h){
  node_t *t = h;
  int count=1;
  while(1){
    if(t->next->data==-1) {
        delete(t);}
    if(count%m==0||cdigi(count,m)){
      t->data -= 1;
    }
    if(t->next==t) break;
    t = t->next;
    count++;
  }
  printf("%d\n",t->number);
}

node_t *append(node_t* h,int x,int n)
{  
    node_t *t = (node_t*)malloc(sizeof(node_t));  
    t->data = x; 
   t->number = n; 
    if(h == NULL)  
    {  
        h = t; 
        t -> next = h;    
    }  
    else  
    {  
        node_t *to = nodest;  
        while(to -> next != nodest)  
        {  
            to = to -> next;  
        }  
        to -> next = new_node;  
    //printf("%d\n",to -> next ->data);  
        new_node -> next = nodest;  
    }  
  return nodest;
}  

int main(void) {
  node_t *startNode;
  startNode = NULL;
  scanf("%d %d",&n,&m);
  for(int i=1;i<=n;i++){
    int s;
    scanf("%d",&s);
    startNode = append(startNode,s,i);
  }
  //show(startNode);
  play(startNode);
  return 0;
}