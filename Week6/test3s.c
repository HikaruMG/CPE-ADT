#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int value;
    struct node *top;
    struct node *bot;
} node_t;
typedef node_t stack_t;

stack_t* push(stack_t *s , int value){
    node_t *tnode = (node_t *)malloc(sizeof (node_t));
    tnode->top =  NULL;
    tnode->bot = NULL;
    tnode->value = value;
    if(s == NULL){
        return tnode;
    }
    else{
        s->top = tnode;
        tnode->bot = s;
        return tnode; 
    }
}
stack_t* restack(stack_t *s){
    while(s->bot != NULL){
        s = s->bot;
    }
    return s;
}
int issamilar(stack_t *first, stack_t *second ){
    node_t *tmp1 = first, *tmp2 = second;
    while(tmp1 != NULL){
        if(tmp1->value != tmp2->value){
         return 0;   
        }
        tmp1 = tmp1->top;
        tmp2 = tmp2->bot;
    }
    return  1;
}
int main(void){
    char text[100000];
    int i, n1 = 0, n2 = 0;
    stack_t *first = NULL, *second = NULL;
    fgets(text ,100000, stdin);

    for(i= 0; text[i] != 'x'; i++){
        first = push(first, text[i]);
        n1++;
    }
    i++;
    for(i; text[i] != 'y'; i++){
        second = push(second, text[i]);
        n2++;
    }
    if(n1 != n2){
        printf("0");
    }
    else{
        first = restack(first);
        printf("%d",issamilar(first , second));
    }
    return 0;
}