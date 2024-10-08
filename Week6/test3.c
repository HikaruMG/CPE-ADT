#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    char data;
    struct node *next;
} node_t;

typedef node_t* stack_t;

void push(stack_t *s, char value) {
    node_t *tnode = (node_t*)malloc(sizeof(node_t));
    tnode->data = value;
    tnode->next = *s;
    *s = tnode;
}

char pop(stack_t *s) {
    if (*s == NULL) {
        return '\0';
    } else {
        node_t *tmp = *s;
        char data = tmp->data;
        *s = (*s)->next;
        free(tmp);
        return data;
    }
}
int main(void) {
    char text[1000];
    scanf("%s", text);
    int i,len,px,py,h=NULL;
    for (i = 0; text[i] != '\0'; ++i);
    len = i;

    for(i = 0; i < len; ++i) {
        if (text[i] == 'x') {
            px = i;
            break;
        }
    }
    stack_t first = h;

    for(int i = 0; i < px;i++) {
        push(&first, text[i]);
    }

    bool ans = true;
    for(int i = px +1; i< len-1; i++){
        char top = pop(&first);
        if(top != text[i]){
            ans = false;
            break;
        }
    }
    if (ans) {
        printf("1\n");
    } else {
        printf("0\n");
    }
}