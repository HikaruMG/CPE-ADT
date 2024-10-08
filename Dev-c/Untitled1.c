#include <stdio.h>
typedef struct node{
  int value;
  struct node *link;
}NODE;

int main(){
  NODE *p=NULL,*h=NULL;
  p = (NODE *)malloc(sizeof(NODE));
  printf("Enter Value: "); scanf("%d",&p->value);
  p->link = h;
  h = p;
  printf("h->value = %d\n",h->value);
  return 0;
}
