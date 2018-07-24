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

//char* interceptions[]={"T3_Init","T3_Comm_rank","T3_Finalize","T3_Comm_size"};
   char* interceptions[]={  
  
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
   "T3_Comm_rank", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "T3_Comm_size", "NULL",
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
   "T3_Finalize", "NULL", "NULL",
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
   "NULL", "NULL", "T3_Init",
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
_EXTERN_C_ int T3_Init(int *argc,char ***argv,int i, vector* v){

	printf("T3_Init :) Lvl: %d\n", i);    	
	int ret =1;
        void* f=NULL;
        QMPI_Table_query( _MPI_Init, &f, (*vector_get(v,i)).table); 
//	printf("Önce T3 da level: %d \n ",i);
	ret= exec_func(f,i,_MPI_Init,v,argc,argv);
//	printf("Sonra T3 da level: %d \n",i);
       	printf("Return 3 Lvl: %d\n", i);
	return ret;
}

_EXTERN_C_ void T3_Comm_rank( MPI_Comm comm, int *rank,int i,vector * v ){

        printf("T3_Comm_rank :) \n");

        void* f=NULL;
        QMPI_Table_query(_MPI_Comm_rank,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Comm_rank,v,comm,rank);
        printf("Return 3 \n");
        return ;

}

_EXTERN_C_ void T3_Finalize(int i, vector* v ){

    	printf("T3_Finalize :) \n");
        void* f=NULL;
      	QMPI_Table_query( _MPI_Finalize, &f, (*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Finalize,v);
	printf("Return 3 \n");
        return ;
}

_EXTERN_C_ void T3_Comm_size( MPI_Comm comm, int *size,int i,vector * v ){

        printf("T3_Comm_size :) \n");

        void* f=NULL;
        QMPI_Table_query(_MPI_Comm_size,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Comm_size,v,comm,size);
        printf("Return 3 \n");
        return ;

}

