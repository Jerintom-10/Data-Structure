#include<stdio.h>
#include<stdlib.h>
void mergeArrays(int arr1[],int arr2[],int mer[], int n1,int n2)
{
int i=0, j=0, k=0;
while(i<n1 && i<n2)
{
if(arr1[i]<arr2[j])
{
mer[k]=arr1[i];
i++,k++;
}
else
{
mer[k]=arr2[j];
j++,k++;
}
}
while(i<n1)
{
mer[k++]=arr1[i++];
}
while(j<n2)
{
mer[k++]=arr2[j++];
}
}
int main()
{
int n1,n2,i,j;
printf("enter the no.of elements in the first array: ");
scanf("%d",&n1);
int *arr1=(int *)malloc(n1 * sizeof(int));
printf("enter the elements of the first array : ");
for(i=0;i<n1;i++)
{
scanf("%d",&arr1[i]);
}
printf("enter the no.of elements in the second array: ");
scanf("%d",&n2);
int *arr2=(int *)malloc(n2 * sizeof(int));
printf("enter the elements of the second array: ");
for(j=0;j<n2;j++)
{
scanf("%d",&arr2[j]);
}
int *mer=(int *)malloc(n1 * sizeof(int));
mergeArrays(arr1,arr2,mer,n1,n2);
printf("Merged array is:");
for(i=0;i<n1+n2;i++)
{
printf("%d",mer[i]);
}
free(arr1);
free(arr2);
free(mer);
return 0;
}

