#include <stdio.h>
#include <stdlib.h>
#define MAX 10
int adj[MAX][MAX];  
int visited[MAX];   
int queue[MAX];   
int front = -1, rear = -1;
void enqueue(int vertex)
{
if (rear == MAX - 1)
{
printf("Queue is full!\n");
return;
}
if(front == -1)
front = 0;
queue[++rear] = vertex;
}
int dequeue()
{
if(front == -1 || front > rear)
{
printf("Queue is empty!\n");
return -1;
}
return queue[front++];
}
void bfs(int startVertex, int n)
{
enqueue(startVertex);
visited[startVertex] = 1;
printf("BFS Traversal: ");
while (front <= rear)
{
int currentVertex = dequeue();
printf("%d ", currentVertex);
for (int i = 0; i < n; i++)
{
if (adj[currentVertex][i] == 1 && !visited[i])
{
enqueue(i);
visited[i] = 1;
}
}
}
printf("\n");
}
int main()
{
int n, edges, u, v, startVertex;
printf("Enter the number of vertices: ");
scanf("%d", &n);
printf("Enter the number of edges: ");
scanf("%d", &edges);
for (int i = 0; i < n; i++)
{
for (int j = 0; j < n; j++)
adj[i][j] = 0;
visited[i] = 0;
}
printf("Enter the edges (u v):\n");
for (int i = 0; i < edges; i++)
{
scanf("%d %d", &u, &v);
adj[u][v] = 1;  
adj[v][u] = 1;
}                                                            
printf("Enter the starting vertex: ");
scanf("%d", &startVertex);
bfs(startVertex, n);
return 0;
}
