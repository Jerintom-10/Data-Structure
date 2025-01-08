#include <stdio.h>
#include <stdlib.h>
struct Edge{
    int src, dest, weight;
};

struct Graph {
    int V, E; 
    struct Edge* edges;
};
struct Subset
{
int parent;
int rank;
};
struct Graph* createGraph(int V, int E)
{
struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
graph->V = V;
graph->E = E;
graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
return graph;
}
int find(struct Subset subsets[], int i)
{
if (subsets[i].parent != i)
subsets[i].parent = find(subsets, subsets[i].parent);
return subsets[i].parent;
}
void Union(struct Subset subsets[], int x, int y)
{
int rootX = find(subsets, x);
int rootY = find(subsets, y);
if (subsets[rootX].rank < subsets[rootY].rank)
subsets[rootX].parent = rootY;
else if (subsets[rootX].rank > subsets[rootY].rank)
subsets[rootY].parent = rootX;
else
{
subsets[rootY].parent = rootX
subsets[rootX].rank++;
}
}
int compareEdges(const void* a, const void* b)
{
struct Edge* edgeA = (struct Edge*)a;
struct Edge* edgeB = (struct Edge*)b;
return edgeA->weight - edgeB->weight;
}
void KruskalMST(struct Graph* graph)
{
int V = graph->V;
struct Edge result[V]; 
    int e = 0; 
    int i = 0; 
qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);
struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
for (int v = 0; v < V; v++)
{
subsets[v].parent = v;
subsets[v].rank = 0;
}
while (e < V - 1 && i < graph->E) {
struct Edge nextEdge = graph->edges[i++];
int x = find(subsets, nextEdge.src);
int y = find(subsets, nextEdge.dest);
if (x != y)
{
result[e++] = nextEdge;
Union(subsets, x, y);
}
}
printf("Following are the edges in the MST:\n");
int totalWeight = 0;
for (i = 0; i < e; i++) 
{
printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
totalWeight += result[i].weight;
}
printf("Total weight of MST: %d\n", totalWeight);
free(subsets);
}
int main()
{
int V, E;
printf("Enter the number of vertices and edges: ");
scanf("%d %d", &V, &E);
struct Graph* graph = createGraph(V, E);
printf("Enter the edges (source, destination, weight):\n");
for (int i = 0; i < E; i++)
{
scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
}
KruskalMST(graph);
free(graph->edges);
free(graph);
return 0;
}
