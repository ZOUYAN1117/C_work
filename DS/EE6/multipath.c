#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    int id;
} Edge;

typedef struct Vertex {
    Edge *edges;
    int degree;
    int capacity;
} Vertex;

int compare_edges(const void *a, const void *b) {
    return ((Edge *)a)->id - ((Edge *)b)->id;
}

void add_edge(Vertex *v, int to, int id) {
    if (v->degree >= v->capacity) {
        v->capacity = v->capacity == 0 ? 4 : v->capacity * 2;
        v->edges = realloc(v->edges, v->capacity * sizeof(Edge));
    }
    v->edges[v->degree].to = to;
    v->edges[v->degree].id = id;
    v->degree++;
}

int n, e;
Vertex *vertices;
int *visited;
int *path;

void dfs(int u, int path_len) {
    if (u == n - 1) {
        for (int i = 0; i < path_len; i++) {
            printf("%d%c", path[i], (i == path_len - 1) ? '\n' : ' ');
        }
        return;
    }
    
    for (int i = 0; i < vertices[u].degree; i++) {
        int v = vertices[u].edges[i].to;
        int id = vertices[u].edges[i].id;
        if (!visited[v]) {
            visited[v] = 1;
            path[path_len] = id;
            dfs(v, path_len + 1);
            visited[v] = 0;
        }
    }
}

int main() {
    if (scanf("%d %d", &n, &e) != 2) {
        return 0;
    }
    
    vertices = calloc(n, sizeof(Vertex));
    for (int i = 0; i < e; i++) {
        int id, u, v;
        if (scanf("%d %d %d", &id, &u, &v) != 3) {
            break;
        }
        add_edge(&vertices[u], v, id);
        add_edge(&vertices[v], u, id);
    }
    
    for (int i = 0; i < n; i++) {
        if (vertices[i].degree > 0) {
            qsort(vertices[i].edges, vertices[i].degree, sizeof(Edge), compare_edges);
        }
    }
    
    visited = calloc(n, sizeof(int));
    path = malloc(n * sizeof(int));
    
    visited[0] = 1;
    dfs(0, 0);
    
    // Free memory
    for (int i = 0; i < n; i++) {
        free(vertices[i].edges);
    }
    free(vertices);
    free(visited);
    free(path);
    
    return 0;
}
