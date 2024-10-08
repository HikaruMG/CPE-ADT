#include <stdio.h>
#include <stdlib.h>
#define max_nodes 100000

typedef struct Node {
    int node;
    struct Node* next;
} Node;

Node* adj_list[max_nodes];

void add_edge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->node = v;
    newNode->next = adj_list[u];
    adj_list[u] = newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->node = u;
    newNode->next = adj_list[v];
    adj_list[v] = newNode;
}

int count = 0;
int dis_time[max_nodes], low_time[max_nodes];
int visit[max_nodes];
int spof[max_nodes];
void dfs(int u, int prenode) {
    int degree = 0;
    visit[u] = 1; 
    dis_time[u] = low_time[u] = ++count; 

    Node* tmp = adj_list[u];
    while (tmp != NULL) {
        int v = tmp->node;
        if (!visit[v]) {
            degree++;
            dfs(v, u);
            low_time[u] = (low_time[v]<low_time[u]) ? low_time[v]:low_time[u];
            
            if (prenode != -1 && low_time[v] >= dis_time[u])
                spof[u] = 1;
            if (prenode == -1 && degree > 1)
                spof[u] = 1;
        } else if (v != prenode) {
            low_time[u] = (dis_time[v]<low_time[u]) ? dis_time[v]:low_time[u];
        }
        tmp = tmp->next;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    for (int i = 0; i < n; i++) {
        visit[i] = 0;
        spof[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (!visit[i])
            dfs(i, -1);
    }
    int printspof = 0;
    for (int i = 0; i < n; i++) {
        if (spof[i]) {
            if (printspof) {
                printf(" ");
            }
            printf("%d", i);
            printspof = 1;
        }
    }
    if (!printspof) {
        printf("\n");
    }
    return 0;
}
