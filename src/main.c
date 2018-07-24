#include <mpi.h>
#include <stdio.h>
#include<stdlib.h>

 
int main() {

	MPI_Init(NULL,NULL);
        int rank=0;
	
	MPI_Comm comm=MPI_COMM_WORLD; 
	int gsize=0;
	int sendarray[10]={1,2,3,4,5,6,7,8,9,0}; 
    	int *rbuf; 
    
    	MPI_Comm_size( comm, &gsize);    	
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	rbuf = (int *)malloc(gsize*10*sizeof(int)); 
	//printf ("sendarray: %p  rbuf:%p recv_counts: %p ,disps: %p \n", sendarray, rbuf, recv_counts,disps);
	MPI_Allgather( sendarray, 10, MPI_INT, rbuf, 10 ,MPI_INT, comm); 
	//After the call, every process has the group-wide concatenation of the sets of data.

	for (int i=0; i<10; i++)
	{
		printf("Rank = %d  & int_array[ %d ] \n", rank, rbuf[i]);
	}

	if (rank==0){
	//	int size;
	//	MPI_Comm_size(MPI_COMM_WORLD,&size);
		printf( "Comm size : %d \n", gsize);
	}
   	MPI_Barrier (comm);     

	printf("Hi! from rank: %d  \n",rank);
	MPI_Finalize();
        free(rbuf);
	return 0;
}
