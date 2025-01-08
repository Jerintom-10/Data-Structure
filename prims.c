#include <stdio.h>
#include <limits.h>

#define V 5

// Function to find the vertex with minimum key value
int minKey(int key[], int mstSet[]) {
    int min_val = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (key[v] < min_val && mstSet[v] == 0)
            min_val = key[v], min_index = v;
    return min_index;
}

// Function to print the constructed MST
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}
void primMST(int graph[V][V]) {
    int key[V], parent[V], mstSet[V];
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;
    key[0] = 0;
    parent[0] = -1;

    for (int cout = 0; cout < V - 1; cout++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    printMST(parent, graph);
}

// Driver code
int main() {
    int graph[V][V] = {{0, 2, 0, 6, 0},
                          {2, 0, 3, 8, 5},
                          {0, 3, 0, 0, 7},
                          {6, 8, 0, 0, 9},
                          {0, 5, 7, 9, 0}};

    primMST(graph);

    return 0;
}
