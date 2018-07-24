#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/obj/qmpi.h"

#ifndef _EXTERN_C_
#ifdef __cplusplus
#define _EXTERN_C_ extern "C"
#else /* __cplusplus */
#define _EXTERN_C_
#endif /* __cplusplus */
#endif /* _EXTERN_C_ */

//char* interceptions[]={"T1_Init","T1_Comm_rank","T1_Finalize","T1_Comm_size"};
   char* interceptions[]={  
  
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "T1_Allgather", "T1_Allgatherv", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "T1_Comm_rank", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL",  "T1_Comm_size", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "T1_Finalize", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "T1_Init",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "NULL", "NULL"
   };
_EXTERN_C_ char* get_interceptions(int i )
{
        return interceptions[i];
}


// -------------------------------------------
_EXTERN_C_ int T1_Init(int *argc,char ***argv,int i,vector * v){

        printf("T1_Init :) Lvl: %d\n", i);
        int ret =1;
        void* f=NULL;
        QMPI_Table_query(200,&f,(*vector_get(v,i)).table);
//      printf("Önce T1 da level: %d \n ",i);
        ret= exec_func(f,i,200,v,argc,argv);
//      printf("Sonra T1 da level: %d \n ",i);
        //ret=(f)(argc, argv, ++i, v); 
        // TODO:this EXEC_FUNC thing above must be replaced with function pointer execution
        printf("Return 1 Lvl: %d\n", i);
        return ret;
}

_EXTERN_C_ void T1_Comm_rank(MPI_Comm comm, int *rank,int i,vector * v ){

        printf("T1_Comm_rank :) \n");
        void* f=NULL;
        QMPI_Table_query(_MPI_Comm_rank,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Comm_rank,v,comm,rank);
        printf("Return 1 \n");
        return ;
//    PMPI_Send();
}
_EXTERN_C_ void T1_Finalize(int i, vector* v ){

        printf("T1_Finalize :) \n");
        void* f=NULL;
        QMPI_Table_query( _MPI_Finalize, &f, (*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Finalize,v);
        printf("Return 1 \n");
        return ;
}

_EXTERN_C_ void T1_Comm_size(MPI_Comm comm, int *size,int i,vector * v ){

        printf("T1_Comm_size :) \n");
        void* f=NULL;
        QMPI_Table_query(_MPI_Comm_size,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Comm_size,v,comm,size);
        printf("Return 1 \n");
        return ;
//    PMPI_Send();
}

_EXTERN_C_ void T1_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int i ,vector* v){

        printf("T1_Allgather :) \n");
        void* f=NULL;
        QMPI_Table_query(_MPI_Allgather,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Allgather,v,sendbuf, sendcount, sendtype, recvbuf, recvcount,  recvtype, comm );
        printf("Return 1 \n");
        return ;
//    PMPI_Send();
}

_EXTERN_C_ void T1_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int i ,vector* v){
        printf("T1_Allgather :) \n");
        void* f=NULL;
        QMPI_Table_query(_MPI_Allgatherv,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Allgatherv,v,sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
        printf("Return 1 \n");
        return ;
//    PMPI_Send();
}

