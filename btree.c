#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define M 4
typedef struct BTreeNode
{
int keys[M-1];
struct BTreeNode *child[M];
int n;
int leaf;
}
BTreeNode;
BTreeNode *createNode(int leaf)
{
BTreeNode *node=(BTreeNode*)malloc(sizeof(BTreeNode));
node->leaf=leaf;
node->n=0;
for(int i=0;i<M;i++)
{
node->child[i]=NULL;
}
return node;
}
void traverse(BTreeNode *root)
{
if(root)
{
for(int i=0;i<root->n;i++)
{
if(!root->leaf)
{
traverse(root->child[i]);
}
printf("%d",root->keys[i]);
}
if(!root->leaf)
{
traverse(root->child[root->n]);
}
}
}
BTreeNode *search(BTreeNode *root, int key)
{
int i=0;
while(i<root->n&&key>root->keys[i])
{
i++;
}
if(i<root->n&&key==root->keys[i])
{
return root;
}
if(root->leaf)
{
return NULL;
}
return search(root->child[i],key);
}
void splitChild(BTreeNode *parent, int i, BTreeNode *child)
{
BTreeNode *newChild=createNode(child->leaf);
int mid=M/2;
newChild->n=mid-1;
if(!child->leaf)
{
for(int j=0;j<mid;j++)
{
newChild->child[j]=child->child[j + mid];
}
}
child->n=mid-1;
for(int j=parent->n;j>=i+1;j--)
{
parent->child[j+1]=parent->child[j];
}
parent->child[i+1]=newChild;
for(int j=parent->n-1;j>=i;j--)
{
parent->keys[j+1]=parent->keys[j];
}
parent->keys[i]=child->keys[mid-1];
parent->n++;
}
void insertNonFull(BTreeNode *node, int key)
{
int i=node->n-1;
if(node->leaf)
{
while(i>=0&&key < node->keys[i])
{
node->keys[i+1]=node->keys[i];
i--;
}
node->keys[i+1]=key;
node->n++;
}
else
{
while(i>=0 && key < node->keys[i])
{
i--;
}
i++;
if(node->child[i]->n==M-1)
{
splitChild(node, i, node->child[i]);
if(key > node->keys[i])
{
i++;
}
}
insertNonFull(node->child[i],key);
}
}
BTreeNode *insert(BTreeNode *root, int key)
{
if(root->n==M-1)
{
BTreeNode *newRoot=createNode(0);
newRoot->child[0]=root;
splitChild(newRoot, 0, root);
insertNonFull(newRoot,key);
return newRoot;
}
else
{
insertNonFull(root, key);
return root;
}
}
int main()
{
BTreeNode *root=createNode(1);
int choice,key;
printf("B-Tree Operations(Order %d)\n",M);
while(1)
{
printf("\n1. Insert\n2. Traverse\n3. search\n4. Exit\n");
printf("Enter your choice:");
scanf("%d",&choice);
switch(choice)
{
case 1:
printf("Enter key to insert:");
scanf("%d",&key);
root=insert(root,key);
break;
case 2:
printf("B-Tree:");
traverse(root);
printf("\n");
break;
case 3:
printf("Enter key to search:");
scanf("%d",&key);
if(search(root,key))
{
printf("key %d found in the B-Tree\n",key);
}
else
{
printf("key %d not found in the B-Tree\n",key);
}
break;
case 4:
exit(0);
default:
printf("Invalid choice..Try again\n");
}
}
return 0;
} 
