#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#define M 3
#define K 2
#define N 3
struct reqdmatrix{
int row;
int column;
};

int A[M][K]={{1,4},{2,5},{3,6}};
int B[K][N]={{8,7,6},{5,4,3}};
int C[M][N];
void *finalmatrix( void * args)
{
struct reqdmatrix *data = args;
int i,sum=0;
for(i=0;i<K;i++)
{
	sum=sum+A[data->row][i]*B[i][data->column];//multiplying the two matrices
}
C[data->row][data->column]=sum;//storinmg the value in the final matrix

pthread_exit(0);
}
int main()
{
int i,j;
pthread_t pid;
for(i=0;i<M;i++)
{
	for(j=0;j<N;j++)
	{
		struct reqdmatrix *data = (struct reqdmatrix *)malloc(sizeof(struct reqdmatrix));
			data->row = i;
			data->column = j;
			pthread_create(&pid,NULL,finalmatrix,data);
			pthread_join(pid,NULL);

	}
}
for (i=0;i<M;i++)
{
	for(j=0;j<N;j++)
	{
		printf("%d\t",C[i][j]);
	}
printf("\n");
}
}
