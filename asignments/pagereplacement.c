#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<string.h>
int preop(int arr1[],int x,int count1,int y)
{
int i,c=1;
for(i=y;i<count1;i++)
 {
  if(x==arr1[i])
  {
   c=0;
   break;
  }  
 } 
return c;
}
int present(int x,int arr2[],int y)
{
int i,c=0;
for(i=0;i<y;i++)
{
if(arr2[i]==x)
{
c=1;
}
}
return c;
}
int fifo(int arr1[],int arr2[],int count1,int count2)
{
int c=0,fault=0,i,j=0,flag=0;
for(i=0;i<count1;i++)
{
flag=present(arr1[i],arr2,count2);
if(flag==1)
{
goto lab1;
}
if(j==count2)
{
j=0;
}
fault++;
arr2[j]=arr1[i];
j++;
lab1:flag=0;

}
return fault;
}
int lru(int arr1[],int arr2[],int count1,int count2)
{
int k,min,m,c=0,fault=0,i,j=0,flag=0,index[count2];
for(i=0;i<count1;i++)
{
 flag=present(arr1[i],arr2,count2);
 if(flag==1)
 {
  goto lab1;
 }
 if(j==count2)
 {
  for(k=0;k<count2;k++)
   {
    for(m=i-1;m>=0;m--)
    {
     if(arr1[m]==arr2[k])
     {
      index[k]=m;
      break;
     }
    }
   
   }
  min=index[0];
  for(m=0;m<count2;m++)
  {
   if(min>index[m])
   min=index[m];
  }
  for(k=0;k<count2;k++)
  {
   if(arr1[min]==arr2[k])
   {
     arr2[k]=arr1[i];
   }
  }  
goto lab2;
 }
arr2[j]=arr1[i];
j++;
lab2:fault++;
lab1:flag=0;
}
return fault;
}
int optim(int arr1[],int arr2[],int count1,int count2)
{
int k,max,m,c,fault=0,i,j=0,flag=0,index[count2];
for(i=0;i<count1;i++)
{
 
 flag=present(arr1[i],arr2,count2);
 if(flag==1)
 {
  goto lab1;
 }
 if(j==count2)
 {
  for(k=0;k<count2;k++)
   {
    c=0;
    c=preop(arr1,arr2[k],count1,i+1);
    if(c==1)
    goto lab2;
    for(m=i+1;m<count1;m++)
    {
     if(arr1[m]==arr2[k])
     {
      index[k]=m;
      break;
     }
    }
   }
  max=index[0];
  for(m=0;m<count2;m++)
  {
   if(max<index[m])
   max=index[m];
  }
  for(k=0;k<count2;k++)
  {
   if(arr1[max]==arr2[k])
   {
     arr2[k]=arr1[i];
   }
  }
 fault++;
 goto lab1;
 lab2:arr2[k]=arr1[i];
      fault++;
      goto lab1; 
}
arr2[j]=arr1[i];
j++;
fault++;
lab1:flag=0;
}
return fault;
}

FILE *fp;
void main(int argc,char *argv[])
{
int i,num1,num2,num3,count1,count2;
fp=fopen(argv[1],"r");
if(fp==NULL)
{
printf("filenotfounderror");
}
else
{
if(argc==1)
{
printf("filenameerror\n");
}
else 
{
fscanf(fp,"%d\t",&count1);
fscanf(fp,"%d\n",&count2);
int arr2[count2],arr1[count1],arr3[count2],arr4[count2];
for(i=0;i<count1;i++)
{
fscanf(fp,"%d\t",&arr1[i]);
}
if(argc==2 ||argc==5)
{
num1=fifo(arr1,arr2,count1,count2);
printf("Page Faults in FIFO are %d\n",num1);
num2=lru(arr1,arr3,count1,count2);
printf("Page Faults in LRU are %d\n",num2);
num3=optim(arr1,arr4,count1,count2);
printf("Page Faults in optim are %d\n",num3);
}
else if(argc==3 && (strcmp(argv[2],"FF"))==0)
{ 
num1=fifo(arr1,arr2,count1,count2);
printf("Page Faults in FIFO are %d\n",num1);
}
else if(argc==3 && (strcmp(argv[2],"LR"))==0)
{ 
num1=lru(arr1,arr3,count1,count2);
printf("Page Faults in LRU are %d\n",num1);
}
else if(argc==3 && (strcmp(argv[2],"OP"))==0)
{ 

num1=optim(arr1,arr4,count1,count2);
printf("Page Faults in optim are %d\n",num1);
}

else if(argc==4 && (strcmp(argv[2],"FF"))==0&& (strcmp(argv[3],"LR"))==0)
{ 
num1=fifo(arr1,arr2,count1,count2);
printf("Page Faults in fifo are %d\n",num1);
num2=lru(arr1,arr3,count1,count2);
printf("Page Faults in lru are %d\n",num2);
}
else if(argc==4 && (strcmp(argv[2],"LR"))==0&&( strcmp(argv[3],"OP"))==0)
{ 
num1=lru(arr1,arr3,count1,count2);
printf("Page Faults in lru are %d\n",num1);
num3=optim(arr1,arr4,count1,count2);
printf("Page Faults in optim are %d\n",num3);
}
 
else if(argc==4 && (strcmp(argv[2],"FF"))==0&& (strcmp(argv[3],"OP"))==0)
{ 
num1=fifo(arr1,arr2,count1,count2);
printf("Page Faults in fifo are %d\n",num1);
num3=optim(arr1,arr4,count1,count2);
printf("Page Faults in optim are %d\n",num3);
}
}
}
}
