#include <mpi.h>
#include <stdio.h>
#include<stdlib.h>

 
int main() {

	//MPI_Init(NULL,NULL);
	int i = 0; 
	MPI_Init_thread(NULL,NULL,MPI_THREAD_SINGLE, &i);
        int rank=0;
	
	MPI_Pcontrol(5);
	
	int gsize=0;
        MPI_Comm_size(MPI_COMM_WORLD,&gsize);	

	int to_send=0;
       	int *sendarray=&to_send;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if (rank == 0 )	
	{	*sendarray=929; } 
	MPI_Bcast(sendarray,1,MPI_INT,0,MPI_COMM_WORLD);
	if (rank != 0){    printf("RECEIVED VALUE IS : %d  \n", *sendarray); }

	
	if (rank==0){
		printf( "Comm size : %d \n", gsize);
	}
   	MPI_Barrier (MPI_COMM_WORLD);     

	printf("Hi! from rank: %d  \n",rank);
	MPI_Finalize();
	return 0;
}

