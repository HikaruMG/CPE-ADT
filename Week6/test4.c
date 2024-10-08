#include <stdio.h>
#include <stdlib.h>
#define NMAX 100000
int soi[NMAX];
int top = -1;
int isEmpty() {
    return top == -1;
}
void push(int x) {
    soi[++top] = x;
}
int pop() {
    return soi[top--];
}
int main() {
    int i, n;
    scanf("%d", &n);
    int *parate = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        scanf("%d", &parate[i]);
    }
    int start = 1;
    for (i = 0; i < n; i++) {
        while (!isEmpty() && soi[top] == start) {
            pop();
            start++;
        }
        if (parate[i] == start) {
            start++;
        } else {
            push(parate[i]);
        }
    }
    while (!isEmpty()&&soi[top]==start) {
        pop();
        start++;
    }
    if (start==n+1) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    free(parate);
    return 0;
}
