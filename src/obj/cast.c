#include "qmpi.h"
#include "cast.h"
#include <stdarg.h>

int Cast_Init(void* func_ptr, vector* v,int level,va_list argp){
	if (func_ptr == NULL)
        {
                printf("function pointer for execution is null,function can't be executed , returns \n");
                return 1 ;
        }

        else {
		
		typedef int (*mpifunc)(int *argc,char ***argv,int i , vector* v );
                mpifunc f= (mpifunc) func_ptr;
                int ret= (f ) ( va_arg(argp,int *), va_arg(argp, char ***) , level, v);
                printf(" function is casted! \n");
        }
        return 0;
}
/*
int Cast_Comm_rank(void* func_ptr, vector* v,va_list argp){
        if (func_ptr == NULL)
        {
                printf("function pointer for execution is null,function can't be executed , returns \n");
                return 1 ;
        }

        else {
                typedef int (*mpifunc)(MPI_Comm comm, int *rank,int i , vector* v );
                mpifunc f= (mpifunc) func_ptr;
                //int ret= (f ) (argc, argv, level, v);
                printf(" function is casted! \n");
        }
        return 0;
}
int Cast_Finalize(void* func_ptr, vector* v,va_list argp){
        if (func_ptr == NULL)
        {
                printf("function pointer for execution is null,function can't be executed , returns \n");
                return 1 ;
        }

        else {
                typedef int (*mpifunc)();
                mpifunc f= (mpifunc) func_ptr;
                //int ret= (f ) (argc, argv, level, v);
                printf(" function is casted! \n");
        }
        return 0;
}
*/
