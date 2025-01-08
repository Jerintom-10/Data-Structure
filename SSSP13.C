#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF INT_MAX
int minDistance(int dist[], int sptSet[], int V) 
{
int min = INF, minIndex;
for (int v = 0; v < V; v++) 
{
if (sptSet[v] == 0 && dist[v] <= min)
{
min = dist[v];
minIndex = v;
}
}
return minIndex;
}
void printSolution(int dist[], int V)
{
printf("Vertex \t Distance from Source\n");
for (int i = 0; i < V; i++)
{
printf("%d \t %d\n", i, dist[i]);
}
}
void dijkstra(int **graph, int V, int src) {
int dist[V];
int sptSet[V]; 
for (int i = 0; i < V; i++)
{
dist[i] = INF;
sptSet[i] = 0;
}
dist[src] = 0;
for (int count = 0; count < V - 1; count++) 
{
int u = minDistance(dist, sptSet, V);
sptSet[u] = 1;
for (int v = 0; v < V; v++) {
if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
dist[v] = dist[u] + graph[u][v];
}
}
}
printSolution(dist, V);
}
int main()
{
int V, E;
printf("Enter the number of vertices: ");
scanf("%d", &V);
int **graph = (int **)malloc(V * sizeof(int *));
for (int i = 0; i < V; i++) {
graph[i] = (int *)malloc(V * sizeof(int));
for (int j = 0; j < V; j++)
{
graph[i][j] = 0;
}
}
printf("Enter the number of edges: ");
scanf("%d", &E);
printf("Enter the edges (source, destination, weight):\n");
for (int i = 0; i < E; i++)
{
int src, dest, weight;
scanf("%d %d %d", &src, &dest, &weight);
graph[src][dest] = weight;
graph[dest][src] = weight; 
}
int src;
printf("Enter the source vertex: ");
scanf("%d", &src);
dijkstra(graph, V, src);
for(int i = 0; i < V; i++)
{
free(graph[i]);
}
free(graph);
return 0;
}
