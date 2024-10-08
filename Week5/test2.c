#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *next;
} node_t;

node_t* append(node_t *h){
    int n;
    scanf("%d",&n);
    node_t *t = (node_t *)malloc(sizeof(node_t));
    t->data = n;
    t->next = NULL;

    if (h == NULL) {
        return t;
    }

    node_t *p = h;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = t;
    return h;
    
}

void show(node_t *h){
    node_t *p = h;
    while (p != NULL) {
        printf("%d", p->data);
        if (p->next != NULL) {
            printf(" ");
        }
        p = p->next;
    }
    printf("\n");
}

void get(node_t *h){
    int index;
    scanf("%d",&index);
    node_t *p = h;
    for(int i = 0; i<index;i++){
        p = p->next;
    }
    printf("%d\n", p->data);
}

node_t* reverse(node_t *h){
    node_t *p = h;
    node_t *pp = NULL;
    node_t *np = NULL;
    while (p != NULL)
    {
        np = p->next;
        p->next = pp;
        pp = p;
        p = np;
    }
    return pp;
}

node_t* cut(node_t *h){
    int first,last,index=0;
    scanf("%d %d",&first,&last);
    node_t *p =h;
    node_t *th = NULL;
    node_t *al = NULL;

    while (p != NULL&& index<first)
    {
        p = p->next;
        index++;
    }
    
    while(p != NULL && index <= last){
        node_t *tn = (node_t*)malloc(sizeof(node_t));
        tn->data = p->data;
        tn->next = NULL;
        if (th == NULL){
            th = tn;
            al = th;
        }else{
            al->next = tn;
            al = tn;
        }
        p = p->next;
        index++;
    }
    return th;
}
int main(void) {
    node_t *startNode;
    int n,i;
    char command;

    startNode = NULL;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf(" %c", &command);
        switch (command) {
        case 'A':
            startNode = append(startNode);
            break;
        case 'G':
             get(startNode);
            break;
        case 'S':
            show(startNode);
            break;
        case 'R':
             startNode = reverse(startNode);
            break;
        case 'C':
             startNode = cut(startNode);
            break;
        default:
            break;
        }
    }
    return 0;
}