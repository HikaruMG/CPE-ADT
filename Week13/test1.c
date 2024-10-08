#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int vj;
    int weight;
} Edge;

typedef struct {
    Edge* edges;
    int c_edge;
    int max_arr;
} Node;



void add_edge(Node* list_adj, int vi, int vj, int weight) {

    if (list_adj[vi].c_edge == list_adj[vi].max_arr) {
        list_adj[vi].max_arr *= 2;
        list_adj[vi].edges = (Edge*)realloc(list_adj[vi].edges, list_adj[vi].max_arr * sizeof(Edge));
    }
    list_adj[vi].edges[list_adj[vi].c_edge].vj = vj;
    list_adj[vi].edges[list_adj[vi].c_edge].weight = weight;
    list_adj[vi].c_edge++;
}

void dfs(int u, int t, int currentweight, Node* list_adj, int* visit, int* bestedge) {
    if (u == t) {
        if (currentweight < *bestedge) {
            *bestedge = currentweight;
        }
        return;
    }
    visit[u] = 1;

    for (int i = 0; i < list_adj[u].c_edge; i++) {
        int vj = list_adj[u].edges[i].vj;
        int weight = list_adj[u].edges[i].weight;

        if (!visit[vj]) {
            dfs(vj, t, currentweight + weight, list_adj, visit, bestedge);
        }
    }
    visit[u] = 0;
}

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    Node* list_adj = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) { //init adjList
        list_adj[i].edges = (Edge*)malloc(2 * sizeof(Edge)); // เริ่มต้นด้วยความจุ 2
        list_adj[i].c_edge = 0;
        list_adj[i].max_arr = 2;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(list_adj, u, v, w);
        add_edge(list_adj, v, u, w);
    }

    for (int i = 0; i < p; i++) {
        int* visit = (int*)calloc(n, sizeof(int));
        int bestedge = INT_MAX;
        int vi, vj;
        scanf("%d %d", &vi, &vj);
        dfs(vi, vj, 0, list_adj, visit, &bestedge);

        if (bestedge == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", bestedge);
        }
        free(visit);
    }
    for (int i = 0; i < n; i++) {
        free(list_adj[i].edges);
    }
    free(list_adj);
    return 0;
}
