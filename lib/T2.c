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

//char* interceptions[]={"NULL","T2_Comm_rank","T2_Finalize","T2_Comm_size"};
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
   "T2_Comm_rank", "NULL", "NULL",
   "NULL", "NULL", "NULL",
   "NULL", "T2_Comm_size", "NULL",
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
   "T2_Finalize", "NULL", "NULL",
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
_EXTERN_C_ int T2_Init(int *argc,char ***argv,int i, vector* v){

	printf("T2_Init :) Lvl: %d\n", i);
        int ret =1;
        void* f=NULL;
        QMPI_Table_query(_MPI_Init,&f,(*vector_get(v,i)).table);
//	printf("Önce T2 da level: %d \n ",i);
        ret= exec_func(f,i,_MPI_Init,v,argc,argv);
//	printf("Sonra T2 da level: %d \n",i);
        // TODO:this EXEC_FUNC thing above must be replaced with function pointer execution
        printf("Return 2 Lvl: %d\n", i);
        return ret;
}

_EXTERN_C_ void T2_Comm_rank( MPI_Comm comm, int *rank,int i,vector * v ){

	printf("T2_Comm_rank :) \n");
        void* f=NULL;
        QMPI_Table_query(_MPI_Comm_rank,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Comm_rank,v,comm,rank);
	printf("Return 2 \n");
   	return ;

}
_EXTERN_C_ void T2_Finalize(int i, vector* v ){

   	printf("T2_Finalize :) \n");
        
        void* f=NULL;
        QMPI_Table_query(_MPI_Finalize,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Finalize,v);
        //(f)(++i,v); //TODO: this must be replaced with function pointer execution 
        printf("Return 2 \n");          
        return ;
}

_EXTERN_C_ void T2_Comm_size( MPI_Comm comm, int *size,int i,vector * v ){

        printf("T2_Comm_size :) \n");

//	int r=7;
//	MPI_Comm_rank(MPI_COMM_WORLD,&r);
//	printf("rank in T2_Comm_size = %d \n", r);

        void* f=NULL;
        QMPI_Table_query(_MPI_Comm_size,&f,(*vector_get(v,i)).table);
        exec_func(f,i,_MPI_Comm_size,v,comm,size);
        printf("Return 2 \n");
        return ;

}

