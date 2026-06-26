#include <stdio.h>
#include <stdlib.h>

// Edge structure
typedef struct {
    int id;
    int u;
    int v;
    int weight;
} Edge;

// DSU parent array
int *parent;

// DSU find with path compression
int find_set(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_set(parent[i]);
}

// DSU union
void union_sets(int i, int j) {
    int root_i = find_set(i);
    int root_j = find_set(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

// Comparison function for qsort to sort edges by weight, and secondary by id
int compare_edges(const void *a, const void *b) {
    const Edge *edge_a = (const Edge *)a;
    const Edge *edge_b = (const Edge *)b;
    if (edge_a->weight != edge_b->weight) {
        return edge_a->weight - edge_b->weight;
    }
    return edge_a->id - edge_b->id;
}

// Comparison function for sorting selected edge IDs
int compare_ints(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int main() {
    int n, e;
    if (scanf("%d %d", &n, &e) != 2) {
        return 0;
    }

    Edge *edges = malloc(e * sizeof(Edge));
    for (int i = 0; i < e; i++) {
        if (scanf("%d %d %d %d", &edges[i].id, &edges[i].u, &edges[i].v, &edges[i].weight) != 4) {
            // handle incomplete inputs if any
        }
    }

    // Sort edges by weight
    qsort(edges, e, sizeof(Edge), compare_edges);

    // Initialize DSU parent array
    parent = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int *selected_ids = malloc((n - 1) * sizeof(int));
    int selected_count = 0;
    long long total_weight = 0;

    for (int i = 0; i < e; i++) {
        if (find_set(edges[i].u) != find_set(edges[i].v)) {
            union_sets(edges[i].u, edges[i].v);
            total_weight += edges[i].weight;
            selected_ids[selected_count++] = edges[i].id;
            if (selected_count == n - 1) {
                break;
            }
        }
    }

    // Sort selected edge IDs in ascending order
    qsort(selected_ids, selected_count, sizeof(int), compare_ints);

    // Output results
    printf("%lld\n", total_weight);
    for (int i = 0; i < selected_count; i++) {
        printf("%d%c", selected_ids[i], (i == selected_count - 1) ? '\n' : ' ');
    }

    free(edges);
    free(parent);
    free(selected_ids);

    return 0;
}
