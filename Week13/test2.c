#include <stdio.h>
#include <stdlib.h>
#define max_nodes 100000

typedef struct {
    int **matrixadj;
    int size;
} graph;

graph* newgraph(int n) {
    graph* tmp = (graph*)malloc(sizeof(graph));
    tmp->matrixadj = (int**)malloc(n * sizeof(int*));
    tmp->size = n;
    for (int i = 0; i < n; i++) {
        tmp->matrixadj[i] = (int*)calloc(n, sizeof(int));
    }
    return tmp;
}

int checkcl(graph* graph, int* cl, int size_cl) {
    for (int i = 0; i < size_cl; i++) {
        for (int j = i + 1; j < size_cl; j++) {
            if (!graph->matrixadj[cl[i]][cl[j]]) {
                return 0;
            }
        }
    }
    return 1;
}

void Ismaxcl(graph* graph, int* cl, int size_cl, int start, int* size_max) {
    if (size_cl > *size_max) {
        *size_max = size_cl;
    }
    for (int i = start; i < graph->size; i++) {
        cl[size_cl] = i; 
        if (checkcl(graph, cl, size_cl + 1)) {
            Ismaxcl(graph, cl, size_cl + 1, i + 1, size_max);
        }
    }
}

void addEdgraphe(graph* graph, int vi, int vj) {
    graph->matrixadj[vi][vj] = 1;
    graph->matrixadj[vj][vi] = 1; 
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    graph* graph = newgraph(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdgraphe(graph, u, v);
    }

    int maxcl = 0;
    int cl[max_nodes];
    Ismaxcl(graph, cl, 0, 0, &maxcl);
    printf("%d\n", maxcl);
    return 0;
}
