#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100
typedef struct node
{
int vertex;
struct node* next;
}
node;
typedef struct Graph
{
int numvertices;
node** adjlists;
bool* visited;
}
Graph;
int stack[MAX];
int top=-1;
void push(int v)
{
stack[++top]=v;
}
int pop()
{
return stack[top--];
}
node* createnode(int v)
{
node* newnode=(node*)malloc(sizeof(node));
newnode->vertex=v;
newnode->next=NULL;
return newnode;
}
Graph* createGraph(int vertices)
{
Graph* graph=(Graph*)malloc(sizeof(Graph));
graph->numvertices=vertices;
graph->adjlists=(node**)malloc(vertices * sizeof(node*));
graph->visited=(bool*)malloc(vertices * sizeof(bool));
for(int i=0;i<vertices;i++)
{
graph->adjlists[i]=NULL;
graph->visited[i]=false;
}
return graph;
}
void addEdge(Graph* graph,int src, int dest)
{
node* newnode=createnode(dest);
newnode->next=graph->adjlists[src];
graph->adjlists[src]=newnode;
}
void DFS(Graph* graph,int vertex, bool storeinstack)
{
graph->visited[vertex]=true;
printf("%d",vertex);
node* temp=graph->adjlists[vertex];
while(temp)
{
int connectedVertex=temp->vertex;
if(!graph->visited[connectedVertex])
{
DFS(graph, connectedVertex, storeinstack);
}
temp=temp->next;
}
if(storeinstack)
{
push(vertex);
}
}
Graph* transposeGraph(Graph* graph)
{
Graph* transpose=createGraph(graph->numvertices);
for(int v=0;v<graph->numvertices;v++)
{
node* temp=graph->adjlists[v];
while(temp)
{
addEdge(transpose, temp->vertex, v);
temp=temp->next;
}
}
return transpose;
}
void findSCCs(Graph* graph)
{
for(int i=0;i<graph->numvertices;i++)
{
if(!graph->visited[i])
{
DFS(graph,i,true);
}
}
Graph* transpose=transposeGraph(graph);
for(int i=0;i<graph->numvertices;i++)
{
transpose->visited[i]=false;
}
printf("strongly connected components:\n");
while(top!=-1)
{
int v=pop();
if(!transpose->visited[v])
{
DFS(transpose,v,false);
printf("\n");
}
}
}
int main()
{
int vertices, edges,src,dest;
printf("enter the number of vertices:");
scanf("%d",&vertices);
printf("enter the no.of edges:");
scanf("%d",&edges);
Graph* graph=createGraph(vertices);
printf("enter the edges (source and destination):\n");
for(int i=0;i<edges;i++)
{
scanf("%d%d",&src,&dest);
addEdge(graph,src,dest);
}
findSCCs(graph);
return 0;
}
