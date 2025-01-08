#include<stdio.h>
#include<stdlib.h>
#define SIZE 5
 	int queue[SIZE];
	int front=-1;
	int rear=-1;
	int full(){
 return (rear+1)%SIZE==front;
}
	int empty(){
return front==-1;
}
void enqueue(int number)
{
if(full())
{
printf("Queue is full");
return;
}
if(front==-1){
front=0;
}
rear=(rear+1)%SIZE;
queue[rear]=number;
printf("element %d added",number);
}

void dequeue()
{
if(empty())
{
printf("queue empty");
return;
}
int number=queue[front];
if(front==rear)
{
front=rear=-1;
}
else
{
front=(front+1)%SIZE;
}
printf("Deleted element is:%d\n",number);
}
void display()
{
if (empty())
{
printf("queue is empty");
return;
}
printf("queue is:");
for(int i=front;i!=rear;i=(i+1)%SIZE)
{
printf("%d\t",queue[i]);
}
printf("%d\n",queue[rear]);
}

int main()
{
int choice,value;
while(1)
{
printf("\n1.insert\n\n2.delete\n\n3.display\n\n4.exit\n");
printf("Enter choice:");
scanf("%d",&choice);
switch(choice){
case 1:
printf("Enter the value to insert:");
scanf("%d",&value);
enqueue(value);
break;
case 2:
dequeue();
break;
case 3:
display();
break;
case 4:
exit(0);
default:
printf("Invalid choice");
}
}
return 0;
}


