#define _GNU_SOURCE
#include <dlfcn.h>
#include <mpi.h>
#include <stdio.h>
#include "qmpi.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include "arrays.h"

#ifndef _EXTERN_C_
#ifdef __cplusplus
#define _EXTERN_C_ extern "C"
#else /* __cplusplus */
#define _EXTERN_C_
#endif /* __cplusplus */
#endif /* _EXTERN_C_ */

//---------------------------------------------------------------------------------------------------
void vector_init(vector *v)
{
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = (struct dynamic_lib**)malloc( (v->capacity )  * sizeof(struct dynamic_lib*) );
}

int vector_total(vector *v)
{
    return v->total;
}

static void vector_resize(vector *v, int capacity)
{
    #ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", v->capacity, capacity);
    #endif

    struct dynamic_lib **items = realloc(v->items, sizeof(struct dynamic_lib *) * capacity);
    if (items) {
        v->items= items;
        v->capacity = capacity;
    }
}

void vector_add(vector *v, struct dynamic_lib *item)
{
    if (v->capacity == v->total)
        vector_resize(v, v->capacity * 2);

    v->items[v->total] = (struct dynamic_lib*) malloc (sizeof (struct dynamic_lib) );
    strncpy(   (v->items[v->total])->path,  item->path,  sizeof item->path ) ;
    printf("%s \n",(v->items[v->total])->path);
    (v->items[v->total++])->handle= item->handle;

}

struct dynamic_lib *vector_get(vector *v, int index)
{
    if (index >= 0 && index < v->total)
        {
                return v->items[index];
        }
    return NULL;
}
void vector_free(vector *v)
{
    for (int i = (v->total)-1 ; i >= 0; --i)
        {  free(v->items[i]); }
        free(v->items);
}

//------------------------------------------------------------------------------------------------------------
vector v;
//------------------------------------------------------------------------------------------------------------
dynamic_lib_handle load_lib (const char* path) {

        void* tmp = dlopen( path , RTLD_NOW);

        //Error checks
        const char *dlsym_error = dlerror();
        if (dlsym_error)
        {       printf( "Cannot load %s \n ", dlsym_error); }
        return tmp;
}

int   QMPI_Table_query( _MPI_funcs func_index, void** func_ptr, cell table[])//, int* level )
{
        //if there exists next tool function to execute returns 0 & sets the function ptr
        *func_ptr = (table[func_index]).me;
       
        if(*func_ptr== NULL)
        {
                printf("Error func_ptr NULL , redirecting execution to PMPI  \n");
                *func_ptr = QMPI_Array[func_index];
        }
        return 0;
}

int exec_func(void* func_ptr,int level ,_MPI_funcs func_index, vector* v , ...){
        level=(*vector_get(v,level)).table[func_index].level;
        int ret =0;
        if (func_ptr == NULL)
        {
                printf("function pointer for execution is null,function can't be executed , returns \n");
                return ret ;
        }

        else {
                va_list argp;
                switch(func_index){
		case 0	:
			//int QMPI_Abort(MPI_Comm comm, int errorcode, int level ,vector* v);
			va_start(argp,v);
			typedef int (*abort_func) (MPI_Comm comm, int errorcode, int level ,vector* v);
			abort_func abort_ptr			=	(abort_func) func_ptr;
			MPI_Comm abort_arg1				=	va_arg(argp,MPI_Comm);
			int abort_arg2					=	va_arg(argp,int);
                	ret= (abort_ptr ) ( abort_arg1, abort_arg2, level, v);
			break;
		case 1	:	    
			//int QMPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, int level ,vector* v);
			va_start(argp,v);
			typedef int (*accumulate_func)(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, int level ,vector* v);
			accumulate_func 	accumulate_ptr  =	(accumulate_func) func_ptr;
			const void * accumulate_arg1 		=	va_arg(argp, const void*);
			int accumulate_arg2					=	va_arg(argp,int);
			MPI_Datatype accumulate_arg3		=	va_arg(argp,MPI_Datatype);
			int accumulate_arg4				=	va_arg(argp, int);
			MPI_Aint accumulate_arg5			=	va_arg(argp, MPI_Aint);
			int accumulate_arg6					=	va_arg(argp,int);
			MPI_Datatype accumulate_arg7		=	va_arg(argp,MPI_Datatype);
			MPI_Op accumulate_arg8				=	va_arg(argp,MPI_Op);
			MPI_Win accumulate_arg9				=	va_arg(argp,MPI_Win);
			ret= (accumulate_ptr ) ( accumulate_arg1, accumulate_arg2,accumulate_arg3,accumulate_arg4,accumulate_arg5,accumulate_arg6,accumulate_arg7,accumulate_arg8,accumulate_arg9,level, v);
			break;
		case 2	:	    
			//int QMPI_Add_error_class(int *errorclass, int level ,vector* v);
			va_start(argp,v);
			typedef int (*add_error_func)(int *errorclass, int level ,vector* v);
			add_error_func add_error_ptr 	=(add_error_func) func_ptr;
			int *add_error_arg1				=va_arg(argp,int*);
			ret= (add_error_ptr) (add_error_arg1,level,v);
			break;
		case 3	:	    
					//int QMPI_Add_error_code(int errorclass, int *errorcode, int level ,vector* v);
					va_start(argp,v);
					typedef int (*add_error_code_func) (int errorclass, int *errorcode, int level ,vector* v);
					add_error_code_func 	add_error_code_ptr	= 	(add_error_code_func) func_ptr;
					int add_error_code_arg1 					=	va_arg(argp,int);
					int* add_error_code_arg2 					=	va_arg(argp,int*);
					ret= (add_error_code_ptr) ( add_error_code_arg1, add_error_code_arg2,level,v);
					break;
		case 4	:	    
					//int QMPI_Add_error_string(int errorcode, const char *string, int level ,vector* v);
					va_start(argp,v);
					typedef int (*add_error_string_func) (int errorcode, const char *string, int level ,vector* v);
					add_error_string_func add_error_string_ptr = (add_error_string_func) func_ptr;
					int add_error_string_arg1				   = va_arg(argp,int);
					const char* add_error_string_arg2		   = va_arg(argp, const char*);
					ret= (add_error_string_ptr) (add_error_string_arg1,add_error_string_arg2, level ,v);
					break;
		case 5	:	    
			//int QMPI_Address(void *location, MPI_Aint *address, int level ,vector* v);
			va_start(argp,v);
			typedef int (*address_func) (void *location, MPI_Aint *address, int level ,vector* v);
			address_func address_ptr	=	(address_func) func_ptr;
			void* address_arg1			=	va_arg(argp, void*);
			MPI_Aint* address_arg2		=	va_arg(argp, MPI_Aint*);
			ret= (address_ptr) (address_arg1, address_arg2, level, v);
			break;
		case 6	:	    
			//int QMPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);
			va_start(argp,v);
			typedef int (*allgather_func)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);
			allgather_func allgather_ptr= (allgather_func) func_ptr;
			const void* allgather_arg1	= va_arg(argp,const void*);
			int  allgather_arg2			=va_arg(argp, int );
			MPI_Datatype allgather_arg3	=va_arg(argp, MPI_Datatype);
			void* allgather_arg4		=va_arg(argp, void*);
			int allgather_arg5			=va_arg(argp, int);
			MPI_Datatype allgather_arg6 =va_arg(argp,MPI_Datatype);
			MPI_Comm  allgather_arg7	=va_arg(argp,MPI_Comm);
			printf("Allgather exec func switch case  -0-\n");
			ret= (allgather_ptr)(allgather_arg1, allgather_arg2, allgather_arg3, allgather_arg4, allgather_arg5, allgather_arg6, allgather_arg7,level,v);
			break;
		case 7	:	    
			//int QMPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);
			va_start(argp,v);
			typedef int (*allgatherv_func)(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);
			allgatherv_func allgatherv_ptr 		= (allgatherv_func) func_ptr;
			const void*	allgatherv_arg1		= va_arg(argp, void*);
			int allgatherv_arg2			=va_arg(argp,int);
			MPI_Datatype allgatherv_arg3 		=va_arg(argp,MPI_Datatype);
			void* allgatherv_arg4			=va_arg(argp, void*);
			const int* allgatherv_arg5		=va_arg(argp, int*);
			const int* allgatherv_arg6		=va_arg(argp, int*);
			MPI_Datatype allgatherv_arg7		=va_arg(argp,MPI_Datatype);
			MPI_Comm allgatherv_arg8		=va_arg(argp,MPI_Comm);
			ret= (allgatherv_ptr) (allgatherv_arg1, allgatherv_arg2, allgatherv_arg3, allgatherv_arg4, allgatherv_arg5, allgatherv_arg6, allgatherv_arg7, allgatherv_arg8,level,v);
//			printf("HEREEEEEEEEEE \n");
			break;
		case 8	:	    
			//int QMPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr, int level ,vector* v);
			va_start(argp,v);
			typedef int (*alloc_mem_func)(MPI_Aint size, MPI_Info info, void *baseptr, int level ,vector* v);
			alloc_mem_func alloc_mem_ptr	=	(alloc_mem_func) func_ptr;
			MPI_Aint alloc_mem_arg1			=	va_arg(argp,MPI_Aint);
			MPI_Info alloc_mem_arg2			=	va_arg(argp,MPI_Info);
			void*	 alloc_mem_arg3			=	va_arg(argp, void* );	
			ret= (alloc_mem_ptr) (alloc_mem_arg1, alloc_mem_arg2, alloc_mem_arg3, level, v);
			break;
		case 9	:	    
			//int QMPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level ,vector* v);
			va_start(argp,v);
			typedef int (*allreduce_func) (const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level ,vector* v);
			allreduce_func	allreduce_ptr	= 	(allreduce_func) func_ptr;
			const void* allreduce_arg1		=	va_arg(argp,const void*);
			void*	allreduce_arg2			= 	va_arg(argp,void*);
			int 	allreduce_arg3			=	va_arg(argp, int);
			MPI_Datatype allreduce_arg4		=	va_arg(argp, MPI_Datatype);
			MPI_Op 	allreduce_arg5			=	va_arg(argp,MPI_Op);
			MPI_Comm allreduce_arg6			=	va_arg(argp,MPI_Comm);
			ret= (allreduce_ptr) (allreduce_arg1, allreduce_arg2, allreduce_arg3, allreduce_arg4, allreduce_arg5, allreduce_arg6, level, v);
			break;
		case 10	:	    
			//int QMPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);
			va_start(argp,v);
			typedef int (*alltoall_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);
			alltoall_func	alltoall_ptr	= 	(alltoall_func) func_ptr;
			const void *alltoall_arg1 		=	va_arg(argp, const void*);
			int alltoall_arg2				= 	va_arg(argp, int);
			MPI_Datatype alltoall_arg3		=	va_arg(argp, MPI_Datatype);
			void* alltoall_arg4				=	va_arg(argp, void*);
			int  alltoall_arg5				=	va_arg(argp, int);
			MPI_Datatype alltoall_arg6		=	va_arg(argp, MPI_Datatype);
			MPI_Comm  alltoall_arg7			=	va_arg(argp, MPI_Comm);
			ret= (alltoall_ptr) (alltoall_arg1, alltoall_arg2, alltoall_arg3, alltoall_arg4, alltoall_arg5, alltoall_arg6, alltoall_arg7, level, v);
			break;
    case 11:
        va_start(argp,v);
		typedef int (*alltoallv_func) (const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);
		alltoallv_func QMPI_Alltoallv_ptr = (alltoallv_func) func_ptr;
		const void * alltoallv_func_arg0 = va_arg(argp, const void *);
		const int * alltoallv_func_arg1 = va_arg(argp, const int *);
		const int * alltoallv_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype alltoallv_func_arg3 = va_arg(argp, MPI_Datatype);
		void * alltoallv_func_arg4 = va_arg(argp, void *);
		const int * alltoallv_func_arg5 = va_arg(argp, const int *);
		const int * alltoallv_func_arg6 = va_arg(argp, const int *);
		MPI_Datatype alltoallv_func_arg7 = va_arg(argp, MPI_Datatype);
		MPI_Comm alltoallv_func_arg8 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Alltoallv_ptr) (alltoallv_func_arg0, alltoallv_func_arg1, alltoallv_func_arg2, alltoallv_func_arg3, alltoallv_func_arg4, alltoallv_func_arg5, alltoallv_func_arg6, alltoallv_func_arg7, alltoallv_func_arg8,  level, v);
		break;
		 
        // int QMPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);\n
     
    case 12:
        va_start(argp,v);
		typedef int (*alltoallw_func) (const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, int level, vector *v);
		alltoallw_func QMPI_Alltoallw_ptr = (alltoallw_func) func_ptr;
		const void * alltoallw_func_arg0 = va_arg(argp, const void *);
		const int * alltoallw_func_arg1 = va_arg(argp, const int *);
		const int * alltoallw_func_arg2 = va_arg(argp, const int *);
		const MPI_Datatype * alltoallw_func_arg3 = va_arg(argp, const MPI_Datatype *);
		void * alltoallw_func_arg4 = va_arg(argp, void *);
		const int * alltoallw_func_arg5 = va_arg(argp, const int *);
		const int * alltoallw_func_arg6 = va_arg(argp, const int *);
		const MPI_Datatype * alltoallw_func_arg7 = va_arg(argp, const MPI_Datatype *);
		MPI_Comm alltoallw_func_arg8 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Alltoallw_ptr) (alltoallw_func_arg0, alltoallw_func_arg1, alltoallw_func_arg2, alltoallw_func_arg3, alltoallw_func_arg4, alltoallw_func_arg5, alltoallw_func_arg6, alltoallw_func_arg7, alltoallw_func_arg8,  level, v);
		break;
		 
        // int QMPI_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, int level, vector *v);\n
     
    case 13:
        va_start(argp,v);
		typedef int (*attr_delete_func) (MPI_Comm comm, int keyval, int level, vector *v);
		attr_delete_func QMPI_Attr_delete_ptr = (attr_delete_func) func_ptr;
		MPI_Comm attr_delete_func_arg0 = va_arg(argp, MPI_Comm);
		int attr_delete_func_arg1 = va_arg(argp, int);
		ret = (QMPI_Attr_delete_ptr) (attr_delete_func_arg0, attr_delete_func_arg1,  level, v);
		break;
		 
        // int QMPI_Attr_delete(MPI_Comm comm, int keyval, int level, vector *v);\n
     
    case 14:
        va_start(argp,v);
		typedef int (*attr_get_func) (MPI_Comm comm, int keyval, void *attribute_val, int *flag, int level, vector *v);
		attr_get_func QMPI_Attr_get_ptr = (attr_get_func) func_ptr;
		MPI_Comm attr_get_func_arg0 = va_arg(argp, MPI_Comm);
		int attr_get_func_arg1 = va_arg(argp, int);
		void * attr_get_func_arg2 = va_arg(argp, void *);
		int * attr_get_func_arg3 = va_arg(argp, int *);
		ret = (QMPI_Attr_get_ptr) (attr_get_func_arg0, attr_get_func_arg1, attr_get_func_arg2, attr_get_func_arg3,  level, v);
		break;
		 
        // int QMPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag, int level, vector *v);\n
     
    case 15:
        va_start(argp,v);
		typedef int (*attr_put_func) (MPI_Comm comm, int keyval, void *attribute_val, int level, vector *v);
		attr_put_func QMPI_Attr_put_ptr = (attr_put_func) func_ptr;
		MPI_Comm attr_put_func_arg0 = va_arg(argp, MPI_Comm);
		int attr_put_func_arg1 = va_arg(argp, int);
		void * attr_put_func_arg2 = va_arg(argp, void *);
		ret = (QMPI_Attr_put_ptr) (attr_put_func_arg0, attr_put_func_arg1, attr_put_func_arg2,  level, v);
		break;
		 
        // int QMPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val, int level, vector *v);\n
     
    case 16:
        va_start(argp,v);
		typedef int (*barrier_func) (MPI_Comm comm, int level, vector *v);
		barrier_func QMPI_Barrier_ptr = (barrier_func) func_ptr;
		MPI_Comm barrier_func_arg0 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Barrier_ptr) (barrier_func_arg0,  level, v);
		break;
		 
        // int QMPI_Barrier(MPI_Comm comm, int level, vector *v);\n
     
    case 17:
        va_start(argp,v);
		typedef int (*bcast_func) (void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, int level, vector *v);
		bcast_func QMPI_Bcast_ptr = (bcast_func) func_ptr;
		void * bcast_func_arg0 = va_arg(argp, void *);
		int bcast_func_arg1 = va_arg(argp, int);
		MPI_Datatype bcast_func_arg2 = va_arg(argp, MPI_Datatype);
		int bcast_func_arg3 = va_arg(argp, int);
		MPI_Comm bcast_func_arg4 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Bcast_ptr) (bcast_func_arg0, bcast_func_arg1, bcast_func_arg2, bcast_func_arg3, bcast_func_arg4,  level, v);
		break;
		 
        // int QMPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, int level, vector *v);\n
     
    case 18:
        va_start(argp,v);
		typedef int (*bsend_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level, vector *v);
		bsend_func QMPI_Bsend_ptr = (bsend_func) func_ptr;
		const void * bsend_func_arg0 = va_arg(argp, const void *);
		int bsend_func_arg1 = va_arg(argp, int);
		MPI_Datatype bsend_func_arg2 = va_arg(argp, MPI_Datatype);
		int bsend_func_arg3 = va_arg(argp, int);
		int bsend_func_arg4 = va_arg(argp, int);
		MPI_Comm bsend_func_arg5 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Bsend_ptr) (bsend_func_arg0, bsend_func_arg1, bsend_func_arg2, bsend_func_arg3, bsend_func_arg4, bsend_func_arg5,  level, v);
		break;
		 
        // int QMPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level, vector *v);\n
     
    case 19:
        va_start(argp,v);
		typedef int (*bsend_init_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		bsend_init_func QMPI_Bsend_init_ptr = (bsend_init_func) func_ptr;
		const void * bsend_init_func_arg0 = va_arg(argp, const void *);
		int bsend_init_func_arg1 = va_arg(argp, int);
		MPI_Datatype bsend_init_func_arg2 = va_arg(argp, MPI_Datatype);
		int bsend_init_func_arg3 = va_arg(argp, int);
		int bsend_init_func_arg4 = va_arg(argp, int);
		MPI_Comm bsend_init_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * bsend_init_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Bsend_init_ptr) (bsend_init_func_arg0, bsend_init_func_arg1, bsend_init_func_arg2, bsend_init_func_arg3, bsend_init_func_arg4, bsend_init_func_arg5, bsend_init_func_arg6,  level, v);
		break;
		 
        // int QMPI_Bsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 20:
        va_start(argp,v);
		typedef int (*buffer_attach_func) (void *buffer, int size, int level, vector *v);
		buffer_attach_func QMPI_Buffer_attach_ptr = (buffer_attach_func) func_ptr;
		void * buffer_attach_func_arg0 = va_arg(argp, void *);
		int buffer_attach_func_arg1 = va_arg(argp, int);
		ret = (QMPI_Buffer_attach_ptr) (buffer_attach_func_arg0, buffer_attach_func_arg1,  level, v);
		break;
		 
        // int QMPI_Buffer_attach(void *buffer, int size, int level, vector *v);\n
     
    case 21:
        va_start(argp,v);
		typedef int (*buffer_detach_func) (void *buffer, int *size, int level, vector *v);
		buffer_detach_func QMPI_Buffer_detach_ptr = (buffer_detach_func) func_ptr;
		void * buffer_detach_func_arg0 = va_arg(argp, void *);
		int * buffer_detach_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Buffer_detach_ptr) (buffer_detach_func_arg0, buffer_detach_func_arg1,  level, v);
		break;
		 
        // int QMPI_Buffer_detach(void *buffer, int *size, int level, vector *v);\n
     
    case 22:
        va_start(argp,v);
		typedef int (*cancel_func) (MPI_Request *request, int level, vector *v);
		cancel_func QMPI_Cancel_ptr = (cancel_func) func_ptr;
		MPI_Request * cancel_func_arg0 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Cancel_ptr) (cancel_func_arg0,  level, v);
		break;
		 
        // int QMPI_Cancel(MPI_Request *request, int level, vector *v);\n
     
    case 23:
        va_start(argp,v);
		typedef int (*cart_coords_func) (MPI_Comm comm, int rank, int maxdims, int coords[], int level, vector *v);
		cart_coords_func QMPI_Cart_coords_ptr = (cart_coords_func) func_ptr;
		MPI_Comm cart_coords_func_arg0 = va_arg(argp, MPI_Comm);
		int cart_coords_func_arg1 = va_arg(argp, int);
		int cart_coords_func_arg2 = va_arg(argp, int);
		int* cart_coords_func_arg3 = va_arg(argp, int*);
		ret = (QMPI_Cart_coords_ptr) (cart_coords_func_arg0, cart_coords_func_arg1, cart_coords_func_arg2, cart_coords_func_arg3,  level, v);
		break;
		 
        // int QMPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[], int level, vector *v);\n
     
    case 24:
        va_start(argp,v);
		typedef int (*cart_create_func) (MPI_Comm old_comm, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart, int level, vector *v);
		cart_create_func QMPI_Cart_create_ptr = (cart_create_func) func_ptr;
		MPI_Comm cart_create_func_arg0 = va_arg(argp, MPI_Comm);
		int cart_create_func_arg1 = va_arg(argp, int);
		const int * cart_create_func_arg2 = va_arg(argp, const int *);
		const int * cart_create_func_arg3 = va_arg(argp, const int *);
		int cart_create_func_arg4 = va_arg(argp, int);
		MPI_Comm * cart_create_func_arg5 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Cart_create_ptr) (cart_create_func_arg0, cart_create_func_arg1, cart_create_func_arg2, cart_create_func_arg3, cart_create_func_arg4, cart_create_func_arg5,  level, v);
		break;
		 
        // int QMPI_Cart_create(MPI_Comm old_comm, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart, int level, vector *v);\n
     
    case 25:
        va_start(argp,v);
		typedef int (*cart_get_func) (MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[], int level, vector *v);
		cart_get_func QMPI_Cart_get_ptr = (cart_get_func) func_ptr;
		MPI_Comm cart_get_func_arg0 = va_arg(argp, MPI_Comm);
		int cart_get_func_arg1 = va_arg(argp, int);
		int* cart_get_func_arg2 = va_arg(argp, int*);
		int* cart_get_func_arg3 = va_arg(argp, int*);
		int* cart_get_func_arg4 = va_arg(argp, int*);
		ret = (QMPI_Cart_get_ptr) (cart_get_func_arg0, cart_get_func_arg1, cart_get_func_arg2, cart_get_func_arg3, cart_get_func_arg4,  level, v);
		break;
		 
        // int QMPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[], int level, vector *v);\n
     
    case 26:
        va_start(argp,v);
		typedef int (*cart_map_func) (MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank, int level, vector *v);
		cart_map_func QMPI_Cart_map_ptr = (cart_map_func) func_ptr;
		MPI_Comm cart_map_func_arg0 = va_arg(argp, MPI_Comm);
		int cart_map_func_arg1 = va_arg(argp, int);
		const int * cart_map_func_arg2 = va_arg(argp, const int *);
		const int * cart_map_func_arg3 = va_arg(argp, const int *);
		int * cart_map_func_arg4 = va_arg(argp, int *);
		ret = (QMPI_Cart_map_ptr) (cart_map_func_arg0, cart_map_func_arg1, cart_map_func_arg2, cart_map_func_arg3, cart_map_func_arg4,  level, v);
		break;
		 
        // int QMPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank, int level, vector *v);\n
     
    case 27:
        va_start(argp,v);
		typedef int (*cart_rank_func) (MPI_Comm comm, const int coords[], int *rank, int level, vector *v);
		cart_rank_func QMPI_Cart_rank_ptr = (cart_rank_func) func_ptr;
		MPI_Comm cart_rank_func_arg0 = va_arg(argp, MPI_Comm);
		const int * cart_rank_func_arg1 = va_arg(argp, const int *);
		int * cart_rank_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Cart_rank_ptr) (cart_rank_func_arg0, cart_rank_func_arg1, cart_rank_func_arg2,  level, v);
		break;
		 
        // int QMPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank, int level, vector *v);\n
     
    case 28:
        va_start(argp,v);
		typedef int (*cart_shift_func) (MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest, int level, vector *v);
		cart_shift_func QMPI_Cart_shift_ptr = (cart_shift_func) func_ptr;
		MPI_Comm cart_shift_func_arg0 = va_arg(argp, MPI_Comm);
		int cart_shift_func_arg1 = va_arg(argp, int);
		int cart_shift_func_arg2 = va_arg(argp, int);
		int * cart_shift_func_arg3 = va_arg(argp, int *);
		int * cart_shift_func_arg4 = va_arg(argp, int *);
		ret = (QMPI_Cart_shift_ptr) (cart_shift_func_arg0, cart_shift_func_arg1, cart_shift_func_arg2, cart_shift_func_arg3, cart_shift_func_arg4,  level, v);
		break;
		 
        // int QMPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest, int level, vector *v);\n
     
    case 29:
        va_start(argp,v);
		typedef int (*cart_sub_func) (MPI_Comm comm, const int remain_dims[], MPI_Comm *new_comm, int level, vector *v);
		cart_sub_func QMPI_Cart_sub_ptr = (cart_sub_func) func_ptr;
		MPI_Comm cart_sub_func_arg0 = va_arg(argp, MPI_Comm);
		const int * cart_sub_func_arg1 = va_arg(argp, const int *);
		MPI_Comm * cart_sub_func_arg2 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Cart_sub_ptr) (cart_sub_func_arg0, cart_sub_func_arg1, cart_sub_func_arg2,  level, v);
		break;
		 
        // int QMPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *new_comm, int level, vector *v);\n
     
    case 30:
        va_start(argp,v);
		typedef int (*cartdim_get_func) (MPI_Comm comm, int *ndims, int level, vector *v);
		cartdim_get_func QMPI_Cartdim_get_ptr = (cartdim_get_func) func_ptr;
		MPI_Comm cartdim_get_func_arg0 = va_arg(argp, MPI_Comm);
		int * cartdim_get_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Cartdim_get_ptr) (cartdim_get_func_arg0, cartdim_get_func_arg1,  level, v);
		break;
		 
        // int QMPI_Cartdim_get(MPI_Comm comm, int *ndims, int level, vector *v);\n
     
    case 31:
        va_start(argp,v);
		typedef int (*close_port_func) (const char *port_name, int level, vector *v);
		close_port_func QMPI_Close_port_ptr = (close_port_func) func_ptr;
		const char * close_port_func_arg0 = va_arg(argp, const char *);
		ret = (QMPI_Close_port_ptr) (close_port_func_arg0,  level, v);
		break;
		 
        // int QMPI_Close_port(const char *port_name, int level, vector *v);\n
     
    case 32:
        va_start(argp,v);
		typedef int (*comm_accept_func) (const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm, int level, vector *v);
		comm_accept_func QMPI_Comm_accept_ptr = (comm_accept_func) func_ptr;
		const char * comm_accept_func_arg0 = va_arg(argp, const char *);
		MPI_Info comm_accept_func_arg1 = va_arg(argp, MPI_Info);
		int comm_accept_func_arg2 = va_arg(argp, int);
		MPI_Comm comm_accept_func_arg3 = va_arg(argp, MPI_Comm);
		MPI_Comm * comm_accept_func_arg4 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_accept_ptr) (comm_accept_func_arg0, comm_accept_func_arg1, comm_accept_func_arg2, comm_accept_func_arg3, comm_accept_func_arg4,  level, v);
		break;
		 
        // int QMPI_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 33:
        va_start(argp,v);
		typedef int (*comm_call_errhandler_func) (MPI_Comm comm, int errorcode, int level, vector *v);
		comm_call_errhandler_func QMPI_Comm_call_errhandler_ptr = (comm_call_errhandler_func) func_ptr;
		MPI_Comm comm_call_errhandler_func_arg0 = va_arg(argp, MPI_Comm);
		int comm_call_errhandler_func_arg1 = va_arg(argp, int);
		ret = (QMPI_Comm_call_errhandler_ptr) (comm_call_errhandler_func_arg0, comm_call_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_call_errhandler(MPI_Comm comm, int errorcode, int level, vector *v);\n
     
    case 34:
        va_start(argp,v);
		typedef int (*comm_compare_func) (MPI_Comm comm1, MPI_Comm comm2, int *result, int level, vector *v);
		comm_compare_func QMPI_Comm_compare_ptr = (comm_compare_func) func_ptr;
		MPI_Comm comm_compare_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Comm comm_compare_func_arg1 = va_arg(argp, MPI_Comm);
		int * comm_compare_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Comm_compare_ptr) (comm_compare_func_arg0, comm_compare_func_arg1, comm_compare_func_arg2,  level, v);
		break;
		 
        // int QMPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result, int level, vector *v);\n
     
    case 35:
        va_start(argp,v);
		typedef int (*comm_connect_func) (const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm, int level, vector *v);
		comm_connect_func QMPI_Comm_connect_ptr = (comm_connect_func) func_ptr;
		const char * comm_connect_func_arg0 = va_arg(argp, const char *);
		MPI_Info comm_connect_func_arg1 = va_arg(argp, MPI_Info);
		int comm_connect_func_arg2 = va_arg(argp, int);
		MPI_Comm comm_connect_func_arg3 = va_arg(argp, MPI_Comm);
		MPI_Comm * comm_connect_func_arg4 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_connect_ptr) (comm_connect_func_arg0, comm_connect_func_arg1, comm_connect_func_arg2, comm_connect_func_arg3, comm_connect_func_arg4,  level, v);
		break;
		 
        // int QMPI_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 36:
        va_start(argp,v);
		typedef int (*comm_create_func) (MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm, int level, vector *v);
		comm_create_func QMPI_Comm_create_ptr = (comm_create_func) func_ptr;
		MPI_Comm comm_create_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Group comm_create_func_arg1 = va_arg(argp, MPI_Group);
		MPI_Comm * comm_create_func_arg2 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_create_ptr) (comm_create_func_arg0, comm_create_func_arg1, comm_create_func_arg2,  level, v);
		break;
		 
        // int QMPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 37:
        va_start(argp,v);
		typedef int (*comm_create_errhandler_func) (MPI_Comm_errhandler_function *function, MPI_Errhandler *errhandler, int level, vector *v);
		comm_create_errhandler_func QMPI_Comm_create_errhandler_ptr = (comm_create_errhandler_func) func_ptr;
		MPI_Comm_errhandler_function * comm_create_errhandler_func_arg0 = va_arg(argp, MPI_Comm_errhandler_function *);
		MPI_Errhandler * comm_create_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_Comm_create_errhandler_ptr) (comm_create_errhandler_func_arg0, comm_create_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_create_errhandler(MPI_Comm_errhandler_function *function, MPI_Errhandler *errhandler, int level, vector *v);\n
     
    case 38:
        va_start(argp,v);
		typedef int (*comm_create_group_func) (MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm, int level, vector *v);
		comm_create_group_func QMPI_Comm_create_group_ptr = (comm_create_group_func) func_ptr;
		MPI_Comm comm_create_group_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Group comm_create_group_func_arg1 = va_arg(argp, MPI_Group);
		int comm_create_group_func_arg2 = va_arg(argp, int);
		MPI_Comm * comm_create_group_func_arg3 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_create_group_ptr) (comm_create_group_func_arg0, comm_create_group_func_arg1, comm_create_group_func_arg2, comm_create_group_func_arg3,  level, v);
		break;
		 
        // int QMPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 39:
        va_start(argp,v);
		typedef int (*comm_create_keyval_func) (MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state, int level, vector *v);
		comm_create_keyval_func QMPI_Comm_create_keyval_ptr = (comm_create_keyval_func) func_ptr;
		MPI_Comm_copy_attr_function * comm_create_keyval_func_arg0 = va_arg(argp, MPI_Comm_copy_attr_function *);
		MPI_Comm_delete_attr_function * comm_create_keyval_func_arg1 = va_arg(argp, MPI_Comm_delete_attr_function *);
		int * comm_create_keyval_func_arg2 = va_arg(argp, int *);
		void * comm_create_keyval_func_arg3 = va_arg(argp, void *);
		ret = (QMPI_Comm_create_keyval_ptr) (comm_create_keyval_func_arg0, comm_create_keyval_func_arg1, comm_create_keyval_func_arg2, comm_create_keyval_func_arg3,  level, v);
		break;
		 
        // int QMPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state, int level, vector *v);\n
     
    case 40:
        va_start(argp,v);
		typedef int (*comm_delete_attr_func) (MPI_Comm comm, int comm_keyval, int level, vector *v);
		comm_delete_attr_func QMPI_Comm_delete_attr_ptr = (comm_delete_attr_func) func_ptr;
		MPI_Comm comm_delete_attr_func_arg0 = va_arg(argp, MPI_Comm);
		int comm_delete_attr_func_arg1 = va_arg(argp, int);
		ret = (QMPI_Comm_delete_attr_ptr) (comm_delete_attr_func_arg0, comm_delete_attr_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval, int level, vector *v);\n
     
    case 41:
        va_start(argp,v);
		typedef int (*comm_disconnect_func) (MPI_Comm *comm, int level, vector *v);
		comm_disconnect_func QMPI_Comm_disconnect_ptr = (comm_disconnect_func) func_ptr;
		MPI_Comm * comm_disconnect_func_arg0 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_disconnect_ptr) (comm_disconnect_func_arg0,  level, v);
		break;
		 
        // int QMPI_Comm_disconnect(MPI_Comm *comm, int level, vector *v);\n
     
    case 42:
        va_start(argp,v);
		typedef int (*comm_dup_func) (MPI_Comm comm, MPI_Comm *newcomm, int level, vector *v);
		comm_dup_func QMPI_Comm_dup_ptr = (comm_dup_func) func_ptr;
		MPI_Comm comm_dup_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Comm * comm_dup_func_arg1 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_dup_ptr) (comm_dup_func_arg0, comm_dup_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 43:
        va_start(argp,v);
		typedef int (*comm_dup_with_info_func) (MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, int level, vector *v);
		comm_dup_with_info_func QMPI_Comm_dup_with_info_ptr = (comm_dup_with_info_func) func_ptr;
		MPI_Comm comm_dup_with_info_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Info comm_dup_with_info_func_arg1 = va_arg(argp, MPI_Info);
		MPI_Comm * comm_dup_with_info_func_arg2 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_dup_with_info_ptr) (comm_dup_with_info_func_arg0, comm_dup_with_info_func_arg1, comm_dup_with_info_func_arg2,  level, v);
		break;
		 
        // int QMPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 44:
        va_start(argp,v);
		typedef int (*comm_free_func) (MPI_Comm *comm, int level, vector *v);
		comm_free_func QMPI_Comm_free_ptr = (comm_free_func) func_ptr;
		MPI_Comm * comm_free_func_arg0 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_free_ptr) (comm_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Comm_free(MPI_Comm *comm, int level, vector *v);\n
     
    case 45:
        va_start(argp,v);
		typedef int (*comm_free_keyval_func) (int *comm_keyval, int level, vector *v);
		comm_free_keyval_func QMPI_Comm_free_keyval_ptr = (comm_free_keyval_func) func_ptr;
		int * comm_free_keyval_func_arg0 = va_arg(argp, int *);
		ret = (QMPI_Comm_free_keyval_ptr) (comm_free_keyval_func_arg0,  level, v);
		break;
		 
        // int QMPI_Comm_free_keyval(int *comm_keyval, int level, vector *v);\n
     
    case 46:
        va_start(argp,v);
		typedef int (*comm_get_attr_func) (MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag, int level, vector *v);
		comm_get_attr_func QMPI_Comm_get_attr_ptr = (comm_get_attr_func) func_ptr;
		MPI_Comm comm_get_attr_func_arg0 = va_arg(argp, MPI_Comm);
		int comm_get_attr_func_arg1 = va_arg(argp, int);
		void * comm_get_attr_func_arg2 = va_arg(argp, void *);
		int * comm_get_attr_func_arg3 = va_arg(argp, int *);
		ret = (QMPI_Comm_get_attr_ptr) (comm_get_attr_func_arg0, comm_get_attr_func_arg1, comm_get_attr_func_arg2, comm_get_attr_func_arg3,  level, v);
		break;
		 
        // int QMPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag, int level, vector *v);\n
     
    case 47:
        va_start(argp,v);
		typedef int (*comm_get_errhandler_func) (MPI_Comm comm, MPI_Errhandler *erhandler, int level, vector *v);
		comm_get_errhandler_func QMPI_Comm_get_errhandler_ptr = (comm_get_errhandler_func) func_ptr;
		MPI_Comm comm_get_errhandler_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Errhandler * comm_get_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_Comm_get_errhandler_ptr) (comm_get_errhandler_func_arg0, comm_get_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *erhandler, int level, vector *v);\n
     
    case 48:
        va_start(argp,v);
		typedef int (*comm_get_info_func) (MPI_Comm comm, MPI_Info *info_used, int level, vector *v);
		comm_get_info_func QMPI_Comm_get_info_ptr = (comm_get_info_func) func_ptr;
		MPI_Comm comm_get_info_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Info * comm_get_info_func_arg1 = va_arg(argp, MPI_Info *);
		ret = (QMPI_Comm_get_info_ptr) (comm_get_info_func_arg0, comm_get_info_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used, int level, vector *v);\n
     
    case 49:
        va_start(argp,v);
		typedef int (*comm_get_name_func) (MPI_Comm comm, char *comm_name, int *resultlen, int level, vector *v);
		comm_get_name_func QMPI_Comm_get_name_ptr = (comm_get_name_func) func_ptr;
		MPI_Comm comm_get_name_func_arg0 = va_arg(argp, MPI_Comm);
		char * comm_get_name_func_arg1 = va_arg(argp, char *);
		int * comm_get_name_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Comm_get_name_ptr) (comm_get_name_func_arg0, comm_get_name_func_arg1, comm_get_name_func_arg2,  level, v);
		break;
		 
        // int QMPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen, int level, vector *v);\n
     
    case 50:
        va_start(argp,v);
		typedef int (*comm_get_parent_func) (MPI_Comm *parent, int level, vector *v);
		comm_get_parent_func QMPI_Comm_get_parent_ptr = (comm_get_parent_func) func_ptr;
		MPI_Comm * comm_get_parent_func_arg0 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_get_parent_ptr) (comm_get_parent_func_arg0,  level, v);
		break;
		 
        // int QMPI_Comm_get_parent(MPI_Comm *parent, int level, vector *v);\n
     
    case 51:
        va_start(argp,v);
		typedef int (*comm_group_func) (MPI_Comm comm, MPI_Group *group, int level, vector *v);
		comm_group_func QMPI_Comm_group_ptr = (comm_group_func) func_ptr;
		MPI_Comm comm_group_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Group * comm_group_func_arg1 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Comm_group_ptr) (comm_group_func_arg0, comm_group_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_group(MPI_Comm comm, MPI_Group *group, int level, vector *v);\n
     
    case 52:
        va_start(argp,v);
		typedef int (*comm_idup_func) (MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request, int level, vector *v);
		comm_idup_func QMPI_Comm_idup_ptr = (comm_idup_func) func_ptr;
		MPI_Comm comm_idup_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Comm * comm_idup_func_arg1 = va_arg(argp, MPI_Comm *);
		MPI_Request * comm_idup_func_arg2 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Comm_idup_ptr) (comm_idup_func_arg0, comm_idup_func_arg1, comm_idup_func_arg2,  level, v);
		break;
		 
        // int QMPI_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request, int level, vector *v);\n
     
    case 53:
        va_start(argp,v);
		typedef int (*comm_join_func) (int fd, MPI_Comm *intercomm, int level, vector *v);
		comm_join_func QMPI_Comm_join_ptr = (comm_join_func) func_ptr;
		int comm_join_func_arg0 = va_arg(argp, int);
		MPI_Comm * comm_join_func_arg1 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_join_ptr) (comm_join_func_arg0, comm_join_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_join(int fd, MPI_Comm *intercomm, int level, vector *v);\n
     
    case 54:
        va_start(argp, v);
        typedef int (*comm_rank_func)(MPI_Comm comm,int *rank,int i , vector* v );
        comm_rank_func comm_rank_ptr =  (comm_rank_func) func_ptr;;
        MPI_Comm comm_rank_arg_1 =      va_arg(argp, MPI_Comm);
        int* comm_rank_arg_2 =          va_arg( argp, int* );
        ret= (comm_rank_ptr ) ( comm_rank_arg_1, comm_rank_arg_2, level, v);
		break;
		 
        // int QMPI_Comm_rank(MPI_Comm comm, int *rank, int level, vector *v);\n
     
    case 55:
        va_start(argp,v);
		typedef int (*comm_remote_group_func) (MPI_Comm comm, MPI_Group *group, int level, vector *v);
		comm_remote_group_func QMPI_Comm_remote_group_ptr = (comm_remote_group_func) func_ptr;
		MPI_Comm comm_remote_group_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Group * comm_remote_group_func_arg1 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Comm_remote_group_ptr) (comm_remote_group_func_arg0, comm_remote_group_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group, int level, vector *v);\n
     
    case 56:
        va_start(argp,v);
		typedef int (*comm_remote_size_func) (MPI_Comm comm, int *size, int level, vector *v);
		comm_remote_size_func QMPI_Comm_remote_size_ptr = (comm_remote_size_func) func_ptr;
		MPI_Comm comm_remote_size_func_arg0 = va_arg(argp, MPI_Comm);
		int * comm_remote_size_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Comm_remote_size_ptr) (comm_remote_size_func_arg0, comm_remote_size_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_remote_size(MPI_Comm comm, int *size, int level, vector *v);\n
     
    case 57:
        va_start(argp,v);
		typedef int (*comm_set_attr_func) (MPI_Comm comm, int comm_keyval, void *attribute_val, int level, vector *v);
		comm_set_attr_func QMPI_Comm_set_attr_ptr = (comm_set_attr_func) func_ptr;
		MPI_Comm comm_set_attr_func_arg0 = va_arg(argp, MPI_Comm);
		int comm_set_attr_func_arg1 = va_arg(argp, int);
		void * comm_set_attr_func_arg2 = va_arg(argp, void *);
		ret = (QMPI_Comm_set_attr_ptr) (comm_set_attr_func_arg0, comm_set_attr_func_arg1, comm_set_attr_func_arg2,  level, v);
		break;
		 
        // int QMPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int level, vector *v);\n
     
    case 58:
        va_start(argp,v);
		typedef int (*comm_set_errhandler_func) (MPI_Comm comm, MPI_Errhandler errhandler, int level, vector *v);
		comm_set_errhandler_func QMPI_Comm_set_errhandler_ptr = (comm_set_errhandler_func) func_ptr;
		MPI_Comm comm_set_errhandler_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Errhandler comm_set_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler);
		ret = (QMPI_Comm_set_errhandler_ptr) (comm_set_errhandler_func_arg0, comm_set_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler, int level, vector *v);\n
     
    case 59:
        va_start(argp,v);
		typedef int (*comm_set_info_func) (MPI_Comm comm, MPI_Info info, int level, vector *v);
		comm_set_info_func QMPI_Comm_set_info_ptr = (comm_set_info_func) func_ptr;
		MPI_Comm comm_set_info_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Info comm_set_info_func_arg1 = va_arg(argp, MPI_Info);
		ret = (QMPI_Comm_set_info_ptr) (comm_set_info_func_arg0, comm_set_info_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_set_info(MPI_Comm comm, MPI_Info info, int level, vector *v);\n
     
    case 60:
        va_start(argp,v);
		typedef int (*comm_set_name_func) (MPI_Comm comm, const char *comm_name, int level, vector *v);
		comm_set_name_func QMPI_Comm_set_name_ptr = (comm_set_name_func) func_ptr;
		MPI_Comm comm_set_name_func_arg0 = va_arg(argp, MPI_Comm);
		const char * comm_set_name_func_arg1 = va_arg(argp, const char *);
		ret = (QMPI_Comm_set_name_ptr) (comm_set_name_func_arg0, comm_set_name_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_set_name(MPI_Comm comm, const char *comm_name, int level, vector *v);\n
     
    case 61:
        va_start(argp, v);
        typedef int (*comm_size_func)(MPI_Comm comm,int *size,int i , vector* v);
        comm_size_func comm_size_ptr = (comm_size_func) func_ptr;;
        MPI_Comm comm_size_arg_1 = va_arg( argp, MPI_Comm);
        int* comm_size_arg_2 =      va_arg( argp, int* );
        ret= (comm_size_ptr ) ( comm_size_arg_1, comm_size_arg_2, level, v);
        break;
		 
        // int QMPI_Comm_size(MPI_Comm comm, int *size, int level, vector *v);\n
     
    case 62:
        va_start(argp,v);
		typedef int (*comm_split_func) (MPI_Comm comm, int color, int key, MPI_Comm *newcomm, int level, vector *v);
		comm_split_func QMPI_Comm_split_ptr = (comm_split_func) func_ptr;
		MPI_Comm comm_split_func_arg0 = va_arg(argp, MPI_Comm);
		int comm_split_func_arg1 = va_arg(argp, int);
		int comm_split_func_arg2 = va_arg(argp, int);
		MPI_Comm * comm_split_func_arg3 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_split_ptr) (comm_split_func_arg0, comm_split_func_arg1, comm_split_func_arg2, comm_split_func_arg3,  level, v);
		break;
		 
        // int QMPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 63:
        va_start(argp,v);
		typedef int (*comm_split_type_func) (MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm, int level, vector *v);
		comm_split_type_func QMPI_Comm_split_type_ptr = (comm_split_type_func) func_ptr;
		MPI_Comm comm_split_type_func_arg0 = va_arg(argp, MPI_Comm);
		int comm_split_type_func_arg1 = va_arg(argp, int);
		int comm_split_type_func_arg2 = va_arg(argp, int);
		MPI_Info comm_split_type_func_arg3 = va_arg(argp, MPI_Info);
		MPI_Comm * comm_split_type_func_arg4 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Comm_split_type_ptr) (comm_split_type_func_arg0, comm_split_type_func_arg1, comm_split_type_func_arg2, comm_split_type_func_arg3, comm_split_type_func_arg4,  level, v);
		break;
		 
        // int QMPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 64:
        va_start(argp,v);
		typedef int (*comm_test_inter_func) (MPI_Comm comm, int *flag, int level, vector *v);
		comm_test_inter_func QMPI_Comm_test_inter_ptr = (comm_test_inter_func) func_ptr;
		MPI_Comm comm_test_inter_func_arg0 = va_arg(argp, MPI_Comm);
		int * comm_test_inter_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Comm_test_inter_ptr) (comm_test_inter_func_arg0, comm_test_inter_func_arg1,  level, v);
		break;
		 
        // int QMPI_Comm_test_inter(MPI_Comm comm, int *flag, int level, vector *v);\n
     
    case 65:
        va_start(argp,v);
		typedef int (*compare_and_swap_func) (const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win, int level, vector *v);
		compare_and_swap_func QMPI_Compare_and_swap_ptr = (compare_and_swap_func) func_ptr;
		const void * compare_and_swap_func_arg0 = va_arg(argp, const void *);
		const void * compare_and_swap_func_arg1 = va_arg(argp, const void *);
		void * compare_and_swap_func_arg2 = va_arg(argp, void *);
		MPI_Datatype compare_and_swap_func_arg3 = va_arg(argp, MPI_Datatype);
		int compare_and_swap_func_arg4 = va_arg(argp, int);
		MPI_Aint compare_and_swap_func_arg5 = va_arg(argp, MPI_Aint);
		MPI_Win compare_and_swap_func_arg6 = va_arg(argp, MPI_Win);
		ret = (QMPI_Compare_and_swap_ptr) (compare_and_swap_func_arg0, compare_and_swap_func_arg1, compare_and_swap_func_arg2, compare_and_swap_func_arg3, compare_and_swap_func_arg4, compare_and_swap_func_arg5, compare_and_swap_func_arg6,  level, v);
		break;
		 
        // int QMPI_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win, int level, vector *v);\n
     
    case 66:
        va_start(argp,v);
		typedef int (*dims_create_func) (int nnodes, int ndims, int dims[], int level, vector *v);
		dims_create_func QMPI_Dims_create_ptr = (dims_create_func) func_ptr;
		int dims_create_func_arg0 = va_arg(argp, int);
		int dims_create_func_arg1 = va_arg(argp, int);
		int* dims_create_func_arg2 = va_arg(argp, int*);
		ret = (QMPI_Dims_create_ptr) (dims_create_func_arg0, dims_create_func_arg1, dims_create_func_arg2,  level, v);
		break;
		 
        // int QMPI_Dims_create(int nnodes, int ndims, int dims[], int level, vector *v);\n
     
    case 67:
        va_start(argp,v);
		typedef int (*dist_graph_create_func) (MPI_Comm comm_old, int n, const int nodes[], const int degrees[], const int targets[], const int weights[], MPI_Info info, int reorder, MPI_Comm *newcomm, int level, vector *v);
		dist_graph_create_func QMPI_Dist_graph_create_ptr = (dist_graph_create_func) func_ptr;
		MPI_Comm dist_graph_create_func_arg0 = va_arg(argp, MPI_Comm);
		int dist_graph_create_func_arg1 = va_arg(argp, int);
		const int * dist_graph_create_func_arg2 = va_arg(argp, const int *);
		const int * dist_graph_create_func_arg3 = va_arg(argp, const int *);
		const int * dist_graph_create_func_arg4 = va_arg(argp, const int *);
		const int * dist_graph_create_func_arg5 = va_arg(argp, const int *);
		MPI_Info dist_graph_create_func_arg6 = va_arg(argp, MPI_Info);
		int dist_graph_create_func_arg7 = va_arg(argp, int);
		MPI_Comm * dist_graph_create_func_arg8 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Dist_graph_create_ptr) (dist_graph_create_func_arg0, dist_graph_create_func_arg1, dist_graph_create_func_arg2, dist_graph_create_func_arg3, dist_graph_create_func_arg4, dist_graph_create_func_arg5, dist_graph_create_func_arg6, dist_graph_create_func_arg7, dist_graph_create_func_arg8,  level, v);
		break;
		 
        // int QMPI_Dist_graph_create(MPI_Comm comm_old, int n, const int nodes[], const int degrees[], const int targets[], const int weights[], MPI_Info info, int reorder, MPI_Comm *newcomm, int level, vector *v);\n
     
    case 68:
        va_start(argp,v);
		typedef int (*dist_graph_create_adjacent_func) (MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph, int level, vector *v);
		dist_graph_create_adjacent_func QMPI_Dist_graph_create_adjacent_ptr = (dist_graph_create_adjacent_func) func_ptr;
		MPI_Comm dist_graph_create_adjacent_func_arg0 = va_arg(argp, MPI_Comm);
		int dist_graph_create_adjacent_func_arg1 = va_arg(argp, int);
		const int * dist_graph_create_adjacent_func_arg2 = va_arg(argp, const int *);
		const int * dist_graph_create_adjacent_func_arg3 = va_arg(argp, const int *);
		int dist_graph_create_adjacent_func_arg4 = va_arg(argp, int);
		const int * dist_graph_create_adjacent_func_arg5 = va_arg(argp, const int *);
		const int * dist_graph_create_adjacent_func_arg6 = va_arg(argp, const int *);
		MPI_Info dist_graph_create_adjacent_func_arg7 = va_arg(argp, MPI_Info);
		int dist_graph_create_adjacent_func_arg8 = va_arg(argp, int);
		MPI_Comm * dist_graph_create_adjacent_func_arg9 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Dist_graph_create_adjacent_ptr) (dist_graph_create_adjacent_func_arg0, dist_graph_create_adjacent_func_arg1, dist_graph_create_adjacent_func_arg2, dist_graph_create_adjacent_func_arg3, dist_graph_create_adjacent_func_arg4, dist_graph_create_adjacent_func_arg5, dist_graph_create_adjacent_func_arg6, dist_graph_create_adjacent_func_arg7, dist_graph_create_adjacent_func_arg8, dist_graph_create_adjacent_func_arg9,  level, v);
		break;
		 
        // int QMPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph, int level, vector *v);\n
     
    case 69:
        va_start(argp,v);
		typedef int (*dist_graph_neighbors_func) (MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[], int level, vector *v);
		dist_graph_neighbors_func QMPI_Dist_graph_neighbors_ptr = (dist_graph_neighbors_func) func_ptr;
		MPI_Comm dist_graph_neighbors_func_arg0 = va_arg(argp, MPI_Comm);
		int dist_graph_neighbors_func_arg1 = va_arg(argp, int);
		int* dist_graph_neighbors_func_arg2 = va_arg(argp, int*);
		int* dist_graph_neighbors_func_arg3 = va_arg(argp, int*);
		int dist_graph_neighbors_func_arg4 = va_arg(argp, int);
		int* dist_graph_neighbors_func_arg5 = va_arg(argp, int*);
		int* dist_graph_neighbors_func_arg6 = va_arg(argp, int*);
		ret = (QMPI_Dist_graph_neighbors_ptr) (dist_graph_neighbors_func_arg0, dist_graph_neighbors_func_arg1, dist_graph_neighbors_func_arg2, dist_graph_neighbors_func_arg3, dist_graph_neighbors_func_arg4, dist_graph_neighbors_func_arg5, dist_graph_neighbors_func_arg6,  level, v);
		break;
		 
        // int QMPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[], int level, vector *v);\n
     
    case 70:
        va_start(argp,v);
		typedef int (*dist_graph_neighbors_count_func) (MPI_Comm comm, int *inneighbors, int *outneighbors, int *weighted, int level, vector *v);
		dist_graph_neighbors_count_func QMPI_Dist_graph_neighbors_count_ptr = (dist_graph_neighbors_count_func) func_ptr;
		MPI_Comm dist_graph_neighbors_count_func_arg0 = va_arg(argp, MPI_Comm);
		int * dist_graph_neighbors_count_func_arg1 = va_arg(argp, int *);
		int * dist_graph_neighbors_count_func_arg2 = va_arg(argp, int *);
		int * dist_graph_neighbors_count_func_arg3 = va_arg(argp, int *);
		ret = (QMPI_Dist_graph_neighbors_count_ptr) (dist_graph_neighbors_count_func_arg0, dist_graph_neighbors_count_func_arg1, dist_graph_neighbors_count_func_arg2, dist_graph_neighbors_count_func_arg3,  level, v);
		break;
		 
        // int QMPI_Dist_graph_neighbors_count(MPI_Comm comm, int *inneighbors, int *outneighbors, int *weighted, int level, vector *v);\n
     
    case 71:
        va_start(argp,v);
		typedef int (*errhandler_create_func) (MPI_Handler_function *function, MPI_Errhandler *errhandler, int level, vector *v);
		errhandler_create_func QMPI_Errhandler_create_ptr = (errhandler_create_func) func_ptr;
		MPI_Handler_function * errhandler_create_func_arg0 = va_arg(argp, MPI_Handler_function *);
		MPI_Errhandler * errhandler_create_func_arg1 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_Errhandler_create_ptr) (errhandler_create_func_arg0, errhandler_create_func_arg1,  level, v);
		break;
		 
        // int QMPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler, int level, vector *v);\n
     
    case 72:
        va_start(argp,v);
		typedef int (*errhandler_free_func) (MPI_Errhandler *errhandler, int level, vector *v);
		errhandler_free_func QMPI_Errhandler_free_ptr = (errhandler_free_func) func_ptr;
		MPI_Errhandler * errhandler_free_func_arg0 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_Errhandler_free_ptr) (errhandler_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Errhandler_free(MPI_Errhandler *errhandler, int level, vector *v);\n
     
    case 73:
        va_start(argp,v);
		typedef int (*errhandler_get_func) (MPI_Comm comm, MPI_Errhandler *errhandler, int level, vector *v);
		errhandler_get_func QMPI_Errhandler_get_ptr = (errhandler_get_func) func_ptr;
		MPI_Comm errhandler_get_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Errhandler * errhandler_get_func_arg1 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_Errhandler_get_ptr) (errhandler_get_func_arg0, errhandler_get_func_arg1,  level, v);
		break;
		 
        // int QMPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler, int level, vector *v);\n
     
    case 74:
        va_start(argp,v);
		typedef int (*errhandler_set_func) (MPI_Comm comm, MPI_Errhandler errhandler, int level, vector *v);
		errhandler_set_func QMPI_Errhandler_set_ptr = (errhandler_set_func) func_ptr;
		MPI_Comm errhandler_set_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Errhandler errhandler_set_func_arg1 = va_arg(argp, MPI_Errhandler);
		ret = (QMPI_Errhandler_set_ptr) (errhandler_set_func_arg0, errhandler_set_func_arg1,  level, v);
		break;
		 
        // int QMPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler, int level, vector *v);\n
     
    case 75:
        va_start(argp,v);
		typedef int (*error_class_func) (int errorcode, int *errorclass, int level, vector *v);
		error_class_func QMPI_Error_class_ptr = (error_class_func) func_ptr;
		int error_class_func_arg0 = va_arg(argp, int);
		int * error_class_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Error_class_ptr) (error_class_func_arg0, error_class_func_arg1,  level, v);
		break;
		 
        // int QMPI_Error_class(int errorcode, int *errorclass, int level, vector *v);\n
     
    case 76:
        va_start(argp,v);
		typedef int (*error_string_func) (int errorcode, char *string, int *resultlen, int level, vector *v);
		error_string_func QMPI_Error_string_ptr = (error_string_func) func_ptr;
		int error_string_func_arg0 = va_arg(argp, int);
		char * error_string_func_arg1 = va_arg(argp, char *);
		int * error_string_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Error_string_ptr) (error_string_func_arg0, error_string_func_arg1, error_string_func_arg2,  level, v);
		break;
		 
        // int QMPI_Error_string(int errorcode, char *string, int *resultlen, int level, vector *v);\n
     
    case 77:
        va_start(argp,v);
		typedef int (*exscan_func) (const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level, vector *v);
		exscan_func QMPI_Exscan_ptr = (exscan_func) func_ptr;
		const void * exscan_func_arg0 = va_arg(argp, const void *);
		void * exscan_func_arg1 = va_arg(argp, void *);
		int exscan_func_arg2 = va_arg(argp, int);
		MPI_Datatype exscan_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op exscan_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm exscan_func_arg5 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Exscan_ptr) (exscan_func_arg0, exscan_func_arg1, exscan_func_arg2, exscan_func_arg3, exscan_func_arg4, exscan_func_arg5,  level, v);
		break;
		 
        // int QMPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level, vector *v);\n
     
    case 78:
        va_start(argp,v);
		typedef int (*fetch_and_op_func) (const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win, int level, vector *v);
		fetch_and_op_func QMPI_Fetch_and_op_ptr = (fetch_and_op_func) func_ptr;
		const void * fetch_and_op_func_arg0 = va_arg(argp, const void *);
		void * fetch_and_op_func_arg1 = va_arg(argp, void *);
		MPI_Datatype fetch_and_op_func_arg2 = va_arg(argp, MPI_Datatype);
		int fetch_and_op_func_arg3 = va_arg(argp, int);
		MPI_Aint fetch_and_op_func_arg4 = va_arg(argp, MPI_Aint);
		MPI_Op fetch_and_op_func_arg5 = va_arg(argp, MPI_Op);
		MPI_Win fetch_and_op_func_arg6 = va_arg(argp, MPI_Win);
		ret = (QMPI_Fetch_and_op_ptr) (fetch_and_op_func_arg0, fetch_and_op_func_arg1, fetch_and_op_func_arg2, fetch_and_op_func_arg3, fetch_and_op_func_arg4, fetch_and_op_func_arg5, fetch_and_op_func_arg6,  level, v);
		break;
		 
        // int QMPI_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win, int level, vector *v);\n
     
    case 79:
        va_start(argp,v);
		typedef int (*file_call_errhandler_func) (MPI_File fh, int errorcode, int level, vector *v);
		file_call_errhandler_func QMPI_File_call_errhandler_ptr = (file_call_errhandler_func) func_ptr;
		MPI_File file_call_errhandler_func_arg0 = va_arg(argp, MPI_File);
		int file_call_errhandler_func_arg1 = va_arg(argp, int);
		ret = (QMPI_File_call_errhandler_ptr) (file_call_errhandler_func_arg0, file_call_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_call_errhandler(MPI_File fh, int errorcode, int level, vector *v);\n
     
    case 80:
        va_start(argp,v);
		typedef int (*file_close_func) (MPI_File *fh, int level, vector *v);
		file_close_func QMPI_File_close_ptr = (file_close_func) func_ptr;
		MPI_File * file_close_func_arg0 = va_arg(argp, MPI_File *);
		ret = (QMPI_File_close_ptr) (file_close_func_arg0,  level, v);
		break;
		 
        // int QMPI_File_close(MPI_File *fh, int level, vector *v);\n
     
    case 81:
        va_start(argp,v);
		typedef int (*file_create_errhandler_func) (MPI_File_errhandler_function *function, MPI_Errhandler *errhandler, int level, vector *v);
		file_create_errhandler_func QMPI_File_create_errhandler_ptr = (file_create_errhandler_func) func_ptr;
		MPI_File_errhandler_function * file_create_errhandler_func_arg0 = va_arg(argp, MPI_File_errhandler_function *);
		MPI_Errhandler * file_create_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_File_create_errhandler_ptr) (file_create_errhandler_func_arg0, file_create_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_create_errhandler(MPI_File_errhandler_function *function, MPI_Errhandler *errhandler, int level, vector *v);\n
     
    case 82:
        va_start(argp,v);
		typedef int (*file_delete_func) (const char *filename, MPI_Info info, int level, vector *v);
		file_delete_func QMPI_File_delete_ptr = (file_delete_func) func_ptr;
		const char * file_delete_func_arg0 = va_arg(argp, const char *);
		MPI_Info file_delete_func_arg1 = va_arg(argp, MPI_Info);
		ret = (QMPI_File_delete_ptr) (file_delete_func_arg0, file_delete_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_delete(const char *filename, MPI_Info info, int level, vector *v);\n
     
    case 83:
        va_start(argp,v);
		typedef int (*file_get_amode_func) (MPI_File fh, int *amode, int level, vector *v);
		file_get_amode_func QMPI_File_get_amode_ptr = (file_get_amode_func) func_ptr;
		MPI_File file_get_amode_func_arg0 = va_arg(argp, MPI_File);
		int * file_get_amode_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_File_get_amode_ptr) (file_get_amode_func_arg0, file_get_amode_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_get_amode(MPI_File fh, int *amode, int level, vector *v);\n
     
    case 84:
        va_start(argp,v);
		typedef int (*file_get_atomicity_func) (MPI_File fh, int *flag, int level, vector *v);
		file_get_atomicity_func QMPI_File_get_atomicity_ptr = (file_get_atomicity_func) func_ptr;
		MPI_File file_get_atomicity_func_arg0 = va_arg(argp, MPI_File);
		int * file_get_atomicity_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_File_get_atomicity_ptr) (file_get_atomicity_func_arg0, file_get_atomicity_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_get_atomicity(MPI_File fh, int *flag, int level, vector *v);\n
     
    case 85:
        va_start(argp,v);
		typedef int (*file_get_byte_offset_func) (MPI_File fh, MPI_Offset offset, MPI_Offset *disp, int level, vector *v);
		file_get_byte_offset_func QMPI_File_get_byte_offset_ptr = (file_get_byte_offset_func) func_ptr;
		MPI_File file_get_byte_offset_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_get_byte_offset_func_arg1 = va_arg(argp, MPI_Offset);
		MPI_Offset * file_get_byte_offset_func_arg2 = va_arg(argp, MPI_Offset *);
		ret = (QMPI_File_get_byte_offset_ptr) (file_get_byte_offset_func_arg0, file_get_byte_offset_func_arg1, file_get_byte_offset_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp, int level, vector *v);\n
     
    case 86:
        va_start(argp,v);
		typedef int (*file_get_errhandler_func) (MPI_File file, MPI_Errhandler *errhandler, int level, vector *v);
		file_get_errhandler_func QMPI_File_get_errhandler_ptr = (file_get_errhandler_func) func_ptr;
		MPI_File file_get_errhandler_func_arg0 = va_arg(argp, MPI_File);
		MPI_Errhandler * file_get_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_File_get_errhandler_ptr) (file_get_errhandler_func_arg0, file_get_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler, int level, vector *v);\n
     
    case 87:
        va_start(argp,v);
		typedef int (*file_get_group_func) (MPI_File fh, MPI_Group *group, int level, vector *v);
		file_get_group_func QMPI_File_get_group_ptr = (file_get_group_func) func_ptr;
		MPI_File file_get_group_func_arg0 = va_arg(argp, MPI_File);
		MPI_Group * file_get_group_func_arg1 = va_arg(argp, MPI_Group *);
		ret = (QMPI_File_get_group_ptr) (file_get_group_func_arg0, file_get_group_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_get_group(MPI_File fh, MPI_Group *group, int level, vector *v);\n
     
    case 88:
        va_start(argp,v);
		typedef int (*file_get_info_func) (MPI_File fh, MPI_Info *info_used, int level, vector *v);
		file_get_info_func QMPI_File_get_info_ptr = (file_get_info_func) func_ptr;
		MPI_File file_get_info_func_arg0 = va_arg(argp, MPI_File);
		MPI_Info * file_get_info_func_arg1 = va_arg(argp, MPI_Info *);
		ret = (QMPI_File_get_info_ptr) (file_get_info_func_arg0, file_get_info_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_get_info(MPI_File fh, MPI_Info *info_used, int level, vector *v);\n
     
    case 89:
        va_start(argp,v);
		typedef int (*file_get_position_func) (MPI_File fh, MPI_Offset *offset, int level, vector *v);
		file_get_position_func QMPI_File_get_position_ptr = (file_get_position_func) func_ptr;
		MPI_File file_get_position_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset * file_get_position_func_arg1 = va_arg(argp, MPI_Offset *);
		ret = (QMPI_File_get_position_ptr) (file_get_position_func_arg0, file_get_position_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_get_position(MPI_File fh, MPI_Offset *offset, int level, vector *v);\n
     
    case 90:
        va_start(argp,v);
		typedef int (*file_get_position_shared_func) (MPI_File fh, MPI_Offset *offset, int level, vector *v);
		file_get_position_shared_func QMPI_File_get_position_shared_ptr = (file_get_position_shared_func) func_ptr;
		MPI_File file_get_position_shared_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset * file_get_position_shared_func_arg1 = va_arg(argp, MPI_Offset *);
		ret = (QMPI_File_get_position_shared_ptr) (file_get_position_shared_func_arg0, file_get_position_shared_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset, int level, vector *v);\n
     
    case 91:
        va_start(argp,v);
		typedef int (*file_get_size_func) (MPI_File fh, MPI_Offset *size, int level, vector *v);
		file_get_size_func QMPI_File_get_size_ptr = (file_get_size_func) func_ptr;
		MPI_File file_get_size_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset * file_get_size_func_arg1 = va_arg(argp, MPI_Offset *);
		ret = (QMPI_File_get_size_ptr) (file_get_size_func_arg0, file_get_size_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_get_size(MPI_File fh, MPI_Offset *size, int level, vector *v);\n
     
    case 92:
        va_start(argp,v);
		typedef int (*file_get_type_extent_func) (MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent, int level, vector *v);
		file_get_type_extent_func QMPI_File_get_type_extent_ptr = (file_get_type_extent_func) func_ptr;
		MPI_File file_get_type_extent_func_arg0 = va_arg(argp, MPI_File);
		MPI_Datatype file_get_type_extent_func_arg1 = va_arg(argp, MPI_Datatype);
		MPI_Aint * file_get_type_extent_func_arg2 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_File_get_type_extent_ptr) (file_get_type_extent_func_arg0, file_get_type_extent_func_arg1, file_get_type_extent_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent, int level, vector *v);\n
     
    case 93:
        va_start(argp,v);
		typedef int (*file_get_view_func) (MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep, int level, vector *v);
		file_get_view_func QMPI_File_get_view_ptr = (file_get_view_func) func_ptr;
		MPI_File file_get_view_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset * file_get_view_func_arg1 = va_arg(argp, MPI_Offset *);
		MPI_Datatype * file_get_view_func_arg2 = va_arg(argp, MPI_Datatype *);
		MPI_Datatype * file_get_view_func_arg3 = va_arg(argp, MPI_Datatype *);
		char * file_get_view_func_arg4 = va_arg(argp, char *);
		ret = (QMPI_File_get_view_ptr) (file_get_view_func_arg0, file_get_view_func_arg1, file_get_view_func_arg2, file_get_view_func_arg3, file_get_view_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep, int level, vector *v);\n
     
    case 94:
        va_start(argp,v);
		typedef int (*file_iread_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iread_func QMPI_File_iread_ptr = (file_iread_func) func_ptr;
		MPI_File file_iread_func_arg0 = va_arg(argp, MPI_File);
		void * file_iread_func_arg1 = va_arg(argp, void *);
		int file_iread_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_iread_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iread_func_arg4 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iread_ptr) (file_iread_func_arg0, file_iread_func_arg1, file_iread_func_arg2, file_iread_func_arg3, file_iread_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 95:
        va_start(argp,v);
		typedef int (*file_iread_all_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iread_all_func QMPI_File_iread_all_ptr = (file_iread_all_func) func_ptr;
		MPI_File file_iread_all_func_arg0 = va_arg(argp, MPI_File);
		void * file_iread_all_func_arg1 = va_arg(argp, void *);
		int file_iread_all_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_iread_all_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iread_all_func_arg4 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iread_all_ptr) (file_iread_all_func_arg0, file_iread_all_func_arg1, file_iread_all_func_arg2, file_iread_all_func_arg3, file_iread_all_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_iread_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 96:
        va_start(argp,v);
		typedef int (*file_iread_at_func) (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iread_at_func QMPI_File_iread_at_ptr = (file_iread_at_func) func_ptr;
		MPI_File file_iread_at_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_iread_at_func_arg1 = va_arg(argp, MPI_Offset);
		void * file_iread_at_func_arg2 = va_arg(argp, void *);
		int file_iread_at_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_iread_at_func_arg4 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iread_at_func_arg5 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iread_at_ptr) (file_iread_at_func_arg0, file_iread_at_func_arg1, file_iread_at_func_arg2, file_iread_at_func_arg3, file_iread_at_func_arg4, file_iread_at_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 97:
        va_start(argp,v);
		typedef int (*file_iread_at_all_func) (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iread_at_all_func QMPI_File_iread_at_all_ptr = (file_iread_at_all_func) func_ptr;
		MPI_File file_iread_at_all_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_iread_at_all_func_arg1 = va_arg(argp, MPI_Offset);
		void * file_iread_at_all_func_arg2 = va_arg(argp, void *);
		int file_iread_at_all_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_iread_at_all_func_arg4 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iread_at_all_func_arg5 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iread_at_all_ptr) (file_iread_at_all_func_arg0, file_iread_at_all_func_arg1, file_iread_at_all_func_arg2, file_iread_at_all_func_arg3, file_iread_at_all_func_arg4, file_iread_at_all_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_iread_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 98:
        va_start(argp,v);
		typedef int (*file_iread_shared_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iread_shared_func QMPI_File_iread_shared_ptr = (file_iread_shared_func) func_ptr;
		MPI_File file_iread_shared_func_arg0 = va_arg(argp, MPI_File);
		void * file_iread_shared_func_arg1 = va_arg(argp, void *);
		int file_iread_shared_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_iread_shared_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iread_shared_func_arg4 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iread_shared_ptr) (file_iread_shared_func_arg0, file_iread_shared_func_arg1, file_iread_shared_func_arg2, file_iread_shared_func_arg3, file_iread_shared_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 99:
        va_start(argp,v);
		typedef int (*file_iwrite_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iwrite_func QMPI_File_iwrite_ptr = (file_iwrite_func) func_ptr;
		MPI_File file_iwrite_func_arg0 = va_arg(argp, MPI_File);
		const void * file_iwrite_func_arg1 = va_arg(argp, const void *);
		int file_iwrite_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_iwrite_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iwrite_func_arg4 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iwrite_ptr) (file_iwrite_func_arg0, file_iwrite_func_arg1, file_iwrite_func_arg2, file_iwrite_func_arg3, file_iwrite_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 100:
        va_start(argp,v);
		typedef int (*file_iwrite_all_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iwrite_all_func QMPI_File_iwrite_all_ptr = (file_iwrite_all_func) func_ptr;
		MPI_File file_iwrite_all_func_arg0 = va_arg(argp, MPI_File);
		const void * file_iwrite_all_func_arg1 = va_arg(argp, const void *);
		int file_iwrite_all_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_iwrite_all_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iwrite_all_func_arg4 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iwrite_all_ptr) (file_iwrite_all_func_arg0, file_iwrite_all_func_arg1, file_iwrite_all_func_arg2, file_iwrite_all_func_arg3, file_iwrite_all_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_iwrite_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 101:
        va_start(argp,v);
		typedef int (*file_iwrite_at_func) (MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iwrite_at_func QMPI_File_iwrite_at_ptr = (file_iwrite_at_func) func_ptr;
		MPI_File file_iwrite_at_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_iwrite_at_func_arg1 = va_arg(argp, MPI_Offset);
		const void * file_iwrite_at_func_arg2 = va_arg(argp, const void *);
		int file_iwrite_at_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_iwrite_at_func_arg4 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iwrite_at_func_arg5 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iwrite_at_ptr) (file_iwrite_at_func_arg0, file_iwrite_at_func_arg1, file_iwrite_at_func_arg2, file_iwrite_at_func_arg3, file_iwrite_at_func_arg4, file_iwrite_at_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 102:
        va_start(argp,v);
		typedef int (*file_iwrite_at_all_func) (MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iwrite_at_all_func QMPI_File_iwrite_at_all_ptr = (file_iwrite_at_all_func) func_ptr;
		MPI_File file_iwrite_at_all_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_iwrite_at_all_func_arg1 = va_arg(argp, MPI_Offset);
		const void * file_iwrite_at_all_func_arg2 = va_arg(argp, const void *);
		int file_iwrite_at_all_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_iwrite_at_all_func_arg4 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iwrite_at_all_func_arg5 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iwrite_at_all_ptr) (file_iwrite_at_all_func_arg0, file_iwrite_at_all_func_arg1, file_iwrite_at_all_func_arg2, file_iwrite_at_all_func_arg3, file_iwrite_at_all_func_arg4, file_iwrite_at_all_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_iwrite_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 103:
        va_start(argp,v);
		typedef int (*file_iwrite_shared_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);
		file_iwrite_shared_func QMPI_File_iwrite_shared_ptr = (file_iwrite_shared_func) func_ptr;
		MPI_File file_iwrite_shared_func_arg0 = va_arg(argp, MPI_File);
		const void * file_iwrite_shared_func_arg1 = va_arg(argp, const void *);
		int file_iwrite_shared_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_iwrite_shared_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Request * file_iwrite_shared_func_arg4 = va_arg(argp, MPI_Request *);
		ret = (QMPI_File_iwrite_shared_ptr) (file_iwrite_shared_func_arg0, file_iwrite_shared_func_arg1, file_iwrite_shared_func_arg2, file_iwrite_shared_func_arg3, file_iwrite_shared_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_iwrite_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level, vector *v);\n
     
    case 104:
        va_start(argp,v);
		typedef int (*file_open_func) (MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh, int level, vector *v);
		file_open_func QMPI_File_open_ptr = (file_open_func) func_ptr;
		MPI_Comm file_open_func_arg0 = va_arg(argp, MPI_Comm);
		const char * file_open_func_arg1 = va_arg(argp, const char *);
		int file_open_func_arg2 = va_arg(argp, int);
		MPI_Info file_open_func_arg3 = va_arg(argp, MPI_Info);
		MPI_File * file_open_func_arg4 = va_arg(argp, MPI_File *);
		ret = (QMPI_File_open_ptr) (file_open_func_arg0, file_open_func_arg1, file_open_func_arg2, file_open_func_arg3, file_open_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh, int level, vector *v);\n
     
    case 105:
        va_start(argp,v);
		typedef int (*file_preallocate_func) (MPI_File fh, MPI_Offset size, int level, vector *v);
		file_preallocate_func QMPI_File_preallocate_ptr = (file_preallocate_func) func_ptr;
		MPI_File file_preallocate_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_preallocate_func_arg1 = va_arg(argp, MPI_Offset);
		ret = (QMPI_File_preallocate_ptr) (file_preallocate_func_arg0, file_preallocate_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_preallocate(MPI_File fh, MPI_Offset size, int level, vector *v);\n
     
    case 106:
        va_start(argp,v);
		typedef int (*file_read_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_read_func QMPI_File_read_ptr = (file_read_func) func_ptr;
		MPI_File file_read_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_func_arg1 = va_arg(argp, void *);
		int file_read_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_read_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_read_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_ptr) (file_read_func_arg0, file_read_func_arg1, file_read_func_arg2, file_read_func_arg3, file_read_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 107:
        va_start(argp,v);
		typedef int (*file_read_all_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_read_all_func QMPI_File_read_all_ptr = (file_read_all_func) func_ptr;
		MPI_File file_read_all_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_all_func_arg1 = va_arg(argp, void *);
		int file_read_all_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_read_all_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_read_all_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_all_ptr) (file_read_all_func_arg0, file_read_all_func_arg1, file_read_all_func_arg2, file_read_all_func_arg3, file_read_all_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 108:
        va_start(argp,v);
		typedef int (*file_read_all_begin_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, int level, vector *v);
		file_read_all_begin_func QMPI_File_read_all_begin_ptr = (file_read_all_begin_func) func_ptr;
		MPI_File file_read_all_begin_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_all_begin_func_arg1 = va_arg(argp, void *);
		int file_read_all_begin_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_read_all_begin_func_arg3 = va_arg(argp, MPI_Datatype);
		ret = (QMPI_File_read_all_begin_ptr) (file_read_all_begin_func_arg0, file_read_all_begin_func_arg1, file_read_all_begin_func_arg2, file_read_all_begin_func_arg3,  level, v);
		break;
		 
        // int QMPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype, int level, vector *v);\n
     
    case 109:
        va_start(argp,v);
		typedef int (*file_read_all_end_func) (MPI_File fh, void *buf, MPI_Status *status, int level, vector *v);
		file_read_all_end_func QMPI_File_read_all_end_ptr = (file_read_all_end_func) func_ptr;
		MPI_File file_read_all_end_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_all_end_func_arg1 = va_arg(argp, void *);
		MPI_Status * file_read_all_end_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_all_end_ptr) (file_read_all_end_func_arg0, file_read_all_end_func_arg1, file_read_all_end_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status, int level, vector *v);\n
     
    case 110:
        va_start(argp,v);
		typedef int (*file_read_at_func) (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_read_at_func QMPI_File_read_at_ptr = (file_read_at_func) func_ptr;
		MPI_File file_read_at_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_read_at_func_arg1 = va_arg(argp, MPI_Offset);
		void * file_read_at_func_arg2 = va_arg(argp, void *);
		int file_read_at_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_read_at_func_arg4 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_read_at_func_arg5 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_at_ptr) (file_read_at_func_arg0, file_read_at_func_arg1, file_read_at_func_arg2, file_read_at_func_arg3, file_read_at_func_arg4, file_read_at_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 111:
        va_start(argp,v);
		typedef int (*file_read_at_all_func) (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_read_at_all_func QMPI_File_read_at_all_ptr = (file_read_at_all_func) func_ptr;
		MPI_File file_read_at_all_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_read_at_all_func_arg1 = va_arg(argp, MPI_Offset);
		void * file_read_at_all_func_arg2 = va_arg(argp, void *);
		int file_read_at_all_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_read_at_all_func_arg4 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_read_at_all_func_arg5 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_at_all_ptr) (file_read_at_all_func_arg0, file_read_at_all_func_arg1, file_read_at_all_func_arg2, file_read_at_all_func_arg3, file_read_at_all_func_arg4, file_read_at_all_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 112:
        va_start(argp,v);
		typedef int (*file_read_at_all_begin_func) (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, int level, vector *v);
		file_read_at_all_begin_func QMPI_File_read_at_all_begin_ptr = (file_read_at_all_begin_func) func_ptr;
		MPI_File file_read_at_all_begin_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_read_at_all_begin_func_arg1 = va_arg(argp, MPI_Offset);
		void * file_read_at_all_begin_func_arg2 = va_arg(argp, void *);
		int file_read_at_all_begin_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_read_at_all_begin_func_arg4 = va_arg(argp, MPI_Datatype);
		ret = (QMPI_File_read_at_all_begin_ptr) (file_read_at_all_begin_func_arg0, file_read_at_all_begin_func_arg1, file_read_at_all_begin_func_arg2, file_read_at_all_begin_func_arg3, file_read_at_all_begin_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, int level, vector *v);\n
     
    case 113:
        va_start(argp,v);
		typedef int (*file_read_at_all_end_func) (MPI_File fh, void *buf, MPI_Status *status, int level, vector *v);
		file_read_at_all_end_func QMPI_File_read_at_all_end_ptr = (file_read_at_all_end_func) func_ptr;
		MPI_File file_read_at_all_end_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_at_all_end_func_arg1 = va_arg(argp, void *);
		MPI_Status * file_read_at_all_end_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_at_all_end_ptr) (file_read_at_all_end_func_arg0, file_read_at_all_end_func_arg1, file_read_at_all_end_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status, int level, vector *v);\n
     
    case 114:
        va_start(argp,v);
		typedef int (*file_read_ordered_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_read_ordered_func QMPI_File_read_ordered_ptr = (file_read_ordered_func) func_ptr;
		MPI_File file_read_ordered_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_ordered_func_arg1 = va_arg(argp, void *);
		int file_read_ordered_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_read_ordered_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_read_ordered_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_ordered_ptr) (file_read_ordered_func_arg0, file_read_ordered_func_arg1, file_read_ordered_func_arg2, file_read_ordered_func_arg3, file_read_ordered_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 115:
        va_start(argp,v);
		typedef int (*file_read_ordered_begin_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, int level, vector *v);
		file_read_ordered_begin_func QMPI_File_read_ordered_begin_ptr = (file_read_ordered_begin_func) func_ptr;
		MPI_File file_read_ordered_begin_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_ordered_begin_func_arg1 = va_arg(argp, void *);
		int file_read_ordered_begin_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_read_ordered_begin_func_arg3 = va_arg(argp, MPI_Datatype);
		ret = (QMPI_File_read_ordered_begin_ptr) (file_read_ordered_begin_func_arg0, file_read_ordered_begin_func_arg1, file_read_ordered_begin_func_arg2, file_read_ordered_begin_func_arg3,  level, v);
		break;
		 
        // int QMPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype, int level, vector *v);\n
     
    case 116:
        va_start(argp,v);
		typedef int (*file_read_ordered_end_func) (MPI_File fh, void *buf, MPI_Status *status, int level, vector *v);
		file_read_ordered_end_func QMPI_File_read_ordered_end_ptr = (file_read_ordered_end_func) func_ptr;
		MPI_File file_read_ordered_end_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_ordered_end_func_arg1 = va_arg(argp, void *);
		MPI_Status * file_read_ordered_end_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_ordered_end_ptr) (file_read_ordered_end_func_arg0, file_read_ordered_end_func_arg1, file_read_ordered_end_func_arg2, level, v);
		break;
		 
        // int QMPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status);\n
     
    case 117:
        va_start(argp,v);
		typedef int (*file_read_shared_func) (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_read_shared_func QMPI_File_read_shared_ptr = (file_read_shared_func) func_ptr;
		MPI_File file_read_shared_func_arg0 = va_arg(argp, MPI_File);
		void * file_read_shared_func_arg1 = va_arg(argp, void *);
		int file_read_shared_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_read_shared_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_read_shared_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_read_shared_ptr) (file_read_shared_func_arg0, file_read_shared_func_arg1, file_read_shared_func_arg2, file_read_shared_func_arg3, file_read_shared_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 118:
        va_start(argp,v);
		typedef int (*file_seek_func) (MPI_File fh, MPI_Offset offset, int whence, int level, vector *v);
		file_seek_func QMPI_File_seek_ptr = (file_seek_func) func_ptr;
		MPI_File file_seek_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_seek_func_arg1 = va_arg(argp, MPI_Offset);
		int file_seek_func_arg2 = va_arg(argp, int);
		ret = (QMPI_File_seek_ptr) (file_seek_func_arg0, file_seek_func_arg1, file_seek_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_seek(MPI_File fh, MPI_Offset offset, int whence, int level, vector *v);\n
     
    case 119:
        va_start(argp,v);
		typedef int (*file_seek_shared_func) (MPI_File fh, MPI_Offset offset, int whence, int level, vector *v);
		file_seek_shared_func QMPI_File_seek_shared_ptr = (file_seek_shared_func) func_ptr;
		MPI_File file_seek_shared_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_seek_shared_func_arg1 = va_arg(argp, MPI_Offset);
		int file_seek_shared_func_arg2 = va_arg(argp, int);
		ret = (QMPI_File_seek_shared_ptr) (file_seek_shared_func_arg0, file_seek_shared_func_arg1, file_seek_shared_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence, int level, vector *v);\n
     
    case 120:
        va_start(argp,v);
		typedef int (*file_set_atomicity_func) (MPI_File fh, int flag, int level, vector *v);
		file_set_atomicity_func QMPI_File_set_atomicity_ptr = (file_set_atomicity_func) func_ptr;
		MPI_File file_set_atomicity_func_arg0 = va_arg(argp, MPI_File);
		int file_set_atomicity_func_arg1 = va_arg(argp, int);
		ret = (QMPI_File_set_atomicity_ptr) (file_set_atomicity_func_arg0, file_set_atomicity_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_set_atomicity(MPI_File fh, int flag, int level, vector *v);\n
     
    case 121:
        va_start(argp,v);
		typedef int (*file_set_errhandler_func) (MPI_File file, MPI_Errhandler errhandler, int level, vector *v);
		file_set_errhandler_func QMPI_File_set_errhandler_ptr = (file_set_errhandler_func) func_ptr;
		MPI_File file_set_errhandler_func_arg0 = va_arg(argp, MPI_File);
		MPI_Errhandler file_set_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler);
		ret = (QMPI_File_set_errhandler_ptr) (file_set_errhandler_func_arg0, file_set_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler, int level, vector *v);\n
     
    case 122:
        va_start(argp,v);
		typedef int (*file_set_info_func) (MPI_File fh, MPI_Info info, int level, vector *v);
		file_set_info_func QMPI_File_set_info_ptr = (file_set_info_func) func_ptr;
		MPI_File file_set_info_func_arg0 = va_arg(argp, MPI_File);
		MPI_Info file_set_info_func_arg1 = va_arg(argp, MPI_Info);
		ret = (QMPI_File_set_info_ptr) (file_set_info_func_arg0, file_set_info_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_set_info(MPI_File fh, MPI_Info info, int level, vector *v);\n
     
    case 123:
        va_start(argp,v);
		typedef int (*file_set_size_func) (MPI_File fh, MPI_Offset size, int level, vector *v);
		file_set_size_func QMPI_File_set_size_ptr = (file_set_size_func) func_ptr;
		MPI_File file_set_size_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_set_size_func_arg1 = va_arg(argp, MPI_Offset);
		ret = (QMPI_File_set_size_ptr) (file_set_size_func_arg0, file_set_size_func_arg1,  level, v);
		break;
		 
        // int QMPI_File_set_size(MPI_File fh, MPI_Offset size, int level, vector *v);\n
     
    case 124:
        va_start(argp,v);
		typedef int (*file_set_view_func) (MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info, int level, vector *v);
		file_set_view_func QMPI_File_set_view_ptr = (file_set_view_func) func_ptr;
		MPI_File file_set_view_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_set_view_func_arg1 = va_arg(argp, MPI_Offset);
		MPI_Datatype file_set_view_func_arg2 = va_arg(argp, MPI_Datatype);
		MPI_Datatype file_set_view_func_arg3 = va_arg(argp, MPI_Datatype);
		const char * file_set_view_func_arg4 = va_arg(argp, const char *);
		MPI_Info file_set_view_func_arg5 = va_arg(argp, MPI_Info);
		ret = (QMPI_File_set_view_ptr) (file_set_view_func_arg0, file_set_view_func_arg1, file_set_view_func_arg2, file_set_view_func_arg3, file_set_view_func_arg4, file_set_view_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info, int level, vector *v);\n
     
    case 125:
        va_start(argp,v);
		typedef int (*file_sync_func) (MPI_File fh, int level, vector *v);
		file_sync_func QMPI_File_sync_ptr = (file_sync_func) func_ptr;
		MPI_File file_sync_func_arg0 = va_arg(argp, MPI_File);
		ret = (QMPI_File_sync_ptr) (file_sync_func_arg0,  level, v);
		break;
		 
        // int QMPI_File_sync(MPI_File fh, int level, vector *v);\n
     
    case 126:
        va_start(argp,v);
		typedef int (*file_write_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_write_func QMPI_File_write_ptr = (file_write_func) func_ptr;
		MPI_File file_write_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_func_arg1 = va_arg(argp, const void *);
		int file_write_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_write_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_write_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_ptr) (file_write_func_arg0, file_write_func_arg1, file_write_func_arg2, file_write_func_arg3, file_write_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 127:
        va_start(argp,v);
		typedef int (*file_write_all_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_write_all_func QMPI_File_write_all_ptr = (file_write_all_func) func_ptr;
		MPI_File file_write_all_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_all_func_arg1 = va_arg(argp, const void *);
		int file_write_all_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_write_all_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_write_all_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_all_ptr) (file_write_all_func_arg0, file_write_all_func_arg1, file_write_all_func_arg2, file_write_all_func_arg3, file_write_all_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_write_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 128:
        va_start(argp,v);
		typedef int (*file_write_all_begin_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, int level, vector *v);
		file_write_all_begin_func QMPI_File_write_all_begin_ptr = (file_write_all_begin_func) func_ptr;
		MPI_File file_write_all_begin_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_all_begin_func_arg1 = va_arg(argp, const void *);
		int file_write_all_begin_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_write_all_begin_func_arg3 = va_arg(argp, MPI_Datatype);
		ret = (QMPI_File_write_all_begin_ptr) (file_write_all_begin_func_arg0, file_write_all_begin_func_arg1, file_write_all_begin_func_arg2, file_write_all_begin_func_arg3,  level, v);
		break;
		 
        // int QMPI_File_write_all_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, int level, vector *v);\n
     
    case 129:
        va_start(argp,v);
		typedef int (*file_write_all_end_func) (MPI_File fh, const void *buf, MPI_Status *status, int level, vector *v);
		file_write_all_end_func QMPI_File_write_all_end_ptr = (file_write_all_end_func) func_ptr;
		MPI_File file_write_all_end_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_all_end_func_arg1 = va_arg(argp, const void *);
		MPI_Status * file_write_all_end_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_all_end_ptr) (file_write_all_end_func_arg0, file_write_all_end_func_arg1, file_write_all_end_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_write_all_end(MPI_File fh, const void *buf, MPI_Status *status, int level, vector *v);\n
     
    case 130:
        va_start(argp,v);
		typedef int (*file_write_at_func) (MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_write_at_func QMPI_File_write_at_ptr = (file_write_at_func) func_ptr;
		MPI_File file_write_at_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_write_at_func_arg1 = va_arg(argp, MPI_Offset);
		const void * file_write_at_func_arg2 = va_arg(argp, const void *);
		int file_write_at_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_write_at_func_arg4 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_write_at_func_arg5 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_at_ptr) (file_write_at_func_arg0, file_write_at_func_arg1, file_write_at_func_arg2, file_write_at_func_arg3, file_write_at_func_arg4, file_write_at_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 131:
        va_start(argp,v);
		typedef int (*file_write_at_all_func) (MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_write_at_all_func QMPI_File_write_at_all_ptr = (file_write_at_all_func) func_ptr;
		MPI_File file_write_at_all_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_write_at_all_func_arg1 = va_arg(argp, MPI_Offset);
		const void * file_write_at_all_func_arg2 = va_arg(argp, const void *);
		int file_write_at_all_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_write_at_all_func_arg4 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_write_at_all_func_arg5 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_at_all_ptr) (file_write_at_all_func_arg0, file_write_at_all_func_arg1, file_write_at_all_func_arg2, file_write_at_all_func_arg3, file_write_at_all_func_arg4, file_write_at_all_func_arg5,  level, v);
		break;
		 
        // int QMPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 132:
        va_start(argp,v);
		typedef int (*file_write_at_all_begin_func) (MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, int level, vector *v);
		file_write_at_all_begin_func QMPI_File_write_at_all_begin_ptr = (file_write_at_all_begin_func) func_ptr;
		MPI_File file_write_at_all_begin_func_arg0 = va_arg(argp, MPI_File);
		MPI_Offset file_write_at_all_begin_func_arg1 = va_arg(argp, MPI_Offset);
		const void * file_write_at_all_begin_func_arg2 = va_arg(argp, const void *);
		int file_write_at_all_begin_func_arg3 = va_arg(argp, int);
		MPI_Datatype file_write_at_all_begin_func_arg4 = va_arg(argp, MPI_Datatype);
		ret = (QMPI_File_write_at_all_begin_ptr) (file_write_at_all_begin_func_arg0, file_write_at_all_begin_func_arg1, file_write_at_all_begin_func_arg2, file_write_at_all_begin_func_arg3, file_write_at_all_begin_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, int level, vector *v);\n
     
    case 133:
        va_start(argp,v);
		typedef int (*file_write_at_all_end_func) (MPI_File fh, const void *buf, MPI_Status *status, int level, vector *v);
		file_write_at_all_end_func QMPI_File_write_at_all_end_ptr = (file_write_at_all_end_func) func_ptr;
		MPI_File file_write_at_all_end_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_at_all_end_func_arg1 = va_arg(argp, const void *);
		MPI_Status * file_write_at_all_end_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_at_all_end_ptr) (file_write_at_all_end_func_arg0, file_write_at_all_end_func_arg1, file_write_at_all_end_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_write_at_all_end(MPI_File fh, const void *buf, MPI_Status *status, int level, vector *v);\n
     
    case 134:
        va_start(argp,v);
		typedef int (*file_write_ordered_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_write_ordered_func QMPI_File_write_ordered_ptr = (file_write_ordered_func) func_ptr;
		MPI_File file_write_ordered_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_ordered_func_arg1 = va_arg(argp, const void *);
		int file_write_ordered_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_write_ordered_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_write_ordered_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_ordered_ptr) (file_write_ordered_func_arg0, file_write_ordered_func_arg1, file_write_ordered_func_arg2, file_write_ordered_func_arg3, file_write_ordered_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_write_ordered(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 135:
        va_start(argp,v);
		typedef int (*file_write_ordered_begin_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, int level, vector *v);
		file_write_ordered_begin_func QMPI_File_write_ordered_begin_ptr = (file_write_ordered_begin_func) func_ptr;
		MPI_File file_write_ordered_begin_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_ordered_begin_func_arg1 = va_arg(argp, const void *);
		int file_write_ordered_begin_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_write_ordered_begin_func_arg3 = va_arg(argp, MPI_Datatype);
		ret = (QMPI_File_write_ordered_begin_ptr) (file_write_ordered_begin_func_arg0, file_write_ordered_begin_func_arg1, file_write_ordered_begin_func_arg2, file_write_ordered_begin_func_arg3,  level, v);
		break;
		 
        // int QMPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, int level, vector *v);\n
     
    case 136:
        va_start(argp,v);
		typedef int (*file_write_ordered_end_func) (MPI_File fh, const void *buf, MPI_Status *status, int level, vector *v);
		file_write_ordered_end_func QMPI_File_write_ordered_end_ptr = (file_write_ordered_end_func) func_ptr;
		MPI_File file_write_ordered_end_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_ordered_end_func_arg1 = va_arg(argp, const void *);
		MPI_Status * file_write_ordered_end_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_ordered_end_ptr) (file_write_ordered_end_func_arg0, file_write_ordered_end_func_arg1, file_write_ordered_end_func_arg2,  level, v);
		break;
		 
        // int QMPI_File_write_ordered_end(MPI_File fh, const void *buf, MPI_Status *status, int level, vector *v);\n
     
    case 137:
        va_start(argp,v);
		typedef int (*file_write_shared_func) (MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);
		file_write_shared_func QMPI_File_write_shared_ptr = (file_write_shared_func) func_ptr;
		MPI_File file_write_shared_func_arg0 = va_arg(argp, MPI_File);
		const void * file_write_shared_func_arg1 = va_arg(argp, const void *);
		int file_write_shared_func_arg2 = va_arg(argp, int);
		MPI_Datatype file_write_shared_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Status * file_write_shared_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_File_write_shared_ptr) (file_write_shared_func_arg0, file_write_shared_func_arg1, file_write_shared_func_arg2, file_write_shared_func_arg3, file_write_shared_func_arg4,  level, v);
		break;
		 
        // int QMPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level, vector *v);\n
     
    case 138:
		va_start(argp, v);
        typedef int (*finalize_func)(int i , vector* v);
        finalize_func finalize_ptr= (finalize_func) func_ptr;;
        ret= (finalize_ptr ) ( level, v);
        break;
		 
        // int QMPI_Finalize( int level, vector *v);\n
     
    case 139:
        va_start(argp,v);
		typedef int (*finalized_func) (int *flag, int level, vector *v);
		finalized_func QMPI_Finalized_ptr = (finalized_func) func_ptr;
		int * finalized_func_arg0 = va_arg(argp, int *);
		ret = (QMPI_Finalized_ptr) (finalized_func_arg0,  level, v);
		break;
		 
        // int QMPI_Finalized(int *flag, int level, vector *v);\n
     
    case 140:
        va_start(argp,v);
		typedef int (*free_mem_func) (void *base, int level, vector *v);
		free_mem_func QMPI_Free_mem_ptr = (free_mem_func) func_ptr;
		void * free_mem_func_arg0 = va_arg(argp, void *);
		ret = (QMPI_Free_mem_ptr) (free_mem_func_arg0,  level, v);
		break;
		 
        // int QMPI_Free_mem(void *base, int level, vector *v);\n
     
    case 141:
        va_start(argp,v);
		typedef int (*gather_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level, vector *v);
		gather_func QMPI_Gather_ptr = (gather_func) func_ptr;
		const void * gather_func_arg0 = va_arg(argp, const void *);
		int gather_func_arg1 = va_arg(argp, int);
		MPI_Datatype gather_func_arg2 = va_arg(argp, MPI_Datatype);
		void * gather_func_arg3 = va_arg(argp, void *);
		int gather_func_arg4 = va_arg(argp, int);
		MPI_Datatype gather_func_arg5 = va_arg(argp, MPI_Datatype);
		int gather_func_arg6 = va_arg(argp, int);
		MPI_Comm gather_func_arg7 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Gather_ptr) (gather_func_arg0, gather_func_arg1, gather_func_arg2, gather_func_arg3, gather_func_arg4, gather_func_arg5, gather_func_arg6, gather_func_arg7,  level, v);
		break;
		 
        // int QMPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level, vector *v);\n
     
    case 142:
        va_start(argp,v);
		typedef int (*gatherv_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, int level, vector *v);
		gatherv_func QMPI_Gatherv_ptr = (gatherv_func) func_ptr;
		const void * gatherv_func_arg0 = va_arg(argp, const void *);
		int gatherv_func_arg1 = va_arg(argp, int);
		MPI_Datatype gatherv_func_arg2 = va_arg(argp, MPI_Datatype);
		void * gatherv_func_arg3 = va_arg(argp, void *);
		const int * gatherv_func_arg4 = va_arg(argp, const int *);
		const int * gatherv_func_arg5 = va_arg(argp, const int *);
		MPI_Datatype gatherv_func_arg6 = va_arg(argp, MPI_Datatype);
		int gatherv_func_arg7 = va_arg(argp, int);
		MPI_Comm gatherv_func_arg8 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Gatherv_ptr) (gatherv_func_arg0, gatherv_func_arg1, gatherv_func_arg2, gatherv_func_arg3, gatherv_func_arg4, gatherv_func_arg5, gatherv_func_arg6, gatherv_func_arg7, gatherv_func_arg8,  level, v);
		break;
		 
        // int QMPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, int level, vector *v);\n
     
    case 143:
        va_start(argp,v);
		typedef int (*get_func) (void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, int level, vector *v);
		get_func QMPI_Get_ptr = (get_func) func_ptr;
		void * get_func_arg0 = va_arg(argp, void *);
		int get_func_arg1 = va_arg(argp, int);
		MPI_Datatype get_func_arg2 = va_arg(argp, MPI_Datatype);
		int get_func_arg3 = va_arg(argp, int);
		MPI_Aint get_func_arg4 = va_arg(argp, MPI_Aint);
		int get_func_arg5 = va_arg(argp, int);
		MPI_Datatype get_func_arg6 = va_arg(argp, MPI_Datatype);
		MPI_Win get_func_arg7 = va_arg(argp, MPI_Win);
		ret = (QMPI_Get_ptr) (get_func_arg0, get_func_arg1, get_func_arg2, get_func_arg3, get_func_arg4, get_func_arg5, get_func_arg6, get_func_arg7,  level, v);
		break;
		 
        // int QMPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, int level, vector *v);\n
     
    case 144:
        va_start(argp,v);
		typedef int (*get_accumulate_func) (const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, int level, vector *v);
		get_accumulate_func QMPI_Get_accumulate_ptr = (get_accumulate_func) func_ptr;
		const void * get_accumulate_func_arg0 = va_arg(argp, const void *);
		int get_accumulate_func_arg1 = va_arg(argp, int);
		MPI_Datatype get_accumulate_func_arg2 = va_arg(argp, MPI_Datatype);
		void * get_accumulate_func_arg3 = va_arg(argp, void *);
		int get_accumulate_func_arg4 = va_arg(argp, int);
		MPI_Datatype get_accumulate_func_arg5 = va_arg(argp, MPI_Datatype);
		int get_accumulate_func_arg6 = va_arg(argp, int);
		MPI_Aint get_accumulate_func_arg7 = va_arg(argp, MPI_Aint);
		int get_accumulate_func_arg8 = va_arg(argp, int);
		MPI_Datatype get_accumulate_func_arg9 = va_arg(argp, MPI_Datatype);
		MPI_Op get_accumulate_func_arg10 = va_arg(argp, MPI_Op);
		MPI_Win get_accumulate_func_arg11 = va_arg(argp, MPI_Win);
		ret = (QMPI_Get_accumulate_ptr) (get_accumulate_func_arg0, get_accumulate_func_arg1, get_accumulate_func_arg2, get_accumulate_func_arg3, get_accumulate_func_arg4, get_accumulate_func_arg5, get_accumulate_func_arg6, get_accumulate_func_arg7, get_accumulate_func_arg8, get_accumulate_func_arg9, get_accumulate_func_arg10, get_accumulate_func_arg11,  level, v);
		break;
		 
        // int QMPI_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, int level, vector *v);\n
     
    case 145:
        va_start(argp,v);
		typedef int (*get_address_func) (const void *location, MPI_Aint *address, int level, vector *v);
		get_address_func QMPI_Get_address_ptr = (get_address_func) func_ptr;
		const void * get_address_func_arg0 = va_arg(argp, const void *);
		MPI_Aint * get_address_func_arg1 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_Get_address_ptr) (get_address_func_arg0, get_address_func_arg1,  level, v);
		break;
		 
        // int QMPI_Get_address(const void *location, MPI_Aint *address, int level, vector *v);\n
     
    case 146:
        va_start(argp,v);
		typedef int (*get_count_func) (const MPI_Status *status, MPI_Datatype datatype, int *count, int level, vector *v);
		get_count_func QMPI_Get_count_ptr = (get_count_func) func_ptr;
		const MPI_Status * get_count_func_arg0 = va_arg(argp, const MPI_Status *);
		MPI_Datatype get_count_func_arg1 = va_arg(argp, MPI_Datatype);
		int * get_count_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Get_count_ptr) (get_count_func_arg0, get_count_func_arg1, get_count_func_arg2,  level, v);
		break;
		 
        // int QMPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count, int level, vector *v);\n
     
    case 147:
        va_start(argp,v);
		typedef int (*get_elements_func) (const MPI_Status *status, MPI_Datatype datatype, int *count, int level, vector *v);
		get_elements_func QMPI_Get_elements_ptr = (get_elements_func) func_ptr;
		const MPI_Status * get_elements_func_arg0 = va_arg(argp, const MPI_Status *);
		MPI_Datatype get_elements_func_arg1 = va_arg(argp, MPI_Datatype);
		int * get_elements_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Get_elements_ptr) (get_elements_func_arg0, get_elements_func_arg1, get_elements_func_arg2,  level, v);
		break;
		 
        // int QMPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count, int level, vector *v);\n
     
    case 148:
        va_start(argp,v);
		typedef int (*get_elements_x_func) (const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count, int level, vector *v);
		get_elements_x_func QMPI_Get_elements_x_ptr = (get_elements_x_func) func_ptr;
		const MPI_Status * get_elements_x_func_arg0 = va_arg(argp, const MPI_Status *);
		MPI_Datatype get_elements_x_func_arg1 = va_arg(argp, MPI_Datatype);
		MPI_Count * get_elements_x_func_arg2 = va_arg(argp, MPI_Count *);
		ret = (QMPI_Get_elements_x_ptr) (get_elements_x_func_arg0, get_elements_x_func_arg1, get_elements_x_func_arg2,  level, v);
		break;
		 
        // int QMPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count, int level, vector *v);\n
     
    case 149:
        va_start(argp,v);
		typedef int (*get_library_version_func) (char *version, int *resultlen, int level, vector *v);
		get_library_version_func QMPI_Get_library_version_ptr = (get_library_version_func) func_ptr;
		char * get_library_version_func_arg0 = va_arg(argp, char *);
		int * get_library_version_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Get_library_version_ptr) (get_library_version_func_arg0, get_library_version_func_arg1,  level, v);
		break;
		 
        // int QMPI_Get_library_version(char *version, int *resultlen, int level, vector *v);\n
     
    case 150:
        va_start(argp,v);
		typedef int (*get_processor_name_func) (char *name, int *resultlen, int level, vector *v);
		get_processor_name_func QMPI_Get_processor_name_ptr = (get_processor_name_func) func_ptr;
		char * get_processor_name_func_arg0 = va_arg(argp, char *);
		int * get_processor_name_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Get_processor_name_ptr) (get_processor_name_func_arg0, get_processor_name_func_arg1,  level, v);
		break;
		 
        // int QMPI_Get_processor_name(char *name, int *resultlen, int level, vector *v);\n
     
    case 151:
        va_start(argp,v);
		typedef int (*get_version_func) (int *version, int *subversion, int level, vector *v);
		get_version_func QMPI_Get_version_ptr = (get_version_func) func_ptr;
		int * get_version_func_arg0 = va_arg(argp, int *);
		int * get_version_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Get_version_ptr) (get_version_func_arg0, get_version_func_arg1,  level, v);
		break;
		 
        // int QMPI_Get_version(int *version, int *subversion, int level, vector *v);\n
     
    case 152:
        va_start(argp,v);
		typedef int (*graph_create_func) (MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph, int level, vector *v);
		graph_create_func QMPI_Graph_create_ptr = (graph_create_func) func_ptr;
		MPI_Comm graph_create_func_arg0 = va_arg(argp, MPI_Comm);
		int graph_create_func_arg1 = va_arg(argp, int);
		const int * graph_create_func_arg2 = va_arg(argp, const int *);
		const int * graph_create_func_arg3 = va_arg(argp, const int *);
		int graph_create_func_arg4 = va_arg(argp, int);
		MPI_Comm * graph_create_func_arg5 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Graph_create_ptr) (graph_create_func_arg0, graph_create_func_arg1, graph_create_func_arg2, graph_create_func_arg3, graph_create_func_arg4, graph_create_func_arg5,  level, v);
		break;
		 
        // int QMPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph, int level, vector *v);\n
     
    case 153:
        va_start(argp,v);
		typedef int (*graph_get_func) (MPI_Comm comm, int maxindex, int maxedges, int index[], int edges[], int level, vector *v);
		graph_get_func QMPI_Graph_get_ptr = (graph_get_func) func_ptr;
		MPI_Comm graph_get_func_arg0 = va_arg(argp, MPI_Comm);
		int graph_get_func_arg1 = va_arg(argp, int);
		int graph_get_func_arg2 = va_arg(argp, int);
		int* graph_get_func_arg3 = va_arg(argp, int*);
		int* graph_get_func_arg4 = va_arg(argp, int*);
		ret = (QMPI_Graph_get_ptr) (graph_get_func_arg0, graph_get_func_arg1, graph_get_func_arg2, graph_get_func_arg3, graph_get_func_arg4,  level, v);
		break;
		 
        // int QMPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int index[], int edges[], int level, vector *v);\n
     
    case 154:
        va_start(argp,v);
		typedef int (*graph_map_func) (MPI_Comm comm, int nnodes, const int index[], const int edges[], int *newrank, int level, vector *v);
		graph_map_func QMPI_Graph_map_ptr = (graph_map_func) func_ptr;
		MPI_Comm graph_map_func_arg0 = va_arg(argp, MPI_Comm);
		int graph_map_func_arg1 = va_arg(argp, int);
		const int * graph_map_func_arg2 = va_arg(argp, const int *);
		const int * graph_map_func_arg3 = va_arg(argp, const int *);
		int * graph_map_func_arg4 = va_arg(argp, int *);
		ret = (QMPI_Graph_map_ptr) (graph_map_func_arg0, graph_map_func_arg1, graph_map_func_arg2, graph_map_func_arg3, graph_map_func_arg4,  level, v);
		break;
		 
        // int QMPI_Graph_map(MPI_Comm comm, int nnodes, const int index[], const int edges[], int *newrank, int level, vector *v);\n
     
    case 155:
        va_start(argp,v);
		typedef int (*graph_neighbors_func) (MPI_Comm comm, int rank, int maxneighbors, int neighbors[], int level, vector *v);
		graph_neighbors_func QMPI_Graph_neighbors_ptr = (graph_neighbors_func) func_ptr;
		MPI_Comm graph_neighbors_func_arg0 = va_arg(argp, MPI_Comm);
		int graph_neighbors_func_arg1 = va_arg(argp, int);
		int graph_neighbors_func_arg2 = va_arg(argp, int);
		int* graph_neighbors_func_arg3 = va_arg(argp, int*);
		ret = (QMPI_Graph_neighbors_ptr) (graph_neighbors_func_arg0, graph_neighbors_func_arg1, graph_neighbors_func_arg2, graph_neighbors_func_arg3,  level, v);
		break;
		 
        // int QMPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[], int level, vector *v);\n
     
    case 156:
        va_start(argp,v);
		typedef int (*graph_neighbors_count_func) (MPI_Comm comm, int rank, int *nneighbors, int level, vector *v);
		graph_neighbors_count_func QMPI_Graph_neighbors_count_ptr = (graph_neighbors_count_func) func_ptr;
		MPI_Comm graph_neighbors_count_func_arg0 = va_arg(argp, MPI_Comm);
		int graph_neighbors_count_func_arg1 = va_arg(argp, int);
		int * graph_neighbors_count_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Graph_neighbors_count_ptr) (graph_neighbors_count_func_arg0, graph_neighbors_count_func_arg1, graph_neighbors_count_func_arg2,  level, v);
		break;
		 
        // int QMPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors, int level, vector *v);\n
     
    case 157:
        va_start(argp,v);
		typedef int (*graphdims_get_func) (MPI_Comm comm, int *nnodes, int *nedges, int level, vector *v);
		graphdims_get_func QMPI_Graphdims_get_ptr = (graphdims_get_func) func_ptr;
		MPI_Comm graphdims_get_func_arg0 = va_arg(argp, MPI_Comm);
		int * graphdims_get_func_arg1 = va_arg(argp, int *);
		int * graphdims_get_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Graphdims_get_ptr) (graphdims_get_func_arg0, graphdims_get_func_arg1, graphdims_get_func_arg2,  level, v);
		break;
		 
        // int QMPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges, int level, vector *v);\n
     
    case 158:
        va_start(argp,v);
		typedef int (*grequest_complete_func) (MPI_Request request, int level, vector *v);
		grequest_complete_func QMPI_Grequest_complete_ptr = (grequest_complete_func) func_ptr;
		MPI_Request grequest_complete_func_arg0 = va_arg(argp, MPI_Request);
		ret = (QMPI_Grequest_complete_ptr) (grequest_complete_func_arg0,  level, v);
		break;
		 
        // int QMPI_Grequest_complete(MPI_Request request, int level, vector *v);\n
     
    case 159:
        va_start(argp,v);
		typedef int (*grequest_start_func) (MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request, int level, vector *v);
		grequest_start_func QMPI_Grequest_start_ptr = (grequest_start_func) func_ptr;
		MPI_Grequest_query_function * grequest_start_func_arg0 = va_arg(argp, MPI_Grequest_query_function *);
		MPI_Grequest_free_function * grequest_start_func_arg1 = va_arg(argp, MPI_Grequest_free_function *);
		MPI_Grequest_cancel_function * grequest_start_func_arg2 = va_arg(argp, MPI_Grequest_cancel_function *);
		void * grequest_start_func_arg3 = va_arg(argp, void *);
		MPI_Request * grequest_start_func_arg4 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Grequest_start_ptr) (grequest_start_func_arg0, grequest_start_func_arg1, grequest_start_func_arg2, grequest_start_func_arg3, grequest_start_func_arg4,  level, v);
		break;
		 
        // int QMPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request, int level, vector *v);\n
     
    case 160:
        va_start(argp,v);
		typedef int (*group_compare_func) (MPI_Group group1, MPI_Group group2, int *result, int level, vector *v);
		group_compare_func QMPI_Group_compare_ptr = (group_compare_func) func_ptr;
		MPI_Group group_compare_func_arg0 = va_arg(argp, MPI_Group);
		MPI_Group group_compare_func_arg1 = va_arg(argp, MPI_Group);
		int * group_compare_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Group_compare_ptr) (group_compare_func_arg0, group_compare_func_arg1, group_compare_func_arg2,  level, v);
		break;
		 
        // int QMPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result, int level, vector *v);\n
     
    case 161:
        va_start(argp,v);
		typedef int (*group_difference_func) (MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level, vector *v);
		group_difference_func QMPI_Group_difference_ptr = (group_difference_func) func_ptr;
		MPI_Group group_difference_func_arg0 = va_arg(argp, MPI_Group);
		MPI_Group group_difference_func_arg1 = va_arg(argp, MPI_Group);
		MPI_Group * group_difference_func_arg2 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Group_difference_ptr) (group_difference_func_arg0, group_difference_func_arg1, group_difference_func_arg2,  level, v);
		break;
		 
        // int QMPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level, vector *v);\n
     
    case 162:
        va_start(argp,v);
		typedef int (*group_excl_func) (MPI_Group group, int n, const int ranks[], MPI_Group *newgroup, int level, vector *v);
		group_excl_func QMPI_Group_excl_ptr = (group_excl_func) func_ptr;
		MPI_Group group_excl_func_arg0 = va_arg(argp, MPI_Group);
		int group_excl_func_arg1 = va_arg(argp, int);
		const int * group_excl_func_arg2 = va_arg(argp, const int *);
		MPI_Group * group_excl_func_arg3 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Group_excl_ptr) (group_excl_func_arg0, group_excl_func_arg1, group_excl_func_arg2, group_excl_func_arg3,  level, v);
		break;
		 
        // int QMPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup, int level, vector *v);\n
     
    case 163:
        va_start(argp,v);
		typedef int (*group_free_func) (MPI_Group *group, int level, vector *v);
		group_free_func QMPI_Group_free_ptr = (group_free_func) func_ptr;
		MPI_Group * group_free_func_arg0 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Group_free_ptr) (group_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Group_free(MPI_Group *group, int level, vector *v);\n
     
    case 164:
        va_start(argp,v);
		typedef int (*group_incl_func) (MPI_Group group, int n, const int ranks[], MPI_Group *newgroup, int level, vector *v);
		group_incl_func QMPI_Group_incl_ptr = (group_incl_func) func_ptr;
		MPI_Group group_incl_func_arg0 = va_arg(argp, MPI_Group);
		int group_incl_func_arg1 = va_arg(argp, int);
		const int * group_incl_func_arg2 = va_arg(argp, const int *);
		MPI_Group * group_incl_func_arg3 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Group_incl_ptr) (group_incl_func_arg0, group_incl_func_arg1, group_incl_func_arg2, group_incl_func_arg3,  level, v);
		break;
		 
        // int QMPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup, int level, vector *v);\n
     
    case 165:
        va_start(argp,v);
		typedef int (*group_intersection_func) (MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level, vector *v);
		group_intersection_func QMPI_Group_intersection_ptr = (group_intersection_func) func_ptr;
		MPI_Group group_intersection_func_arg0 = va_arg(argp, MPI_Group);
		MPI_Group group_intersection_func_arg1 = va_arg(argp, MPI_Group);
		MPI_Group * group_intersection_func_arg2 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Group_intersection_ptr) (group_intersection_func_arg0, group_intersection_func_arg1, group_intersection_func_arg2,  level, v);
		break;
		 
        // int QMPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level, vector *v);\n
     
    case 166:
        va_start(argp,v);
		typedef int (*group_range_excl_func) (MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup, int level, vector *v);
		group_range_excl_func QMPI_Group_range_excl_ptr = (group_range_excl_func) func_ptr;
		MPI_Group group_range_excl_func_arg0 = va_arg(argp, MPI_Group);
		int group_range_excl_func_arg1 = va_arg(argp, int);
		int *group_range_excl_func_arg2 = va_arg(argp, int(*)[]);
		MPI_Group * group_range_excl_func_arg3 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Group_range_excl_ptr) (group_range_excl_func_arg0, group_range_excl_func_arg1, group_range_excl_func_arg2, group_range_excl_func_arg3,  level, v);
		break;
		 
        // int QMPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup, int level, vector *v);\n
     
    case 167:
        va_start(argp,v);
		typedef int (*group_range_incl_func) (MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup, int level, vector *v);
		group_range_incl_func QMPI_Group_range_incl_ptr = (group_range_incl_func) func_ptr;
		MPI_Group group_range_incl_func_arg0 = va_arg(argp, MPI_Group);
		int group_range_incl_func_arg1 = va_arg(argp, int);
		int* group_range_incl_func_arg2 = va_arg(argp, int*);
		MPI_Group * group_range_incl_func_arg3 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Group_range_incl_ptr) (group_range_incl_func_arg0, group_range_incl_func_arg1, group_range_incl_func_arg2, group_range_incl_func_arg3,  level, v);
		break;
		 
        // int QMPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup, int level, vector *v);\n
     
    case 168:
        va_start(argp,v);
		typedef int (*group_rank_func) (MPI_Group group, int *rank, int level, vector *v);
		group_rank_func QMPI_Group_rank_ptr = (group_rank_func) func_ptr;
		MPI_Group group_rank_func_arg0 = va_arg(argp, MPI_Group);
		int * group_rank_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Group_rank_ptr) (group_rank_func_arg0, group_rank_func_arg1,  level, v);
		break;
		 
        // int QMPI_Group_rank(MPI_Group group, int *rank, int level, vector *v);\n
     
    case 169:
        va_start(argp,v);
		typedef int (*group_size_func) (MPI_Group group, int *size, int level, vector *v);
		group_size_func QMPI_Group_size_ptr = (group_size_func) func_ptr;
		MPI_Group group_size_func_arg0 = va_arg(argp, MPI_Group);
		int * group_size_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Group_size_ptr) (group_size_func_arg0, group_size_func_arg1,  level, v);
		break;
		 
        // int QMPI_Group_size(MPI_Group group, int *size, int level, vector *v);\n
     
    case 170:
        va_start(argp,v);
		typedef int (*group_translate_ranks_func) (MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[], int level, vector *v);
		group_translate_ranks_func QMPI_Group_translate_ranks_ptr = (group_translate_ranks_func) func_ptr;
		MPI_Group group_translate_ranks_func_arg0 = va_arg(argp, MPI_Group);
		int group_translate_ranks_func_arg1 = va_arg(argp, int);
		const int * group_translate_ranks_func_arg2 = va_arg(argp, const int *);
		MPI_Group group_translate_ranks_func_arg3 = va_arg(argp, MPI_Group);
		int* group_translate_ranks_func_arg4 = va_arg(argp, int*);
		ret = (QMPI_Group_translate_ranks_ptr) (group_translate_ranks_func_arg0, group_translate_ranks_func_arg1, group_translate_ranks_func_arg2, group_translate_ranks_func_arg3, group_translate_ranks_func_arg4,  level, v);
		break;
		 
        // int QMPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[], int level, vector *v);\n
     
    case 171:
        va_start(argp,v);
		typedef int (*group_union_func) (MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level, vector *v);
		group_union_func QMPI_Group_union_ptr = (group_union_func) func_ptr;
		MPI_Group group_union_func_arg0 = va_arg(argp, MPI_Group);
		MPI_Group group_union_func_arg1 = va_arg(argp, MPI_Group);
		MPI_Group * group_union_func_arg2 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Group_union_ptr) (group_union_func_arg0, group_union_func_arg1, group_union_func_arg2,  level, v);
		break;
		 
        // int QMPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level, vector *v);\n
     
    case 172:
        va_start(argp,v);
		typedef int (*iallgather_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		iallgather_func QMPI_Iallgather_ptr = (iallgather_func) func_ptr;
		const void * iallgather_func_arg0 = va_arg(argp, const void *);
		int iallgather_func_arg1 = va_arg(argp, int);
		MPI_Datatype iallgather_func_arg2 = va_arg(argp, MPI_Datatype);
		void * iallgather_func_arg3 = va_arg(argp, void *);
		int iallgather_func_arg4 = va_arg(argp, int);
		MPI_Datatype iallgather_func_arg5 = va_arg(argp, MPI_Datatype);
		MPI_Comm iallgather_func_arg6 = va_arg(argp, MPI_Comm);
		MPI_Request * iallgather_func_arg7 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Iallgather_ptr) (iallgather_func_arg0, iallgather_func_arg1, iallgather_func_arg2, iallgather_func_arg3, iallgather_func_arg4, iallgather_func_arg5, iallgather_func_arg6, iallgather_func_arg7,  level, v);
		break;
		 
        // int QMPI_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 173:
        va_start(argp,v);
		typedef int (*iallgatherv_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		iallgatherv_func QMPI_Iallgatherv_ptr = (iallgatherv_func) func_ptr;
		const void * iallgatherv_func_arg0 = va_arg(argp, const void *);
		int iallgatherv_func_arg1 = va_arg(argp, int);
		MPI_Datatype iallgatherv_func_arg2 = va_arg(argp, MPI_Datatype);
		void * iallgatherv_func_arg3 = va_arg(argp, void *);
		const int * iallgatherv_func_arg4 = va_arg(argp, const int *);
		const int * iallgatherv_func_arg5 = va_arg(argp, const int *);
		MPI_Datatype iallgatherv_func_arg6 = va_arg(argp, MPI_Datatype);
		MPI_Comm iallgatherv_func_arg7 = va_arg(argp, MPI_Comm);
		MPI_Request * iallgatherv_func_arg8 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Iallgatherv_ptr) (iallgatherv_func_arg0, iallgatherv_func_arg1, iallgatherv_func_arg2, iallgatherv_func_arg3, iallgatherv_func_arg4, iallgatherv_func_arg5, iallgatherv_func_arg6, iallgatherv_func_arg7, iallgatherv_func_arg8,  level, v);
		break;
		 
        // int QMPI_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 174:
        va_start(argp,v);
		typedef int (*iallreduce_func) (const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		iallreduce_func QMPI_Iallreduce_ptr = (iallreduce_func) func_ptr;
		const void * iallreduce_func_arg0 = va_arg(argp, const void *);
		void * iallreduce_func_arg1 = va_arg(argp, void *);
		int iallreduce_func_arg2 = va_arg(argp, int);
		MPI_Datatype iallreduce_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op iallreduce_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm iallreduce_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * iallreduce_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Iallreduce_ptr) (iallreduce_func_arg0, iallreduce_func_arg1, iallreduce_func_arg2, iallreduce_func_arg3, iallreduce_func_arg4, iallreduce_func_arg5, iallreduce_func_arg6,  level, v);
		break;
		 
        // int QMPI_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 175:
        va_start(argp,v);
		typedef int (*ialltoall_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ialltoall_func QMPI_Ialltoall_ptr = (ialltoall_func) func_ptr;
		const void * ialltoall_func_arg0 = va_arg(argp, const void *);
		int ialltoall_func_arg1 = va_arg(argp, int);
		MPI_Datatype ialltoall_func_arg2 = va_arg(argp, MPI_Datatype);
		void * ialltoall_func_arg3 = va_arg(argp, void *);
		int ialltoall_func_arg4 = va_arg(argp, int);
		MPI_Datatype ialltoall_func_arg5 = va_arg(argp, MPI_Datatype);
		MPI_Comm ialltoall_func_arg6 = va_arg(argp, MPI_Comm);
		MPI_Request * ialltoall_func_arg7 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ialltoall_ptr) (ialltoall_func_arg0, ialltoall_func_arg1, ialltoall_func_arg2, ialltoall_func_arg3, ialltoall_func_arg4, ialltoall_func_arg5, ialltoall_func_arg6, ialltoall_func_arg7,  level, v);
		break;
		 
        // int QMPI_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 176:
        va_start(argp,v);
		typedef int (*ialltoallv_func) (const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ialltoallv_func QMPI_Ialltoallv_ptr = (ialltoallv_func) func_ptr;
		const void * ialltoallv_func_arg0 = va_arg(argp, const void *);
		const int * ialltoallv_func_arg1 = va_arg(argp, const int *);
		const int * ialltoallv_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype ialltoallv_func_arg3 = va_arg(argp, MPI_Datatype);
		void * ialltoallv_func_arg4 = va_arg(argp, void *);
		const int * ialltoallv_func_arg5 = va_arg(argp, const int *);
		const int * ialltoallv_func_arg6 = va_arg(argp, const int *);
		MPI_Datatype ialltoallv_func_arg7 = va_arg(argp, MPI_Datatype);
		MPI_Comm ialltoallv_func_arg8 = va_arg(argp, MPI_Comm);
		MPI_Request * ialltoallv_func_arg9 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ialltoallv_ptr) (ialltoallv_func_arg0, ialltoallv_func_arg1, ialltoallv_func_arg2, ialltoallv_func_arg3, ialltoallv_func_arg4, ialltoallv_func_arg5, ialltoallv_func_arg6, ialltoallv_func_arg7, ialltoallv_func_arg8, ialltoallv_func_arg9,  level, v);
		break;
		 
        // int QMPI_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 177:
        va_start(argp,v);
		typedef int (*ialltoallw_func) (const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ialltoallw_func QMPI_Ialltoallw_ptr = (ialltoallw_func) func_ptr;
		const void * ialltoallw_func_arg0 = va_arg(argp, const void *);
		const int * ialltoallw_func_arg1 = va_arg(argp, const int *);
		const int * ialltoallw_func_arg2 = va_arg(argp, const int *);
		const MPI_Datatype * ialltoallw_func_arg3 = va_arg(argp, const MPI_Datatype *);
		void * ialltoallw_func_arg4 = va_arg(argp, void *);
		const int * ialltoallw_func_arg5 = va_arg(argp, const int *);
		const int * ialltoallw_func_arg6 = va_arg(argp, const int *);
		const MPI_Datatype * ialltoallw_func_arg7 = va_arg(argp, const MPI_Datatype *);
		MPI_Comm ialltoallw_func_arg8 = va_arg(argp, MPI_Comm);
		MPI_Request * ialltoallw_func_arg9 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ialltoallw_ptr) (ialltoallw_func_arg0, ialltoallw_func_arg1, ialltoallw_func_arg2, ialltoallw_func_arg3, ialltoallw_func_arg4, ialltoallw_func_arg5, ialltoallw_func_arg6, ialltoallw_func_arg7, ialltoallw_func_arg8, ialltoallw_func_arg9,  level, v);
		break;
		 
        // int QMPI_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 178:
        va_start(argp,v);
		typedef int (*ibarrier_func) (MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ibarrier_func QMPI_Ibarrier_ptr = (ibarrier_func) func_ptr;
		MPI_Comm ibarrier_func_arg0 = va_arg(argp, MPI_Comm);
		MPI_Request * ibarrier_func_arg1 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ibarrier_ptr) (ibarrier_func_arg0, ibarrier_func_arg1,  level, v);
		break;
		 
        // int QMPI_Ibarrier(MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 179:
        va_start(argp,v);
		typedef int (*ibcast_func) (void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ibcast_func QMPI_Ibcast_ptr = (ibcast_func) func_ptr;
		void * ibcast_func_arg0 = va_arg(argp, void *);
		int ibcast_func_arg1 = va_arg(argp, int);
		MPI_Datatype ibcast_func_arg2 = va_arg(argp, MPI_Datatype);
		int ibcast_func_arg3 = va_arg(argp, int);
		MPI_Comm ibcast_func_arg4 = va_arg(argp, MPI_Comm);
		MPI_Request * ibcast_func_arg5 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ibcast_ptr) (ibcast_func_arg0, ibcast_func_arg1, ibcast_func_arg2, ibcast_func_arg3, ibcast_func_arg4, ibcast_func_arg5,  level, v);
		break;
		 
        // int QMPI_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 180:
        va_start(argp,v);
		typedef int (*ibsend_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ibsend_func QMPI_Ibsend_ptr = (ibsend_func) func_ptr;
		const void * ibsend_func_arg0 = va_arg(argp, const void *);
		int ibsend_func_arg1 = va_arg(argp, int);
		MPI_Datatype ibsend_func_arg2 = va_arg(argp, MPI_Datatype);
		int ibsend_func_arg3 = va_arg(argp, int);
		int ibsend_func_arg4 = va_arg(argp, int);
		MPI_Comm ibsend_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * ibsend_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ibsend_ptr) (ibsend_func_arg0, ibsend_func_arg1, ibsend_func_arg2, ibsend_func_arg3, ibsend_func_arg4, ibsend_func_arg5, ibsend_func_arg6,  level, v);
		break;
		 
        // int QMPI_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 181:
        va_start(argp,v);
		typedef int (*iexscan_func) (const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		iexscan_func QMPI_Iexscan_ptr = (iexscan_func) func_ptr;
		const void * iexscan_func_arg0 = va_arg(argp, const void *);
		void * iexscan_func_arg1 = va_arg(argp, void *);
		int iexscan_func_arg2 = va_arg(argp, int);
		MPI_Datatype iexscan_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op iexscan_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm iexscan_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * iexscan_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Iexscan_ptr) (iexscan_func_arg0, iexscan_func_arg1, iexscan_func_arg2, iexscan_func_arg3, iexscan_func_arg4, iexscan_func_arg5, iexscan_func_arg6,  level, v);
		break;
		 
        // int QMPI_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 182:
        va_start(argp,v);
		typedef int (*igather_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		igather_func QMPI_Igather_ptr = (igather_func) func_ptr;
		const void * igather_func_arg0 = va_arg(argp, const void *);
		int igather_func_arg1 = va_arg(argp, int);
		MPI_Datatype igather_func_arg2 = va_arg(argp, MPI_Datatype);
		void * igather_func_arg3 = va_arg(argp, void *);
		int igather_func_arg4 = va_arg(argp, int);
		MPI_Datatype igather_func_arg5 = va_arg(argp, MPI_Datatype);
		int igather_func_arg6 = va_arg(argp, int);
		MPI_Comm igather_func_arg7 = va_arg(argp, MPI_Comm);
		MPI_Request * igather_func_arg8 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Igather_ptr) (igather_func_arg0, igather_func_arg1, igather_func_arg2, igather_func_arg3, igather_func_arg4, igather_func_arg5, igather_func_arg6, igather_func_arg7, igather_func_arg8,  level, v);
		break;
		 
        // int QMPI_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 183:
        va_start(argp,v);
		typedef int (*igatherv_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		igatherv_func QMPI_Igatherv_ptr = (igatherv_func) func_ptr;
		const void * igatherv_func_arg0 = va_arg(argp, const void *);
		int igatherv_func_arg1 = va_arg(argp, int);
		MPI_Datatype igatherv_func_arg2 = va_arg(argp, MPI_Datatype);
		void * igatherv_func_arg3 = va_arg(argp, void *);
		const int * igatherv_func_arg4 = va_arg(argp, const int *);
		const int * igatherv_func_arg5 = va_arg(argp, const int *);
		MPI_Datatype igatherv_func_arg6 = va_arg(argp, MPI_Datatype);
		int igatherv_func_arg7 = va_arg(argp, int);
		MPI_Comm igatherv_func_arg8 = va_arg(argp, MPI_Comm);
		MPI_Request * igatherv_func_arg9 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Igatherv_ptr) (igatherv_func_arg0, igatherv_func_arg1, igatherv_func_arg2, igatherv_func_arg3, igatherv_func_arg4, igatherv_func_arg5, igatherv_func_arg6, igatherv_func_arg7, igatherv_func_arg8, igatherv_func_arg9,  level, v);
		break;
		 
        // int QMPI_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 184:
        va_start(argp,v);
		typedef int (*improbe_func) (int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status, int level, vector *v);
		improbe_func QMPI_Improbe_ptr = (improbe_func) func_ptr;
		int improbe_func_arg0 = va_arg(argp, int);
		int improbe_func_arg1 = va_arg(argp, int);
		MPI_Comm improbe_func_arg2 = va_arg(argp, MPI_Comm);
		int * improbe_func_arg3 = va_arg(argp, int *);
		MPI_Message * improbe_func_arg4 = va_arg(argp, MPI_Message *);
		MPI_Status * improbe_func_arg5 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Improbe_ptr) (improbe_func_arg0, improbe_func_arg1, improbe_func_arg2, improbe_func_arg3, improbe_func_arg4, improbe_func_arg5,  level, v);
		break;
		 
        // int QMPI_Improbe(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status, int level, vector *v);\n
     
    case 185:
        va_start(argp,v);
		typedef int (*imrecv_func) (void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Request *request, int level, vector *v);
		imrecv_func QMPI_Imrecv_ptr = (imrecv_func) func_ptr;
		void * imrecv_func_arg0 = va_arg(argp, void *);
		int imrecv_func_arg1 = va_arg(argp, int);
		MPI_Datatype imrecv_func_arg2 = va_arg(argp, MPI_Datatype);
		MPI_Message * imrecv_func_arg3 = va_arg(argp, MPI_Message *);
		MPI_Request * imrecv_func_arg4 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Imrecv_ptr) (imrecv_func_arg0, imrecv_func_arg1, imrecv_func_arg2, imrecv_func_arg3, imrecv_func_arg4,  level, v);
		break;
		 
        // int QMPI_Imrecv(void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Request *request, int level, vector *v);\n
     
    case 186:
        va_start(argp,v);
		typedef int (*ineighbor_allgather_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ineighbor_allgather_func QMPI_Ineighbor_allgather_ptr = (ineighbor_allgather_func) func_ptr;
		const void * ineighbor_allgather_func_arg0 = va_arg(argp, const void *);
		int ineighbor_allgather_func_arg1 = va_arg(argp, int);
		MPI_Datatype ineighbor_allgather_func_arg2 = va_arg(argp, MPI_Datatype);
		void * ineighbor_allgather_func_arg3 = va_arg(argp, void *);
		int ineighbor_allgather_func_arg4 = va_arg(argp, int);
		MPI_Datatype ineighbor_allgather_func_arg5 = va_arg(argp, MPI_Datatype);
		MPI_Comm ineighbor_allgather_func_arg6 = va_arg(argp, MPI_Comm);
		MPI_Request * ineighbor_allgather_func_arg7 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ineighbor_allgather_ptr) (ineighbor_allgather_func_arg0, ineighbor_allgather_func_arg1, ineighbor_allgather_func_arg2, ineighbor_allgather_func_arg3, ineighbor_allgather_func_arg4, ineighbor_allgather_func_arg5, ineighbor_allgather_func_arg6, ineighbor_allgather_func_arg7,  level, v);
		break;
		 
        // int QMPI_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 187:
        va_start(argp,v);
		typedef int (*ineighbor_allgatherv_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ineighbor_allgatherv_func QMPI_Ineighbor_allgatherv_ptr = (ineighbor_allgatherv_func) func_ptr;
		const void * ineighbor_allgatherv_func_arg0 = va_arg(argp, const void *);
		int ineighbor_allgatherv_func_arg1 = va_arg(argp, int);
		MPI_Datatype ineighbor_allgatherv_func_arg2 = va_arg(argp, MPI_Datatype);
		void * ineighbor_allgatherv_func_arg3 = va_arg(argp, void *);
		const int * ineighbor_allgatherv_func_arg4 = va_arg(argp, const int *);
		const int * ineighbor_allgatherv_func_arg5 = va_arg(argp, const int *);
		MPI_Datatype ineighbor_allgatherv_func_arg6 = va_arg(argp, MPI_Datatype);
		MPI_Comm ineighbor_allgatherv_func_arg7 = va_arg(argp, MPI_Comm);
		MPI_Request * ineighbor_allgatherv_func_arg8 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ineighbor_allgatherv_ptr) (ineighbor_allgatherv_func_arg0, ineighbor_allgatherv_func_arg1, ineighbor_allgatherv_func_arg2, ineighbor_allgatherv_func_arg3, ineighbor_allgatherv_func_arg4, ineighbor_allgatherv_func_arg5, ineighbor_allgatherv_func_arg6, ineighbor_allgatherv_func_arg7, ineighbor_allgatherv_func_arg8,  level, v);
		break;
		 
        // int QMPI_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 188:
        va_start(argp,v);
		typedef int (*ineighbor_alltoall_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ineighbor_alltoall_func QMPI_Ineighbor_alltoall_ptr = (ineighbor_alltoall_func) func_ptr;
		const void * ineighbor_alltoall_func_arg0 = va_arg(argp, const void *);
		int ineighbor_alltoall_func_arg1 = va_arg(argp, int);
		MPI_Datatype ineighbor_alltoall_func_arg2 = va_arg(argp, MPI_Datatype);
		void * ineighbor_alltoall_func_arg3 = va_arg(argp, void *);
		int ineighbor_alltoall_func_arg4 = va_arg(argp, int);
		MPI_Datatype ineighbor_alltoall_func_arg5 = va_arg(argp, MPI_Datatype);
		MPI_Comm ineighbor_alltoall_func_arg6 = va_arg(argp, MPI_Comm);
		MPI_Request * ineighbor_alltoall_func_arg7 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ineighbor_alltoall_ptr) (ineighbor_alltoall_func_arg0, ineighbor_alltoall_func_arg1, ineighbor_alltoall_func_arg2, ineighbor_alltoall_func_arg3, ineighbor_alltoall_func_arg4, ineighbor_alltoall_func_arg5, ineighbor_alltoall_func_arg6, ineighbor_alltoall_func_arg7,  level, v);
		break;
		 
        // int QMPI_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 189:
        va_start(argp,v);
		typedef int (*ineighbor_alltoallv_func) (const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ineighbor_alltoallv_func QMPI_Ineighbor_alltoallv_ptr = (ineighbor_alltoallv_func) func_ptr;
		const void * ineighbor_alltoallv_func_arg0 = va_arg(argp, const void *);
		const int * ineighbor_alltoallv_func_arg1 = va_arg(argp, const int *);
		const int * ineighbor_alltoallv_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype ineighbor_alltoallv_func_arg3 = va_arg(argp, MPI_Datatype);
		void * ineighbor_alltoallv_func_arg4 = va_arg(argp, void *);
		const int * ineighbor_alltoallv_func_arg5 = va_arg(argp, const int *);
		const int * ineighbor_alltoallv_func_arg6 = va_arg(argp, const int *);
		MPI_Datatype ineighbor_alltoallv_func_arg7 = va_arg(argp, MPI_Datatype);
		MPI_Comm ineighbor_alltoallv_func_arg8 = va_arg(argp, MPI_Comm);
		MPI_Request * ineighbor_alltoallv_func_arg9 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ineighbor_alltoallv_ptr) (ineighbor_alltoallv_func_arg0, ineighbor_alltoallv_func_arg1, ineighbor_alltoallv_func_arg2, ineighbor_alltoallv_func_arg3, ineighbor_alltoallv_func_arg4, ineighbor_alltoallv_func_arg5, ineighbor_alltoallv_func_arg6, ineighbor_alltoallv_func_arg7, ineighbor_alltoallv_func_arg8, ineighbor_alltoallv_func_arg9,  level, v);
		break;
		 
        // int QMPI_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 190:
        va_start(argp,v);
		typedef int (*ineighbor_alltoallw_func) (const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ineighbor_alltoallw_func QMPI_Ineighbor_alltoallw_ptr = (ineighbor_alltoallw_func) func_ptr;
		const void * ineighbor_alltoallw_func_arg0 = va_arg(argp, const void *);
		const int * ineighbor_alltoallw_func_arg1 = va_arg(argp, const int *);
		const MPI_Aint * ineighbor_alltoallw_func_arg2 = va_arg(argp, const MPI_Aint *);
		const MPI_Datatype * ineighbor_alltoallw_func_arg3 = va_arg(argp, const MPI_Datatype *);
		void * ineighbor_alltoallw_func_arg4 = va_arg(argp, void *);
		const int * ineighbor_alltoallw_func_arg5 = va_arg(argp, const int *);
		const MPI_Aint * ineighbor_alltoallw_func_arg6 = va_arg(argp, const MPI_Aint *);
		const MPI_Datatype * ineighbor_alltoallw_func_arg7 = va_arg(argp, const MPI_Datatype *);
		MPI_Comm ineighbor_alltoallw_func_arg8 = va_arg(argp, MPI_Comm);
		MPI_Request * ineighbor_alltoallw_func_arg9 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ineighbor_alltoallw_ptr) (ineighbor_alltoallw_func_arg0, ineighbor_alltoallw_func_arg1, ineighbor_alltoallw_func_arg2, ineighbor_alltoallw_func_arg3, ineighbor_alltoallw_func_arg4, ineighbor_alltoallw_func_arg5, ineighbor_alltoallw_func_arg6, ineighbor_alltoallw_func_arg7, ineighbor_alltoallw_func_arg8, ineighbor_alltoallw_func_arg9,  level, v);
		break;
		 
        // int QMPI_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 191:
        va_start(argp,v);
		typedef int (*info_create_func) (MPI_Info *info, int level, vector *v);
		info_create_func QMPI_Info_create_ptr = (info_create_func) func_ptr;
		MPI_Info * info_create_func_arg0 = va_arg(argp, MPI_Info *);
		ret = (QMPI_Info_create_ptr) (info_create_func_arg0,  level, v);
		break;
		 
        // int QMPI_Info_create(MPI_Info *info, int level, vector *v);\n
     
    case 192:
        va_start(argp,v);
		typedef int (*info_delete_func) (MPI_Info info, const char *key, int level, vector *v);
		info_delete_func QMPI_Info_delete_ptr = (info_delete_func) func_ptr;
		MPI_Info info_delete_func_arg0 = va_arg(argp, MPI_Info);
		const char * info_delete_func_arg1 = va_arg(argp, const char *);
		ret = (QMPI_Info_delete_ptr) (info_delete_func_arg0, info_delete_func_arg1,  level, v);
		break;
		 
        // int QMPI_Info_delete(MPI_Info info, const char *key, int level, vector *v);\n
     
    case 193:
        va_start(argp,v);
		typedef int (*info_dup_func) (MPI_Info info, MPI_Info *newinfo, int level, vector *v);
		info_dup_func QMPI_Info_dup_ptr = (info_dup_func) func_ptr;
		MPI_Info info_dup_func_arg0 = va_arg(argp, MPI_Info);
		MPI_Info * info_dup_func_arg1 = va_arg(argp, MPI_Info *);
		ret = (QMPI_Info_dup_ptr) (info_dup_func_arg0, info_dup_func_arg1,  level, v);
		break;
		 
        // int QMPI_Info_dup(MPI_Info info, MPI_Info *newinfo, int level, vector *v);\n
     
    case 194:
        va_start(argp,v);
		typedef int (*info_free_func) (MPI_Info *info, int level, vector *v);
		info_free_func QMPI_Info_free_ptr = (info_free_func) func_ptr;
		MPI_Info * info_free_func_arg0 = va_arg(argp, MPI_Info *);
		ret = (QMPI_Info_free_ptr) (info_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Info_free(MPI_Info *info, int level, vector *v);\n
     
    case 195:
        va_start(argp,v);
		typedef int (*info_get_func) (MPI_Info info, const char *key, int valuelen, char *value, int *flag, int level, vector *v);
		info_get_func QMPI_Info_get_ptr = (info_get_func) func_ptr;
		MPI_Info info_get_func_arg0 = va_arg(argp, MPI_Info);
		const char * info_get_func_arg1 = va_arg(argp, const char *);
		int info_get_func_arg2 = va_arg(argp, int);
		char * info_get_func_arg3 = va_arg(argp, char *);
		int * info_get_func_arg4 = va_arg(argp, int *);
		ret = (QMPI_Info_get_ptr) (info_get_func_arg0, info_get_func_arg1, info_get_func_arg2, info_get_func_arg3, info_get_func_arg4,  level, v);
		break;
		 
        // int QMPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag, int level, vector *v);\n
     
    case 196:
        va_start(argp,v);
		typedef int (*info_get_nkeys_func) (MPI_Info info, int *nkeys, int level, vector *v);
		info_get_nkeys_func QMPI_Info_get_nkeys_ptr = (info_get_nkeys_func) func_ptr;
		MPI_Info info_get_nkeys_func_arg0 = va_arg(argp, MPI_Info);
		int * info_get_nkeys_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Info_get_nkeys_ptr) (info_get_nkeys_func_arg0, info_get_nkeys_func_arg1,  level, v);
		break;
		 
        // int QMPI_Info_get_nkeys(MPI_Info info, int *nkeys, int level, vector *v);\n
     
    case 197:
        va_start(argp,v);
		typedef int (*info_get_nthkey_func) (MPI_Info info, int n, char *key, int level, vector *v);
		info_get_nthkey_func QMPI_Info_get_nthkey_ptr = (info_get_nthkey_func) func_ptr;
		MPI_Info info_get_nthkey_func_arg0 = va_arg(argp, MPI_Info);
		int info_get_nthkey_func_arg1 = va_arg(argp, int);
		char * info_get_nthkey_func_arg2 = va_arg(argp, char *);
		ret = (QMPI_Info_get_nthkey_ptr) (info_get_nthkey_func_arg0, info_get_nthkey_func_arg1, info_get_nthkey_func_arg2,  level, v);
		break;
		 
        // int QMPI_Info_get_nthkey(MPI_Info info, int n, char *key, int level, vector *v);\n
     
    case 198:
        va_start(argp,v);
		typedef int (*info_get_valuelen_func) (MPI_Info info, const char *key, int *valuelen, int *flag, int level, vector *v);
		info_get_valuelen_func QMPI_Info_get_valuelen_ptr = (info_get_valuelen_func) func_ptr;
		MPI_Info info_get_valuelen_func_arg0 = va_arg(argp, MPI_Info);
		const char * info_get_valuelen_func_arg1 = va_arg(argp, const char *);
		int * info_get_valuelen_func_arg2 = va_arg(argp, int *);
		int * info_get_valuelen_func_arg3 = va_arg(argp, int *);
		ret = (QMPI_Info_get_valuelen_ptr) (info_get_valuelen_func_arg0, info_get_valuelen_func_arg1, info_get_valuelen_func_arg2, info_get_valuelen_func_arg3,  level, v);
		break;
		 
        // int QMPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag, int level, vector *v);\n
     
    case 199:
        va_start(argp,v);
		typedef int (*info_set_func) (MPI_Info info, const char *key, const char *value, int level, vector *v);
		info_set_func QMPI_Info_set_ptr = (info_set_func) func_ptr;
		MPI_Info info_set_func_arg0 = va_arg(argp, MPI_Info);
		const char * info_set_func_arg1 = va_arg(argp, const char *);
		const char * info_set_func_arg2 = va_arg(argp, const char *);
		ret = (QMPI_Info_set_ptr) (info_set_func_arg0, info_set_func_arg1, info_set_func_arg2,  level, v);
		break;
		 
        // int QMPI_Info_set(MPI_Info info, const char *key, const char *value, int level, vector *v);\n
     
    case 200:
        va_start(argp,v);
		typedef int (*init_func)(int *argc,char ***argv,int i , vector* v );
        init_func init_ptr= (init_func) func_ptr;;
        int* init_arg_1=(va_arg( argp, int* ));
        char*** init_arg_2=va_arg(argp, char ***) ;
        ret= (init_ptr ) ( init_arg_1, init_arg_2 , level, v);
		break;
		 
        // int QMPI_Init(int *argc, int first_level, vector* v, int level,  vector* v);\n
     
    case 201:
        va_start(argp,v);
		typedef int (*init_thread_func) (int *argc, char ***argv, int required, int *provided, int level,  vector* v);
		init_thread_func QMPI_Init_thread_ptr = (init_thread_func) func_ptr;
		int * init_thread_func_arg0 = va_arg(argp, int *);
		char *** init_thread_func_arg1 = va_arg(argp, char***);
		int init_thread_func_arg2 = va_arg(argp, int);
		int * init_thread_func_arg3 = va_arg(argp, int *);
		ret = (QMPI_Init_thread_ptr) (init_thread_func_arg0, init_thread_func_arg1, init_thread_func_arg2,init_thread_func_arg3, level, v);
		break;
		 
        // int QMPI_Init_thread(int *argc, char ***argv, int required, int *provided, int level,  vector* v);\n
     
    case 202:
        va_start(argp,v);
		typedef int (*initialized_func) (int *flag, int level, vector *v);
		initialized_func QMPI_Initialized_ptr = (initialized_func) func_ptr;
		int * initialized_func_arg0 = va_arg(argp, int *);
		ret = (QMPI_Initialized_ptr) (initialized_func_arg0,  level, v);
		break;
		 
        // int QMPI_Initialized(int *flag, int level, vector *v);\n
     
    case 203:
        va_start(argp,v);
		typedef int (*intercomm_create_func) (MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm *newintercomm, int level, vector *v);
		intercomm_create_func QMPI_Intercomm_create_ptr = (intercomm_create_func) func_ptr;
		MPI_Comm intercomm_create_func_arg0 = va_arg(argp, MPI_Comm);
		int intercomm_create_func_arg1 = va_arg(argp, int);
		MPI_Comm intercomm_create_func_arg2 = va_arg(argp, MPI_Comm);
		int intercomm_create_func_arg3 = va_arg(argp, int);
		int intercomm_create_func_arg4 = va_arg(argp, int);
		MPI_Comm * intercomm_create_func_arg5 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Intercomm_create_ptr) (intercomm_create_func_arg0, intercomm_create_func_arg1, intercomm_create_func_arg2, intercomm_create_func_arg3, intercomm_create_func_arg4, intercomm_create_func_arg5,  level, v);
		break;
		 
        // int QMPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm *newintercomm, int level, vector *v);\n
     
    case 204:
        va_start(argp,v);
		typedef int (*intercomm_merge_func) (MPI_Comm intercomm, int high, MPI_Comm *newintercomm, int level, vector *v);
		intercomm_merge_func QMPI_Intercomm_merge_ptr = (intercomm_merge_func) func_ptr;
		MPI_Comm intercomm_merge_func_arg0 = va_arg(argp, MPI_Comm);
		int intercomm_merge_func_arg1 = va_arg(argp, int);
		MPI_Comm * intercomm_merge_func_arg2 = va_arg(argp, MPI_Comm *);
		ret = (QMPI_Intercomm_merge_ptr) (intercomm_merge_func_arg0, intercomm_merge_func_arg1, intercomm_merge_func_arg2,  level, v);
		break;
		 
        // int QMPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintercomm, int level, vector *v);\n
     
    case 205:
        va_start(argp,v);
		typedef int (*iprobe_func) (int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status, int level, vector *v);
		iprobe_func QMPI_Iprobe_ptr = (iprobe_func) func_ptr;
		int iprobe_func_arg0 = va_arg(argp, int);
		int iprobe_func_arg1 = va_arg(argp, int);
		MPI_Comm iprobe_func_arg2 = va_arg(argp, MPI_Comm);
		int * iprobe_func_arg3 = va_arg(argp, int *);
		MPI_Status * iprobe_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Iprobe_ptr) (iprobe_func_arg0, iprobe_func_arg1, iprobe_func_arg2, iprobe_func_arg3, iprobe_func_arg4,  level, v);
		break;
		 
        // int QMPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status, int level, vector *v);\n
     
    case 206:
        va_start(argp,v);
		typedef int (*irecv_func) (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		irecv_func QMPI_Irecv_ptr = (irecv_func) func_ptr;
		void * irecv_func_arg0 = va_arg(argp, void *);
		int irecv_func_arg1 = va_arg(argp, int);
		MPI_Datatype irecv_func_arg2 = va_arg(argp, MPI_Datatype);
		int irecv_func_arg3 = va_arg(argp, int);
		int irecv_func_arg4 = va_arg(argp, int);
		MPI_Comm irecv_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * irecv_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Irecv_ptr) (irecv_func_arg0, irecv_func_arg1, irecv_func_arg2, irecv_func_arg3, irecv_func_arg4, irecv_func_arg5, irecv_func_arg6,  level, v);
		break;
		 
        // int QMPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 207:
        va_start(argp,v);
		typedef int (*ireduce_func) (const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ireduce_func QMPI_Ireduce_ptr = (ireduce_func) func_ptr;
		const void * ireduce_func_arg0 = va_arg(argp, const void *);
		void * ireduce_func_arg1 = va_arg(argp, void *);
		int ireduce_func_arg2 = va_arg(argp, int);
		MPI_Datatype ireduce_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op ireduce_func_arg4 = va_arg(argp, MPI_Op);
		int ireduce_func_arg5 = va_arg(argp, int);
		MPI_Comm ireduce_func_arg6 = va_arg(argp, MPI_Comm);
		MPI_Request * ireduce_func_arg7 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ireduce_ptr) (ireduce_func_arg0, ireduce_func_arg1, ireduce_func_arg2, ireduce_func_arg3, ireduce_func_arg4, ireduce_func_arg5, ireduce_func_arg6, ireduce_func_arg7,  level, v);
		break;
		 
        // int QMPI_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 208:
        va_start(argp,v);
		typedef int (*ireduce_scatter_func) (const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ireduce_scatter_func QMPI_Ireduce_scatter_ptr = (ireduce_scatter_func) func_ptr;
		const void * ireduce_scatter_func_arg0 = va_arg(argp, const void *);
		void * ireduce_scatter_func_arg1 = va_arg(argp, void *);
		const int * ireduce_scatter_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype ireduce_scatter_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op ireduce_scatter_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm ireduce_scatter_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * ireduce_scatter_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ireduce_scatter_ptr) (ireduce_scatter_func_arg0, ireduce_scatter_func_arg1, ireduce_scatter_func_arg2, ireduce_scatter_func_arg3, ireduce_scatter_func_arg4, ireduce_scatter_func_arg5, ireduce_scatter_func_arg6,  level, v);
		break;
		 
        // int QMPI_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 209:
        va_start(argp,v);
		typedef int (*ireduce_scatter_block_func) (const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ireduce_scatter_block_func QMPI_Ireduce_scatter_block_ptr = (ireduce_scatter_block_func) func_ptr;
		const void * ireduce_scatter_block_func_arg0 = va_arg(argp, const void *);
		void * ireduce_scatter_block_func_arg1 = va_arg(argp, void *);
		int ireduce_scatter_block_func_arg2 = va_arg(argp, int);
		MPI_Datatype ireduce_scatter_block_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op ireduce_scatter_block_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm ireduce_scatter_block_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * ireduce_scatter_block_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ireduce_scatter_block_ptr) (ireduce_scatter_block_func_arg0, ireduce_scatter_block_func_arg1, ireduce_scatter_block_func_arg2, ireduce_scatter_block_func_arg3, ireduce_scatter_block_func_arg4, ireduce_scatter_block_func_arg5, ireduce_scatter_block_func_arg6,  level, v);
		break;
		 
        // int QMPI_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 210:
        va_start(argp,v);
		typedef int (*irsend_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		irsend_func QMPI_Irsend_ptr = (irsend_func) func_ptr;
		const void * irsend_func_arg0 = va_arg(argp, const void *);
		int irsend_func_arg1 = va_arg(argp, int);
		MPI_Datatype irsend_func_arg2 = va_arg(argp, MPI_Datatype);
		int irsend_func_arg3 = va_arg(argp, int);
		int irsend_func_arg4 = va_arg(argp, int);
		MPI_Comm irsend_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * irsend_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Irsend_ptr) (irsend_func_arg0, irsend_func_arg1, irsend_func_arg2, irsend_func_arg3, irsend_func_arg4, irsend_func_arg5, irsend_func_arg6,  level, v);
		break;
		 
        // int QMPI_Irsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 211:
        va_start(argp,v);
		typedef int (*is_thread_main_func) (int *flag, int level, vector *v);
		is_thread_main_func QMPI_Is_thread_main_ptr = (is_thread_main_func) func_ptr;
		int * is_thread_main_func_arg0 = va_arg(argp, int *);
		ret = (QMPI_Is_thread_main_ptr) (is_thread_main_func_arg0,  level, v);
		break;
		 
        // int QMPI_Is_thread_main(int *flag, int level, vector *v);\n
     
    case 212:
        va_start(argp,v);
		typedef int (*iscan_func) (const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		iscan_func QMPI_Iscan_ptr = (iscan_func) func_ptr;
		const void * iscan_func_arg0 = va_arg(argp, const void *);
		void * iscan_func_arg1 = va_arg(argp, void *);
		int iscan_func_arg2 = va_arg(argp, int);
		MPI_Datatype iscan_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op iscan_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm iscan_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * iscan_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Iscan_ptr) (iscan_func_arg0, iscan_func_arg1, iscan_func_arg2, iscan_func_arg3, iscan_func_arg4, iscan_func_arg5, iscan_func_arg6,  level, v);
		break;
		 
        // int QMPI_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 213:
        va_start(argp,v);
		typedef int (*iscatter_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		iscatter_func QMPI_Iscatter_ptr = (iscatter_func) func_ptr;
		const void * iscatter_func_arg0 = va_arg(argp, const void *);
		int iscatter_func_arg1 = va_arg(argp, int);
		MPI_Datatype iscatter_func_arg2 = va_arg(argp, MPI_Datatype);
		void * iscatter_func_arg3 = va_arg(argp, void *);
		int iscatter_func_arg4 = va_arg(argp, int);
		MPI_Datatype iscatter_func_arg5 = va_arg(argp, MPI_Datatype);
		int iscatter_func_arg6 = va_arg(argp, int);
		MPI_Comm iscatter_func_arg7 = va_arg(argp, MPI_Comm);
		MPI_Request * iscatter_func_arg8 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Iscatter_ptr) (iscatter_func_arg0, iscatter_func_arg1, iscatter_func_arg2, iscatter_func_arg3, iscatter_func_arg4, iscatter_func_arg5, iscatter_func_arg6, iscatter_func_arg7, iscatter_func_arg8,  level, v);
		break;
		 
        // int QMPI_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 214:
        va_start(argp,v);
		typedef int (*iscatterv_func) (const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		iscatterv_func QMPI_Iscatterv_ptr = (iscatterv_func) func_ptr;
		const void * iscatterv_func_arg0 = va_arg(argp, const void *);
		const int * iscatterv_func_arg1 = va_arg(argp, const int *);
		const int * iscatterv_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype iscatterv_func_arg3 = va_arg(argp, MPI_Datatype);
		void * iscatterv_func_arg4 = va_arg(argp, void *);
		int iscatterv_func_arg5 = va_arg(argp, int);
		MPI_Datatype iscatterv_func_arg6 = va_arg(argp, MPI_Datatype);
		int iscatterv_func_arg7 = va_arg(argp, int);
		MPI_Comm iscatterv_func_arg8 = va_arg(argp, MPI_Comm);
		MPI_Request * iscatterv_func_arg9 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Iscatterv_ptr) (iscatterv_func_arg0, iscatterv_func_arg1, iscatterv_func_arg2, iscatterv_func_arg3, iscatterv_func_arg4, iscatterv_func_arg5, iscatterv_func_arg6, iscatterv_func_arg7, iscatterv_func_arg8, iscatterv_func_arg9,  level, v);
		break;
		 
        // int QMPI_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 215:
        va_start(argp,v);
		typedef int (*isend_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		isend_func QMPI_Isend_ptr = (isend_func) func_ptr;
		const void * isend_func_arg0 = va_arg(argp, const void *);
		int isend_func_arg1 = va_arg(argp, int);
		MPI_Datatype isend_func_arg2 = va_arg(argp, MPI_Datatype);
		int isend_func_arg3 = va_arg(argp, int);
		int isend_func_arg4 = va_arg(argp, int);
		MPI_Comm isend_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * isend_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Isend_ptr) (isend_func_arg0, isend_func_arg1, isend_func_arg2, isend_func_arg3, isend_func_arg4, isend_func_arg5, isend_func_arg6,  level, v);
		break;
		 
        // int QMPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 216:
        va_start(argp,v);
		typedef int (*issend_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		issend_func QMPI_Issend_ptr = (issend_func) func_ptr;
		const void * issend_func_arg0 = va_arg(argp, const void *);
		int issend_func_arg1 = va_arg(argp, int);
		MPI_Datatype issend_func_arg2 = va_arg(argp, MPI_Datatype);
		int issend_func_arg3 = va_arg(argp, int);
		int issend_func_arg4 = va_arg(argp, int);
		MPI_Comm issend_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * issend_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Issend_ptr) (issend_func_arg0, issend_func_arg1, issend_func_arg2, issend_func_arg3, issend_func_arg4, issend_func_arg5, issend_func_arg6,  level, v);
		break;
		 
        // int QMPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 217:
        va_start(argp,v);
		typedef int (*keyval_create_func) (MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state, int level, vector *v);
		keyval_create_func QMPI_Keyval_create_ptr = (keyval_create_func) func_ptr;
		MPI_Copy_function * keyval_create_func_arg0 = va_arg(argp, MPI_Copy_function *);
		MPI_Delete_function * keyval_create_func_arg1 = va_arg(argp, MPI_Delete_function *);
		int * keyval_create_func_arg2 = va_arg(argp, int *);
		void * keyval_create_func_arg3 = va_arg(argp, void *);
		ret = (QMPI_Keyval_create_ptr) (keyval_create_func_arg0, keyval_create_func_arg1, keyval_create_func_arg2, keyval_create_func_arg3,  level, v);
		break;
		 
        // int QMPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state, int level, vector *v);\n
     
    case 218:
        va_start(argp,v);
		typedef int (*keyval_free_func) (int *keyval, int level, vector *v);
		keyval_free_func QMPI_Keyval_free_ptr = (keyval_free_func) func_ptr;
		int * keyval_free_func_arg0 = va_arg(argp, int *);
		ret = (QMPI_Keyval_free_ptr) (keyval_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Keyval_free(int *keyval, int level, vector *v);\n
     
    case 219:
        va_start(argp,v);
		typedef int (*lookup_name_func) (const char *service_name, MPI_Info info, char *port_name, int level, vector *v);
		lookup_name_func QMPI_Lookup_name_ptr = (lookup_name_func) func_ptr;
		const char * lookup_name_func_arg0 = va_arg(argp, const char *);
		MPI_Info lookup_name_func_arg1 = va_arg(argp, MPI_Info);
		char * lookup_name_func_arg2 = va_arg(argp, char *);
		ret = (QMPI_Lookup_name_ptr) (lookup_name_func_arg0, lookup_name_func_arg1, lookup_name_func_arg2,  level, v);
		break;
		 
        // int QMPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name, int level, vector *v);\n
     
    case 220:
        va_start(argp,v);
		typedef int (*mprobe_func) (int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status, int level, vector *v);
		mprobe_func QMPI_Mprobe_ptr = (mprobe_func) func_ptr;
		int mprobe_func_arg0 = va_arg(argp, int);
		int mprobe_func_arg1 = va_arg(argp, int);
		MPI_Comm mprobe_func_arg2 = va_arg(argp, MPI_Comm);
		MPI_Message * mprobe_func_arg3 = va_arg(argp, MPI_Message *);
		MPI_Status * mprobe_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Mprobe_ptr) (mprobe_func_arg0, mprobe_func_arg1, mprobe_func_arg2, mprobe_func_arg3, mprobe_func_arg4,  level, v);
		break;
		 
        // int QMPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status, int level, vector *v);\n
     
    case 221:
        va_start(argp,v);
		typedef int (*mrecv_func) (void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Status *status, int level, vector *v);
		mrecv_func QMPI_Mrecv_ptr = (mrecv_func) func_ptr;
		void * mrecv_func_arg0 = va_arg(argp, void *);
		int mrecv_func_arg1 = va_arg(argp, int);
		MPI_Datatype mrecv_func_arg2 = va_arg(argp, MPI_Datatype);
		MPI_Message * mrecv_func_arg3 = va_arg(argp, MPI_Message *);
		MPI_Status * mrecv_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Mrecv_ptr) (mrecv_func_arg0, mrecv_func_arg1, mrecv_func_arg2, mrecv_func_arg3, mrecv_func_arg4,  level, v);
		break;
		 
        // int QMPI_Mrecv(void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Status *status, int level, vector *v);\n
     
    case 222:
        va_start(argp,v);
		typedef int (*neighbor_allgather_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);
		neighbor_allgather_func QMPI_Neighbor_allgather_ptr = (neighbor_allgather_func) func_ptr;
		const void * neighbor_allgather_func_arg0 = va_arg(argp, const void *);
		int neighbor_allgather_func_arg1 = va_arg(argp, int);
		MPI_Datatype neighbor_allgather_func_arg2 = va_arg(argp, MPI_Datatype);
		void * neighbor_allgather_func_arg3 = va_arg(argp, void *);
		int neighbor_allgather_func_arg4 = va_arg(argp, int);
		MPI_Datatype neighbor_allgather_func_arg5 = va_arg(argp, MPI_Datatype);
		MPI_Comm neighbor_allgather_func_arg6 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Neighbor_allgather_ptr) (neighbor_allgather_func_arg0, neighbor_allgather_func_arg1, neighbor_allgather_func_arg2, neighbor_allgather_func_arg3, neighbor_allgather_func_arg4, neighbor_allgather_func_arg5, neighbor_allgather_func_arg6,  level, v);
		break;
		 
        // int QMPI_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);\n
     
    case 223:
        va_start(argp,v);
		typedef int (*neighbor_allgatherv_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);
		neighbor_allgatherv_func QMPI_Neighbor_allgatherv_ptr = (neighbor_allgatherv_func) func_ptr;
		const void * neighbor_allgatherv_func_arg0 = va_arg(argp, const void *);
		int neighbor_allgatherv_func_arg1 = va_arg(argp, int);
		MPI_Datatype neighbor_allgatherv_func_arg2 = va_arg(argp, MPI_Datatype);
		void * neighbor_allgatherv_func_arg3 = va_arg(argp, void *);
		const int * neighbor_allgatherv_func_arg4 = va_arg(argp, const int *);
		const int * neighbor_allgatherv_func_arg5 = va_arg(argp, const int *);
		MPI_Datatype neighbor_allgatherv_func_arg6 = va_arg(argp, MPI_Datatype);
		MPI_Comm neighbor_allgatherv_func_arg7 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Neighbor_allgatherv_ptr) (neighbor_allgatherv_func_arg0, neighbor_allgatherv_func_arg1, neighbor_allgatherv_func_arg2, neighbor_allgatherv_func_arg3, neighbor_allgatherv_func_arg4, neighbor_allgatherv_func_arg5, neighbor_allgatherv_func_arg6, neighbor_allgatherv_func_arg7,  level, v);
		break;
		 
        // int QMPI_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);\n
     
    case 224:
        va_start(argp,v);
		typedef int (*neighbor_alltoall_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);
		neighbor_alltoall_func QMPI_Neighbor_alltoall_ptr = (neighbor_alltoall_func) func_ptr;
		const void * neighbor_alltoall_func_arg0 = va_arg(argp, const void *);
		int neighbor_alltoall_func_arg1 = va_arg(argp, int);
		MPI_Datatype neighbor_alltoall_func_arg2 = va_arg(argp, MPI_Datatype);
		void * neighbor_alltoall_func_arg3 = va_arg(argp, void *);
		int neighbor_alltoall_func_arg4 = va_arg(argp, int);
		MPI_Datatype neighbor_alltoall_func_arg5 = va_arg(argp, MPI_Datatype);
		MPI_Comm neighbor_alltoall_func_arg6 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Neighbor_alltoall_ptr) (neighbor_alltoall_func_arg0, neighbor_alltoall_func_arg1, neighbor_alltoall_func_arg2, neighbor_alltoall_func_arg3, neighbor_alltoall_func_arg4, neighbor_alltoall_func_arg5, neighbor_alltoall_func_arg6,  level, v);
		break;
		 
        // int QMPI_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);\n
     
    case 225:
        va_start(argp,v);
		typedef int (*neighbor_alltoallv_func) (const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);
		neighbor_alltoallv_func QMPI_Neighbor_alltoallv_ptr = (neighbor_alltoallv_func) func_ptr;
		const void * neighbor_alltoallv_func_arg0 = va_arg(argp, const void *);
		const int * neighbor_alltoallv_func_arg1 = va_arg(argp, const int *);
		const int * neighbor_alltoallv_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype neighbor_alltoallv_func_arg3 = va_arg(argp, MPI_Datatype);
		void * neighbor_alltoallv_func_arg4 = va_arg(argp, void *);
		const int * neighbor_alltoallv_func_arg5 = va_arg(argp, const int *);
		const int * neighbor_alltoallv_func_arg6 = va_arg(argp, const int *);
		MPI_Datatype neighbor_alltoallv_func_arg7 = va_arg(argp, MPI_Datatype);
		MPI_Comm neighbor_alltoallv_func_arg8 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Neighbor_alltoallv_ptr) (neighbor_alltoallv_func_arg0, neighbor_alltoallv_func_arg1, neighbor_alltoallv_func_arg2, neighbor_alltoallv_func_arg3, neighbor_alltoallv_func_arg4, neighbor_alltoallv_func_arg5, neighbor_alltoallv_func_arg6, neighbor_alltoallv_func_arg7, neighbor_alltoallv_func_arg8,  level, v);
		break;
		 
        // int QMPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int level, vector *v);\n
     
    case 226:
        va_start(argp,v);
		typedef int (*neighbor_alltoallw_func) (const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, int level, vector *v);
		neighbor_alltoallw_func QMPI_Neighbor_alltoallw_ptr = (neighbor_alltoallw_func) func_ptr;
		const void * neighbor_alltoallw_func_arg0 = va_arg(argp, const void *);
		const int * neighbor_alltoallw_func_arg1 = va_arg(argp, const int *);
		const MPI_Aint * neighbor_alltoallw_func_arg2 = va_arg(argp, const MPI_Aint *);
		const MPI_Datatype * neighbor_alltoallw_func_arg3 = va_arg(argp, const MPI_Datatype *);
		void * neighbor_alltoallw_func_arg4 = va_arg(argp, void *);
		const int * neighbor_alltoallw_func_arg5 = va_arg(argp, const int *);
		const MPI_Aint * neighbor_alltoallw_func_arg6 = va_arg(argp, const MPI_Aint *);
		const MPI_Datatype * neighbor_alltoallw_func_arg7 = va_arg(argp, const MPI_Datatype *);
		MPI_Comm neighbor_alltoallw_func_arg8 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Neighbor_alltoallw_ptr) (neighbor_alltoallw_func_arg0, neighbor_alltoallw_func_arg1, neighbor_alltoallw_func_arg2, neighbor_alltoallw_func_arg3, neighbor_alltoallw_func_arg4, neighbor_alltoallw_func_arg5, neighbor_alltoallw_func_arg6, neighbor_alltoallw_func_arg7, neighbor_alltoallw_func_arg8,  level, v);
		break;
		 
        // int QMPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, int level, vector *v);\n
     
    case 227:
        va_start(argp,v);
		typedef int (*op_commutative_func) (MPI_Op op, int *commute, int level, vector *v);
		op_commutative_func QMPI_Op_commutative_ptr = (op_commutative_func) func_ptr;
		MPI_Op op_commutative_func_arg0 = va_arg(argp, MPI_Op);
		int * op_commutative_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Op_commutative_ptr) (op_commutative_func_arg0, op_commutative_func_arg1,  level, v);
		break;
		 
        // int QMPI_Op_commutative(MPI_Op op, int *commute, int level, vector *v);\n
     
    case 228:
        va_start(argp,v);
		typedef int (*op_create_func) (MPI_User_function *function, int commute, MPI_Op *op, int level, vector *v);
		op_create_func QMPI_Op_create_ptr = (op_create_func) func_ptr;
		MPI_User_function * op_create_func_arg0 = va_arg(argp, MPI_User_function *);
		int op_create_func_arg1 = va_arg(argp, int);
		MPI_Op * op_create_func_arg2 = va_arg(argp, MPI_Op *);
		ret = (QMPI_Op_create_ptr) (op_create_func_arg0, op_create_func_arg1, op_create_func_arg2,  level, v);
		break;
		 
        // int QMPI_Op_create(MPI_User_function *function, int commute, MPI_Op *op, int level, vector *v);\n
     
    case 229:
        va_start(argp,v);
		typedef int (*op_free_func) (MPI_Op *op, int level, vector *v);
		op_free_func QMPI_Op_free_ptr = (op_free_func) func_ptr;
		MPI_Op * op_free_func_arg0 = va_arg(argp, MPI_Op *);
		ret = (QMPI_Op_free_ptr) (op_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Op_free(MPI_Op *op, int level, vector *v);\n
     
    case 230:
        va_start(argp,v);
		typedef int (*open_port_func) (MPI_Info info, char *port_name, int level, vector *v);
		open_port_func QMPI_Open_port_ptr = (open_port_func) func_ptr;
		MPI_Info open_port_func_arg0 = va_arg(argp, MPI_Info);
		char * open_port_func_arg1 = va_arg(argp, char *);
		ret = (QMPI_Open_port_ptr) (open_port_func_arg0, open_port_func_arg1,  level, v);
		break;
		 
        // int QMPI_Open_port(MPI_Info info, char *port_name, int level, vector *v);\n
     
    case 231:
        va_start(argp,v);
		typedef int (*pack_func) (const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm, int level, vector *v);
		pack_func QMPI_Pack_ptr = (pack_func) func_ptr;
		const void * pack_func_arg0 = va_arg(argp, const void *);
		int pack_func_arg1 = va_arg(argp, int);
		MPI_Datatype pack_func_arg2 = va_arg(argp, MPI_Datatype);
		void * pack_func_arg3 = va_arg(argp, void *);
		int pack_func_arg4 = va_arg(argp, int);
		int * pack_func_arg5 = va_arg(argp, int *);
		MPI_Comm pack_func_arg6 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Pack_ptr) (pack_func_arg0, pack_func_arg1, pack_func_arg2, pack_func_arg3, pack_func_arg4, pack_func_arg5, pack_func_arg6,  level, v);
		break;
		 
        // int QMPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm, int level, vector *v);\n
     
    case 232:
        va_start(argp,v);
		typedef int (*pack_external_func) (const char datarep[], const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position, int level, vector *v);
		pack_external_func QMPI_Pack_external_ptr = (pack_external_func) func_ptr;
		const char * pack_external_func_arg0 = va_arg(argp, const char *);
		const void * pack_external_func_arg1 = va_arg(argp, const void *);
		int pack_external_func_arg2 = va_arg(argp, int);
		MPI_Datatype pack_external_func_arg3 = va_arg(argp, MPI_Datatype);
		void * pack_external_func_arg4 = va_arg(argp, void *);
		MPI_Aint pack_external_func_arg5 = va_arg(argp, MPI_Aint);
		MPI_Aint * pack_external_func_arg6 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_Pack_external_ptr) (pack_external_func_arg0, pack_external_func_arg1, pack_external_func_arg2, pack_external_func_arg3, pack_external_func_arg4, pack_external_func_arg5, pack_external_func_arg6,  level, v);
		break;
		 
        // int QMPI_Pack_external(const char datarep[], const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position, int level, vector *v);\n
     
    case 233:
        va_start(argp,v);
		typedef int (*pack_external_size_func) (const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint *size, int level, vector *v);
		pack_external_size_func QMPI_Pack_external_size_ptr = (pack_external_size_func) func_ptr;
		const char * pack_external_size_func_arg0 = va_arg(argp, const char *);
		int pack_external_size_func_arg1 = va_arg(argp, int);
		MPI_Datatype pack_external_size_func_arg2 = va_arg(argp, MPI_Datatype);
		MPI_Aint * pack_external_size_func_arg3 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_Pack_external_size_ptr) (pack_external_size_func_arg0, pack_external_size_func_arg1, pack_external_size_func_arg2, pack_external_size_func_arg3,  level, v);
		break;
		 
        // int QMPI_Pack_external_size(const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint *size, int level, vector *v);\n
     
    case 234:
        va_start(argp,v);
		typedef int (*pack_size_func) (int incount, MPI_Datatype datatype, MPI_Comm comm, int *size, int level, vector *v);
		pack_size_func QMPI_Pack_size_ptr = (pack_size_func) func_ptr;
		int pack_size_func_arg0 = va_arg(argp, int);
		MPI_Datatype pack_size_func_arg1 = va_arg(argp, MPI_Datatype);
		MPI_Comm pack_size_func_arg2 = va_arg(argp, MPI_Comm);
		int * pack_size_func_arg3 = va_arg(argp, int *);
		ret = (QMPI_Pack_size_ptr) (pack_size_func_arg0, pack_size_func_arg1, pack_size_func_arg2, pack_size_func_arg3,  level, v);
		break;
		 
        // int QMPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size, int level, vector *v);\n
     
    case 235: // TODO: FIX THİS     !!!!!!!!!!!
        /*va_start(argp,v);
		typedef int (*pcontrol_func) (const int first_level, int level,  vector* v);
		pcontrol_func QMPI_Pcontrol_ptr = (pcontrol_func) func_ptr;
		const pcontrol_func_arg0 = va_arg(argp, const);
		ret = (QMPI_Pcontrol_ptr) (pcontrol_func_arg0, level, v);
		*/break;
		 
        // int QMPI_Pcontrol(const int first_level, int level,  vector* v);\n
     
    case 236:
        va_start(argp,v);
		typedef int (*probe_func) (int source, int tag, MPI_Comm comm, MPI_Status *status, int level, vector *v);
		probe_func QMPI_Probe_ptr = (probe_func) func_ptr;
		int probe_func_arg0 = va_arg(argp, int);
		int probe_func_arg1 = va_arg(argp, int);
		MPI_Comm probe_func_arg2 = va_arg(argp, MPI_Comm);
		MPI_Status * probe_func_arg3 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Probe_ptr) (probe_func_arg0, probe_func_arg1, probe_func_arg2, probe_func_arg3,  level, v);
		break;
		 
        // int QMPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status, int level, vector *v);\n
     
    case 237:
        va_start(argp,v);
		typedef int (*publish_name_func) (const char *service_name, MPI_Info info, const char *port_name, int level, vector *v);
		publish_name_func QMPI_Publish_name_ptr = (publish_name_func) func_ptr;
		const char * publish_name_func_arg0 = va_arg(argp, const char *);
		MPI_Info publish_name_func_arg1 = va_arg(argp, MPI_Info);
		const char * publish_name_func_arg2 = va_arg(argp, const char *);
		ret = (QMPI_Publish_name_ptr) (publish_name_func_arg0, publish_name_func_arg1, publish_name_func_arg2,  level, v);
		break;
		 
        // int QMPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name, int level, vector *v);\n
     
    case 238:
        va_start(argp,v);
		typedef int (*put_func) (const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, int level, vector *v);
		put_func QMPI_Put_ptr = (put_func) func_ptr;
		const void * put_func_arg0 = va_arg(argp, const void *);
		int put_func_arg1 = va_arg(argp, int);
		MPI_Datatype put_func_arg2 = va_arg(argp, MPI_Datatype);
		int put_func_arg3 = va_arg(argp, int);
		MPI_Aint put_func_arg4 = va_arg(argp, MPI_Aint);
		int put_func_arg5 = va_arg(argp, int);
		MPI_Datatype put_func_arg6 = va_arg(argp, MPI_Datatype);
		MPI_Win put_func_arg7 = va_arg(argp, MPI_Win);
		ret = (QMPI_Put_ptr) (put_func_arg0, put_func_arg1, put_func_arg2, put_func_arg3, put_func_arg4, put_func_arg5, put_func_arg6, put_func_arg7,  level, v);
		break;
		 
        // int QMPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, int level, vector *v);\n
     
    case 239:
        va_start(argp,v);
		typedef int (*query_thread_func) (int *provided, int level, vector *v);
		query_thread_func QMPI_Query_thread_ptr = (query_thread_func) func_ptr;
		int * query_thread_func_arg0 = va_arg(argp, int *);
		ret = (QMPI_Query_thread_ptr) (query_thread_func_arg0,  level, v);
		break;
		 
        // int QMPI_Query_thread(int *provided, int level, vector *v);\n
     
    case 240:
        va_start(argp,v);
		typedef int (*raccumulate_func) (const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request, int level, vector *v);
		raccumulate_func QMPI_Raccumulate_ptr = (raccumulate_func) func_ptr;
		const void * raccumulate_func_arg0 = va_arg(argp, const void *);
		int raccumulate_func_arg1 = va_arg(argp, int);
		MPI_Datatype raccumulate_func_arg2 = va_arg(argp, MPI_Datatype);
		int raccumulate_func_arg3 = va_arg(argp, int);
		MPI_Aint raccumulate_func_arg4 = va_arg(argp, MPI_Aint);
		int raccumulate_func_arg5 = va_arg(argp, int);
		MPI_Datatype raccumulate_func_arg6 = va_arg(argp, MPI_Datatype);
		MPI_Op raccumulate_func_arg7 = va_arg(argp, MPI_Op);
		MPI_Win raccumulate_func_arg8 = va_arg(argp, MPI_Win);
		MPI_Request * raccumulate_func_arg9 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Raccumulate_ptr) (raccumulate_func_arg0, raccumulate_func_arg1, raccumulate_func_arg2, raccumulate_func_arg3, raccumulate_func_arg4, raccumulate_func_arg5, raccumulate_func_arg6, raccumulate_func_arg7, raccumulate_func_arg8, raccumulate_func_arg9,  level, v);
		break;
		 
        // int QMPI_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request, int level, vector *v);\n
     
    case 241:
        va_start(argp,v);
		typedef int (*recv_func) (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, int level, vector *v);
		recv_func QMPI_Recv_ptr = (recv_func) func_ptr;
		void * recv_func_arg0 = va_arg(argp, void *);
		int recv_func_arg1 = va_arg(argp, int);
		MPI_Datatype recv_func_arg2 = va_arg(argp, MPI_Datatype);
		int recv_func_arg3 = va_arg(argp, int);
		int recv_func_arg4 = va_arg(argp, int);
		MPI_Comm recv_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Status * recv_func_arg6 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Recv_ptr) (recv_func_arg0, recv_func_arg1, recv_func_arg2, recv_func_arg3, recv_func_arg4, recv_func_arg5, recv_func_arg6,  level, v);
		break;
		 
        // int QMPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, int level, vector *v);\n
     
    case 242:
        va_start(argp,v);
		typedef int (*recv_init_func) (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		recv_init_func QMPI_Recv_init_ptr = (recv_init_func) func_ptr;
		void * recv_init_func_arg0 = va_arg(argp, void *);
		int recv_init_func_arg1 = va_arg(argp, int);
		MPI_Datatype recv_init_func_arg2 = va_arg(argp, MPI_Datatype);
		int recv_init_func_arg3 = va_arg(argp, int);
		int recv_init_func_arg4 = va_arg(argp, int);
		MPI_Comm recv_init_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * recv_init_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Recv_init_ptr) (recv_init_func_arg0, recv_init_func_arg1, recv_init_func_arg2, recv_init_func_arg3, recv_init_func_arg4, recv_init_func_arg5, recv_init_func_arg6,  level, v);
		break;
		 
        // int QMPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 243:
        va_start(argp,v);
		typedef int (*reduce_func) (const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, int level, vector *v);
		reduce_func QMPI_Reduce_ptr = (reduce_func) func_ptr;
		const void * reduce_func_arg0 = va_arg(argp, const void *);
		void * reduce_func_arg1 = va_arg(argp, void *);
		int reduce_func_arg2 = va_arg(argp, int);
		MPI_Datatype reduce_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op reduce_func_arg4 = va_arg(argp, MPI_Op);
		int reduce_func_arg5 = va_arg(argp, int);
		MPI_Comm reduce_func_arg6 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Reduce_ptr) (reduce_func_arg0, reduce_func_arg1, reduce_func_arg2, reduce_func_arg3, reduce_func_arg4, reduce_func_arg5, reduce_func_arg6,  level, v);
		break;
		 
        // int QMPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, int level, vector *v);\n
     
    case 244:
        va_start(argp,v);
		typedef int (*reduce_local_func) (const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op, int level, vector *v);
		reduce_local_func QMPI_Reduce_local_ptr = (reduce_local_func) func_ptr;
		const void * reduce_local_func_arg0 = va_arg(argp, const void *);
		void * reduce_local_func_arg1 = va_arg(argp, void *);
		int reduce_local_func_arg2 = va_arg(argp, int);
		MPI_Datatype reduce_local_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op reduce_local_func_arg4 = va_arg(argp, MPI_Op);
		ret = (QMPI_Reduce_local_ptr) (reduce_local_func_arg0, reduce_local_func_arg1, reduce_local_func_arg2, reduce_local_func_arg3, reduce_local_func_arg4,  level, v);
		break;
		 
        // int QMPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op, int level, vector *v);\n
     
    case 245:
        va_start(argp,v);
		typedef int (*reduce_scatter_func) (const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level, vector *v);
		reduce_scatter_func QMPI_Reduce_scatter_ptr = (reduce_scatter_func) func_ptr;
		const void * reduce_scatter_func_arg0 = va_arg(argp, const void *);
		void * reduce_scatter_func_arg1 = va_arg(argp, void *);
		const int * reduce_scatter_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype reduce_scatter_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op reduce_scatter_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm reduce_scatter_func_arg5 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Reduce_scatter_ptr) (reduce_scatter_func_arg0, reduce_scatter_func_arg1, reduce_scatter_func_arg2, reduce_scatter_func_arg3, reduce_scatter_func_arg4, reduce_scatter_func_arg5,  level, v);
		break;
		 
        // int QMPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level, vector *v);\n
     
    case 246:
        va_start(argp,v);
		typedef int (*reduce_scatter_block_func) (const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level, vector *v);
		reduce_scatter_block_func QMPI_Reduce_scatter_block_ptr = (reduce_scatter_block_func) func_ptr;
		const void * reduce_scatter_block_func_arg0 = va_arg(argp, const void *);
		void * reduce_scatter_block_func_arg1 = va_arg(argp, void *);
		int reduce_scatter_block_func_arg2 = va_arg(argp, int);
		MPI_Datatype reduce_scatter_block_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op reduce_scatter_block_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm reduce_scatter_block_func_arg5 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Reduce_scatter_block_ptr) (reduce_scatter_block_func_arg0, reduce_scatter_block_func_arg1, reduce_scatter_block_func_arg2, reduce_scatter_block_func_arg3, reduce_scatter_block_func_arg4, reduce_scatter_block_func_arg5,  level, v);
		break;
		 
        // int QMPI_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level, vector *v);\n
     
    case 247:
        va_start(argp,v);
		typedef int (*register_datarep_func) (const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state, int level, vector *v);
		register_datarep_func QMPI_Register_datarep_ptr = (register_datarep_func) func_ptr;
		const char * register_datarep_func_arg0 = va_arg(argp, const char *);
		MPI_Datarep_conversion_function * register_datarep_func_arg1 = va_arg(argp, MPI_Datarep_conversion_function *);
		MPI_Datarep_conversion_function * register_datarep_func_arg2 = va_arg(argp, MPI_Datarep_conversion_function *);
		MPI_Datarep_extent_function * register_datarep_func_arg3 = va_arg(argp, MPI_Datarep_extent_function *);
		void * register_datarep_func_arg4 = va_arg(argp, void *);
		ret = (QMPI_Register_datarep_ptr) (register_datarep_func_arg0, register_datarep_func_arg1, register_datarep_func_arg2, register_datarep_func_arg3, register_datarep_func_arg4,  level, v);
		break;
		 
        // int QMPI_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state, int level, vector *v);\n
     
    case 248:
        va_start(argp,v);
		typedef int (*request_free_func) (MPI_Request *request, int level, vector *v);
		request_free_func QMPI_Request_free_ptr = (request_free_func) func_ptr;
		MPI_Request * request_free_func_arg0 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Request_free_ptr) (request_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Request_free(MPI_Request *request, int level, vector *v);\n
     
    case 249:
        va_start(argp,v);
		typedef int (*request_get_status_func) (MPI_Request request, int *flag, MPI_Status *status, int level, vector *v);
		request_get_status_func QMPI_Request_get_status_ptr = (request_get_status_func) func_ptr;
		MPI_Request request_get_status_func_arg0 = va_arg(argp, MPI_Request);
		int * request_get_status_func_arg1 = va_arg(argp, int *);
		MPI_Status * request_get_status_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Request_get_status_ptr) (request_get_status_func_arg0, request_get_status_func_arg1, request_get_status_func_arg2,  level, v);
		break;
		 
        // int QMPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status, int level, vector *v);\n
     
    case 250:
        va_start(argp,v);
		typedef int (*rget_func) (void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request, int level, vector *v);
		rget_func QMPI_Rget_ptr = (rget_func) func_ptr;
		void * rget_func_arg0 = va_arg(argp, void *);
		int rget_func_arg1 = va_arg(argp, int);
		MPI_Datatype rget_func_arg2 = va_arg(argp, MPI_Datatype);
		int rget_func_arg3 = va_arg(argp, int);
		MPI_Aint rget_func_arg4 = va_arg(argp, MPI_Aint);
		int rget_func_arg5 = va_arg(argp, int);
		MPI_Datatype rget_func_arg6 = va_arg(argp, MPI_Datatype);
		MPI_Win rget_func_arg7 = va_arg(argp, MPI_Win);
		MPI_Request * rget_func_arg8 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Rget_ptr) (rget_func_arg0, rget_func_arg1, rget_func_arg2, rget_func_arg3, rget_func_arg4, rget_func_arg5, rget_func_arg6, rget_func_arg7, rget_func_arg8,  level, v);
		break;
		 
        // int QMPI_Rget(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request, int level, vector *v);\n
     
    case 251:
        va_start(argp,v);
		typedef int (*rget_accumulate_func) (const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request, int level, vector *v);
		rget_accumulate_func QMPI_Rget_accumulate_ptr = (rget_accumulate_func) func_ptr;
		const void * rget_accumulate_func_arg0 = va_arg(argp, const void *);
		int rget_accumulate_func_arg1 = va_arg(argp, int);
		MPI_Datatype rget_accumulate_func_arg2 = va_arg(argp, MPI_Datatype);
		void * rget_accumulate_func_arg3 = va_arg(argp, void *);
		int rget_accumulate_func_arg4 = va_arg(argp, int);
		MPI_Datatype rget_accumulate_func_arg5 = va_arg(argp, MPI_Datatype);
		int rget_accumulate_func_arg6 = va_arg(argp, int);
		MPI_Aint rget_accumulate_func_arg7 = va_arg(argp, MPI_Aint);
		int rget_accumulate_func_arg8 = va_arg(argp, int);
		MPI_Datatype rget_accumulate_func_arg9 = va_arg(argp, MPI_Datatype);
		MPI_Op rget_accumulate_func_arg10 = va_arg(argp, MPI_Op);
		MPI_Win rget_accumulate_func_arg11 = va_arg(argp, MPI_Win);
		MPI_Request * rget_accumulate_func_arg12 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Rget_accumulate_ptr) (rget_accumulate_func_arg0, rget_accumulate_func_arg1, rget_accumulate_func_arg2, rget_accumulate_func_arg3, rget_accumulate_func_arg4, rget_accumulate_func_arg5, rget_accumulate_func_arg6, rget_accumulate_func_arg7, rget_accumulate_func_arg8, rget_accumulate_func_arg9, rget_accumulate_func_arg10, rget_accumulate_func_arg11, rget_accumulate_func_arg12,  level, v);
		break;
		 
        // int QMPI_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request, int level, vector *v);\n
     
    case 252:
        va_start(argp,v);
		typedef int (*rput_func) (const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_cout, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request, int level, vector *v);
		rput_func QMPI_Rput_ptr = (rput_func) func_ptr;
		const void * rput_func_arg0 = va_arg(argp, const void *);
		int rput_func_arg1 = va_arg(argp, int);
		MPI_Datatype rput_func_arg2 = va_arg(argp, MPI_Datatype);
		int rput_func_arg3 = va_arg(argp, int);
		MPI_Aint rput_func_arg4 = va_arg(argp, MPI_Aint);
		int rput_func_arg5 = va_arg(argp, int);
		MPI_Datatype rput_func_arg6 = va_arg(argp, MPI_Datatype);
		MPI_Win rput_func_arg7 = va_arg(argp, MPI_Win);
		MPI_Request * rput_func_arg8 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Rput_ptr) (rput_func_arg0, rput_func_arg1, rput_func_arg2, rput_func_arg3, rput_func_arg4, rput_func_arg5, rput_func_arg6, rput_func_arg7, rput_func_arg8,  level, v);
		break;
		 
        // int QMPI_Rput(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_cout, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request, int level, vector *v);\n
     
    case 253:
        va_start(argp,v);
		typedef int (*rsend_func) (const void *ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level, vector *v);
		rsend_func QMPI_Rsend_ptr = (rsend_func) func_ptr;
		const void * rsend_func_arg0 = va_arg(argp, const void *);
		int rsend_func_arg1 = va_arg(argp, int);
		MPI_Datatype rsend_func_arg2 = va_arg(argp, MPI_Datatype);
		int rsend_func_arg3 = va_arg(argp, int);
		int rsend_func_arg4 = va_arg(argp, int);
		MPI_Comm rsend_func_arg5 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Rsend_ptr) (rsend_func_arg0, rsend_func_arg1, rsend_func_arg2, rsend_func_arg3, rsend_func_arg4, rsend_func_arg5,  level, v);
		break;
		 
        // int QMPI_Rsend(const void *ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level, vector *v);\n
     
    case 254:
        va_start(argp,v);
		typedef int (*rsend_init_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		rsend_init_func QMPI_Rsend_init_ptr = (rsend_init_func) func_ptr;
		const void * rsend_init_func_arg0 = va_arg(argp, const void *);
		int rsend_init_func_arg1 = va_arg(argp, int);
		MPI_Datatype rsend_init_func_arg2 = va_arg(argp, MPI_Datatype);
		int rsend_init_func_arg3 = va_arg(argp, int);
		int rsend_init_func_arg4 = va_arg(argp, int);
		MPI_Comm rsend_init_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * rsend_init_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Rsend_init_ptr) (rsend_init_func_arg0, rsend_init_func_arg1, rsend_init_func_arg2, rsend_init_func_arg3, rsend_init_func_arg4, rsend_init_func_arg5, rsend_init_func_arg6,  level, v);
		break;
		 
        // int QMPI_Rsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 255:
        va_start(argp,v);
		typedef int (*scan_func) (const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level, vector *v);
		scan_func QMPI_Scan_ptr = (scan_func) func_ptr;
		const void * scan_func_arg0 = va_arg(argp, const void *);
		void * scan_func_arg1 = va_arg(argp, void *);
		int scan_func_arg2 = va_arg(argp, int);
		MPI_Datatype scan_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Op scan_func_arg4 = va_arg(argp, MPI_Op);
		MPI_Comm scan_func_arg5 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Scan_ptr) (scan_func_arg0, scan_func_arg1, scan_func_arg2, scan_func_arg3, scan_func_arg4, scan_func_arg5,  level, v);
		break;
		 
        // int QMPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level, vector *v);\n
     
    case 256:
        va_start(argp,v);
		typedef int (*scatter_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level, vector *v);
		scatter_func QMPI_Scatter_ptr = (scatter_func) func_ptr;
		const void * scatter_func_arg0 = va_arg(argp, const void *);
		int scatter_func_arg1 = va_arg(argp, int);
		MPI_Datatype scatter_func_arg2 = va_arg(argp, MPI_Datatype);
		void * scatter_func_arg3 = va_arg(argp, void *);
		int scatter_func_arg4 = va_arg(argp, int);
		MPI_Datatype scatter_func_arg5 = va_arg(argp, MPI_Datatype);
		int scatter_func_arg6 = va_arg(argp, int);
		MPI_Comm scatter_func_arg7 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Scatter_ptr) (scatter_func_arg0, scatter_func_arg1, scatter_func_arg2, scatter_func_arg3, scatter_func_arg4, scatter_func_arg5, scatter_func_arg6, scatter_func_arg7,  level, v);
		break;
		 
        // int QMPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level, vector *v);\n
     
    case 257:
        va_start(argp,v);
		typedef int (*scatterv_func) (const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level, vector *v);
		scatterv_func QMPI_Scatterv_ptr = (scatterv_func) func_ptr;
		const void * scatterv_func_arg0 = va_arg(argp, const void *);
		const int * scatterv_func_arg1 = va_arg(argp, const int *);
		const int * scatterv_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype scatterv_func_arg3 = va_arg(argp, MPI_Datatype);
		void * scatterv_func_arg4 = va_arg(argp, void *);
		int scatterv_func_arg5 = va_arg(argp, int);
		MPI_Datatype scatterv_func_arg6 = va_arg(argp, MPI_Datatype);
		int scatterv_func_arg7 = va_arg(argp, int);
		MPI_Comm scatterv_func_arg8 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Scatterv_ptr) (scatterv_func_arg0, scatterv_func_arg1, scatterv_func_arg2, scatterv_func_arg3, scatterv_func_arg4, scatterv_func_arg5, scatterv_func_arg6, scatterv_func_arg7, scatterv_func_arg8,  level, v);
		break;
		 
        // int QMPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level, vector *v);\n
     
    case 258:
        va_start(argp,v);
		typedef int (*send_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level, vector *v);
		send_func QMPI_Send_ptr = (send_func) func_ptr;
		const void * send_func_arg0 = va_arg(argp, const void *);
		int send_func_arg1 = va_arg(argp, int);
		MPI_Datatype send_func_arg2 = va_arg(argp, MPI_Datatype);
		int send_func_arg3 = va_arg(argp, int);
		int send_func_arg4 = va_arg(argp, int);
		MPI_Comm send_func_arg5 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Send_ptr) (send_func_arg0, send_func_arg1, send_func_arg2, send_func_arg3, send_func_arg4, send_func_arg5,  level, v);
		break;
		 
        // int QMPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level, vector *v);\n
     
    case 259:
        va_start(argp,v);
		typedef int (*send_init_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		send_init_func QMPI_Send_init_ptr = (send_init_func) func_ptr;
		const void * send_init_func_arg0 = va_arg(argp, const void *);
		int send_init_func_arg1 = va_arg(argp, int);
		MPI_Datatype send_init_func_arg2 = va_arg(argp, MPI_Datatype);
		int send_init_func_arg3 = va_arg(argp, int);
		int send_init_func_arg4 = va_arg(argp, int);
		MPI_Comm send_init_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * send_init_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Send_init_ptr) (send_init_func_arg0, send_init_func_arg1, send_init_func_arg2, send_init_func_arg3, send_init_func_arg4, send_init_func_arg5, send_init_func_arg6,  level, v);
		break;
		 
        // int QMPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 260:
        va_start(argp,v);
		typedef int (*sendrecv_func) (const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status, int level, vector *v);
		sendrecv_func QMPI_Sendrecv_ptr = (sendrecv_func) func_ptr;
		const void * sendrecv_func_arg0 = va_arg(argp, const void *);
		int sendrecv_func_arg1 = va_arg(argp, int);
		MPI_Datatype sendrecv_func_arg2 = va_arg(argp, MPI_Datatype);
		int sendrecv_func_arg3 = va_arg(argp, int);
		int sendrecv_func_arg4 = va_arg(argp, int);
		void * sendrecv_func_arg5 = va_arg(argp, void *);
		int sendrecv_func_arg6 = va_arg(argp, int);
		MPI_Datatype sendrecv_func_arg7 = va_arg(argp, MPI_Datatype);
		int sendrecv_func_arg8 = va_arg(argp, int);
		int sendrecv_func_arg9 = va_arg(argp, int);
		MPI_Comm sendrecv_func_arg10 = va_arg(argp, MPI_Comm);
		MPI_Status * sendrecv_func_arg11 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Sendrecv_ptr) (sendrecv_func_arg0, sendrecv_func_arg1, sendrecv_func_arg2, sendrecv_func_arg3, sendrecv_func_arg4, sendrecv_func_arg5, sendrecv_func_arg6, sendrecv_func_arg7, sendrecv_func_arg8, sendrecv_func_arg9, sendrecv_func_arg10, sendrecv_func_arg11,  level, v);
		break;
		 
        // int QMPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status, int level, vector *v);\n
     
    case 261:
        va_start(argp,v);
		typedef int (*sendrecv_replace_func) (void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status, int level, vector *v);
		sendrecv_replace_func QMPI_Sendrecv_replace_ptr = (sendrecv_replace_func) func_ptr;
		void * sendrecv_replace_func_arg0 = va_arg(argp, void *);
		int sendrecv_replace_func_arg1 = va_arg(argp, int);
		MPI_Datatype sendrecv_replace_func_arg2 = va_arg(argp, MPI_Datatype);
		int sendrecv_replace_func_arg3 = va_arg(argp, int);
		int sendrecv_replace_func_arg4 = va_arg(argp, int);
		int sendrecv_replace_func_arg5 = va_arg(argp, int);
		int sendrecv_replace_func_arg6 = va_arg(argp, int);
		MPI_Comm sendrecv_replace_func_arg7 = va_arg(argp, MPI_Comm);
		MPI_Status * sendrecv_replace_func_arg8 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Sendrecv_replace_ptr) (sendrecv_replace_func_arg0, sendrecv_replace_func_arg1, sendrecv_replace_func_arg2, sendrecv_replace_func_arg3, sendrecv_replace_func_arg4, sendrecv_replace_func_arg5, sendrecv_replace_func_arg6, sendrecv_replace_func_arg7, sendrecv_replace_func_arg8,  level, v);
		break;
		 
        // int QMPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status, int level, vector *v);\n
     
    case 262:
        va_start(argp,v);
		typedef int (*ssend_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level, vector *v);
		ssend_func QMPI_Ssend_ptr = (ssend_func) func_ptr;
		const void * ssend_func_arg0 = va_arg(argp, const void *);
		int ssend_func_arg1 = va_arg(argp, int);
		MPI_Datatype ssend_func_arg2 = va_arg(argp, MPI_Datatype);
		int ssend_func_arg3 = va_arg(argp, int);
		int ssend_func_arg4 = va_arg(argp, int);
		MPI_Comm ssend_func_arg5 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Ssend_ptr) (ssend_func_arg0, ssend_func_arg1, ssend_func_arg2, ssend_func_arg3, ssend_func_arg4, ssend_func_arg5,  level, v);
		break;
		 
        // int QMPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level, vector *v);\n
     
    case 263:
        va_start(argp,v);
		typedef int (*ssend_init_func) (const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);
		ssend_init_func QMPI_Ssend_init_ptr = (ssend_init_func) func_ptr;
		const void * ssend_init_func_arg0 = va_arg(argp, const void *);
		int ssend_init_func_arg1 = va_arg(argp, int);
		MPI_Datatype ssend_init_func_arg2 = va_arg(argp, MPI_Datatype);
		int ssend_init_func_arg3 = va_arg(argp, int);
		int ssend_init_func_arg4 = va_arg(argp, int);
		MPI_Comm ssend_init_func_arg5 = va_arg(argp, MPI_Comm);
		MPI_Request * ssend_init_func_arg6 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Ssend_init_ptr) (ssend_init_func_arg0, ssend_init_func_arg1, ssend_init_func_arg2, ssend_init_func_arg3, ssend_init_func_arg4, ssend_init_func_arg5, ssend_init_func_arg6,  level, v);
		break;
		 
        // int QMPI_Ssend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level, vector *v);\n
     
    case 264:
        va_start(argp,v);
		typedef int (*start_func) (MPI_Request *request, int level, vector *v);
		start_func QMPI_Start_ptr = (start_func) func_ptr;
		MPI_Request * start_func_arg0 = va_arg(argp, MPI_Request *);
		ret = (QMPI_Start_ptr) (start_func_arg0,  level, v);
		break;
		 
        // int QMPI_Start(MPI_Request *request, int level, vector *v);\n
     
    case 265:
        va_start(argp,v);
		typedef int (*startall_func) (int count, MPI_Request array_of_requests[], int level, vector *v);
		startall_func QMPI_Startall_ptr = (startall_func) func_ptr;
		int startall_func_arg0 = va_arg(argp, int);
		MPI_Request* startall_func_arg1 = va_arg(argp, MPI_Request*);
		ret = (QMPI_Startall_ptr) (startall_func_arg0, startall_func_arg1,  level, v);
		break;
		 
        // int QMPI_Startall(int count, MPI_Request array_of_requests[], int level, vector *v);\n
     
    case 266:
        va_start(argp,v);
		typedef int (*status_set_cancelled_func) (MPI_Status *status, int flag, int level, vector *v);
		status_set_cancelled_func QMPI_Status_set_cancelled_ptr = (status_set_cancelled_func) func_ptr;
		MPI_Status * status_set_cancelled_func_arg0 = va_arg(argp, MPI_Status *);
		int status_set_cancelled_func_arg1 = va_arg(argp, int);
		ret = (QMPI_Status_set_cancelled_ptr) (status_set_cancelled_func_arg0, status_set_cancelled_func_arg1,  level, v);
		break;
		 
        // int QMPI_Status_set_cancelled(MPI_Status *status, int flag, int level, vector *v);\n
     
    case 267:
        va_start(argp,v);
		typedef int (*status_set_elements_func) (MPI_Status *status, MPI_Datatype datatype, int count, int level, vector *v);
		status_set_elements_func QMPI_Status_set_elements_ptr = (status_set_elements_func) func_ptr;
		MPI_Status * status_set_elements_func_arg0 = va_arg(argp, MPI_Status *);
		MPI_Datatype status_set_elements_func_arg1 = va_arg(argp, MPI_Datatype);
		int status_set_elements_func_arg2 = va_arg(argp, int);
		ret = (QMPI_Status_set_elements_ptr) (status_set_elements_func_arg0, status_set_elements_func_arg1, status_set_elements_func_arg2,  level, v);
		break;
		 
        // int QMPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count, int level, vector *v);\n
     
    case 268:
        va_start(argp,v);
		typedef int (*status_set_elements_x_func) (MPI_Status *status, MPI_Datatype datatype, MPI_Count count, int level, vector *v);
		status_set_elements_x_func QMPI_Status_set_elements_x_ptr = (status_set_elements_x_func) func_ptr;
		MPI_Status * status_set_elements_x_func_arg0 = va_arg(argp, MPI_Status *);
		MPI_Datatype status_set_elements_x_func_arg1 = va_arg(argp, MPI_Datatype);
		MPI_Count status_set_elements_x_func_arg2 = va_arg(argp, MPI_Count);
		ret = (QMPI_Status_set_elements_x_ptr) (status_set_elements_x_func_arg0, status_set_elements_x_func_arg1, status_set_elements_x_func_arg2,  level, v);
		break;
		 
        // int QMPI_Status_set_elements_x(MPI_Status *status, MPI_Datatype datatype, MPI_Count count, int level, vector *v);\n
     
    case 269:
        va_start(argp,v);
		typedef int (*test_func) (MPI_Request *request, int *flag, MPI_Status *status, int level, vector *v);
		test_func QMPI_Test_ptr = (test_func) func_ptr;
		MPI_Request * test_func_arg0 = va_arg(argp, MPI_Request *);
		int * test_func_arg1 = va_arg(argp, int *);
		MPI_Status * test_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Test_ptr) (test_func_arg0, test_func_arg1, test_func_arg2,  level, v);
		break;
		 
        // int QMPI_Test(MPI_Request *request, int *flag, MPI_Status *status, int level, vector *v);\n
     
    case 270:
        va_start(argp,v);
		typedef int (*test_cancelled_func) (const MPI_Status *status, int *flag, int level, vector *v);
		test_cancelled_func QMPI_Test_cancelled_ptr = (test_cancelled_func) func_ptr;
		const MPI_Status * test_cancelled_func_arg0 = va_arg(argp, const MPI_Status *);
		int * test_cancelled_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Test_cancelled_ptr) (test_cancelled_func_arg0, test_cancelled_func_arg1,  level, v);
		break;
		 
        // int QMPI_Test_cancelled(const MPI_Status *status, int *flag, int level, vector *v);\n
     
    case 271:
        va_start(argp,v);
		typedef int (*testall_func) (int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[], int level, vector *v);
		testall_func QMPI_Testall_ptr = (testall_func) func_ptr;
		int testall_func_arg0 = va_arg(argp, int);
		MPI_Request* testall_func_arg1 = va_arg(argp, MPI_Request*);
		int * testall_func_arg2 = va_arg(argp, int *);
		MPI_Status* testall_func_arg3 = va_arg(argp, MPI_Status*);
		ret = (QMPI_Testall_ptr) (testall_func_arg0, testall_func_arg1, testall_func_arg2, testall_func_arg3,  level, v);
		break;
		 
        // int QMPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[], int level, vector *v);\n
     
    case 272:
        va_start(argp,v);
		typedef int (*testany_func) (int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status, int level, vector *v);
		testany_func QMPI_Testany_ptr = (testany_func) func_ptr;
		int testany_func_arg0 = va_arg(argp, int);
		MPI_Request* testany_func_arg1 = va_arg(argp, MPI_Request*);
		int * testany_func_arg2 = va_arg(argp, int *);
		int * testany_func_arg3 = va_arg(argp, int *);
		MPI_Status * testany_func_arg4 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Testany_ptr) (testany_func_arg0, testany_func_arg1, testany_func_arg2, testany_func_arg3, testany_func_arg4,  level, v);
		break;
		 
        // int QMPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status, int level, vector *v);\n
     
    case 273:
        va_start(argp,v);
		typedef int (*testsome_func) (int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[], int level, vector *v);
		testsome_func QMPI_Testsome_ptr = (testsome_func) func_ptr;
		int testsome_func_arg0 = va_arg(argp, int);
		MPI_Request* testsome_func_arg1 = va_arg(argp, MPI_Request*);
		int * testsome_func_arg2 = va_arg(argp, int *);
		int* testsome_func_arg3 = va_arg(argp, int*);
		MPI_Status* testsome_func_arg4 = va_arg(argp, MPI_Status*);
		ret = (QMPI_Testsome_ptr) (testsome_func_arg0, testsome_func_arg1, testsome_func_arg2, testsome_func_arg3, testsome_func_arg4,  level, v);
		break;
		 
        // int QMPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[], int level, vector *v);\n
     
    case 274:
        va_start(argp,v);
		typedef int (*topo_test_func) (MPI_Comm comm, int *status, int level, vector *v);
		topo_test_func QMPI_Topo_test_ptr = (topo_test_func) func_ptr;
		MPI_Comm topo_test_func_arg0 = va_arg(argp, MPI_Comm);
		int * topo_test_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Topo_test_ptr) (topo_test_func_arg0, topo_test_func_arg1,  level, v);
		break;
		 
        // int QMPI_Topo_test(MPI_Comm comm, int *status, int level, vector *v);\n
     
    case 275:
        va_start(argp,v);
		typedef int (*type_commit_func) (MPI_Datatype *type, int level, vector *v);
		type_commit_func QMPI_Type_commit_ptr = (type_commit_func) func_ptr;
		MPI_Datatype * type_commit_func_arg0 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_commit_ptr) (type_commit_func_arg0,  level, v);
		break;
		 
        // int QMPI_Type_commit(MPI_Datatype *type, int level, vector *v);\n
     
    case 276:
        va_start(argp,v);
		typedef int (*type_contiguous_func) (int count, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_contiguous_func QMPI_Type_contiguous_ptr = (type_contiguous_func) func_ptr;
		int type_contiguous_func_arg0 = va_arg(argp, int);
		MPI_Datatype type_contiguous_func_arg1 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_contiguous_func_arg2 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_contiguous_ptr) (type_contiguous_func_arg0, type_contiguous_func_arg1, type_contiguous_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 277:
        va_start(argp,v);
		typedef int (*type_create_darray_func) (int size, int rank, int ndims, const int gsize_array[], const int distrib_array[], const int darg_array[], const int psize_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_create_darray_func QMPI_Type_create_darray_ptr = (type_create_darray_func) func_ptr;
		int type_create_darray_func_arg0 = va_arg(argp, int);
		int type_create_darray_func_arg1 = va_arg(argp, int);
		int type_create_darray_func_arg2 = va_arg(argp, int);
		const int * type_create_darray_func_arg3 = va_arg(argp, const int *);
		const int * type_create_darray_func_arg4 = va_arg(argp, const int *);
		const int * type_create_darray_func_arg5 = va_arg(argp, const int *);
		const int * type_create_darray_func_arg6 = va_arg(argp, const int *);
		int type_create_darray_func_arg7 = va_arg(argp, int);
		MPI_Datatype type_create_darray_func_arg8 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_create_darray_func_arg9 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_darray_ptr) (type_create_darray_func_arg0, type_create_darray_func_arg1, type_create_darray_func_arg2, type_create_darray_func_arg3, type_create_darray_func_arg4, type_create_darray_func_arg5, type_create_darray_func_arg6, type_create_darray_func_arg7, type_create_darray_func_arg8, type_create_darray_func_arg9,  level, v);
		break;
		 
        // int QMPI_Type_create_darray(int size, int rank, int ndims, const int gsize_array[], const int distrib_array[], const int darg_array[], const int psize_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 278:
        va_start(argp,v);
		typedef int (*type_create_f90_complex_func) (int p, int r, MPI_Datatype *newtype, int level, vector *v);
		type_create_f90_complex_func QMPI_Type_create_f90_complex_ptr = (type_create_f90_complex_func) func_ptr;
		int type_create_f90_complex_func_arg0 = va_arg(argp, int);
		int type_create_f90_complex_func_arg1 = va_arg(argp, int);
		MPI_Datatype * type_create_f90_complex_func_arg2 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_f90_complex_ptr) (type_create_f90_complex_func_arg0, type_create_f90_complex_func_arg1, type_create_f90_complex_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 279:
        va_start(argp,v);
		typedef int (*type_create_f90_integer_func) (int r, MPI_Datatype *newtype, int level, vector *v);
		type_create_f90_integer_func QMPI_Type_create_f90_integer_ptr = (type_create_f90_integer_func) func_ptr;
		int type_create_f90_integer_func_arg0 = va_arg(argp, int);
		MPI_Datatype * type_create_f90_integer_func_arg1 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_f90_integer_ptr) (type_create_f90_integer_func_arg0, type_create_f90_integer_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_create_f90_integer(int r, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 280:
        va_start(argp,v);
		typedef int (*type_create_f90_real_func) (int p, int r, MPI_Datatype *newtype, int level, vector *v);
		type_create_f90_real_func QMPI_Type_create_f90_real_ptr = (type_create_f90_real_func) func_ptr;
		int type_create_f90_real_func_arg0 = va_arg(argp, int);
		int type_create_f90_real_func_arg1 = va_arg(argp, int);
		MPI_Datatype * type_create_f90_real_func_arg2 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_f90_real_ptr) (type_create_f90_real_func_arg0, type_create_f90_real_func_arg1, type_create_f90_real_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 281:
        va_start(argp,v);
		typedef int (*type_create_hindexed_func) (int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_create_hindexed_func QMPI_Type_create_hindexed_ptr = (type_create_hindexed_func) func_ptr;
		int type_create_hindexed_func_arg0 = va_arg(argp, int);
		const int * type_create_hindexed_func_arg1 = va_arg(argp, const int *);
		const MPI_Aint * type_create_hindexed_func_arg2 = va_arg(argp, const MPI_Aint *);
		MPI_Datatype type_create_hindexed_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_create_hindexed_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_hindexed_ptr) (type_create_hindexed_func_arg0, type_create_hindexed_func_arg1, type_create_hindexed_func_arg2, type_create_hindexed_func_arg3, type_create_hindexed_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 282:
        va_start(argp,v);
		typedef int (*type_create_hindexed_block_func) (int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_create_hindexed_block_func QMPI_Type_create_hindexed_block_ptr = (type_create_hindexed_block_func) func_ptr;
		int type_create_hindexed_block_func_arg0 = va_arg(argp, int);
		int type_create_hindexed_block_func_arg1 = va_arg(argp, int);
		const MPI_Aint * type_create_hindexed_block_func_arg2 = va_arg(argp, const MPI_Aint *);
		MPI_Datatype type_create_hindexed_block_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_create_hindexed_block_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_hindexed_block_ptr) (type_create_hindexed_block_func_arg0, type_create_hindexed_block_func_arg1, type_create_hindexed_block_func_arg2, type_create_hindexed_block_func_arg3, type_create_hindexed_block_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 283:
        va_start(argp,v);
		typedef int (*type_create_hvector_func) (int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_create_hvector_func QMPI_Type_create_hvector_ptr = (type_create_hvector_func) func_ptr;
		int type_create_hvector_func_arg0 = va_arg(argp, int);
		int type_create_hvector_func_arg1 = va_arg(argp, int);
		MPI_Aint type_create_hvector_func_arg2 = va_arg(argp, MPI_Aint);
		MPI_Datatype type_create_hvector_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_create_hvector_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_hvector_ptr) (type_create_hvector_func_arg0, type_create_hvector_func_arg1, type_create_hvector_func_arg2, type_create_hvector_func_arg3, type_create_hvector_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 284:
        va_start(argp,v);
		typedef int (*type_create_indexed_block_func) (int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_create_indexed_block_func QMPI_Type_create_indexed_block_ptr = (type_create_indexed_block_func) func_ptr;
		int type_create_indexed_block_func_arg0 = va_arg(argp, int);
		int type_create_indexed_block_func_arg1 = va_arg(argp, int);
		const int * type_create_indexed_block_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype type_create_indexed_block_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_create_indexed_block_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_indexed_block_ptr) (type_create_indexed_block_func_arg0, type_create_indexed_block_func_arg1, type_create_indexed_block_func_arg2, type_create_indexed_block_func_arg3, type_create_indexed_block_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 285:
        va_start(argp,v);
		typedef int (*type_create_keyval_func) (MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state, int level, vector *v);
		type_create_keyval_func QMPI_Type_create_keyval_ptr = (type_create_keyval_func) func_ptr;
		MPI_Type_copy_attr_function * type_create_keyval_func_arg0 = va_arg(argp, MPI_Type_copy_attr_function *);
		MPI_Type_delete_attr_function * type_create_keyval_func_arg1 = va_arg(argp, MPI_Type_delete_attr_function *);
		int * type_create_keyval_func_arg2 = va_arg(argp, int *);
		void * type_create_keyval_func_arg3 = va_arg(argp, void *);
		ret = (QMPI_Type_create_keyval_ptr) (type_create_keyval_func_arg0, type_create_keyval_func_arg1, type_create_keyval_func_arg2, type_create_keyval_func_arg3,  level, v);
		break;
		 
        // int QMPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state, int level, vector *v);\n
     
    case 286:
        va_start(argp,v);
		typedef int (*type_create_resized_func) (MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype, int level, vector *v);
		type_create_resized_func QMPI_Type_create_resized_ptr = (type_create_resized_func) func_ptr;
		MPI_Datatype type_create_resized_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Aint type_create_resized_func_arg1 = va_arg(argp, MPI_Aint);
		MPI_Aint type_create_resized_func_arg2 = va_arg(argp, MPI_Aint);
		MPI_Datatype * type_create_resized_func_arg3 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_resized_ptr) (type_create_resized_func_arg0, type_create_resized_func_arg1, type_create_resized_func_arg2, type_create_resized_func_arg3,  level, v);
		break;
		 
        // int QMPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 287:
        va_start(argp,v);
		typedef int (*type_create_struct_func) (int count, const int array_of_block_lengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype, int level, vector *v);
		type_create_struct_func QMPI_Type_create_struct_ptr = (type_create_struct_func) func_ptr;
		int type_create_struct_func_arg0 = va_arg(argp, int);
		const int * type_create_struct_func_arg1 = va_arg(argp, const int *);
		const MPI_Aint * type_create_struct_func_arg2 = va_arg(argp, const MPI_Aint *);
		const MPI_Datatype * type_create_struct_func_arg3 = va_arg(argp, const MPI_Datatype *);
		MPI_Datatype * type_create_struct_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_struct_ptr) (type_create_struct_func_arg0, type_create_struct_func_arg1, type_create_struct_func_arg2, type_create_struct_func_arg3, type_create_struct_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_create_struct(int count, const int array_of_block_lengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype, int level, vector *v);\n
     
    case 288:
        va_start(argp,v);
		typedef int (*type_create_subarray_func) (int ndims, const int size_array[], const int subsize_array[], const int start_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_create_subarray_func QMPI_Type_create_subarray_ptr = (type_create_subarray_func) func_ptr;
		int type_create_subarray_func_arg0 = va_arg(argp, int);
		const int * type_create_subarray_func_arg1 = va_arg(argp, const int *);
		const int * type_create_subarray_func_arg2 = va_arg(argp, const int *);
		const int * type_create_subarray_func_arg3 = va_arg(argp, const int *);
		int type_create_subarray_func_arg4 = va_arg(argp, int);
		MPI_Datatype type_create_subarray_func_arg5 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_create_subarray_func_arg6 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_create_subarray_ptr) (type_create_subarray_func_arg0, type_create_subarray_func_arg1, type_create_subarray_func_arg2, type_create_subarray_func_arg3, type_create_subarray_func_arg4, type_create_subarray_func_arg5, type_create_subarray_func_arg6,  level, v);
		break;
		 
        // int QMPI_Type_create_subarray(int ndims, const int size_array[], const int subsize_array[], const int start_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 289:
        va_start(argp,v);
		typedef int (*type_delete_attr_func) (MPI_Datatype type, int type_keyval, int level, vector *v);
		type_delete_attr_func QMPI_Type_delete_attr_ptr = (type_delete_attr_func) func_ptr;
		MPI_Datatype type_delete_attr_func_arg0 = va_arg(argp, MPI_Datatype);
		int type_delete_attr_func_arg1 = va_arg(argp, int);
		ret = (QMPI_Type_delete_attr_ptr) (type_delete_attr_func_arg0, type_delete_attr_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_delete_attr(MPI_Datatype type, int type_keyval, int level, vector *v);\n
     
    case 290:
        va_start(argp,v);
		typedef int (*type_dup_func) (MPI_Datatype type, MPI_Datatype *newtype, int level, vector *v);
		type_dup_func QMPI_Type_dup_ptr = (type_dup_func) func_ptr;
		MPI_Datatype type_dup_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_dup_func_arg1 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_dup_ptr) (type_dup_func_arg0, type_dup_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_dup(MPI_Datatype type, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 291:
        va_start(argp,v);
		typedef int (*type_extent_func) (MPI_Datatype type, MPI_Aint *extent, int level, vector *v);
		type_extent_func QMPI_Type_extent_ptr = (type_extent_func) func_ptr;
		MPI_Datatype type_extent_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Aint * type_extent_func_arg1 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_Type_extent_ptr) (type_extent_func_arg0, type_extent_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_extent(MPI_Datatype type, MPI_Aint *extent, int level, vector *v);\n
     
    case 292:
        va_start(argp,v);
		typedef int (*type_free_func) (MPI_Datatype *type, int level, vector *v);
		type_free_func QMPI_Type_free_ptr = (type_free_func) func_ptr;
		MPI_Datatype * type_free_func_arg0 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_free_ptr) (type_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Type_free(MPI_Datatype *type, int level, vector *v);\n
     
    case 293:
        va_start(argp,v);
		typedef int (*type_free_keyval_func) (int *type_keyval, int level, vector *v);
		type_free_keyval_func QMPI_Type_free_keyval_ptr = (type_free_keyval_func) func_ptr;
		int * type_free_keyval_func_arg0 = va_arg(argp, int *);
		ret = (QMPI_Type_free_keyval_ptr) (type_free_keyval_func_arg0,  level, v);
		break;
		 
        // int QMPI_Type_free_keyval(int *type_keyval, int level, vector *v);\n
     
    case 294:
        va_start(argp,v);
		typedef int (*type_get_attr_func) (MPI_Datatype type, int type_keyval, void *attribute_val, int *flag, int level, vector *v);
		type_get_attr_func QMPI_Type_get_attr_ptr = (type_get_attr_func) func_ptr;
		MPI_Datatype type_get_attr_func_arg0 = va_arg(argp, MPI_Datatype);
		int type_get_attr_func_arg1 = va_arg(argp, int);
		void * type_get_attr_func_arg2 = va_arg(argp, void *);
		int * type_get_attr_func_arg3 = va_arg(argp, int *);
		ret = (QMPI_Type_get_attr_ptr) (type_get_attr_func_arg0, type_get_attr_func_arg1, type_get_attr_func_arg2, type_get_attr_func_arg3,  level, v);
		break;
		 
        // int QMPI_Type_get_attr(MPI_Datatype type, int type_keyval, void *attribute_val, int *flag, int level, vector *v);\n
     
    case 295:
        va_start(argp,v);
		typedef int (*type_get_contents_func) (MPI_Datatype mtype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[], int level, vector *v);
		type_get_contents_func QMPI_Type_get_contents_ptr = (type_get_contents_func) func_ptr;
		MPI_Datatype type_get_contents_func_arg0 = va_arg(argp, MPI_Datatype);
		int type_get_contents_func_arg1 = va_arg(argp, int);
		int type_get_contents_func_arg2 = va_arg(argp, int);
		int type_get_contents_func_arg3 = va_arg(argp, int);
		int* type_get_contents_func_arg4 = va_arg(argp, int*);
		MPI_Aint* type_get_contents_func_arg5 = va_arg(argp, MPI_Aint*);
		MPI_Datatype* type_get_contents_func_arg6 = va_arg(argp, MPI_Datatype*);
		ret = (QMPI_Type_get_contents_ptr) (type_get_contents_func_arg0, type_get_contents_func_arg1, type_get_contents_func_arg2, type_get_contents_func_arg3, type_get_contents_func_arg4, type_get_contents_func_arg5, type_get_contents_func_arg6,  level, v);
		break;
		 
        // int QMPI_Type_get_contents(MPI_Datatype mtype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[], int level, vector *v);\n
     
    case 296:
        va_start(argp,v);
		typedef int (*type_get_envelope_func) (MPI_Datatype type, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner, int level, vector *v);
		type_get_envelope_func QMPI_Type_get_envelope_ptr = (type_get_envelope_func) func_ptr;
		MPI_Datatype type_get_envelope_func_arg0 = va_arg(argp, MPI_Datatype);
		int * type_get_envelope_func_arg1 = va_arg(argp, int *);
		int * type_get_envelope_func_arg2 = va_arg(argp, int *);
		int * type_get_envelope_func_arg3 = va_arg(argp, int *);
		int * type_get_envelope_func_arg4 = va_arg(argp, int *);
		ret = (QMPI_Type_get_envelope_ptr) (type_get_envelope_func_arg0, type_get_envelope_func_arg1, type_get_envelope_func_arg2, type_get_envelope_func_arg3, type_get_envelope_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_get_envelope(MPI_Datatype type, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner, int level, vector *v);\n
     
    case 297:
        va_start(argp,v);
		typedef int (*type_get_extent_func) (MPI_Datatype type, MPI_Aint *lb, MPI_Aint *extent, int level, vector *v);
		type_get_extent_func QMPI_Type_get_extent_ptr = (type_get_extent_func) func_ptr;
		MPI_Datatype type_get_extent_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Aint * type_get_extent_func_arg1 = va_arg(argp, MPI_Aint *);
		MPI_Aint * type_get_extent_func_arg2 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_Type_get_extent_ptr) (type_get_extent_func_arg0, type_get_extent_func_arg1, type_get_extent_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_get_extent(MPI_Datatype type, MPI_Aint *lb, MPI_Aint *extent, int level, vector *v);\n
     
    case 298:
        va_start(argp,v);
		typedef int (*type_get_extent_x_func) (MPI_Datatype type, MPI_Count *lb, MPI_Count *extent, int level, vector *v);
		type_get_extent_x_func QMPI_Type_get_extent_x_ptr = (type_get_extent_x_func) func_ptr;
		MPI_Datatype type_get_extent_x_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Count * type_get_extent_x_func_arg1 = va_arg(argp, MPI_Count *);
		MPI_Count * type_get_extent_x_func_arg2 = va_arg(argp, MPI_Count *);
		ret = (QMPI_Type_get_extent_x_ptr) (type_get_extent_x_func_arg0, type_get_extent_x_func_arg1, type_get_extent_x_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_get_extent_x(MPI_Datatype type, MPI_Count *lb, MPI_Count *extent, int level, vector *v);\n
     
    case 299:
        va_start(argp,v);
		typedef int (*type_get_name_func) (MPI_Datatype type, char *type_name, int *resultlen, int level, vector *v);
		type_get_name_func QMPI_Type_get_name_ptr = (type_get_name_func) func_ptr;
		MPI_Datatype type_get_name_func_arg0 = va_arg(argp, MPI_Datatype);
		char * type_get_name_func_arg1 = va_arg(argp, char *);
		int * type_get_name_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Type_get_name_ptr) (type_get_name_func_arg0, type_get_name_func_arg1, type_get_name_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_get_name(MPI_Datatype type, char *type_name, int *resultlen, int level, vector *v);\n
     
    case 300:
        va_start(argp,v);
		typedef int (*type_get_true_extent_func) (MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent, int level, vector *v);
		type_get_true_extent_func QMPI_Type_get_true_extent_ptr = (type_get_true_extent_func) func_ptr;
		MPI_Datatype type_get_true_extent_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Aint * type_get_true_extent_func_arg1 = va_arg(argp, MPI_Aint *);
		MPI_Aint * type_get_true_extent_func_arg2 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_Type_get_true_extent_ptr) (type_get_true_extent_func_arg0, type_get_true_extent_func_arg1, type_get_true_extent_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent, int level, vector *v);\n
     
    case 301:
        va_start(argp,v);
		typedef int (*type_get_true_extent_x_func) (MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent, int level, vector *v);
		type_get_true_extent_x_func QMPI_Type_get_true_extent_x_ptr = (type_get_true_extent_x_func) func_ptr;
		MPI_Datatype type_get_true_extent_x_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Count * type_get_true_extent_x_func_arg1 = va_arg(argp, MPI_Count *);
		MPI_Count * type_get_true_extent_x_func_arg2 = va_arg(argp, MPI_Count *);
		ret = (QMPI_Type_get_true_extent_x_ptr) (type_get_true_extent_x_func_arg0, type_get_true_extent_x_func_arg1, type_get_true_extent_x_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent, int level, vector *v);\n
     
    case 302:
        va_start(argp,v);
		typedef int (*type_hindexed_func) (int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_hindexed_func QMPI_Type_hindexed_ptr = (type_hindexed_func) func_ptr;
		int type_hindexed_func_arg0 = va_arg(argp, int);
		int* type_hindexed_func_arg1 = va_arg(argp, int*);
		MPI_Aint* type_hindexed_func_arg2 = va_arg(argp, MPI_Aint*);
		MPI_Datatype type_hindexed_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_hindexed_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_hindexed_ptr) (type_hindexed_func_arg0, type_hindexed_func_arg1, type_hindexed_func_arg2, type_hindexed_func_arg3, type_hindexed_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 303:
        va_start(argp,v);
		typedef int (*type_hvector_func) (int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_hvector_func QMPI_Type_hvector_ptr = (type_hvector_func) func_ptr;
		int type_hvector_func_arg0 = va_arg(argp, int);
		int type_hvector_func_arg1 = va_arg(argp, int);
		MPI_Aint type_hvector_func_arg2 = va_arg(argp, MPI_Aint);
		MPI_Datatype type_hvector_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_hvector_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_hvector_ptr) (type_hvector_func_arg0, type_hvector_func_arg1, type_hvector_func_arg2, type_hvector_func_arg3, type_hvector_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 304:
        va_start(argp,v);
		typedef int (*type_indexed_func) (int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_indexed_func QMPI_Type_indexed_ptr = (type_indexed_func) func_ptr;
		int type_indexed_func_arg0 = va_arg(argp, int);
		const int * type_indexed_func_arg1 = va_arg(argp, const int *);
		const int * type_indexed_func_arg2 = va_arg(argp, const int *);
		MPI_Datatype type_indexed_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_indexed_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_indexed_ptr) (type_indexed_func_arg0, type_indexed_func_arg1, type_indexed_func_arg2, type_indexed_func_arg3, type_indexed_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 305:
        va_start(argp,v);
		typedef int (*type_lb_func) (MPI_Datatype type, MPI_Aint *lb, int level, vector *v);
		type_lb_func QMPI_Type_lb_ptr = (type_lb_func) func_ptr;
		MPI_Datatype type_lb_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Aint * type_lb_func_arg1 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_Type_lb_ptr) (type_lb_func_arg0, type_lb_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_lb(MPI_Datatype type, MPI_Aint *lb, int level, vector *v);\n
     
    case 306:
        va_start(argp,v);
		typedef int (*type_match_size_func) (int typeclass, int size, MPI_Datatype *type, int level, vector *v);
		type_match_size_func QMPI_Type_match_size_ptr = (type_match_size_func) func_ptr;
		int type_match_size_func_arg0 = va_arg(argp, int);
		int type_match_size_func_arg1 = va_arg(argp, int);
		MPI_Datatype * type_match_size_func_arg2 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_match_size_ptr) (type_match_size_func_arg0, type_match_size_func_arg1, type_match_size_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_match_size(int typeclass, int size, MPI_Datatype *type, int level, vector *v);\n
     
    case 307:
        va_start(argp,v);
		typedef int (*type_set_attr_func) (MPI_Datatype type, int type_keyval, void *attr_val, int level, vector *v);
		type_set_attr_func QMPI_Type_set_attr_ptr = (type_set_attr_func) func_ptr;
		MPI_Datatype type_set_attr_func_arg0 = va_arg(argp, MPI_Datatype);
		int type_set_attr_func_arg1 = va_arg(argp, int);
		void * type_set_attr_func_arg2 = va_arg(argp, void *);
		ret = (QMPI_Type_set_attr_ptr) (type_set_attr_func_arg0, type_set_attr_func_arg1, type_set_attr_func_arg2,  level, v);
		break;
		 
        // int QMPI_Type_set_attr(MPI_Datatype type, int type_keyval, void *attr_val, int level, vector *v);\n
     
    case 308:
        va_start(argp,v);
		typedef int (*type_set_name_func) (MPI_Datatype type, const char *type_name, int level, vector *v);
		type_set_name_func QMPI_Type_set_name_ptr = (type_set_name_func) func_ptr;
		MPI_Datatype type_set_name_func_arg0 = va_arg(argp, MPI_Datatype);
		const char * type_set_name_func_arg1 = va_arg(argp, const char *);
		ret = (QMPI_Type_set_name_ptr) (type_set_name_func_arg0, type_set_name_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_set_name(MPI_Datatype type, const char *type_name, int level, vector *v);\n
     
    case 309:
        va_start(argp,v);
		typedef int (*type_size_func) (MPI_Datatype type, int *size, int level, vector *v);
		type_size_func QMPI_Type_size_ptr = (type_size_func) func_ptr;
		MPI_Datatype type_size_func_arg0 = va_arg(argp, MPI_Datatype);
		int * type_size_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Type_size_ptr) (type_size_func_arg0, type_size_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_size(MPI_Datatype type, int *size, int level, vector *v);\n
     
    case 310:
        va_start(argp,v);
		typedef int (*type_size_x_func) (MPI_Datatype type, MPI_Count *size, int level, vector *v);
		type_size_x_func QMPI_Type_size_x_ptr = (type_size_x_func) func_ptr;
		MPI_Datatype type_size_x_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Count * type_size_x_func_arg1 = va_arg(argp, MPI_Count *);
		ret = (QMPI_Type_size_x_ptr) (type_size_x_func_arg0, type_size_x_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_size_x(MPI_Datatype type, MPI_Count *size, int level, vector *v);\n
     
    case 311:
        va_start(argp,v);
		typedef int (*type_struct_func) (int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype, int level, vector *v);
		type_struct_func QMPI_Type_struct_ptr = (type_struct_func) func_ptr;
		int type_struct_func_arg0 = va_arg(argp, int);
		int* type_struct_func_arg1 = va_arg(argp, int*);
		MPI_Aint* type_struct_func_arg2 = va_arg(argp, MPI_Aint*);
		MPI_Datatype* type_struct_func_arg3 = va_arg(argp, MPI_Datatype*);
		MPI_Datatype * type_struct_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_struct_ptr) (type_struct_func_arg0, type_struct_func_arg1, type_struct_func_arg2, type_struct_func_arg3, type_struct_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_struct(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype, int level, vector *v);\n
     
    case 312:
        va_start(argp,v);
		typedef int (*type_ub_func) (MPI_Datatype mtype, MPI_Aint *ub, int level, vector *v);
		type_ub_func QMPI_Type_ub_ptr = (type_ub_func) func_ptr;
		MPI_Datatype type_ub_func_arg0 = va_arg(argp, MPI_Datatype);
		MPI_Aint * type_ub_func_arg1 = va_arg(argp, MPI_Aint *);
		ret = (QMPI_Type_ub_ptr) (type_ub_func_arg0, type_ub_func_arg1,  level, v);
		break;
		 
        // int QMPI_Type_ub(MPI_Datatype mtype, MPI_Aint *ub, int level, vector *v);\n
     
    case 313:
        va_start(argp,v);
		typedef int (*type_vector_func) (int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);
		type_vector_func QMPI_Type_vector_ptr = (type_vector_func) func_ptr;
		int type_vector_func_arg0 = va_arg(argp, int);
		int type_vector_func_arg1 = va_arg(argp, int);
		int type_vector_func_arg2 = va_arg(argp, int);
		MPI_Datatype type_vector_func_arg3 = va_arg(argp, MPI_Datatype);
		MPI_Datatype * type_vector_func_arg4 = va_arg(argp, MPI_Datatype *);
		ret = (QMPI_Type_vector_ptr) (type_vector_func_arg0, type_vector_func_arg1, type_vector_func_arg2, type_vector_func_arg3, type_vector_func_arg4,  level, v);
		break;
		 
        // int QMPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level, vector *v);\n
     
    case 314:
        va_start(argp,v);
		typedef int (*unpack_func) (const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm, int level, vector *v);
		unpack_func QMPI_Unpack_ptr = (unpack_func) func_ptr;
		const void * unpack_func_arg0 = va_arg(argp, const void *);
		int unpack_func_arg1 = va_arg(argp, int);
		int * unpack_func_arg2 = va_arg(argp, int *);
		void * unpack_func_arg3 = va_arg(argp, void *);
		int unpack_func_arg4 = va_arg(argp, int);
		MPI_Datatype unpack_func_arg5 = va_arg(argp, MPI_Datatype);
		MPI_Comm unpack_func_arg6 = va_arg(argp, MPI_Comm);
		ret = (QMPI_Unpack_ptr) (unpack_func_arg0, unpack_func_arg1, unpack_func_arg2, unpack_func_arg3, unpack_func_arg4, unpack_func_arg5, unpack_func_arg6,  level, v);
		break;
		 
        // int QMPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm, int level, vector *v);\n
     
    case 315:
        va_start(argp,v);
		typedef int (*unpack_external_func) (const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype, int level, vector *v);
		unpack_external_func QMPI_Unpack_external_ptr = (unpack_external_func) func_ptr;
		const char * unpack_external_func_arg0 = va_arg(argp, const char *);
		const void * unpack_external_func_arg1 = va_arg(argp, const void *);
		MPI_Aint unpack_external_func_arg2 = va_arg(argp, MPI_Aint);
		MPI_Aint * unpack_external_func_arg3 = va_arg(argp, MPI_Aint *);
		void * unpack_external_func_arg4 = va_arg(argp, void *);
		int unpack_external_func_arg5 = va_arg(argp, int);
		MPI_Datatype unpack_external_func_arg6 = va_arg(argp, MPI_Datatype);
		ret = (QMPI_Unpack_external_ptr) (unpack_external_func_arg0, unpack_external_func_arg1, unpack_external_func_arg2, unpack_external_func_arg3, unpack_external_func_arg4, unpack_external_func_arg5, unpack_external_func_arg6,  level, v);
		break;
		 
        // int QMPI_Unpack_external(const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype, int level, vector *v);\n
     
    case 316:
        va_start(argp,v);
		typedef int (*unpublish_name_func) (const char *service_name, MPI_Info info, const char *port_name, int level, vector *v);
		unpublish_name_func QMPI_Unpublish_name_ptr = (unpublish_name_func) func_ptr;
		const char * unpublish_name_func_arg0 = va_arg(argp, const char *);
		MPI_Info unpublish_name_func_arg1 = va_arg(argp, MPI_Info);
		const char * unpublish_name_func_arg2 = va_arg(argp, const char *);
		ret = (QMPI_Unpublish_name_ptr) (unpublish_name_func_arg0, unpublish_name_func_arg1, unpublish_name_func_arg2,  level, v);
		break;
		 
        // int QMPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name, int level, vector *v);\n
     
    case 317:
        va_start(argp,v);
		typedef int (*wait_func) (MPI_Request *request, MPI_Status *status, int level, vector *v);
		wait_func QMPI_Wait_ptr = (wait_func) func_ptr;
		MPI_Request * wait_func_arg0 = va_arg(argp, MPI_Request *);
		MPI_Status * wait_func_arg1 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Wait_ptr) (wait_func_arg0, wait_func_arg1,  level, v);
		break;
		 
        // int QMPI_Wait(MPI_Request *request, MPI_Status *status, int level, vector *v);\n
     
    case 318:
        va_start(argp,v);
		typedef int (*waitall_func) (int count, MPI_Request array_of_requests[], MPI_Status *array_of_statuses, int level, vector *v);
		waitall_func QMPI_Waitall_ptr = (waitall_func) func_ptr;
		int waitall_func_arg0 = va_arg(argp, int);
		MPI_Request* waitall_func_arg1 = va_arg(argp, MPI_Request*);
		MPI_Status * waitall_func_arg2 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Waitall_ptr) (waitall_func_arg0, waitall_func_arg1, waitall_func_arg2,  level, v);
		break;
		 
        // int QMPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status *array_of_statuses, int level, vector *v);\n
     
    case 319:
        va_start(argp,v);
		typedef int (*waitany_func) (int count, MPI_Request array_of_requests[], int *index, MPI_Status *status, int level, vector *v);
		waitany_func QMPI_Waitany_ptr = (waitany_func) func_ptr;
		int waitany_func_arg0 = va_arg(argp, int);
		MPI_Request* waitany_func_arg1 = va_arg(argp, MPI_Request*);
		int * waitany_func_arg2 = va_arg(argp, int *);
		MPI_Status * waitany_func_arg3 = va_arg(argp, MPI_Status *);
		ret = (QMPI_Waitany_ptr) (waitany_func_arg0, waitany_func_arg1, waitany_func_arg2, waitany_func_arg3,  level, v);
		break;
		 
        // int QMPI_Waitany(int count, MPI_Request array_of_requests[], int *index, MPI_Status *status, int level, vector *v);\n
     
    case 320:
        va_start(argp,v);
		typedef int (*waitsome_func) (int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[], int level, vector *v);
		waitsome_func QMPI_Waitsome_ptr = (waitsome_func) func_ptr;
		int waitsome_func_arg0 = va_arg(argp, int);
		MPI_Request* waitsome_func_arg1 = va_arg(argp, MPI_Request*);
		int * waitsome_func_arg2 = va_arg(argp, int *);
		int* waitsome_func_arg3 = va_arg(argp, int*);
		MPI_Status* waitsome_func_arg4 = va_arg(argp, MPI_Status*);
		ret = (QMPI_Waitsome_ptr) (waitsome_func_arg0, waitsome_func_arg1, waitsome_func_arg2, waitsome_func_arg3, waitsome_func_arg4,  level, v);
		break;
		 
        // int QMPI_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[], int level, vector *v);\n
     
    case 321:
        va_start(argp,v);
		typedef int (*win_allocate_func) (MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win, int level, vector *v);
		win_allocate_func QMPI_Win_allocate_ptr = (win_allocate_func) func_ptr;
		MPI_Aint win_allocate_func_arg0 = va_arg(argp, MPI_Aint);
		int win_allocate_func_arg1 = va_arg(argp, int);
		MPI_Info win_allocate_func_arg2 = va_arg(argp, MPI_Info);
		MPI_Comm win_allocate_func_arg3 = va_arg(argp, MPI_Comm);
		void * win_allocate_func_arg4 = va_arg(argp, void *);
		MPI_Win * win_allocate_func_arg5 = va_arg(argp, MPI_Win *);
		ret = (QMPI_Win_allocate_ptr) (win_allocate_func_arg0, win_allocate_func_arg1, win_allocate_func_arg2, win_allocate_func_arg3, win_allocate_func_arg4, win_allocate_func_arg5,  level, v);
		break;
		 
        // int QMPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win, int level, vector *v);\n
     
    case 322:
        va_start(argp,v);
		typedef int (*win_allocate_shared_func) (MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win, int level, vector *v);
		win_allocate_shared_func QMPI_Win_allocate_shared_ptr = (win_allocate_shared_func) func_ptr;
		MPI_Aint win_allocate_shared_func_arg0 = va_arg(argp, MPI_Aint);
		int win_allocate_shared_func_arg1 = va_arg(argp, int);
		MPI_Info win_allocate_shared_func_arg2 = va_arg(argp, MPI_Info);
		MPI_Comm win_allocate_shared_func_arg3 = va_arg(argp, MPI_Comm);
		void * win_allocate_shared_func_arg4 = va_arg(argp, void *);
		MPI_Win * win_allocate_shared_func_arg5 = va_arg(argp, MPI_Win *);
		ret = (QMPI_Win_allocate_shared_ptr) (win_allocate_shared_func_arg0, win_allocate_shared_func_arg1, win_allocate_shared_func_arg2, win_allocate_shared_func_arg3, win_allocate_shared_func_arg4, win_allocate_shared_func_arg5,  level, v);
		break;
		 
        // int QMPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win, int level, vector *v);\n
     
    case 323:
        va_start(argp,v);
		typedef int (*win_attach_func) (MPI_Win win, void *base, MPI_Aint size, int level, vector *v);
		win_attach_func QMPI_Win_attach_ptr = (win_attach_func) func_ptr;
		MPI_Win win_attach_func_arg0 = va_arg(argp, MPI_Win);
		void * win_attach_func_arg1 = va_arg(argp, void *);
		MPI_Aint win_attach_func_arg2 = va_arg(argp, MPI_Aint);
		ret = (QMPI_Win_attach_ptr) (win_attach_func_arg0, win_attach_func_arg1, win_attach_func_arg2,  level, v);
		break;
		 
        // int QMPI_Win_attach(MPI_Win win, void *base, MPI_Aint size, int level, vector *v);\n
     
    case 324:
        va_start(argp,v);
		typedef int (*win_call_errhandler_func) (MPI_Win win, int errorcode, int level, vector *v);
		win_call_errhandler_func QMPI_Win_call_errhandler_ptr = (win_call_errhandler_func) func_ptr;
		MPI_Win win_call_errhandler_func_arg0 = va_arg(argp, MPI_Win);
		int win_call_errhandler_func_arg1 = va_arg(argp, int);
		ret = (QMPI_Win_call_errhandler_ptr) (win_call_errhandler_func_arg0, win_call_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_call_errhandler(MPI_Win win, int errorcode, int level, vector *v);\n
     
    case 325:
        va_start(argp,v);
		typedef int (*win_complete_func) (MPI_Win win, int level, vector *v);
		win_complete_func QMPI_Win_complete_ptr = (win_complete_func) func_ptr;
		MPI_Win win_complete_func_arg0 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_complete_ptr) (win_complete_func_arg0,  level, v);
		break;
		 
        // int QMPI_Win_complete(MPI_Win win, int level, vector *v);\n
     
    case 326:
        va_start(argp,v);
		typedef int (*win_create_func) (void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win, int level, vector *v);
		win_create_func QMPI_Win_create_ptr = (win_create_func) func_ptr;
		void * win_create_func_arg0 = va_arg(argp, void *);
		MPI_Aint win_create_func_arg1 = va_arg(argp, MPI_Aint);
		int win_create_func_arg2 = va_arg(argp, int);
		MPI_Info win_create_func_arg3 = va_arg(argp, MPI_Info);
		MPI_Comm win_create_func_arg4 = va_arg(argp, MPI_Comm);
		MPI_Win * win_create_func_arg5 = va_arg(argp, MPI_Win *);
		ret = (QMPI_Win_create_ptr) (win_create_func_arg0, win_create_func_arg1, win_create_func_arg2, win_create_func_arg3, win_create_func_arg4, win_create_func_arg5,  level, v);
		break;
		 
        // int QMPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win, int level, vector *v);\n
     
    case 327:
        va_start(argp,v);
		typedef int (*win_create_dynamic_func) (MPI_Info info, MPI_Comm comm, MPI_Win *win, int level, vector *v);
		win_create_dynamic_func QMPI_Win_create_dynamic_ptr = (win_create_dynamic_func) func_ptr;
		MPI_Info win_create_dynamic_func_arg0 = va_arg(argp, MPI_Info);
		MPI_Comm win_create_dynamic_func_arg1 = va_arg(argp, MPI_Comm);
		MPI_Win * win_create_dynamic_func_arg2 = va_arg(argp, MPI_Win *);
		ret = (QMPI_Win_create_dynamic_ptr) (win_create_dynamic_func_arg0, win_create_dynamic_func_arg1, win_create_dynamic_func_arg2,  level, v);
		break;
		 
        // int QMPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win *win, int level, vector *v);\n
     
    case 328:
        va_start(argp,v);
		typedef int (*win_create_errhandler_func) (MPI_Win_errhandler_function *function, MPI_Errhandler *errhandler, int level, vector *v);
		win_create_errhandler_func QMPI_Win_create_errhandler_ptr = (win_create_errhandler_func) func_ptr;
		MPI_Win_errhandler_function * win_create_errhandler_func_arg0 = va_arg(argp, MPI_Win_errhandler_function *);
		MPI_Errhandler * win_create_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_Win_create_errhandler_ptr) (win_create_errhandler_func_arg0, win_create_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_create_errhandler(MPI_Win_errhandler_function *function, MPI_Errhandler *errhandler, int level, vector *v);\n
     
    case 329:
        va_start(argp,v);
		typedef int (*win_create_keyval_func) (MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state, int level, vector *v);
		win_create_keyval_func QMPI_Win_create_keyval_ptr = (win_create_keyval_func) func_ptr;
		MPI_Win_copy_attr_function * win_create_keyval_func_arg0 = va_arg(argp, MPI_Win_copy_attr_function *);
		MPI_Win_delete_attr_function * win_create_keyval_func_arg1 = va_arg(argp, MPI_Win_delete_attr_function *);
		int * win_create_keyval_func_arg2 = va_arg(argp, int *);
		void * win_create_keyval_func_arg3 = va_arg(argp, void *);
		ret = (QMPI_Win_create_keyval_ptr) (win_create_keyval_func_arg0, win_create_keyval_func_arg1, win_create_keyval_func_arg2, win_create_keyval_func_arg3,  level, v);
		break;
		 
        // int QMPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state, int level, vector *v);\n
     
    case 330:
        va_start(argp,v);
		typedef int (*win_delete_attr_func) (MPI_Win win, int win_keyval, int level, vector *v);
		win_delete_attr_func QMPI_Win_delete_attr_ptr = (win_delete_attr_func) func_ptr;
		MPI_Win win_delete_attr_func_arg0 = va_arg(argp, MPI_Win);
		int win_delete_attr_func_arg1 = va_arg(argp, int);
		ret = (QMPI_Win_delete_attr_ptr) (win_delete_attr_func_arg0, win_delete_attr_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_delete_attr(MPI_Win win, int win_keyval, int level, vector *v);\n
     
    case 331:
        va_start(argp,v);
		typedef int (*win_detach_func) (MPI_Win win, const void *base, int level, vector *v);
		win_detach_func QMPI_Win_detach_ptr = (win_detach_func) func_ptr;
		MPI_Win win_detach_func_arg0 = va_arg(argp, MPI_Win);
		const void * win_detach_func_arg1 = va_arg(argp, const void *);
		ret = (QMPI_Win_detach_ptr) (win_detach_func_arg0, win_detach_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_detach(MPI_Win win, const void *base, int level, vector *v);\n
     
    case 332:
        va_start(argp,v);
		typedef int (*win_fence_func) (int assert, MPI_Win win, int level, vector *v);
		win_fence_func QMPI_Win_fence_ptr = (win_fence_func) func_ptr;
		int win_fence_func_arg0 = va_arg(argp, int);
		MPI_Win win_fence_func_arg1 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_fence_ptr) (win_fence_func_arg0, win_fence_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_fence(int assert, MPI_Win win, int level, vector *v);\n
     
    case 333:
        va_start(argp,v);
		typedef int (*win_flush_func) (int rank, MPI_Win win, int level, vector *v);
		win_flush_func QMPI_Win_flush_ptr = (win_flush_func) func_ptr;
		int win_flush_func_arg0 = va_arg(argp, int);
		MPI_Win win_flush_func_arg1 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_flush_ptr) (win_flush_func_arg0, win_flush_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_flush(int rank, MPI_Win win, int level, vector *v);\n
     
    case 334:
        va_start(argp,v);
		typedef int (*win_flush_all_func) (MPI_Win win, int level, vector *v);
		win_flush_all_func QMPI_Win_flush_all_ptr = (win_flush_all_func) func_ptr;
		MPI_Win win_flush_all_func_arg0 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_flush_all_ptr) (win_flush_all_func_arg0,  level, v);
		break;
		 
        // int QMPI_Win_flush_all(MPI_Win win, int level, vector *v);\n
     
    case 335:
        va_start(argp,v);
		typedef int (*win_flush_local_func) (int rank, MPI_Win win, int level, vector *v);
		win_flush_local_func QMPI_Win_flush_local_ptr = (win_flush_local_func) func_ptr;
		int win_flush_local_func_arg0 = va_arg(argp, int);
		MPI_Win win_flush_local_func_arg1 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_flush_local_ptr) (win_flush_local_func_arg0, win_flush_local_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_flush_local(int rank, MPI_Win win, int level, vector *v);\n
     
    case 336:
        va_start(argp,v);
		typedef int (*win_flush_local_all_func) (MPI_Win win, int level, vector *v);
		win_flush_local_all_func QMPI_Win_flush_local_all_ptr = (win_flush_local_all_func) func_ptr;
		MPI_Win win_flush_local_all_func_arg0 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_flush_local_all_ptr) (win_flush_local_all_func_arg0,  level, v);
		break;
		 
        // int QMPI_Win_flush_local_all(MPI_Win win, int level, vector *v);\n
     
    case 337:
        va_start(argp,v);
		typedef int (*win_free_func) (MPI_Win *win, int level, vector *v);
		win_free_func QMPI_Win_free_ptr = (win_free_func) func_ptr;
		MPI_Win * win_free_func_arg0 = va_arg(argp, MPI_Win *);
		ret = (QMPI_Win_free_ptr) (win_free_func_arg0,  level, v);
		break;
		 
        // int QMPI_Win_free(MPI_Win *win, int level, vector *v);\n
     
    case 338:
        va_start(argp,v);
		typedef int (*win_free_keyval_func) (int *win_keyval, int level, vector *v);
		win_free_keyval_func QMPI_Win_free_keyval_ptr = (win_free_keyval_func) func_ptr;
		int * win_free_keyval_func_arg0 = va_arg(argp, int *);
		ret = (QMPI_Win_free_keyval_ptr) (win_free_keyval_func_arg0,  level, v);
		break;
		 
        // int QMPI_Win_free_keyval(int *win_keyval, int level, vector *v);\n
     
    case 339:
        va_start(argp,v);
		typedef int (*win_get_attr_func) (MPI_Win win, int win_keyval, void *attribute_val, int *flag, int level, vector *v);
		win_get_attr_func QMPI_Win_get_attr_ptr = (win_get_attr_func) func_ptr;
		MPI_Win win_get_attr_func_arg0 = va_arg(argp, MPI_Win);
		int win_get_attr_func_arg1 = va_arg(argp, int);
		void * win_get_attr_func_arg2 = va_arg(argp, void *);
		int * win_get_attr_func_arg3 = va_arg(argp, int *);
		ret = (QMPI_Win_get_attr_ptr) (win_get_attr_func_arg0, win_get_attr_func_arg1, win_get_attr_func_arg2, win_get_attr_func_arg3,  level, v);
		break;
		 
        // int QMPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag, int level, vector *v);\n
     
    case 340:
        va_start(argp,v);
		typedef int (*win_get_errhandler_func) (MPI_Win win, MPI_Errhandler *errhandler, int level, vector *v);
		win_get_errhandler_func QMPI_Win_get_errhandler_ptr = (win_get_errhandler_func) func_ptr;
		MPI_Win win_get_errhandler_func_arg0 = va_arg(argp, MPI_Win);
		MPI_Errhandler * win_get_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler *);
		ret = (QMPI_Win_get_errhandler_ptr) (win_get_errhandler_func_arg0, win_get_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler, int level, vector *v);\n
     
    case 341:
        va_start(argp,v);
		typedef int (*win_get_group_func) (MPI_Win win, MPI_Group *group, int level, vector *v);
		win_get_group_func QMPI_Win_get_group_ptr = (win_get_group_func) func_ptr;
		MPI_Win win_get_group_func_arg0 = va_arg(argp, MPI_Win);
		MPI_Group * win_get_group_func_arg1 = va_arg(argp, MPI_Group *);
		ret = (QMPI_Win_get_group_ptr) (win_get_group_func_arg0, win_get_group_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_get_group(MPI_Win win, MPI_Group *group, int level, vector *v);\n
     
    case 342:
        va_start(argp,v);
		typedef int (*win_get_info_func) (MPI_Win win, MPI_Info *info_used, int level, vector *v);
		win_get_info_func QMPI_Win_get_info_ptr = (win_get_info_func) func_ptr;
		MPI_Win win_get_info_func_arg0 = va_arg(argp, MPI_Win);
		MPI_Info * win_get_info_func_arg1 = va_arg(argp, MPI_Info *);
		ret = (QMPI_Win_get_info_ptr) (win_get_info_func_arg0, win_get_info_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_get_info(MPI_Win win, MPI_Info *info_used, int level, vector *v);\n
     
    case 343:
        va_start(argp,v);
		typedef int (*win_get_name_func) (MPI_Win win, char *win_name, int *resultlen, int level, vector *v);
		win_get_name_func QMPI_Win_get_name_ptr = (win_get_name_func) func_ptr;
		MPI_Win win_get_name_func_arg0 = va_arg(argp, MPI_Win);
		char * win_get_name_func_arg1 = va_arg(argp, char *);
		int * win_get_name_func_arg2 = va_arg(argp, int *);
		ret = (QMPI_Win_get_name_ptr) (win_get_name_func_arg0, win_get_name_func_arg1, win_get_name_func_arg2,  level, v);
		break;
		 
        // int QMPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen, int level, vector *v);\n
     
    case 344:
        va_start(argp,v);
		typedef int (*win_lock_func) (int lock_type, int rank, int assert, MPI_Win win, int level, vector *v);
		win_lock_func QMPI_Win_lock_ptr = (win_lock_func) func_ptr;
		int win_lock_func_arg0 = va_arg(argp, int);
		int win_lock_func_arg1 = va_arg(argp, int);
		int win_lock_func_arg2 = va_arg(argp, int);
		MPI_Win win_lock_func_arg3 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_lock_ptr) (win_lock_func_arg0, win_lock_func_arg1, win_lock_func_arg2, win_lock_func_arg3,  level, v);
		break;
		 
        // int QMPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win, int level, vector *v);\n
     
    case 345:
        va_start(argp,v);
		typedef int (*win_lock_all_func) (int assert, MPI_Win win, int level, vector *v);
		win_lock_all_func QMPI_Win_lock_all_ptr = (win_lock_all_func) func_ptr;
		int win_lock_all_func_arg0 = va_arg(argp, int);
		MPI_Win win_lock_all_func_arg1 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_lock_all_ptr) (win_lock_all_func_arg0, win_lock_all_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_lock_all(int assert, MPI_Win win, int level, vector *v);\n
     
    case 346:
        va_start(argp,v);
		typedef int (*win_post_func) (MPI_Group group, int assert, MPI_Win win, int level, vector *v);
		win_post_func QMPI_Win_post_ptr = (win_post_func) func_ptr;
		MPI_Group win_post_func_arg0 = va_arg(argp, MPI_Group);
		int win_post_func_arg1 = va_arg(argp, int);
		MPI_Win win_post_func_arg2 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_post_ptr) (win_post_func_arg0, win_post_func_arg1, win_post_func_arg2,  level, v);
		break;
		 
        // int QMPI_Win_post(MPI_Group group, int assert, MPI_Win win, int level, vector *v);\n
     
    case 347:
        va_start(argp,v);
		typedef int (*win_set_attr_func) (MPI_Win win, int win_keyval, void *attribute_val, int level, vector *v);
		win_set_attr_func QMPI_Win_set_attr_ptr = (win_set_attr_func) func_ptr;
		MPI_Win win_set_attr_func_arg0 = va_arg(argp, MPI_Win);
		int win_set_attr_func_arg1 = va_arg(argp, int);
		void * win_set_attr_func_arg2 = va_arg(argp, void *);
		ret = (QMPI_Win_set_attr_ptr) (win_set_attr_func_arg0, win_set_attr_func_arg1, win_set_attr_func_arg2,  level, v);
		break;
		 
        // int QMPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val, int level, vector *v);\n
     
    case 348:
        va_start(argp,v);
		typedef int (*win_set_errhandler_func) (MPI_Win win, MPI_Errhandler errhandler, int level, vector *v);
		win_set_errhandler_func QMPI_Win_set_errhandler_ptr = (win_set_errhandler_func) func_ptr;
		MPI_Win win_set_errhandler_func_arg0 = va_arg(argp, MPI_Win);
		MPI_Errhandler win_set_errhandler_func_arg1 = va_arg(argp, MPI_Errhandler);
		ret = (QMPI_Win_set_errhandler_ptr) (win_set_errhandler_func_arg0, win_set_errhandler_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler, int level, vector *v);\n
     
    case 349:
        va_start(argp,v);
		typedef int (*win_set_info_func) (MPI_Win win, MPI_Info info, int level, vector *v);
		win_set_info_func QMPI_Win_set_info_ptr = (win_set_info_func) func_ptr;
		MPI_Win win_set_info_func_arg0 = va_arg(argp, MPI_Win);
		MPI_Info win_set_info_func_arg1 = va_arg(argp, MPI_Info);
		ret = (QMPI_Win_set_info_ptr) (win_set_info_func_arg0, win_set_info_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_set_info(MPI_Win win, MPI_Info info, int level, vector *v);\n
     
    case 350:
        va_start(argp,v);
		typedef int (*win_set_name_func) (MPI_Win win, const char *win_name, int level, vector *v);
		win_set_name_func QMPI_Win_set_name_ptr = (win_set_name_func) func_ptr;
		MPI_Win win_set_name_func_arg0 = va_arg(argp, MPI_Win);
		const char * win_set_name_func_arg1 = va_arg(argp, const char *);
		ret = (QMPI_Win_set_name_ptr) (win_set_name_func_arg0, win_set_name_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_set_name(MPI_Win win, const char *win_name, int level, vector *v);\n
     
    case 351:
        va_start(argp,v);
		typedef int (*win_shared_query_func) (MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr, int level, vector *v);
		win_shared_query_func QMPI_Win_shared_query_ptr = (win_shared_query_func) func_ptr;
		MPI_Win win_shared_query_func_arg0 = va_arg(argp, MPI_Win);
		int win_shared_query_func_arg1 = va_arg(argp, int);
		MPI_Aint * win_shared_query_func_arg2 = va_arg(argp, MPI_Aint *);
		int * win_shared_query_func_arg3 = va_arg(argp, int *);
		void * win_shared_query_func_arg4 = va_arg(argp, void *);
		ret = (QMPI_Win_shared_query_ptr) (win_shared_query_func_arg0, win_shared_query_func_arg1, win_shared_query_func_arg2, win_shared_query_func_arg3, win_shared_query_func_arg4,  level, v);
		break;
		 
        // int QMPI_Win_shared_query(MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr, int level, vector *v);\n
     
    case 352:
        va_start(argp,v);
		typedef int (*win_start_func) (MPI_Group group, int assert, MPI_Win win, int level, vector *v);
		win_start_func QMPI_Win_start_ptr = (win_start_func) func_ptr;
		MPI_Group win_start_func_arg0 = va_arg(argp, MPI_Group);
		int win_start_func_arg1 = va_arg(argp, int);
		MPI_Win win_start_func_arg2 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_start_ptr) (win_start_func_arg0, win_start_func_arg1, win_start_func_arg2,  level, v);
		break;
		 
        // int QMPI_Win_start(MPI_Group group, int assert, MPI_Win win, int level, vector *v);\n
     
    case 353:
        va_start(argp,v);
		typedef int (*win_sync_func) (MPI_Win win, int level, vector *v);
		win_sync_func QMPI_Win_sync_ptr = (win_sync_func) func_ptr;
		MPI_Win win_sync_func_arg0 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_sync_ptr) (win_sync_func_arg0,  level, v);
		break;
		 
        // int QMPI_Win_sync(MPI_Win win, int level, vector *v);\n
     
    case 354:
        va_start(argp,v);
		typedef int (*win_test_func) (MPI_Win win, int *flag, int level, vector *v);
		win_test_func QMPI_Win_test_ptr = (win_test_func) func_ptr;
		MPI_Win win_test_func_arg0 = va_arg(argp, MPI_Win);
		int * win_test_func_arg1 = va_arg(argp, int *);
		ret = (QMPI_Win_test_ptr) (win_test_func_arg0, win_test_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_test(MPI_Win win, int *flag, int level, vector *v);\n
     
    case 355:
        va_start(argp,v);
		typedef int (*win_unlock_func) (int rank, MPI_Win win, int level, vector *v);
		win_unlock_func QMPI_Win_unlock_ptr = (win_unlock_func) func_ptr;
		int win_unlock_func_arg0 = va_arg(argp, int);
		MPI_Win win_unlock_func_arg1 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_unlock_ptr) (win_unlock_func_arg0, win_unlock_func_arg1,  level, v);
		break;
		 
        // int QMPI_Win_unlock(int rank, MPI_Win win, int level, vector *v);\n
     
    case 356:
        va_start(argp,v);
		typedef int (*win_unlock_all_func) (MPI_Win win, int level, vector *v);
		win_unlock_all_func QMPI_Win_unlock_all_ptr = (win_unlock_all_func) func_ptr;
		MPI_Win win_unlock_all_func_arg0 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_unlock_all_ptr) (win_unlock_all_func_arg0,  level, v);
		break;
		 
        // int QMPI_Win_unlock_all(MPI_Win win, int level, vector *v);\n
     
    case 357:
        va_start(argp,v);
		typedef int (*win_wait_func) (MPI_Win win, int level, vector *v);
		win_wait_func QMPI_Win_wait_ptr = (win_wait_func) func_ptr;
		MPI_Win win_wait_func_arg0 = va_arg(argp, MPI_Win);
		ret = (QMPI_Win_wait_ptr) (win_wait_func_arg0,  level, v);
		break;
		 
        // int QMPI_Win_wait(MPI_Win win, int level, vector *v);

    case 358: 
    	va_start(argp,v);
		typedef double (*wtick_func) (int level,  vector* v);
		wtick_func QMPI_Wtick_ptr = (wtick_func) func_ptr;
		ret = (QMPI_Wtick_ptr) ( level, v);
		break;
    //double QMPI_Wtick( int level,  vector* v);
    case 359:
    	va_start(argp,v);
		typedef double (*wtime_func) (int level,  vector* v);
		wtime_func QMPI_Wtime_ptr = (wtime_func) func_ptr;
		ret = (QMPI_Wtime_ptr) ( level, v);
		break;
    //double QMPI_Wtime( int level,  vector* v);    

                }
                va_end(argp);
        }
        return ret;
}


void get_tool_interceptions( struct dynamic_lib* l )
{
        if ( (*l).handle == NULL){
                printf("handle null, returns to get_interceptions \n");
                return;
        }

        mpi_func func =(mpi_func) dlsym( (*l).handle , "get_interceptions");

        if (func == NULL)
        {
                printf("get interceptions function can't be found null, returns \n");
                return;
        }
        else {
                for(int i =0; i< NUM_MPI_FUNCS ; i++) 
                {
                        (*l).mpi_interceptions[i]=func(i);
                }
        }
        return;
}


void*  get_func_ptr(const dynamic_lib_handle handle, char* func_name){

        if (handle == NULL)
        {
                printf("handle null, returns for \n");
                return NULL ;
        }
        void*  status = dlsym(handle , func_name);
        const char *dlsym_error = dlerror();
        if (dlsym_error)
        {       printf( "Cannot load pointer: %s \n ", dlsym_error); }

        if (status == NULL)
        {
                printf("function pointer return value in get_func_ptr = NULL \n");

        }
        return status;
}
int split (char* paths, int next)
{
        if( (paths+next)== NULL )
        {
                printf("NULL \n");
                return -2;
        }
        else if ( *(paths+ next)=='\0' )
        {
                printf(" End of paths \n ");
                return -3;
        }else{
                ++next;
                while( *(paths+ next )!='\0' && *(paths+next)!=':')
                {
                        ++next;
                }
        }
        return next;
}
/* ================== C Wrappers for MPI_Init ================== */
_EXTERN_C_ int QMPI_Init(int *argc, char ***argv, int level,  vector* v){
  //printf( "QMPI da No problem with the return stuff :) Level: %d \n",level);
  return PMPI_Init(argc, argv);
}

_EXTERN_C_ int MPI_Init(int *argc, char ***argv) { 
  vector_init(&v);

  struct dynamic_lib dl0={"./qmpi",NULL,NULL,NULL,0};
  vector_add(&v, &dl0);
  printf("1st path : %s \n",(* vector_get(&v,0)).path);
  int num_tools =1;
  char* paths=getenv("TOOLS");
  if(paths!=NULL){
    //strcat(paths, "\0");
    int next =0;            
    int start = 0;
    while (next>=0)
    {       start = next;
            if( *(paths+start) == ':')
            {
              ++start;
            }
              next=split(paths, start);
              if(next >= 0 )
              {
		memset(dl0.path, 0, sizeof(dl0.path));
		strncpy(dl0.path,paths+start,(next-start)*sizeof(char) );
                strcat(dl0.path, "\0");
                vector_add(&v, &dl0);
                ++num_tools;
              }
    }
    for ( int i =1 ; i< vector_total(&v); ++i)
    {
    	(*vector_get(&v,i)).handle=load_lib(  (*vector_get(&v,i)).path ) ;
    	get_tool_interceptions( vector_get(&v,i) );
    	printf("path: %s \n",  (*vector_get(&v,i)).path);
    	/*for(int k =0; k< NUM_MPI_FUNCS ; k++) 
    	{
      		printf(" func name %s \n",(*vector_get(&v,i)).mpi_interceptions[k] );
    	}*/
    }
  }
  //Get list of functions in the tool libraries intercepting with QMPI
  // Fill in the maps with function pointers to MPI intercepting functions
  struct dynamic_lib* prev_dl=NULL;
  struct dynamic_lib* next_dl=NULL;
  struct dynamic_lib* this_dl=NULL;

  for (int i =1; i<vector_total(&v); i++){
    //jump the first qmpi stuct in the vector
    prev_dl=vector_get(&v,i-1);
    for(int index=0 ; index < NUM_MPI_FUNCS ; ++index){ 
      if (   strcmp( (*vector_get(&v,i)).mpi_interceptions[index],"NULL" ) != 0 )
      {
        //get function pointer
        void* tmp_vec =get_func_ptr( (*vector_get(&v,i)).handle , (*vector_get(&v,i)).mpi_interceptions[index] );
        //put into the map of the previous dynamic_library structure
 //       printf("1- Vec Tool : %s func name %s level: %d \n", (*prev_dl).path, (*vector_get(&v,i)).mpi_interceptions[index],i);
        ((*prev_dl).table[index]).me = get_func_ptr( (*vector_get(&v,i)).handle , (*vector_get(&v,i)).mpi_interceptions[index] );
        ((*prev_dl).table[index]).level=i;
      }else if ( i != vector_total(&v)-1  ){
        //if function doesn't exist and NOT filling in the map of the last synamic_lib structure
        int n=i+1;
        next_dl=vector_get(&v,n);
        for( ;(n != vector_total(&v)) && (strcmp( (*next_dl).mpi_interceptions[index] ,  "NULL") == 0); ++n )
        {
          next_dl=vector_get(&v,n);
        }
        if(n >= vector_total(&v)-1){
          //printf("Path:%s  value :%s\n",(*next_dl).path, (*next_dl).mpi_interceptions[index]);
          if( strcmp( (*next_dl).mpi_interceptions[index] ,  "NULL") == 0 )
          {
           // printf("2- Vec Tool : %s func name QMPI -All NULL- level: %d \n",  (*prev_dl).path,n);
            (*prev_dl).table[index].me=QMPI_Array[index];
            (*prev_dl).table[index].level=n;
          }else{
            (*prev_dl).table[index].me=get_func_ptr( (*next_dl).handle, (*next_dl).mpi_interceptions[index] );
            if(n>=vector_total(&v)){ --n; }
            (*prev_dl).table[index].level=n;
            //printf("3- Vec Tool : %s Func name %s , level: %d\n",  (*prev_dl).path, (*next_dl).mpi_interceptions[index],n);
          }
        }else{
          //printf("4- Vec Tool : %s ,Func name: %s , level: %d \n",(*prev_dl).path, (*next_dl).mpi_interceptions[index],n);
          (*prev_dl).table[index].me= get_func_ptr( (*next_dl).handle, (*next_dl).mpi_interceptions[index] );
          (*prev_dl).table[index].level=n;
        }
      }else{
        //printf("5- Vec Tool : %s func name %s , level: %d\n", (*prev_dl).path, "QMPI",i);
        (*prev_dl).table[index].me=QMPI_Array[index]; // this will be fixed with an array and different func_ptr for all  index values
        (*prev_dl).table[index].level=i;
      }
      if(i == vector_total(&v)-1 ){
        this_dl=vector_get(&v,i);
        //printf("6- Vec Tool : %s func name %s , level: %d\n", (*this_dl).path, "QMPI",i);
        (*this_dl).table[index].me=QMPI_Array[index];
        (*this_dl).table[index].level=i;
      }
    }
  }
  void* f_dl=NULL;//200 =func_index
  QMPI_Table_query(_MPI_Init,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Init,&v,argc,argv);
  return ret;
}
/* ================== C Wrappers for MPI_Abort ================== 0*/
_EXTERN_C_ int QMPI_Abort(MPI_Comm comm, int errorcode, int level,  vector* v){
	return PMPI_Abort(comm, errorcode);
}
_EXTERN_C_ int MPI_Abort(MPI_Comm comm, int errorcode) { 
    void* f_dl=NULL;
    QMPI_Table_query(_MPI_Abort,&f_dl,(*vector_get(&v, 0)).table );
    int ret=exec_func(f_dl,0,_MPI_Abort,&v,comm,errorcode);
    return ret;
}
/* ================== C Wrappers for MPI_Accumulate ================== 1*/
_EXTERN_C_ int QMPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win , int level,  vector* v){
	  return PMPI_Accumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype,  op, win) ;
}
_EXTERN_C_ int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win) { 
  void* f_dl=NULL;
    QMPI_Table_query(1,&f_dl,(*vector_get(&v, 0)).table );
    int ret=exec_func(f_dl,0,1,&v,origin_addr, origin_count,origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
    return ret;
}
/* ================== C Wrappers for MPI_Add_error_class ================== 2*/
_EXTERN_C_ int QMPI_Add_error_class(int *errorclass, int level,  vector* v){
	 return PMPI_Add_error_class(errorclass);
}
_EXTERN_C_ int MPI_Add_error_class(int *errorclass) { 
 	void* f_dl=NULL;
    QMPI_Table_query(_MPI_Accumulate,&f_dl,(*vector_get(&v, 0)).table );
    int ret=exec_func(f_dl,0,_MPI_Accumulate,&v,errorclass);
    return ret;
}
/* ================== C Wrappers for MPI_Add_error_code ==================3 */
_EXTERN_C_ int QMPI_Add_error_code(int errorclass, int *errorcode, int level,  vector* v){
	return PMPI_Add_error_code(errorclass, errorcode);
}
_EXTERN_C_ int MPI_Add_error_code(int errorclass, int *errorcode) { 
	void* f_dl=NULL;
    QMPI_Table_query(3,&f_dl,(*vector_get(&v, 0)).table );
    int ret=exec_func(f_dl,0,3,&v,errorclass, errorcode);
    return ret;
}
/* ================== C Wrappers for MPI_Add_error_string ================== 4*/
_EXTERN_C_ int QMPI_Add_error_string(int errorcode, const char *string, int level,  vector* v){
	return PMPI_Add_error_string(errorcode, string);	
}
_EXTERN_C_ int MPI_Add_error_string(int errorcode, const char *string) { 
   void* f_dl=NULL;
   QMPI_Table_query(_MPI_Add_error_string,&f_dl,(*vector_get(&v, 0)).table );
   int ret=exec_func(f_dl,0,_MPI_Add_error_string,&v,errorcode, string);
   return ret;
}
/* ================== C Wrappers for MPI_Address ================== 5*/
_EXTERN_C_ int QMPI_Address(void *location, MPI_Aint *address, int level,  vector* v){
	return PMPI_Address(location, address);
}
_EXTERN_C_ int MPI_Address(void *location, MPI_Aint *address) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Address,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Address,&v,location, address);
  return ret;
}
/* ================== C Wrappers for MPI_Allgather ================== 6*/
_EXTERN_C_ int QMPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v){
	printf("QMPI_Allgather -2-\n");
	return PMPI_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}
_EXTERN_C_ int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { 
  void* f_dl=NULL;
  printf("MPI_Allgather -1-\n");
  QMPI_Table_query(_MPI_Allgather,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Allgather,&v,sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Allgatherv ================== 7*/
_EXTERN_C_ int QMPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v){
	return PMPI_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs,recvtype, comm);
}
_EXTERN_C_ int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Allgatherv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Allgatherv,&v,sendbuf, sendcount, sendtype,recvbuf, recvcounts, displs,recvtype,comm);
  return ret;
}
/* ================== C Wrappers for MPI_Alloc_mem ================== 8*/
_EXTERN_C_ int QMPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr , int level,  vector* v){
	return PMPI_Alloc_mem(size, info, baseptr);
}
_EXTERN_C_ int MPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Alloc_mem,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Alloc_mem,&v,size, info, baseptr);
  return ret;
}
/* ================== C Wrappers for MPI_Allreduce ================== 9*/
_EXTERN_C_ int QMPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm , int level,  vector* v){
	return PMPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
}
_EXTERN_C_ int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Allreduce,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Allreduce,&v,sendbuf, recvbuf, count, datatype, op, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Alltoall ================== 10*/
_EXTERN_C_ int QMPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm , int level,  vector* v){
	return PMPI_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}
_EXTERN_C_ int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Alltoall,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Alltoall,&v,sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Alltoallv ================== 11*/
_EXTERN_C_ int QMPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v){
	return PMPI_Alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}
_EXTERN_C_ int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Alltoallv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Alltoallv,&v,sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Alltoallw ================== 12*/
_EXTERN_C_ int QMPI_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, int level,  vector* v){	
	return PMPI_Alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes,comm);
}
_EXTERN_C_ int MPI_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Alltoallw,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Alltoallw,&v,sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes,comm);
  return ret;
}
/* ================== C Wrappers for MPI_Attr_delete ================== 13*/
_EXTERN_C_ int QMPI_Attr_delete(MPI_Comm comm, int keyval, int level,  vector* v){
	return PMPI_Attr_delete(comm, keyval);
}
_EXTERN_C_ int MPI_Attr_delete(MPI_Comm comm, int keyval) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Attr_delete,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Attr_delete,&v,comm, keyval);
  return ret;
}
/* ================== C Wrappers for MPI_Attr_get ================== 14*/
_EXTERN_C_ int QMPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag, int level,  vector* v){
	return PMPI_Attr_get(comm, keyval, attribute_val, flag);
}
_EXTERN_C_ int MPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Attr_get,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Attr_get,&v,comm, keyval, attribute_val, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Attr_put ================== 15*/
_EXTERN_C_ int QMPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val, int level,  vector* v){
	return PMPI_Attr_put(comm, keyval, attribute_val);
}
_EXTERN_C_ int MPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Attr_put,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Attr_put,&v,comm, keyval, attribute_val);
  return ret;
}
/* ================== C Wrappers for MPI_Barrier ==================16 */
_EXTERN_C_ int QMPI_Barrier(MPI_Comm comm, int level,  vector* v){
	return PMPI_Barrier(comm);
}
_EXTERN_C_ int MPI_Barrier(MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Barrier,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Barrier,&v,comm);
  return ret;
}
/* ================== C Wrappers for MPI_Bcast ================== 17*/
_EXTERN_C_ int QMPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, int level,  vector* v){
	return PMPI_Bcast(buffer, count, datatype, root, comm);
}
_EXTERN_C_ int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Bcast,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Bcast,&v,buffer, count, datatype, root, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Bsend ================== 18*/
_EXTERN_C_ int QMPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level,  vector* v){
	return PMPI_Bsend(buf, count, datatype, dest, tag, comm);
}
_EXTERN_C_ int MPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { 
   void* f_dl=NULL;
  QMPI_Table_query(_MPI_Bsend,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Bsend,&v,buf, count, datatype, dest, tag, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Bsend_init ==================19 */
_EXTERN_C_ int QMPI_Bsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
	 return PMPI_Bsend_init(buf, count, datatype, dest, tag, comm, request);
}
_EXTERN_C_ int MPI_Bsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Bsend_init,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Bsend_init,&v,buf, count, datatype, dest, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Buffer_attach ==================20 */
_EXTERN_C_ int QMPI_Buffer_attach(void *buffer, int size, int level,  vector* v){
	return PMPI_Buffer_attach(buffer, size);
}
_EXTERN_C_ int MPI_Buffer_attach(void *buffer, int size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Buffer_attach,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Buffer_attach,&v,buffer, size);
  return ret;
}
/* ================== C Wrappers for MPI_Buffer_detach ================== 21*/
_EXTERN_C_ int QMPI_Buffer_detach(void *buffer, int *size, int level,  vector* v){
	return PMPI_Buffer_detach(buffer, size);
}
_EXTERN_C_ int MPI_Buffer_detach(void *buffer, int *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Buffer_detach,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Buffer_detach,&v,buffer, size);
  return ret;
}
/* ================== C Wrappers for MPI_Cancel ================== 22*/
_EXTERN_C_ int QMPI_Cancel(MPI_Request *request, int level,  vector* v){
	return PMPI_Cancel(request);
}
_EXTERN_C_ int MPI_Cancel(MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cancel,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cancel,&v,request);
  return ret;
}
/* ================== C Wrappers for MPI_Cart_coords ================== 23*/
_EXTERN_C_ int QMPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[], int level,  vector* v){
	return PMPI_Cart_coords(comm, rank, maxdims, coords);
}
_EXTERN_C_ int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cart_coords,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cart_coords,&v,comm, rank, maxdims, coords);
  return ret;
}
/* ================== C Wrappers for MPI_Cart_create ================== 24*/
_EXTERN_C_ int QMPI_Cart_create(MPI_Comm old_comm, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart, int level,  vector* v){
	return  PMPI_Cart_create(old_comm, ndims, dims, periods, reorder, comm_cart);
}
_EXTERN_C_ int MPI_Cart_create(MPI_Comm old_comm, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cart_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cart_create,&v,old_comm, ndims, dims, periods, reorder, comm_cart);
  return ret;
}
/* ================== C Wrappers for MPI_Cart_get ==================25 */
_EXTERN_C_ int QMPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[], int level,  vector* v){
	return PMPI_Cart_get( comm, maxdims, dims, periods, coords);
}
_EXTERN_C_ int MPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cart_get,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cart_get,&v,comm, maxdims, dims, periods, coords);
  return ret;
}
/* ================== C Wrappers for MPI_Cart_map ================== 26*/
_EXTERN_C_ int QMPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank, int level,  vector* v){
	return PMPI_Cart_map( comm, ndims, dims, periods, newrank);
}
_EXTERN_C_ int MPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cart_map,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cart_map,&v,comm, ndims, dims, periods, newrank);
  return ret;
}
/* ================== C Wrappers for MPI_Cart_rank ================== 27*/
_EXTERN_C_ int QMPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank, int level,  vector* v){
	return PMPI_Cart_rank(comm, coords, rank);
}
_EXTERN_C_ int MPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cart_rank,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cart_rank,&v,comm, coords, rank);
  return ret;
}
/* ================== C Wrappers for MPI_Cart_shift ================== 28*/
_EXTERN_C_ int QMPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest, int level,  vector* v){
	return PMPI_Cart_shift(comm, direction, disp, rank_source, rank_dest);
}
_EXTERN_C_ int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest) { 

  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cart_shift,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cart_shift,&v,comm, direction, disp, rank_source, rank_dest);
  return ret;
}
/* ================== C Wrappers for MPI_Cart_sub ================== 29*/
_EXTERN_C_ int QMPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *new_comm, int level,  vector* v){
	return PMPI_Cart_sub( comm, remain_dims, new_comm);
}
_EXTERN_C_ int MPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *new_comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cart_sub,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cart_sub,&v,comm, remain_dims, new_comm);
  return ret;
}

/* ================== C Wrappers for MPI_Cartdim_get ================== 30*/
_EXTERN_C_ int QMPI_Cartdim_get(MPI_Comm comm, int *ndims, int level,  vector* v){
	return PMPI_Cartdim_get(comm, ndims);
}
_EXTERN_C_ int MPI_Cartdim_get(MPI_Comm comm, int *ndims) { 
   void* f_dl=NULL;
  QMPI_Table_query(_MPI_Cartdim_get,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Cartdim_get,&v,comm, ndims);
  return ret;
}
/* ================== C Wrappers for MPI_Close_port ================== 31*/
_EXTERN_C_ int QMPI_Close_port(const char *port_name, int level,  vector* v){
	return PMPI_Close_port(port_name);
}
_EXTERN_C_ int MPI_Close_port(const char *port_name) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Close_port,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Close_port,&v,port_name);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_accept ================== 32*/
_EXTERN_C_ int QMPI_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Comm_accept(port_name, info, root, comm, newcomm);
}
_EXTERN_C_ int MPI_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_accept,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_accept,&v,port_name, info, root, comm, newcomm);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_call_errhandler ================== 33*/
_EXTERN_C_ int QMPI_Comm_call_errhandler(MPI_Comm comm, int errorcode, int level,  vector* v){
  return PMPI_Comm_call_errhandler(comm, errorcode);
}
_EXTERN_C_ int MPI_Comm_call_errhandler(MPI_Comm comm, int errorcode) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_call_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_call_errhandler,&v,comm, errorcode);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_compare ================== 34*/
_EXTERN_C_ int QMPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result, int level,  vector* v){
  return PMPI_Comm_compare(comm1, comm2, result);
}
_EXTERN_C_ int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_compare,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_compare,&v,comm1, comm2, result);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_connect ================== 35*/
_EXTERN_C_ int QMPI_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Comm_connect(port_name, info, root, comm, newcomm);
}
_EXTERN_C_ int MPI_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_connect,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_connect,&v,port_name, info, root, comm, newcomm);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_create ================== 36*/
_EXTERN_C_ int QMPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Comm_create(comm, group, newcomm);
}
_EXTERN_C_ int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_create,&v,comm, group, newcomm);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_create_errhandler ================== 37*/
_EXTERN_C_ int QMPI_Comm_create_errhandler(MPI_Comm_errhandler_function *function, MPI_Errhandler *errhandler, int level,  vector* v){
  return PMPI_Comm_create_errhandler(function, errhandler);
}
_EXTERN_C_ int MPI_Comm_create_errhandler(MPI_Comm_errhandler_function *function, MPI_Errhandler *errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_create_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_create_errhandler,&v,function, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_create_group ================== 38*/
_EXTERN_C_ int QMPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Comm_create_group(comm, group, tag, newcomm);
}
_EXTERN_C_ int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_create_group,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_create_group,&v,comm, group, tag, newcomm);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_create_keyval ==================39*/
_EXTERN_C_ int QMPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state, int level,  vector* v){
  return PMPI_Comm_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
}
_EXTERN_C_ int MPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_create_keyval,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_create_keyval,&v,comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_delete_attr ================== 40*/
_EXTERN_C_ int QMPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval, int level,  vector* v){
  return PMPI_Comm_delete_attr(comm, comm_keyval);
}
_EXTERN_C_ int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_delete_attr,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_delete_attr,&v,comm, comm_keyval);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_disconnect ================== 41*/
_EXTERN_C_ int QMPI_Comm_disconnect(MPI_Comm *comm, int level,  vector* v){
  return PMPI_Comm_disconnect(comm);
}
_EXTERN_C_ int MPI_Comm_disconnect(MPI_Comm *comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_disconnect,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_disconnect,&v,comm);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_dup ==================42*/
_EXTERN_C_ int QMPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Comm_dup(comm, newcomm);
}
_EXTERN_C_ int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_dup,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_dup,&v,comm, newcomm);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_dup_with_info ================== 43*/
_EXTERN_C_ int QMPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Comm_dup_with_info(comm, info,newcomm);
}
_EXTERN_C_ int MPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_dup_with_info,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_dup_with_info,&v,comm, info,newcomm);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_free ==================44 */
_EXTERN_C_ int QMPI_Comm_free(MPI_Comm *comm, int level,  vector* v){
  return PMPI_Comm_free(comm);
}
_EXTERN_C_ int MPI_Comm_free(MPI_Comm *comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_free,&v,comm);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_free_keyval ================== 45*/
_EXTERN_C_ int QMPI_Comm_free_keyval(int *comm_keyval, int level,  vector* v){
  return PMPI_Comm_free_keyval(comm_keyval);
}
_EXTERN_C_ int MPI_Comm_free_keyval(int *comm_keyval) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_free_keyval,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_free_keyval,&v,comm_keyval);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_get_attr ================== 46*/
_EXTERN_C_ int QMPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag, int level,  vector* v){
  return PMPI_Comm_get_attr(comm,comm_keyval,attribute_val,flag);
}
_EXTERN_C_ int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_get_attr,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_get_attr,&v,comm,comm_keyval,attribute_val,flag);
  return ret; 
}
/* ================== C Wrappers for MPI_Comm_get_errhandler ================== 47*/
_EXTERN_C_ int QMPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *erhandler, int level,  vector* v){
  return PMPI_Comm_get_errhandler(comm, erhandler);
}
_EXTERN_C_ int MPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *erhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_get_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_get_errhandler,&v,comm, erhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_get_info ================== 48*/
_EXTERN_C_ int QMPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used, int level,  vector* v){
  return PMPI_Comm_get_info(comm,info_used) ;
}
_EXTERN_C_ int MPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_get_info,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_get_info,&v,comm,info_used);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_get_name ==================49 */
_EXTERN_C_ int QMPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen, int level,  vector* v){
  return PMPI_Comm_get_name(comm, comm_name, resultlen);
}
_EXTERN_C_ int MPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_get_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_get_name,&v,comm, comm_name, resultlen);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_get_parent ================== 50*/
_EXTERN_C_ int QMPI_Comm_get_parent(MPI_Comm *parent, int level,  vector* v){
  return PMPI_Comm_get_parent(parent);
}
_EXTERN_C_ int MPI_Comm_get_parent(MPI_Comm *parent) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_get_parent,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_get_parent,&v,parent);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_group ==================51 */
_EXTERN_C_ int QMPI_Comm_group(MPI_Comm comm, MPI_Group *group, int level,  vector* v){
  return PMPI_Comm_group(comm,group);
}
_EXTERN_C_ int MPI_Comm_group(MPI_Comm comm, MPI_Group *group) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_group,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_group,&v,comm,group);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_idup ================== 52*/
_EXTERN_C_ int QMPI_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request, int level,  vector* v){
  return PMPI_Comm_idup(comm, newcomm, request);
}
_EXTERN_C_ int MPI_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_idup,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_idup,&v,comm, newcomm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_join ================== 53*/
_EXTERN_C_ int QMPI_Comm_join(int fd, MPI_Comm *intercomm, int level,  vector* v){
  return PMPI_Comm_join(fd, intercomm);
}
_EXTERN_C_ int MPI_Comm_join(int fd, MPI_Comm *intercomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_join,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_join,&v,fd, intercomm);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_rank ================== 54*/
_EXTERN_C_ int QMPI_Comm_rank(MPI_Comm comm, int *rank, int level,  vector* v){
  return PMPI_Comm_rank(comm, rank);
}
_EXTERN_C_ int MPI_Comm_rank(MPI_Comm comm, int *rank) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_rank,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_rank,&v,comm, rank);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_remote_group ================== 55*/
_EXTERN_C_ int QMPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group, int level,  vector* v){
  return PMPI_Comm_remote_group(comm, group);
}
_EXTERN_C_ int MPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_remote_group,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_remote_group,&v,comm, group);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_remote_size ================== 56*/
_EXTERN_C_ int QMPI_Comm_remote_size(MPI_Comm comm, int *size, int level,  vector* v){
  return PMPI_Comm_remote_size(comm, size);
}
_EXTERN_C_ int MPI_Comm_remote_size(MPI_Comm comm, int *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_remote_size,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_remote_size,&v,comm, size);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_set_attr ================== 57*/
_EXTERN_C_ int QMPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int level,  vector* v){
  return PMPI_Comm_set_attr(comm, comm_keyval, attribute_val);
}
_EXTERN_C_ int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_set_attr,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_set_attr,&v,comm, comm_keyval, attribute_val);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_set_errhandler ==================58 */
_EXTERN_C_ int QMPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler, int level,  vector* v){
  return PMPI_Comm_set_errhandler(comm, errhandler);
}
_EXTERN_C_ int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_set_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_set_errhandler,&v,comm,  errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_set_info ================== 59*/
_EXTERN_C_ int QMPI_Comm_set_info(MPI_Comm comm, MPI_Info info, int level,  vector* v){
  return PMPI_Comm_set_info(comm, info);
}
_EXTERN_C_ int MPI_Comm_set_info(MPI_Comm comm, MPI_Info info) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_set_info,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_set_info,&v,comm, info);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_set_name ================== 60*/
_EXTERN_C_ int QMPI_Comm_set_name(MPI_Comm comm, const char *comm_name, int level,  vector* v){
  return PMPI_Comm_set_name(comm, comm_name) ;
}
_EXTERN_C_ int MPI_Comm_set_name(MPI_Comm comm, const char *comm_name) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_set_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_set_name,&v,comm, comm_name);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_size ================== 61*/
_EXTERN_C_ int QMPI_Comm_size(MPI_Comm comm, int *size, int level,  vector* v){
  return PMPI_Comm_size(comm, size) ;
}
_EXTERN_C_ int MPI_Comm_size(MPI_Comm comm, int *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_size,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_size,&v,comm, size);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_split ================== */
_EXTERN_C_ int QMPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Comm_split(comm, color, key,newcomm);
}
_EXTERN_C_ int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_split,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_split,&v,comm, color, key,newcomm);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_split_type ================== */
_EXTERN_C_ int QMPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Comm_split_type(comm, split_type, key, info, newcomm);
}
_EXTERN_C_ int MPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_split_type,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_split_type,&v,comm, split_type, key, info, newcomm);
  return ret;
}
/* ================== C Wrappers for MPI_Comm_test_inter ================== */
_EXTERN_C_ int QMPI_Comm_test_inter(MPI_Comm comm, int *flag, int level,  vector* v){
  return PMPI_Comm_test_inter(comm, flag);
}
_EXTERN_C_ int MPI_Comm_test_inter(MPI_Comm comm, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Comm_test_inter,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Comm_test_inter,&v,comm, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Compare_and_swap ================== */
_EXTERN_C_ int QMPI_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win, int level,  vector* v){
  return PMPI_Compare_and_swap(origin_addr, compare_addr, result_addr, datatype, target_rank, target_disp, win);
}
_EXTERN_C_ int MPI_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Compare_and_swap,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Compare_and_swap,&v,origin_addr, compare_addr, result_addr, datatype, target_rank, target_disp, win);
  return ret;
}
/* ================== C Wrappers for MPI_Dims_create ================== */
_EXTERN_C_ int QMPI_Dims_create(int nnodes, int ndims, int dims[], int level,  vector* v){
  return PMPI_Dims_create( nnodes, ndims, dims);
}
_EXTERN_C_ int MPI_Dims_create(int nnodes, int ndims, int dims[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Dims_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Dims_create,&v,nnodes, ndims, dims);
  return ret;
}
/* ================== C Wrappers for MPI_Dist_graph_create ================== */
_EXTERN_C_ int QMPI_Dist_graph_create(MPI_Comm comm_old, int n, const int nodes[], const int degrees[], const int targets[], const int weights[], MPI_Info info, int reorder, MPI_Comm *newcomm, int level,  vector* v){
  return PMPI_Dist_graph_create(comm_old, n, nodes, degrees, targets, weights, info, reorder, newcomm);
}
_EXTERN_C_ int MPI_Dist_graph_create(MPI_Comm comm_old, int n, const int nodes[], const int degrees[], const int targets[], const int weights[], MPI_Info info, int reorder, MPI_Comm *newcomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Dist_graph_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Dist_graph_create,&v,comm_old, n, nodes, degrees, targets, weights, info, reorder, newcomm);
  return ret;
}
/* ================== C Wrappers for MPI_Dist_graph_create_adjacent ================== */
_EXTERN_C_ int QMPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph, int level,  vector* v){
  return PMPI_Dist_graph_create_adjacent(comm_old, indegree, sources, sourceweights, outdegree, destinations, destweights,  info, reorder, comm_dist_graph);

}
_EXTERN_C_ int MPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Dist_graph_create_adjacent,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Dist_graph_create_adjacent,&v,comm_old, indegree, sources, sourceweights, outdegree, destinations, destweights,  info, reorder, comm_dist_graph);
  return ret;
}
/* ================== C Wrappers for MPI_Dist_graph_neighbors ================== */
_EXTERN_C_ int QMPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[], int level,  vector* v){
  return PMPI_Dist_graph_neighbors(comm, maxindegree,sources, sourceweights, maxoutdegree, destinations, destweights);
}
_EXTERN_C_ int MPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Dist_graph_neighbors,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Dist_graph_neighbors,&v,comm, maxindegree,sources, sourceweights, maxoutdegree, destinations, destweights);
  return ret;
}
/* ================== C Wrappers for MPI_Dist_graph_neighbors_count ================== */
_EXTERN_C_ int QMPI_Dist_graph_neighbors_count(MPI_Comm comm, int *inneighbors, int *outneighbors, int *weighted, int level,  vector* v){
  return PMPI_Dist_graph_neighbors_count(comm, inneighbors, outneighbors, weighted);
}
_EXTERN_C_ int MPI_Dist_graph_neighbors_count(MPI_Comm comm, int *inneighbors, int *outneighbors, int *weighted) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Dist_graph_neighbors_count,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Dist_graph_neighbors_count,&v,comm, inneighbors, outneighbors, weighted);
  return ret;
}
/* ================== C Wrappers for MPI_Errhandler_create ================== */
_EXTERN_C_ int QMPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler, int level,  vector* v){
  return PMPI_Errhandler_create(function, errhandler);
}
_EXTERN_C_ int MPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Errhandler_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Errhandler_create,&v,function, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Errhandler_free ================== */
_EXTERN_C_ int QMPI_Errhandler_free(MPI_Errhandler *errhandler, int level,  vector* v){
  return PMPI_Errhandler_free(errhandler);
}
_EXTERN_C_ int MPI_Errhandler_free(MPI_Errhandler *errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Errhandler_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Errhandler_free,&v, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Errhandler_get ================== */
_EXTERN_C_ int QMPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler, int level,  vector* v){
  return PMPI_Errhandler_get(comm, errhandler);
}
_EXTERN_C_ int MPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Errhandler_get,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Errhandler_get,&v,comm, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Errhandler_set ================== */
_EXTERN_C_ int QMPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler, int level,  vector* v){
  return PMPI_Errhandler_set(comm, errhandler);
}
_EXTERN_C_ int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Errhandler_set,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Errhandler_set,&v,comm, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Error_class ================== */
_EXTERN_C_ int QMPI_Error_class(int errorcode, int *errorclass, int level,  vector* v){
  return PMPI_Error_class(errorcode, errorclass);
}
_EXTERN_C_ int MPI_Error_class(int errorcode, int *errorclass) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Error_class,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Error_class,&v,errorcode, errorclass);
  return ret;
}
/* ================== C Wrappers for MPI_Error_string ================== */
_EXTERN_C_ int QMPI_Error_string(int errorcode, char *string, int *resultlen, int level,  vector* v){
  return PMPI_Error_string(errorcode, string, resultlen);
}
_EXTERN_C_ int MPI_Error_string(int errorcode, char *string, int *resultlen) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Error_string,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Error_string,&v,errorcode, string, resultlen);
  return ret;
}
/* ================== C Wrappers for MPI_Exscan ================== */
_EXTERN_C_ int QMPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level,  vector* v){
  return PMPI_Exscan(sendbuf, recvbuf, count, datatype, op, comm);
}
_EXTERN_C_ int MPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Exscan,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Exscan,&v,sendbuf, recvbuf, count, datatype, op, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Fetch_and_op ================== */
_EXTERN_C_ int QMPI_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win, int level,  vector* v){
  return PMPI_Fetch_and_op(origin_addr, result_addr, datatype, target_rank, target_disp, op, win);
}
_EXTERN_C_ int MPI_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Fetch_and_op,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Fetch_and_op,&v,origin_addr, result_addr, datatype, target_rank, target_disp, op, win);
  return ret;
}
/* ================== C Wrappers for MPI_File_call_errhandler ================== */
_EXTERN_C_ int QMPI_File_call_errhandler(MPI_File fh, int errorcode, int level,  vector* v){
  return PMPI_File_call_errhandler(fh, errorcode);
}
_EXTERN_C_ int MPI_File_call_errhandler(MPI_File fh, int errorcode) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_call_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_call_errhandler,&v,fh, errorcode);
  return ret;
}
/* ================== C Wrappers for MPI_File_close ================== */
_EXTERN_C_ int QMPI_File_close(MPI_File *fh, int level,  vector* v){
  return PMPI_File_close(fh);
}
_EXTERN_C_ int MPI_File_close(MPI_File *fh) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_close,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_close,&v,fh);
  return ret;
}
/* ================== C Wrappers for MPI_File_create_errhandler ================== */
_EXTERN_C_ int QMPI_File_create_errhandler(MPI_File_errhandler_function *function, MPI_Errhandler *errhandler, int level,  vector* v){
  return PMPI_File_create_errhandler(function, errhandler);
}
_EXTERN_C_ int MPI_File_create_errhandler(MPI_File_errhandler_function *function, MPI_Errhandler *errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_create_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_create_errhandler,&v,function, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_File_delete ================== */
_EXTERN_C_ int QMPI_File_delete(const char *filename, MPI_Info info, int level,  vector* v){
  return PMPI_File_delete(filename, info);
}
_EXTERN_C_ int MPI_File_delete(const char *filename, MPI_Info info) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_delete,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_delete,&v,filename, info);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_amode ================== */
_EXTERN_C_ int QMPI_File_get_amode(MPI_File fh, int *amode, int level,  vector* v){
  return PMPI_File_get_amode(fh, amode);
}
_EXTERN_C_ int MPI_File_get_amode(MPI_File fh, int *amode) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_amode,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_amode,&v,fh, amode);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_atomicity ================== */
_EXTERN_C_ int QMPI_File_get_atomicity(MPI_File fh, int *flag, int level,  vector* v){
  return PMPI_File_get_atomicity( fh, flag);
}
_EXTERN_C_ int MPI_File_get_atomicity(MPI_File fh, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_atomicity,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_atomicity,&v, fh, flag);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_byte_offset ================== */
_EXTERN_C_ int QMPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp, int level,  vector* v){
  return PMPI_File_get_byte_offset(fh, offset, disp);
}
_EXTERN_C_ int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_byte_offset,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_byte_offset,&v,fh, offset, disp);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_errhandler ================== */
_EXTERN_C_ int QMPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler, int level,  vector* v){
  return PMPI_File_get_errhandler( file, errhandler);
}
_EXTERN_C_ int MPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_errhandler,&v,file, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_group ================== */
_EXTERN_C_ int QMPI_File_get_group(MPI_File fh, MPI_Group *group, int level,  vector* v){
  return PMPI_File_get_group( fh, group);
}
_EXTERN_C_ int MPI_File_get_group(MPI_File fh, MPI_Group *group) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_group,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_group,&v,fh, group);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_info ================== */
_EXTERN_C_ int QMPI_File_get_info(MPI_File fh, MPI_Info *info_used, int level,  vector* v){
  return PMPI_File_get_info( fh, info_used);
}
_EXTERN_C_ int MPI_File_get_info(MPI_File fh, MPI_Info *info_used) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_info,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_info,&v,fh, info_used);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_position ================== */
_EXTERN_C_ int QMPI_File_get_position(MPI_File fh, MPI_Offset *offset, int level,  vector* v){
  return PMPI_File_get_position( fh, offset);
}
_EXTERN_C_ int MPI_File_get_position(MPI_File fh, MPI_Offset *offset) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_position,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_position,&v,fh, offset);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_position_shared ================== */
_EXTERN_C_ int QMPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset, int level,  vector* v){
  return PMPI_File_get_position_shared( fh, offset);
}
_EXTERN_C_ int MPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_position_shared,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_position_shared,&v,fh, offset);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_size ================== */
_EXTERN_C_ int QMPI_File_get_size(MPI_File fh, MPI_Offset *size, int level,  vector* v){
  return PMPI_File_get_size( fh, size);
}
_EXTERN_C_ int MPI_File_get_size(MPI_File fh, MPI_Offset *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_size,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_size,&v,fh, size);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_type_extent ================== */
_EXTERN_C_ int QMPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent, int level,  vector* v){
  return PMPI_File_get_type_extent( fh,  datatype, extent);
}
_EXTERN_C_ int MPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_type_extent,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_type_extent,&v,fh,  datatype, extent);
  return ret;
}
/* ================== C Wrappers for MPI_File_get_view ================== */
_EXTERN_C_ int QMPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep, int level,  vector* v){
  return PMPI_File_get_view( fh, disp, etype, filetype, datarep);
}
_EXTERN_C_ int MPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_get_view,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_get_view,&v,fh, disp, etype, filetype, datarep);
  return ret;
}
/* ================== C Wrappers for MPI_File_iread ================== */
_EXTERN_C_ int QMPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iread( fh, buf, count, datatype, request);
}
_EXTERN_C_ int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iread,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iread,&v,fh, buf, count, datatype, request);
  return ret;
}
/* ================== C Wrappers for MPI_File_iread_all ================== */
_EXTERN_C_ int QMPI_File_iread_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iread_all( fh, buf, count, datatype, request);
}
_EXTERN_C_ int MPI_File_iread_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iread_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iread_all,&v,fh, buf, count, datatype, request);
  return ret;
}

/* ================== C Wrappers for MPI_File_iread_at ================== */
_EXTERN_C_ int QMPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iread_at(fh, offset, buf, count,  datatype, request);
}
_EXTERN_C_ int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iread_at,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iread_at,&v,fh, offset, buf, count,  datatype, request);
  return ret;
}
/* ================== C Wrappers for MPI_File_iread_at_all ================== */
_EXTERN_C_ int QMPI_File_iread_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iread_at_all( fh, offset, buf, count, datatype, request) ;
}
_EXTERN_C_ int MPI_File_iread_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iread_at_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iread_at_all,&v, fh, offset, buf, count, datatype, request);
  return ret;
}
/* ================== C Wrappers for MPI_File_iread_shared ================== */
_EXTERN_C_ int QMPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iread_shared( fh, buf, count, datatype, request);
}
_EXTERN_C_ int MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iread_shared,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iread_shared,&v, fh, buf, count, datatype, request);
  return ret;
}
/* ================== C Wrappers for MPI_File_iwrite ================== */
_EXTERN_C_ int QMPI_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iwrite( fh, buf, count,  datatype, request);
}
_EXTERN_C_ int MPI_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iwrite,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iwrite,&v,fh, buf, count,  datatype, request);
  return ret;
}
/* ================== C Wrappers for MPI_File_iwrite_all ================== */
_EXTERN_C_ int QMPI_File_iwrite_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iwrite_all(fh, buf, count, datatype, request);
}
_EXTERN_C_ int MPI_File_iwrite_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iwrite_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iwrite_all,&v,fh, buf, count, datatype, request);
  return ret;
}
/* ================== C Wrappers for MPI_File_iwrite_at ================== */
_EXTERN_C_ int QMPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iwrite_at( fh, offset, buf, count,  datatype, request);
}
_EXTERN_C_ int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iwrite_at,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iwrite_at,&v, fh, offset, buf, count,  datatype, request);
  return ret;
}
/* ================== C Wrappers for MPI_File_iwrite_at_all ================== */
_EXTERN_C_ int QMPI_File_iwrite_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iwrite_at_all( fh, offset, buf, count, datatype, request) ;
}
_EXTERN_C_ int MPI_File_iwrite_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iwrite_at_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iwrite_at_all,&v,  fh, offset, buf, count, datatype, request);
  return ret;
}
/* ================== C Wrappers for MPI_File_iwrite_shared ================== */
_EXTERN_C_ int QMPI_File_iwrite_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v){
  return PMPI_File_iwrite_shared( fh, buf,  count, datatype,  request) ;
}
_EXTERN_C_ int MPI_File_iwrite_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_iwrite_shared,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_iwrite_shared,&v,fh, buf,  count, datatype,  request);
  return ret;
}
/* ================== C Wrappers for MPI_File_open ================== */
_EXTERN_C_ int QMPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh, int level,  vector* v){
  return PMPI_File_open( comm, filename, amode, info, fh);
}
_EXTERN_C_ int MPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_open,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_open,&v,comm, filename, amode, info, fh);
  return ret;
}
/* ================== C Wrappers for MPI_File_preallocate ================== */
_EXTERN_C_ int QMPI_File_preallocate(MPI_File fh, MPI_Offset size, int level,  vector* v){
  return PMPI_File_preallocate( fh, size);
}
_EXTERN_C_ int MPI_File_preallocate(MPI_File fh, MPI_Offset size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_preallocate,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_preallocate,&v,fh, size);
  return ret;
}
/* ================== C Wrappers for MPI_File_read ================== */
_EXTERN_C_ int QMPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read( fh, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read,&v,fh, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_all ================== */
_EXTERN_C_ int QMPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read_all(fh, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_all,&v,fh, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_all_begin ================== */
_EXTERN_C_ int QMPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype, int level,  vector* v){
  return PMPI_File_read_all_begin( fh, buf, count, datatype);
}
_EXTERN_C_ int MPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_all_begin,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_all_begin,&v, fh, buf, count, datatype);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_all_end ================== */
_EXTERN_C_ int QMPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read_all_end( fh, buf, status);
}
_EXTERN_C_ int MPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_all_end,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_all_end,&v,  fh, buf, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_at ================== */
_EXTERN_C_ int QMPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read_at( fh,  offset, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_at,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_at,&v, fh,  offset, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_at_all ================== */
_EXTERN_C_ int QMPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read_at_all( fh, offset, buf, count, datatype, status) ;
}
_EXTERN_C_ int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_at_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_at_all,&v,  fh, offset, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_at_all_begin ================== */
_EXTERN_C_ int QMPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, int level,  vector* v){
  return PMPI_File_read_at_all_begin( fh, offset, buf, count, datatype);
}
_EXTERN_C_ int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_at_all_begin,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_at_all_begin,&v,  fh, offset, buf, count, datatype);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_at_all_end ================== */
_EXTERN_C_ int QMPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read_at_all_end( fh, buf, status) ;
}
_EXTERN_C_ int MPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_at_all_end,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_at_all_end,&v,  fh, buf, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_ordered ================== */
_EXTERN_C_ int QMPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read_ordered( fh, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_ordered,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_ordered,&v,   fh, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_ordered_begin ================== */
_EXTERN_C_ int QMPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype, int level,  vector* v){
  return PMPI_File_read_ordered_begin( fh, buf, count, datatype);
}
_EXTERN_C_ int MPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_ordered_begin,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_ordered_begin,&v, fh, buf, count, datatype);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_ordered_end ================== */
_EXTERN_C_ int QMPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read_ordered_end( fh, buf, status);
}
_EXTERN_C_ int MPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_ordered_end,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_ordered_end,&v,fh, buf, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_read_shared ================== */
_EXTERN_C_ int QMPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_read_shared( fh, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_read_shared,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_read_shared,&v,fh, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_seek ================== */
_EXTERN_C_ int QMPI_File_seek(MPI_File fh, MPI_Offset offset, int whence, int level,  vector* v){
  return PMPI_File_seek( fh, offset, whence);
}
_EXTERN_C_ int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_seek,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_seek,&v,fh, offset, whence);
  return ret;
}
/* ================== C Wrappers for MPI_File_seek_shared ================== */
_EXTERN_C_ int QMPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence, int level,  vector* v){
  return PMPI_File_seek_shared( fh, offset, whence);
}
_EXTERN_C_ int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_seek_shared,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_seek_shared,&v,fh, offset, whence);
  return ret;
}
/* ================== C Wrappers for MPI_File_set_atomicity ================== */
_EXTERN_C_ int QMPI_File_set_atomicity(MPI_File fh, int flag, int level,  vector* v){
  return PMPI_File_set_atomicity( fh, flag);
}
_EXTERN_C_ int MPI_File_set_atomicity(MPI_File fh, int flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_set_atomicity,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_set_atomicity,&v,fh, flag);
  return ret;
}
/* ================== C Wrappers for MPI_File_set_errhandler ================== */
_EXTERN_C_ int QMPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler, int level,  vector* v){
  return PMPI_File_set_errhandler( file, errhandler) ;
}
_EXTERN_C_ int MPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_set_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_set_errhandler,&v, file, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_File_set_info ================== */
_EXTERN_C_ int QMPI_File_set_info(MPI_File fh, MPI_Info info, int level,  vector* v){
  return PMPI_File_set_info( fh, info);
}
_EXTERN_C_ int MPI_File_set_info(MPI_File fh, MPI_Info info) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_set_info,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_set_info,&v, fh, info);
  return ret;
}
/* ================== C Wrappers for MPI_File_set_size ================== */
_EXTERN_C_ int QMPI_File_set_size(MPI_File fh, MPI_Offset size, int level,  vector* v){
  return PMPI_File_set_size( fh, size);
}
_EXTERN_C_ int MPI_File_set_size(MPI_File fh, MPI_Offset size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_set_size,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_set_size,&v,  fh, size);
  return ret;
}
/* ================== C Wrappers for MPI_File_set_view ================== */
_EXTERN_C_ int QMPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info, int level,  vector* v){
  return PMPI_File_set_view( fh, disp, etype, filetype, datarep, info);
}
_EXTERN_C_ int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_set_view,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_set_view,&v,  fh, disp, etype, filetype, datarep, info);
  return ret;
}
/* ================== C Wrappers for MPI_File_sync ================== */
_EXTERN_C_ int QMPI_File_sync(MPI_File fh, int level,  vector* v){
  return PMPI_File_sync( fh) ;
}
_EXTERN_C_ int MPI_File_sync(MPI_File fh) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_sync,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_sync,&v,  fh);
  return ret;
}
/* ================== C Wrappers for MPI_File_write ================== */
_EXTERN_C_ int QMPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write( fh, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write,&v, fh, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_all ================== */
_EXTERN_C_ int QMPI_File_write_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write_all( fh, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_write_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_all,&v, fh, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_all_begin ================== */
_EXTERN_C_ int QMPI_File_write_all_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, int level,  vector* v){
  return PMPI_File_write_all_begin( fh, buf, count, datatype);
}
_EXTERN_C_ int MPI_File_write_all_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_all_begin,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_all_begin,&v, fh, buf, count, datatype);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_all_end ================== */
_EXTERN_C_ int QMPI_File_write_all_end(MPI_File fh, const void *buf, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write_all_end( fh, buf, status);
}
_EXTERN_C_ int MPI_File_write_all_end(MPI_File fh, const void *buf, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_all_end,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_all_end,&v,fh, buf, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_at ================== */
_EXTERN_C_ int QMPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write_at( fh, offset, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_at,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_at,&v,fh, offset, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_at_all ================== */
_EXTERN_C_ int QMPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write_at_all( fh, offset, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_at_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_at_all,&v,fh, offset, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_at_all_begin ================== */
_EXTERN_C_ int QMPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, int level,  vector* v){
  return PMPI_File_write_at_all_begin( fh, offset, buf, count, datatype) ;
}
_EXTERN_C_ int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_at_all_begin,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_at_all_begin,&v,fh, offset, buf, count, datatype);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_at_all_end ================== */
_EXTERN_C_ int QMPI_File_write_at_all_end(MPI_File fh, const void *buf, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write_at_all_end( fh, buf, status);
}
_EXTERN_C_ int MPI_File_write_at_all_end(MPI_File fh, const void *buf, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_at_all_end,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_at_all_end,&v,fh, buf, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_ordered ================== */
_EXTERN_C_ int QMPI_File_write_ordered(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write_ordered( fh, buf, count, datatype, status);
}
_EXTERN_C_ int MPI_File_write_ordered(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_ordered,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_ordered,&v,fh, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_ordered_begin ================== */
_EXTERN_C_ int QMPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, int level,  vector* v){
  return PMPI_File_write_ordered_begin( fh, buf, count, datatype) ; 
}
_EXTERN_C_ int MPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_ordered_begin,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_ordered_begin,&v,fh, buf, count, datatype);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_ordered_end ================== */
_EXTERN_C_ int QMPI_File_write_ordered_end(MPI_File fh, const void *buf, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write_ordered_end(fh, buf, status) ;
}
_EXTERN_C_ int MPI_File_write_ordered_end(MPI_File fh, const void *buf, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_ordered_end,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_ordered_end,&v,fh, buf, status);
  return ret;
}
/* ================== C Wrappers for MPI_File_write_shared ================== */
_EXTERN_C_ int QMPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v){
  return PMPI_File_write_shared( fh, buf, count, datatype, status) ;
}
_EXTERN_C_ int MPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_File_write_shared,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_File_write_shared,&v,fh, buf, count, datatype, status);
  return ret;
}
/* ================== C Wrappers for MPI_Finalize ================== */
_EXTERN_C_ int QMPI_Finalize( int level,  vector* v){
  return PMPI_Finalize();
}
_EXTERN_C_ int MPI_Finalize() { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Finalize,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Finalize,&v);
  return ret;
}
/* ================== C Wrappers for MPI_Finalized ================== */
_EXTERN_C_ int QMPI_Finalized(int *flag, int level,  vector* v){
  return PMPI_Finalized(flag);
}
_EXTERN_C_ int MPI_Finalized(int *flag) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Finalized,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Finalized,&v);
  return ret;
}
/* ================== C Wrappers for MPI_Free_mem ================== */
_EXTERN_C_ int QMPI_Free_mem(void *base, int level,  vector* v){
  return PMPI_Free_mem(base);
}
_EXTERN_C_ int MPI_Free_mem(void *base) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Free_mem,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Free_mem,&v,base);
  return ret;
}
/* ================== C Wrappers for MPI_Gather ================== */
_EXTERN_C_ int QMPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level,  vector* v){
  return PMPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}
_EXTERN_C_ int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Gather,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Gather,&v,sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Gatherv ================== */
_EXTERN_C_ int QMPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, int level,  vector* v){
  return PMPI_Gatherv( sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
}
_EXTERN_C_ int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Gatherv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Gatherv,&v,sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Get ================== */
_EXTERN_C_ int QMPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, int level,  vector* v){
  return PMPI_Get( origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}
_EXTERN_C_ int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get,&v, origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
  return ret;
}
/* ================== C Wrappers for MPI_Get_accumulate ================== */
_EXTERN_C_ int QMPI_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, int level,  vector* v){
  return PMPI_Get_accumulate( origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
}
_EXTERN_C_ int MPI_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get_accumulate,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get_accumulate,&v,origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
  return ret;
}
/* ================== C Wrappers for MPI_Get_address ================== */
_EXTERN_C_ int QMPI_Get_address(const void *location, MPI_Aint *address, int level,  vector* v){
  return PMPI_Get_address( location, address);
}
_EXTERN_C_ int MPI_Get_address(const void *location, MPI_Aint *address) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get_address,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get_address,&v, location, address);
  return ret;
}
/* ================== C Wrappers for MPI_Get_count ================== */
_EXTERN_C_ int QMPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count, int level,  vector* v){
  return PMPI_Get_count( status, datatype, count);
}
_EXTERN_C_ int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get_count,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get_count,&v,status, datatype, count);
  return ret;
}
/* ================== C Wrappers for MPI_Get_elements ================== */
_EXTERN_C_ int QMPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count, int level,  vector* v){
  return PMPI_Get_elements(status, datatype, count) ;
}
_EXTERN_C_ int MPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get_elements,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get_elements,&v, status, datatype, count);
  return ret;
}
/* ================== C Wrappers for MPI_Get_elements_x ================== */
_EXTERN_C_ int QMPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count, int level,  vector* v){
  return PMPI_Get_elements_x( status, datatype, count);
}
_EXTERN_C_ int MPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get_elements_x,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get_elements_x,&v, status, datatype, count);
  return ret;
}
/* ================== C Wrappers for MPI_Get_library_version ================== */
_EXTERN_C_ int QMPI_Get_library_version(char *version, int *resultlen, int level,  vector* v){
  return PMPI_Get_library_version( version, resultlen);
}
_EXTERN_C_ int MPI_Get_library_version(char *version, int *resultlen) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get_library_version,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get_library_version,&v, version, resultlen);
  return ret;
}
/* ================== C Wrappers for MPI_Get_processor_name ================== */
_EXTERN_C_ int QMPI_Get_processor_name(char *name, int *resultlen, int level,  vector* v){
  return PMPI_Get_processor_name( name, resultlen) ;
}
_EXTERN_C_ int MPI_Get_processor_name(char *name, int *resultlen) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get_processor_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get_processor_name,&v, name, resultlen);
  return ret;
}
/* ================== C Wrappers for MPI_Get_version ================== */
_EXTERN_C_ int QMPI_Get_version(int *version, int *subversion, int level,  vector* v){
  return PMPI_Get_version( version, subversion) ;
}
_EXTERN_C_ int MPI_Get_version(int *version, int *subversion) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Get_version,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Get_version,&v,version, subversion);
  return ret;
}
/* ================== C Wrappers for MPI_Graph_create ================== */
_EXTERN_C_ int QMPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph, int level,  vector* v){
  return PMPI_Graph_create( comm_old, nnodes, index, edges, reorder, comm_graph);
}
_EXTERN_C_ int MPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Graph_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Graph_create,&v,comm_old, nnodes, index, edges, reorder, comm_graph);
  return ret;
}
/* ================== C Wrappers for MPI_Graph_get ================== */
_EXTERN_C_ int QMPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int index[], int edges[], int level,  vector* v){
  return PMPI_Graph_get( comm, maxindex, maxedges, index, edges);
}
_EXTERN_C_ int MPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int index[], int edges[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Graph_get,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Graph_get,&v,comm, maxindex, maxedges, index, edges);
  return ret;
}
/* ================== C Wrappers for MPI_Graph_map ================== */
_EXTERN_C_ int QMPI_Graph_map(MPI_Comm comm, int nnodes, const int index[], const int edges[], int *newrank, int level,  vector* v){
  return PMPI_Graph_map(comm, nnodes, index, edges, newrank);
}
_EXTERN_C_ int MPI_Graph_map(MPI_Comm comm, int nnodes, const int index[], const int edges[], int *newrank) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Graph_map,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Graph_map,&v,comm, nnodes, index, edges, newrank);
  return ret;
}
/* ================== C Wrappers for MPI_Graph_neighbors ================== */
_EXTERN_C_ int QMPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[], int level,  vector* v){
  return PMPI_Graph_neighbors(comm, rank, maxneighbors,  neighbors);
}
_EXTERN_C_ int MPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Graph_neighbors,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Graph_neighbors,&v,comm, rank, maxneighbors,  neighbors);
  return ret;
}
/* ================== C Wrappers for MPI_Graph_neighbors_count ================== */
_EXTERN_C_ int QMPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors, int level,  vector* v){
  return PMPI_Graph_neighbors_count( comm, rank, nneighbors) ;
}
_EXTERN_C_ int MPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Graph_neighbors_count,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Graph_neighbors_count,&v, comm, rank, nneighbors);
  return ret;
}
/* ================== C Wrappers for MPI_Graphdims_get ================== */
_EXTERN_C_ int QMPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges, int level,  vector* v){
  return PMPI_Graphdims_get(comm, nnodes, nedges);
}
_EXTERN_C_ int MPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Graphdims_get,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Graphdims_get,&v,comm, nnodes, nedges);
  return ret;
}
/* ================== C Wrappers for MPI_Grequest_complete ================== */
_EXTERN_C_ int QMPI_Grequest_complete(MPI_Request request, int level,  vector* v){
  return PMPI_Grequest_complete(request);
}
_EXTERN_C_ int MPI_Grequest_complete(MPI_Request request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Grequest_complete,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Grequest_complete,&v,request);
  return ret;
}
/* ================== C Wrappers for MPI_Grequest_start ================== */
_EXTERN_C_ int QMPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request, int level,  vector* v){
  return PMPI_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, request);
}
_EXTERN_C_ int MPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Grequest_start,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Grequest_start,&v,query_fn, free_fn, cancel_fn, extra_state, request);
  return ret;
}
/* ================== C Wrappers for MPI_Group_compare ================== */
_EXTERN_C_ int QMPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result, int level,  vector* v){
  return PMPI_Group_compare( group1, group2, result);
}
_EXTERN_C_ int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_compare,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_compare,&v,group1, group2, result);
  return ret;
}
/* ================== C Wrappers for MPI_Group_difference ================== */
_EXTERN_C_ int QMPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level,  vector* v){
  return PMPI_Group_difference(group1, group2, newgroup);
}
_EXTERN_C_ int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_difference,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_difference,&v,group1, group2, newgroup);
  return ret;
}
/* ================== C Wrappers for MPI_Group_excl ================== */
_EXTERN_C_ int QMPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup, int level,  vector* v){
  return PMPI_Group_excl( group, n, ranks, newgroup);
}
_EXTERN_C_ int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_excl,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_excl,&v,group, n, ranks, newgroup);
  return ret;
}
/* ================== C Wrappers for MPI_Group_free ================== */
_EXTERN_C_ int QMPI_Group_free(MPI_Group *group, int level,  vector* v){
  return PMPI_Group_free(group);
}
_EXTERN_C_ int MPI_Group_free(MPI_Group *group) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_free,&v,group);
  return ret;
}
/* ================== C Wrappers for MPI_Group_incl ================== */
_EXTERN_C_ int QMPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup, int level,  vector* v){
  return PMPI_Group_incl( group, n, ranks, newgroup);
}
_EXTERN_C_ int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_incl,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_incl,&v,group, n, ranks, newgroup);
  return ret;
}
/* ================== C Wrappers for MPI_Group_intersection ================== */
_EXTERN_C_ int QMPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level,  vector* v){
  return PMPI_Group_intersection(group1, group2, newgroup);
}
_EXTERN_C_ int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_intersection,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_intersection,&v,group1, group2, newgroup);
  return ret;
}
/* ================== C Wrappers for MPI_Group_range_excl ================== */
_EXTERN_C_ int QMPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup, int level,  vector* v){
  return PMPI_Group_range_excl( group, n, ranges, newgroup);
}
_EXTERN_C_ int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_range_excl,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_range_excl,&v, group, n, ranges, newgroup);
  return ret;
}
/* ================== C Wrappers for MPI_Group_range_incl ================== */
_EXTERN_C_ int QMPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup, int level,  vector* v){
  return PMPI_Group_range_incl( group, n, ranges, newgroup);
}
_EXTERN_C_ int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_range_incl,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_range_incl,&v,group, n, ranges, newgroup);
  return ret;
}
/* ================== C Wrappers for MPI_Group_rank ================== */
_EXTERN_C_ int QMPI_Group_rank(MPI_Group group, int *rank, int level,  vector* v){
  return PMPI_Group_rank( group, rank);
}
_EXTERN_C_ int MPI_Group_rank(MPI_Group group, int *rank) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_rank,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_rank,&v,group, rank);
  return ret;
}
/* ================== C Wrappers for MPI_Group_size ================== */
_EXTERN_C_ int QMPI_Group_size(MPI_Group group, int *size, int level,  vector* v){
  return PMPI_Group_size( group, size);
}
_EXTERN_C_ int MPI_Group_size(MPI_Group group, int *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_size,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_size,&v,  group, size);
  return ret;
}
/* ================== C Wrappers for MPI_Group_translate_ranks ================== */
_EXTERN_C_ int QMPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[], int level,  vector* v){
  return PMPI_Group_translate_ranks( group1, n, ranks1, group2, ranks2 );
}
_EXTERN_C_ int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_translate_ranks,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_translate_ranks,&v,  group1, n, ranks1, group2, ranks2);
  return ret;
}
/* ================== C Wrappers for MPI_Group_union ================== */
_EXTERN_C_ int QMPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level,  vector* v){
  return PMPI_Group_union( group1, group2, newgroup);
}
_EXTERN_C_ int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Group_union,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Group_union,&v, group1, group2, newgroup);
  return ret;
}
/* ================== C Wrappers for MPI_Iallgather ================== */
_EXTERN_C_ int QMPI_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Iallgather( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}
_EXTERN_C_ int MPI_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Iallgather,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Iallgather,&v, sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Iallgatherv ================== */
_EXTERN_C_ int QMPI_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Iallgatherv( sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}
_EXTERN_C_ int MPI_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Iallgatherv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Iallgatherv,&v,sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Iallreduce ================== */
_EXTERN_C_ int QMPI_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Iallreduce( sendbuf, recvbuf, count, datatype, op, comm, request) ;
}
_EXTERN_C_ int MPI_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Iallreduce,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Iallreduce,&v,sendbuf, recvbuf, count, datatype, op, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ialltoall ================== */
_EXTERN_C_ int QMPI_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ialltoall( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}
_EXTERN_C_ int MPI_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ialltoall,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ialltoall,&v,sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ialltoallv ================== */
_EXTERN_C_ int QMPI_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ialltoallv( sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}
_EXTERN_C_ int MPI_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ialltoallv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ialltoallv,&v,sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ialltoallw ================== */
_EXTERN_C_ int QMPI_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}
_EXTERN_C_ int MPI_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ialltoallw,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ialltoallw,&v,sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ibarrier ================== */
_EXTERN_C_ int QMPI_Ibarrier(MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ibarrier( comm, request) ;
}
_EXTERN_C_ int MPI_Ibarrier(MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ibarrier,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ibarrier,&v,comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ibcast ================== */
_EXTERN_C_ int QMPI_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ibcast(buffer, count, datatype, root, comm, request);
}
_EXTERN_C_ int MPI_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ibcast,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ibcast,&v,buffer, count, datatype, root, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ibsend ================== */
_EXTERN_C_ int QMPI_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ibsend( buf, count, datatype, dest, tag, comm, request);
}
_EXTERN_C_ int MPI_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ibsend,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ibsend,&v,buf, count, datatype, dest, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Iexscan ================== */
_EXTERN_C_ int QMPI_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Iexscan( sendbuf, recvbuf, count, datatype, op, comm, request);
}
_EXTERN_C_ int MPI_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Iexscan,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Iexscan,&v,sendbuf, recvbuf, count, datatype, op, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Igather ================== */
_EXTERN_C_ int QMPI_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Igather( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request) ;
}
_EXTERN_C_ int MPI_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Igather,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Igather,&v,sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Igatherv ================== */
_EXTERN_C_ int QMPI_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Igatherv( sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, request) ;
}
_EXTERN_C_ int MPI_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Igatherv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Igatherv,&v,sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Improbe ================== */
_EXTERN_C_ int QMPI_Improbe(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status, int level,  vector* v){
  return PMPI_Improbe( source, tag, comm, flag, message, status);
}
_EXTERN_C_ int MPI_Improbe(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Improbe,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Improbe,&v,source, tag, comm, flag, message, status);
  return ret;
}
/* ================== C Wrappers for MPI_Imrecv ================== */
_EXTERN_C_ int QMPI_Imrecv(void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Request *request, int level,  vector* v){
  return PMPI_Imrecv( buf, count, type, message, request);
}
_EXTERN_C_ int MPI_Imrecv(void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Imrecv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Imrecv,&v,buf, count, type, message, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ineighbor_allgather ================== */
_EXTERN_C_ int QMPI_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ineighbor_allgather( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}
_EXTERN_C_ int MPI_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ineighbor_allgather,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ineighbor_allgather,&v, sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ineighbor_allgatherv ================== */
_EXTERN_C_ int QMPI_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ineighbor_allgatherv( sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
}
_EXTERN_C_ int MPI_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ineighbor_allgatherv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ineighbor_allgatherv,&v, sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ineighbor_alltoall ================== */
_EXTERN_C_ int QMPI_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ineighbor_alltoall( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
}
_EXTERN_C_ int MPI_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ineighbor_alltoall,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ineighbor_alltoall,&v, sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ineighbor_alltoallv ================== */
_EXTERN_C_ int QMPI_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ineighbor_alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
}
_EXTERN_C_ int MPI_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ineighbor_alltoallv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ineighbor_alltoallv,&v, sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ineighbor_alltoallw ================== */
_EXTERN_C_ int QMPI_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ineighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
}
_EXTERN_C_ int MPI_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ineighbor_alltoallw,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ineighbor_alltoallw,&v, sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Info_create ================== */
_EXTERN_C_ int QMPI_Info_create(MPI_Info *info, int level,  vector* v){
  return PMPI_Info_create(info);
}
_EXTERN_C_ int MPI_Info_create(MPI_Info *info) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_create,&v, info);
  return ret;
}
/* ================== C Wrappers for MPI_Info_delete ================== */
_EXTERN_C_ int QMPI_Info_delete(MPI_Info info, const char *key, int level,  vector* v){
  return PMPI_Info_delete( info, key);
}
_EXTERN_C_ int MPI_Info_delete(MPI_Info info, const char *key) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_delete,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_delete,&v, info);
  return ret;
}
/* ================== C Wrappers for MPI_Info_dup ================== */
_EXTERN_C_ int QMPI_Info_dup(MPI_Info info, MPI_Info *newinfo, int level,  vector* v){
  return PMPI_Info_dup( info, newinfo);
}
_EXTERN_C_ int MPI_Info_dup(MPI_Info info, MPI_Info *newinfo) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_dup,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_dup,&v, info, newinfo);
  return ret;
}
/* ================== C Wrappers for MPI_Info_free ================== */
_EXTERN_C_ int QMPI_Info_free(MPI_Info *info, int level,  vector* v){
  return PMPI_Info_free( info);
}
_EXTERN_C_ int MPI_Info_free(MPI_Info *info) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_free,&v, info);
  return ret;
}
/* ================== C Wrappers for MPI_Info_get ================== */
_EXTERN_C_ int QMPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag, int level,  vector* v){
  return PMPI_Info_get( info, key, valuelen, value, flag);
}
_EXTERN_C_ int MPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_get,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_get,&v,info, key, valuelen, value, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Info_get_nkeys ================== */
_EXTERN_C_ int QMPI_Info_get_nkeys(MPI_Info info, int *nkeys, int level,  vector* v){
  return PMPI_Info_get_nkeys( info, nkeys);
}
_EXTERN_C_ int MPI_Info_get_nkeys(MPI_Info info, int *nkeys) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_get_nkeys,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_get_nkeys,&v,info, nkeys);
  return ret;
}
/* ================== C Wrappers for MPI_Info_get_nthkey ================== */
_EXTERN_C_ int QMPI_Info_get_nthkey(MPI_Info info, int n, char *key, int level,  vector* v){
  return PMPI_Info_get_nthkey( info, n, key);
}
_EXTERN_C_ int MPI_Info_get_nthkey(MPI_Info info, int n, char *key) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_get_nthkey,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_get_nthkey,&v, info, n, key);
  return ret;
}
/* ================== C Wrappers for MPI_Info_get_valuelen ================== */
_EXTERN_C_ int QMPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag, int level,  vector* v){
  return PMPI_Info_get_valuelen( info, key, valuelen, flag);
}
_EXTERN_C_ int MPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_get_valuelen,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_get_valuelen,&v, info, key, valuelen, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Info_set ================== */
_EXTERN_C_ int QMPI_Info_set(MPI_Info info, const char *key, const char *value, int level,  vector* v){
  return PMPI_Info_set( info, key, value);
}
_EXTERN_C_ int MPI_Info_set(MPI_Info info, const char *key, const char *value) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Info_set,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Info_set,&v, info, key, value);
  return ret;
}
/* ================== C Wrappers for MPI_Init_thread ================== */
_EXTERN_C_ int QMPI_Init_thread(int *argc, char ***argv, int required, int *provided, int level,  vector* v){
  return PMPI_Init_thread(argc, argv, required, provided);
}
_EXTERN_C_ int MPI_Init_thread(int *argc, char ***argv, int required, int *provided) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Init_thread,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Init_thread,&v,argc, argv, required, provided);
  return ret;
}
/* ================== C Wrappers for MPI_Initialized ================== */
_EXTERN_C_ int QMPI_Initialized(int *flag, int level,  vector* v){
  return PMPI_Initialized(flag); 
}
_EXTERN_C_ int MPI_Initialized(int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Initialized,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Initialized,&v,flag);
  return ret;
}
/* ================== C Wrappers for MPI_Intercomm_create ================== */
_EXTERN_C_ int QMPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm *newintercomm, int level,  vector* v){
  return PMPI_Intercomm_create(local_comm, local_leader, bridge_comm, remote_leader, tag, newintercomm);
}
_EXTERN_C_ int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm *newintercomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Intercomm_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Intercomm_create,&v,local_comm, local_leader, bridge_comm, remote_leader, tag, newintercomm);
  return ret;
}
/* ================== C Wrappers for MPI_Intercomm_merge ================== */
_EXTERN_C_ int QMPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintercomm, int level,  vector* v){
  return PMPI_Intercomm_merge( intercomm, high, newintercomm);
}
_EXTERN_C_ int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintercomm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Intercomm_merge,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Intercomm_merge,&v,intercomm, high, newintercomm);
  return ret;
}
/* ================== C Wrappers for MPI_Iprobe ================== */
_EXTERN_C_ int QMPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status, int level,  vector* v){
  return PMPI_Iprobe( source, tag, comm, flag, status);
}
_EXTERN_C_ int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Iprobe,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Iprobe,&v, source, tag, comm, flag, status);
  return ret;
}
/* ================== C Wrappers for MPI_Irecv ================== */
_EXTERN_C_ int QMPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Irecv(buf, count, datatype, source, tag, comm, request);
}
_EXTERN_C_ int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Irecv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Irecv,&v,buf, count, datatype, source, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ireduce ================== */
_EXTERN_C_ int QMPI_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ireduce( sendbuf, recvbuf, count, datatype, op, root, comm, request);
}
_EXTERN_C_ int MPI_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ireduce,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ireduce,&v,sendbuf, recvbuf, count, datatype, op, root, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ireduce_scatter ================== */
_EXTERN_C_ int QMPI_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ireduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm, request);
}
_EXTERN_C_ int MPI_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ireduce_scatter,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ireduce_scatter,&v,sendbuf, recvbuf, recvcounts, datatype, op, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Ireduce_scatter_block ================== */
_EXTERN_C_ int QMPI_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ireduce_scatter_block( sendbuf, recvbuf, recvcount, datatype, op, comm, request);
}
_EXTERN_C_ int MPI_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ireduce_scatter_block,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ireduce_scatter_block,&v,sendbuf, recvbuf, recvcount, datatype, op, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Irsend ================== */
_EXTERN_C_ int QMPI_Irsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Irsend( buf, count, datatype, dest, tag, comm, request);
}
_EXTERN_C_ int MPI_Irsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Irsend,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Irsend,&v, buf, count, datatype, dest, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Is_thread_main ================== */
_EXTERN_C_ int QMPI_Is_thread_main(int *flag, int level,  vector* v){
  return PMPI_Is_thread_main( flag) ;
}
_EXTERN_C_ int MPI_Is_thread_main(int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Is_thread_main,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Is_thread_main,&v, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Iscan ================== */
_EXTERN_C_ int QMPI_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Iscan( sendbuf, recvbuf, count, datatype, op,  comm, request);
}
_EXTERN_C_ int MPI_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Iscan,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Iscan,&v, sendbuf, recvbuf, count, datatype, op,  comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Iscatter ================== */
_EXTERN_C_ int QMPI_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Iscatter( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
}
_EXTERN_C_ int MPI_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Iscatter,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Iscatter,&v, sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Iscatterv ================== */
_EXTERN_C_ int QMPI_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Iscatterv( sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, request) ;
}
_EXTERN_C_ int MPI_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Iscatterv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Iscatterv,&v, sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Isend ================== */
_EXTERN_C_ int QMPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Isend( buf, count, datatype, dest, tag, comm, request);
}
_EXTERN_C_ int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Isend,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Isend,&v, buf, count, datatype, dest, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Issend ================== */
_EXTERN_C_ int QMPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Issend( buf, count, datatype, dest,tag, comm, request);
}
_EXTERN_C_ int MPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Issend,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Issend,&v,buf, count, datatype, dest,tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Keyval_create ================== */
_EXTERN_C_ int QMPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state, int level,  vector* v){
  return PMPI_Keyval_create( copy_fn, delete_fn, keyval, extra_state);
}
_EXTERN_C_ int MPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Keyval_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Keyval_create,&v,copy_fn, delete_fn, keyval, extra_state);
  return ret;
}
/* ================== C Wrappers for MPI_Keyval_free ================== */
_EXTERN_C_ int QMPI_Keyval_free(int *keyval, int level,  vector* v){
  return PMPI_Keyval_free( keyval);
}
_EXTERN_C_ int MPI_Keyval_free(int *keyval) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Keyval_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Keyval_free,&v, keyval);
  return ret;
}
/* ================== C Wrappers for MPI_Lookup_name ================== */
_EXTERN_C_ int QMPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name, int level,  vector* v){
  return PMPI_Lookup_name( service_name, info, port_name);
}
_EXTERN_C_ int MPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Lookup_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Lookup_name,&v, service_name, info, port_name);
  return ret;
}
/* ================== C Wrappers for MPI_Mprobe ================== */
_EXTERN_C_ int QMPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status, int level,  vector* v){
  return PMPI_Mprobe( source, tag, comm, message, status);
}
_EXTERN_C_ int MPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Mprobe,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Mprobe,&v, source, tag, comm, message, status);
  return ret;
}
/* ================== C Wrappers for MPI_Mrecv ================== */
_EXTERN_C_ int QMPI_Mrecv(void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Status *status, int level,  vector* v){
  return PMPI_Mrecv( buf, count, type, message, status) ;
}
_EXTERN_C_ int MPI_Mrecv(void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Mrecv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Mrecv,&v,buf, count, type, message, status);
  return ret;
}
/* ================== C Wrappers for MPI_Neighbor_allgather ================== */
_EXTERN_C_ int QMPI_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v){
  return PMPI_Neighbor_allgather( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}
_EXTERN_C_ int MPI_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Neighbor_allgather,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Neighbor_allgather,&v,sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Neighbor_allgatherv ================== */
_EXTERN_C_ int QMPI_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v){
  return PMPI_Neighbor_allgatherv( sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm) ;
}
_EXTERN_C_ int MPI_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Neighbor_allgatherv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Neighbor_allgatherv,&v,sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Neighbor_alltoall ================== */
_EXTERN_C_ int QMPI_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v){
  return PMPI_Neighbor_alltoall( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
}
_EXTERN_C_ int MPI_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Neighbor_alltoall,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Neighbor_alltoall,&v,sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Neighbor_alltoallv ================== */
_EXTERN_C_ int QMPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v){
  return PMPI_Neighbor_alltoallv( sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}
_EXTERN_C_ int MPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Neighbor_alltoallv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Neighbor_alltoallv,&v,sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Neighbor_alltoallw ================== */
_EXTERN_C_ int QMPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, int level,  vector* v){
  return PMPI_Neighbor_alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm) ;
}
_EXTERN_C_ int MPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Neighbor_alltoallw,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Neighbor_alltoallw,&v,sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Op_commutative ================== */
_EXTERN_C_ int QMPI_Op_commutative(MPI_Op op, int *commute, int level,  vector* v){
  return PMPI_Op_commutative( op, commute);
}
_EXTERN_C_ int MPI_Op_commutative(MPI_Op op, int *commute) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Op_commutative,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Op_commutative,&v,op, commute);
  return ret;
}
/* ================== C Wrappers for MPI_Op_create ================== */
_EXTERN_C_ int QMPI_Op_create(MPI_User_function *function, int commute, MPI_Op *op, int level,  vector* v){
  return PMPI_Op_create( function, commute, op);
}
_EXTERN_C_ int MPI_Op_create(MPI_User_function *function, int commute, MPI_Op *op) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Op_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Op_create,&v,function, commute, op);
  return ret;
}
/* ================== C Wrappers for MPI_Op_free ================== */
_EXTERN_C_ int QMPI_Op_free(MPI_Op *op, int level,  vector* v){
  return PMPI_Op_free(op);
}
_EXTERN_C_ int MPI_Op_free(MPI_Op *op) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Op_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Op_free,&v, op);
  return ret;
}
/* ================== C Wrappers for MPI_Open_port ================== */
_EXTERN_C_ int QMPI_Open_port(MPI_Info info, char *port_name, int level,  vector* v){
  return PMPI_Open_port( info, port_name);
}
_EXTERN_C_ int MPI_Open_port(MPI_Info info, char *port_name) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Open_port,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Open_port,&v,  info, port_name);
  return ret;
}
/* ================== C Wrappers for MPI_Pack ================== */
_EXTERN_C_ int QMPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm, int level,  vector* v){
  return PMPI_Pack( inbuf, incount, datatype, outbuf, outsize, position, comm);
}
_EXTERN_C_ int MPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Pack,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Pack,&v, inbuf, incount, datatype, outbuf, outsize, position, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Pack_external ================== */
_EXTERN_C_ int QMPI_Pack_external(const char datarep[], const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position, int level,  vector* v){
  return PMPI_Pack_external( datarep, inbuf, incount, datatype, outbuf, outsize, position);
}
_EXTERN_C_ int MPI_Pack_external(const char datarep[], const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Pack_external,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Pack_external,&v, datarep, inbuf, incount, datatype, outbuf, outsize, position);
  return ret;
}
/* ================== C Wrappers for MPI_Pack_external_size ================== */
_EXTERN_C_ int QMPI_Pack_external_size(const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint *size, int level,  vector* v){
  return PMPI_Pack_external_size( datarep, incount, datatype, size);
}
_EXTERN_C_ int MPI_Pack_external_size(const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Pack_external_size,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Pack_external_size,&v, datarep, incount, datatype, size);
  return ret;
}
/* ================== C Wrappers for MPI_Pack_size ================== */
_EXTERN_C_ int QMPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size, int level,  vector* v){
  return PMPI_Pack_size( incount, datatype, comm, size) ;
}
_EXTERN_C_ int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Pack_size,&f_dl,(*vector_get(&v, 0)).table  );
  int ret=exec_func(f_dl,0,_MPI_Pack_size,&v,incount, datatype, comm, size);
  return ret;
}
/* ================== C Wrappers for MPI_Pcontrol ================== */
/*_EXTERN_C_ int QMPI_Pcontrol(const int level, int levl,  vector* v, ...){ //TODO: FİX THİS !!!!!! vargs_list--------------------------------------------------------------------------------------------
  return PMPI_Pcontrol( level, ...);
}
_EXTERN_C_ int MPI_Pcontrol(const int level, ...) { 
  void* f_dl=NULL;
  QMPI_Table_query(235,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,235,&v,level, ...);
  return ret;
}*/
/* ================== C Wrappers for MPI_Probe ================== */
_EXTERN_C_ int QMPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status, int level,  vector* v){
  return PMPI_Probe( source, tag, comm, status);
}
_EXTERN_C_ int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Probe,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Probe,&v,source, tag, comm, status);
  return ret;
}
/* ================== C Wrappers for MPI_Publish_name ================== */
_EXTERN_C_ int QMPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name, int level,  vector* v){
  return PMPI_Publish_name( service_name, info, port_name);
}
_EXTERN_C_ int MPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Publish_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Publish_name,&v,service_name, info, port_name);
  return ret;
}
/* ================== C Wrappers for MPI_Put ================== */
_EXTERN_C_ int QMPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, int level,  vector* v){
  return PMPI_Put( origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
}
_EXTERN_C_ int MPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Put,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Put,&v,origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
  return ret;
}
/* ================== C Wrappers for MPI_Query_thread ================== */
_EXTERN_C_ int QMPI_Query_thread(int *provided, int level,  vector* v){
  return PMPI_Query_thread(provided);
}
_EXTERN_C_ int MPI_Query_thread(int *provided) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Query_thread,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Query_thread,&v,provided);
  return ret;
}
/* ================== C Wrappers for MPI_Raccumulate ================== */
_EXTERN_C_ int QMPI_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request, int level,  vector* v){
  return PMPI_Raccumulate( origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
}
_EXTERN_C_ int MPI_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Raccumulate,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Raccumulate,&v, origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
  return ret;
}
/* ================== C Wrappers for MPI_Recv ================== */
_EXTERN_C_ int QMPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, int level,  vector* v){
  return PMPI_Recv( buf, count, datatype, source, tag, comm, status);
}
_EXTERN_C_ int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Recv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Recv,&v,buf, count, datatype, source, tag, comm, status);
  return ret;
}
/* ================== C Wrappers for MPI_Recv_init ================== */
_EXTERN_C_ int QMPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Recv_init( buf, count, datatype, source, tag, comm, request);
}
_EXTERN_C_ int MPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Recv_init,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Recv_init,&v, buf, count, datatype, source, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Reduce ================== */
_EXTERN_C_ int QMPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, int level,  vector* v){
  return PMPI_Reduce( sendbuf, recvbuf, count, datatype, op, root, comm);
}
_EXTERN_C_ int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Reduce,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Reduce,&v,  sendbuf, recvbuf, count, datatype, op, root, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Reduce_local ================== */
_EXTERN_C_ int QMPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op, int level,  vector* v){
  return PMPI_Reduce_local( inbuf, inoutbuf, count,  datatype, op);
}
_EXTERN_C_ int MPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Reduce_local,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Reduce_local,&v, inbuf, inoutbuf, count,  datatype, op);
  return ret;
}
/* ================== C Wrappers for MPI_Reduce_scatter ================== */
_EXTERN_C_ int QMPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level,  vector* v){
  return PMPI_Reduce_scatter( sendbuf, recvbuf, recvcounts, datatype, op, comm) ;
}
_EXTERN_C_ int MPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Reduce_scatter,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Reduce_scatter,&v,sendbuf, recvbuf, recvcounts, datatype, op, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Reduce_scatter_block ================== */
_EXTERN_C_ int QMPI_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level,  vector* v){
  return PMPI_Reduce_scatter_block( sendbuf, recvbuf, recvcount, datatype, op, comm);
}
_EXTERN_C_ int MPI_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Reduce_scatter_block,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Reduce_scatter_block,&v,sendbuf, recvbuf, recvcount, datatype, op, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Register_datarep ================== */
_EXTERN_C_ int QMPI_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state, int level,  vector* v){
  return PMPI_Register_datarep( datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
}
_EXTERN_C_ int MPI_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Register_datarep,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Register_datarep,&v,datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
  return ret;
}
/* ================== C Wrappers for MPI_Request_free ================== */
_EXTERN_C_ int QMPI_Request_free(MPI_Request *request, int level,  vector* v){
  return PMPI_Request_free( request);
}
_EXTERN_C_ int MPI_Request_free(MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Request_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Request_free,&v, request);
  return ret;
}
/* ================== C Wrappers for MPI_Request_get_status ================== */
_EXTERN_C_ int QMPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status, int level,  vector* v){
  return PMPI_Request_get_status(request, flag, status);
}
_EXTERN_C_ int MPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Request_get_status,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Request_get_status,&v, request, flag, status);
  return ret;
}
/* ================== C Wrappers for MPI_Rget ================== */
_EXTERN_C_ int QMPI_Rget(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request, int level,  vector* v){
  return PMPI_Rget(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count,  target_datatype, win, request);
}
_EXTERN_C_ int MPI_Rget(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request) { 
 void* f_dl=NULL;
  QMPI_Table_query(_MPI_Rget,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Rget,&v, origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count,  target_datatype, win, request);
  return ret;
}
/* ================== C Wrappers for MPI_Rget_accumulate ================== */
_EXTERN_C_ int QMPI_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request, int level,  vector* v){
  return PMPI_Rget_accumulate( origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request) ;
}
_EXTERN_C_ int MPI_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Rget_accumulate,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Rget_accumulate,&v, origin_addr, origin_count, origin_datatype, result_addr, result_count, result_datatype, target_rank, target_disp, target_count, target_datatype, op, win, request);
  return ret;
}
/* ================== C Wrappers for MPI_Rput ================== */
_EXTERN_C_ int QMPI_Rput(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_cout, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request, int level,  vector* v){
  return PMPI_Rput( origin_addr, origin_count,  origin_datatype, target_rank, target_disp, target_cout, target_datatype, win,request);
}
_EXTERN_C_ int MPI_Rput(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_cout, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Rput,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Rput,&v, origin_addr, origin_count,  origin_datatype, target_rank, target_disp, target_cout, target_datatype, win,request);
  return ret;
}
/* ================== C Wrappers for MPI_Rsend ================== */
_EXTERN_C_ int QMPI_Rsend(const void *ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level,  vector* v){
  return PMPI_Rsend( ibuf, count, datatype, dest, tag, comm);
}
_EXTERN_C_ int MPI_Rsend(const void *ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Rsend,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Rsend,&v, ibuf, count, datatype, dest, tag, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Rsend_init ================== */
_EXTERN_C_ int QMPI_Rsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Rsend_init( buf, count, datatype, dest, tag, comm, request);
}
_EXTERN_C_ int MPI_Rsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Rsend_init,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Rsend_init,&v, buf, count, datatype, dest, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Scan ================== */
_EXTERN_C_ int QMPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level,  vector* v){
  return PMPI_Scan( sendbuf, recvbuf, count, datatype, op, comm);
}
_EXTERN_C_ int MPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Scan,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Scan,&v,sendbuf, recvbuf, count, datatype, op, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Scatter ================== */
_EXTERN_C_ int QMPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level,  vector* v){
  return PMPI_Scatter( sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
}
_EXTERN_C_ int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Scatter,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Scatter,&v,sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Scatterv ================== */
_EXTERN_C_ int QMPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level,  vector* v){
  return  PMPI_Scatterv( sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
}
_EXTERN_C_ int MPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Scatterv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Scatterv,&v,sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Send ================== */
_EXTERN_C_ int QMPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level,  vector* v){
  return PMPI_Send( buf, count, datatype, dest, tag, comm);
}
_EXTERN_C_ int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Send,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Send,&v,buf, count, datatype, dest, tag, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Send_init ================== */
_EXTERN_C_ int QMPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Send_init( buf, count, datatype, dest, tag, comm, request);
}
_EXTERN_C_ int MPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Send_init,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Send_init,&v,buf, count, datatype, dest, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Sendrecv ================== */
_EXTERN_C_ int QMPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status, int level,  vector* v){
  return  PMPI_Sendrecv( sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
}
_EXTERN_C_ int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Sendrecv,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Sendrecv,&v,sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
  return ret;
}
/* ================== C Wrappers for MPI_Sendrecv_replace ================== */
_EXTERN_C_ int QMPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status, int level,  vector* v){ 
  return PMPI_Sendrecv_replace( buf, count, datatype, dest, sendtag, source, recvtag, comm, status) ;
}
_EXTERN_C_ int MPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Sendrecv_replace,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Sendrecv_replace,&v,buf, count, datatype, dest, sendtag, source, recvtag, comm, status);
  return ret;
}
/* ================== C Wrappers for MPI_Ssend ================== */
_EXTERN_C_ int QMPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level,  vector* v){
  return PMPI_Ssend(buf,  count,  datatype,  dest, tag,  comm) ;
}
_EXTERN_C_ int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ssend,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ssend,&v,buf,  count,  datatype,  dest, tag,  comm);
  return ret;
}
/* ================== C Wrappers for MPI_Ssend_init ================== */
_EXTERN_C_ int QMPI_Ssend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v){
  return PMPI_Ssend_init( buf, count, datatype, dest, tag, comm, request);
}
_EXTERN_C_ int MPI_Ssend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Ssend_init,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Ssend_init,&v,buf, count, datatype, dest, tag, comm, request);
  return ret;
}
/* ================== C Wrappers for MPI_Start ================== */
_EXTERN_C_ int QMPI_Start(MPI_Request *request, int level,  vector* v){
  return PMPI_Start(request);
}
_EXTERN_C_ int MPI_Start(MPI_Request *request) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Start,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Start,&v,request);
  return ret;
}
/* ================== C Wrappers for MPI_Startall ================== */
_EXTERN_C_ int QMPI_Startall(int count, MPI_Request array_of_requests[], int level,  vector* v){
  return MPI_Startall( count, array_of_requests);
}
_EXTERN_C_ int MPI_Startall(int count, MPI_Request array_of_requests[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Startall,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Startall,&v,count, array_of_requests);
  return ret;
}
/* ================== C Wrappers for MPI_Status_set_cancelled ================== */
_EXTERN_C_ int QMPI_Status_set_cancelled(MPI_Status *status, int flag, int level,  vector* v){
  return PMPI_Status_set_cancelled( status,  flag);
}
_EXTERN_C_ int MPI_Status_set_cancelled(MPI_Status *status, int flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Status_set_cancelled,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Status_set_cancelled,&v, status,  flag);
  return ret;
}
/* ================== C Wrappers for MPI_Status_set_elements ================== */
_EXTERN_C_ int QMPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count, int level,  vector* v){
  return PMPI_Status_set_elements(status, datatype, count);
}
_EXTERN_C_ int MPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Status_set_elements,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Status_set_elements,&v,status, datatype, count);
  return ret;
}
/* ================== C Wrappers for MPI_Status_set_elements_x ================== */
_EXTERN_C_ int QMPI_Status_set_elements_x(MPI_Status *status, MPI_Datatype datatype, MPI_Count count, int level,  vector* v){
  return PMPI_Status_set_elements_x( status, datatype, count);
}
_EXTERN_C_ int MPI_Status_set_elements_x(MPI_Status *status, MPI_Datatype datatype, MPI_Count count) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Status_set_elements_x,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Status_set_elements_x,&v,status, datatype, count);
  return ret;
}
/* ================== C Wrappers for MPI_Test ================== */
_EXTERN_C_ int QMPI_Test(MPI_Request *request, int *flag, MPI_Status *status, int level,  vector* v){
  return PMPI_Test(request, flag, status);
}
_EXTERN_C_ int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Test,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Test,&v,request, flag, status);
  return ret;
}
/* ================== C Wrappers for MPI_Test_cancelled ================== */
_EXTERN_C_ int QMPI_Test_cancelled(const MPI_Status *status, int *flag, int level,  vector* v){
  return PMPI_Test_cancelled( status, flag);
}
_EXTERN_C_ int MPI_Test_cancelled(const MPI_Status *status, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Test_cancelled,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Test_cancelled,&v,status, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Testall ================== */
_EXTERN_C_ int QMPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[], int level,  vector* v){
  return PMPI_Testall( count, array_of_requests, flag, array_of_statuses) ;
}
_EXTERN_C_ int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Testall,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Testall,&v,count, array_of_requests, flag, array_of_statuses);
  return ret;
}
/* ================== C Wrappers for MPI_Testany ================== */
_EXTERN_C_ int QMPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status, int level,  vector* v){
  return PMPI_Testany( count, array_of_requests, index, flag, status);
}
_EXTERN_C_ int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Testany,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Testany,&v,count, array_of_requests, index, flag, status);
  return ret;
}
/* ================== C Wrappers for MPI_Testsome ================== */
_EXTERN_C_ int QMPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[], int level,  vector* v){
  return PMPI_Testsome( incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
}
_EXTERN_C_ int MPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Testsome,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Testsome,&v, incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
  return ret;
}
/* ================== C Wrappers for MPI_Topo_test ================== */
_EXTERN_C_ int QMPI_Topo_test(MPI_Comm comm, int *status, int level,  vector* v){
  return PMPI_Topo_test( comm, status);
}
_EXTERN_C_ int MPI_Topo_test(MPI_Comm comm, int *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Topo_test,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Topo_test,&v,comm, status);
  return ret;
}
/* ================== C Wrappers for MPI_Type_commit ================== */
_EXTERN_C_ int QMPI_Type_commit(MPI_Datatype *type, int level,  vector* v){
  return PMPI_Type_commit(type);
}
_EXTERN_C_ int MPI_Type_commit(MPI_Datatype *type) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_commit,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_commit,&v,type);
  return ret;
}
/* ================== C Wrappers for MPI_Type_contiguous ================== */
_EXTERN_C_ int QMPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_contiguous( count, oldtype, newtype);
}
_EXTERN_C_ int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_contiguous,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_contiguous,&v,count, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_darray ================== */
_EXTERN_C_ int QMPI_Type_create_darray(int size, int rank, int ndims, const int gsize_array[], const int distrib_array[], const int darg_array[], const int psize_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_darray( size,rank, ndims, gsize_array, distrib_array, darg_array, psize_array, order, oldtype, newtype);
}
_EXTERN_C_ int MPI_Type_create_darray(int size, int rank, int ndims, const int gsize_array[], const int distrib_array[], const int darg_array[], const int psize_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_darray,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_darray,&v,size,rank, ndims, gsize_array, distrib_array, darg_array, psize_array, order, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_f90_complex ================== */
_EXTERN_C_ int QMPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_f90_complex( p, r, newtype);
}
_EXTERN_C_ int MPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_f90_complex,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_f90_complex,&v,p, r, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_f90_integer ================== */
_EXTERN_C_ int QMPI_Type_create_f90_integer(int r, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_f90_integer( r, newtype);
}
_EXTERN_C_ int MPI_Type_create_f90_integer(int r, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_f90_integer,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_f90_integer,&v,r, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_f90_real ================== */
_EXTERN_C_ int QMPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_f90_real( p,  r, newtype);
}
_EXTERN_C_ int MPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_f90_real,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_f90_real,&v,p,  r, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_hindexed ================== */
_EXTERN_C_ int QMPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_hindexed( count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
}
_EXTERN_C_ int MPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_hindexed,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_hindexed,&v,count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_hindexed_block ================== */
_EXTERN_C_ int QMPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_hindexed_block( count, blocklength, array_of_displacements, oldtype, newtype);
}
_EXTERN_C_ int MPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_hindexed_block,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_hindexed_block,&v,count, blocklength, array_of_displacements, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_hvector ================== */
_EXTERN_C_ int QMPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_hvector( count, blocklength, stride, oldtype, newtype) ;
}
_EXTERN_C_ int MPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_hvector,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_hvector,&v, count, blocklength, stride, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_indexed_block ================== */
_EXTERN_C_ int QMPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_indexed_block( count, blocklength, array_of_displacements, oldtype, newtype);
}
_EXTERN_C_ int MPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_indexed_block,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_indexed_block,&v, count, blocklength, array_of_displacements, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_keyval ================== */
_EXTERN_C_ int QMPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state, int level,  vector* v){
  return PMPI_Type_create_keyval( type_copy_attr_fn, type_delete_attr_fn, type_keyval, extra_state);
}
_EXTERN_C_ int MPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_keyval,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_keyval,&v, type_copy_attr_fn, type_delete_attr_fn, type_keyval, extra_state);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_resized ================== */
_EXTERN_C_ int QMPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_resized( oldtype, lb, extent, newtype) ;
}
_EXTERN_C_ int MPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_resized,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_resized,&v, oldtype, lb, extent, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_struct ================== */
_EXTERN_C_ int QMPI_Type_create_struct(int count, const int array_of_block_lengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_struct( count,  array_of_block_lengths, array_of_displacements, array_of_types, newtype);
}
_EXTERN_C_ int MPI_Type_create_struct(int count, const int array_of_block_lengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_struct,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_struct,&v,count,  array_of_block_lengths, array_of_displacements, array_of_types, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_create_subarray ================== */
_EXTERN_C_ int QMPI_Type_create_subarray(int ndims, const int size_array[], const int subsize_array[], const int start_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_create_subarray( ndims,  size_array, subsize_array,  start_array,  order,  oldtype, newtype);
}
_EXTERN_C_ int MPI_Type_create_subarray(int ndims, const int size_array[], const int subsize_array[], const int start_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(288,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,288,&v, ndims,  size_array, subsize_array,  start_array,  order,  oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_delete_attr ================== */
_EXTERN_C_ int QMPI_Type_delete_attr(MPI_Datatype type, int type_keyval, int level,  vector* v){
  return PMPI_Type_delete_attr( type, type_keyval);
}
_EXTERN_C_ int MPI_Type_delete_attr(MPI_Datatype type, int type_keyval) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_create_subarray,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_create_subarray,&v,type, type_keyval);
  return ret;
}
/* ================== C Wrappers for MPI_Type_dup ================== */
_EXTERN_C_ int QMPI_Type_dup(MPI_Datatype type, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_dup(  type, newtype) ;
}
_EXTERN_C_ int MPI_Type_dup(MPI_Datatype type, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_dup,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_dup,&v, type, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_extent ================== */
_EXTERN_C_ int QMPI_Type_extent(MPI_Datatype type, MPI_Aint *extent, int level,  vector* v){
  return PMPI_Type_extent( type, extent);
}
_EXTERN_C_ int MPI_Type_extent(MPI_Datatype type, MPI_Aint *extent) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_extent,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_extent,&v,type, extent);
  return ret;
}
/* ================== C Wrappers for MPI_Type_free ================== */
_EXTERN_C_ int QMPI_Type_free(MPI_Datatype *type, int level,  vector* v){
  return PMPI_Type_free(type);
}
_EXTERN_C_ int MPI_Type_free(MPI_Datatype *type) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_free,&v,type);
  return ret;
}
/* ================== C Wrappers for MPI_Type_free_keyval ================== */
_EXTERN_C_ int QMPI_Type_free_keyval(int *type_keyval, int level,  vector* v){
  return PMPI_Type_free_keyval(type_keyval);
}
_EXTERN_C_ int MPI_Type_free_keyval(int *type_keyval) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_free_keyval,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_free_keyval,&v,type_keyval);
  return ret;
}
/* ================== C Wrappers for MPI_Type_get_attr ================== */
_EXTERN_C_ int QMPI_Type_get_attr(MPI_Datatype type, int type_keyval, void *attribute_val, int *flag, int level,  vector* v){
  return PMPI_Type_get_attr( type, type_keyval, attribute_val, flag);
}
_EXTERN_C_ int MPI_Type_get_attr(MPI_Datatype type, int type_keyval, void *attribute_val, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_get_attr,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_get_attr,&v,type, type_keyval, attribute_val, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Type_get_contents ================== */
_EXTERN_C_ int QMPI_Type_get_contents(MPI_Datatype mtype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[], int level,  vector* v){
  return PMPI_Type_get_contents( mtype,  max_integers, max_addresses,  max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);
}
_EXTERN_C_ int MPI_Type_get_contents(MPI_Datatype mtype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_get_contents,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_get_contents,&v,mtype,  max_integers, max_addresses,  max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);
  return ret;
}
/* ================== C Wrappers for MPI_Type_get_envelope ================== */
_EXTERN_C_ int QMPI_Type_get_envelope(MPI_Datatype type, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner, int level,  vector* v){
  return PMPI_Type_get_envelope( type, num_integers, num_addresses, num_datatypes, combiner) ;
}
_EXTERN_C_ int MPI_Type_get_envelope(MPI_Datatype type, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_get_envelope,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_get_envelope,&v,type, num_integers, num_addresses, num_datatypes, combiner);
  return ret;
}
/* ================== C Wrappers for MPI_Type_get_extent ================== */
_EXTERN_C_ int QMPI_Type_get_extent(MPI_Datatype type, MPI_Aint *lb, MPI_Aint *extent, int level,  vector* v){
  return PMPI_Type_get_extent( type,  lb, extent);
}
_EXTERN_C_ int MPI_Type_get_extent(MPI_Datatype type, MPI_Aint *lb, MPI_Aint *extent) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_get_extent,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_get_extent,&v,type,  lb, extent);
  return ret;
}
/* ================== C Wrappers for MPI_Type_get_extent_x ================== */
_EXTERN_C_ int QMPI_Type_get_extent_x(MPI_Datatype type, MPI_Count *lb, MPI_Count *extent, int level,  vector* v){
  return PMPI_Type_get_extent_x( type, lb, extent);
}
_EXTERN_C_ int MPI_Type_get_extent_x(MPI_Datatype type, MPI_Count *lb, MPI_Count *extent) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_get_extent_x,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_get_extent_x,&v,type, lb, extent);
  return ret;
}
/* ================== C Wrappers for MPI_Type_get_name ================== */
_EXTERN_C_ int QMPI_Type_get_name(MPI_Datatype type, char *type_name, int *resultlen, int level,  vector* v){
  return PMPI_Type_get_name( type, type_name, resultlen);
}
_EXTERN_C_ int MPI_Type_get_name(MPI_Datatype type, char *type_name, int *resultlen) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_get_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_get_name,&v,type, type_name, resultlen);
  return ret;
}
/* ================== C Wrappers for MPI_Type_get_true_extent ================== */
_EXTERN_C_ int QMPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent, int level,  vector* v){
  return PMPI_Type_get_true_extent( datatype, true_lb, true_extent);
}
_EXTERN_C_ int MPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_get_true_extent,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_get_true_extent,&v, datatype, true_lb, true_extent);
  return ret;
}
/* ================== C Wrappers for MPI_Type_get_true_extent_x ================== */
_EXTERN_C_ int QMPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent, int level,  vector* v){
  return PMPI_Type_get_true_extent_x( datatype, true_lb, true_extent);
}
_EXTERN_C_ int MPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_get_true_extent_x,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_get_true_extent_x,&v,datatype, true_lb, true_extent);
  return ret;
}
/* ================== C Wrappers for MPI_Type_hindexed ================== */
_EXTERN_C_ int QMPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_hindexed( count,  array_of_blocklengths, array_of_displacements, oldtype, newtype ) ;
}
_EXTERN_C_ int MPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_hindexed,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_hindexed,&v, count,  array_of_blocklengths, array_of_displacements, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_hvector ================== */
_EXTERN_C_ int QMPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_hvector( count, blocklength, stride, oldtype, newtype);
}
_EXTERN_C_ int MPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_hvector,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_hvector,&v,count, blocklength, stride, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Type_indexed ================== */
_EXTERN_C_ int QMPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_indexed( count, array_of_blocklengths, array_of_displacements, oldtype, newtype );
}
_EXTERN_C_ int MPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_indexed,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_indexed,&v, count, array_of_blocklengths, array_of_displacements, oldtype, newtype );
  return ret;
}
/* ================== C Wrappers for MPI_Type_lb ================== */
_EXTERN_C_ int QMPI_Type_lb(MPI_Datatype type, MPI_Aint *lb, int level,  vector* v){
  return PMPI_Type_lb( type, lb);
}
_EXTERN_C_ int MPI_Type_lb(MPI_Datatype type, MPI_Aint *lb) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_lb,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_lb,&v,type, lb);
  return ret;
}
/* ================== C Wrappers for MPI_Type_match_size ================== */
_EXTERN_C_ int QMPI_Type_match_size(int typeclass, int size, MPI_Datatype *type, int level,  vector* v){
  return PMPI_Type_match_size( typeclass,  size, type);
}
_EXTERN_C_ int MPI_Type_match_size(int typeclass, int size, MPI_Datatype *type) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_match_size,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_match_size,&v,typeclass,  size, type);
  return ret;
}
/* ================== C Wrappers for MPI_Type_set_attr ================== */
_EXTERN_C_ int QMPI_Type_set_attr(MPI_Datatype type, int type_keyval, void *attr_val, int level,  vector* v){
  return PMPI_Type_set_attr( type, type_keyval, attr_val);
}
_EXTERN_C_ int MPI_Type_set_attr(MPI_Datatype type, int type_keyval, void *attr_val) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_set_attr,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_set_attr,&v,type, type_keyval, attr_val);
  return ret;
}
/* ================== C Wrappers for MPI_Type_set_name ================== */
_EXTERN_C_ int QMPI_Type_set_name(MPI_Datatype type, const char *type_name, int level,  vector* v){
  return PMPI_Type_set_name( type, type_name);
}
_EXTERN_C_ int MPI_Type_set_name(MPI_Datatype type, const char *type_name) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_set_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_set_name,&v,type, type_name);
  return ret;
}
/* ================== C Wrappers for MPI_Type_size ================== */
_EXTERN_C_ int QMPI_Type_size(MPI_Datatype type, int *size, int level,  vector* v){
  return PMPI_Type_size( type, size);
}
_EXTERN_C_ int MPI_Type_size(MPI_Datatype type, int *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_size,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_size,&v,type, size);
  return ret;
}
/* ================== C Wrappers for MPI_Type_size_x ================== */
_EXTERN_C_ int QMPI_Type_size_x(MPI_Datatype type, MPI_Count *size, int level,  vector* v){
  return PMPI_Type_size_x( type, size);
}
_EXTERN_C_ int MPI_Type_size_x(MPI_Datatype type, MPI_Count *size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_size_x,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_size_x,&v,type, size);
  return ret;
}
/* ================== C Wrappers for MPI_Type_struct ================== */
_EXTERN_C_ int QMPI_Type_struct(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_struct( count, array_of_blocklengths, array_of_displacements, array_of_types, newtype  );
}
_EXTERN_C_ int MPI_Type_struct(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_struct,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_struct,&v,count, array_of_blocklengths, array_of_displacements, array_of_types, newtype );
  return ret;
}
/* ================== C Wrappers for MPI_Type_ub ================== */
_EXTERN_C_ int QMPI_Type_ub(MPI_Datatype mtype, MPI_Aint *ub, int level,  vector* v){
  return PMPI_Type_ub( mtype, ub);
}
_EXTERN_C_ int MPI_Type_ub(MPI_Datatype mtype, MPI_Aint *ub) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_ub,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_ub,&v,mtype, ub);
  return ret;
}
/* ================== C Wrappers for MPI_Type_vector ================== */
_EXTERN_C_ int QMPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v){
  return PMPI_Type_vector( count, blocklength, stride, oldtype, newtype);
}
_EXTERN_C_ int MPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Type_vector,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Type_vector,&v,count, blocklength, stride, oldtype, newtype);
  return ret;
}
/* ================== C Wrappers for MPI_Unpack ================== */
_EXTERN_C_ int QMPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm, int level,  vector* v){
  return PMPI_Unpack( inbuf, insize, position, outbuf, outcount, datatype, comm) ;
}
_EXTERN_C_ int MPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Unpack,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Unpack,&v,inbuf, insize, position, outbuf, outcount, datatype, comm);
  return ret;
}
/* ================== C Wrappers for MPI_Unpack_external ================== */
_EXTERN_C_ int QMPI_Unpack_external(const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype, int level,  vector* v){
  return PMPI_Unpack_external( datarep, inbuf, insize, position, outbuf, outcount, datatype);
}
_EXTERN_C_ int MPI_Unpack_external(const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Unpack_external,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Unpack_external,&v,datarep, inbuf, insize, position, outbuf, outcount, datatype);
  return ret;
}
/* ================== C Wrappers for MPI_Unpublish_name ================== */
_EXTERN_C_ int QMPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name, int level,  vector* v){
  return PMPI_Unpublish_name(service_name, info, port_name);
}
_EXTERN_C_ int MPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Unpublish_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Unpublish_name,&v,service_name, info, port_name);
  return ret;
}
/* ================== C Wrappers for MPI_Wait ================== */
_EXTERN_C_ int QMPI_Wait(MPI_Request *request, MPI_Status *status, int level,  vector* v){
  return PMPI_Wait( request, status) ;
}
_EXTERN_C_ int MPI_Wait(MPI_Request *request, MPI_Status *status) { 
   void* f_dl=NULL;
  QMPI_Table_query(_MPI_Wait,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Wait,&v,request, status);
  return ret;
}
/* ================== C Wrappers for MPI_Waitall ================== */
_EXTERN_C_ int QMPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status *array_of_statuses, int level,  vector* v){
  return PMPI_Waitall( count, array_of_requests, array_of_statuses);
}
_EXTERN_C_ int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status *array_of_statuses) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Waitall,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Waitall,&v,count, array_of_requests, array_of_statuses);
  return ret;
}
/* ================== C Wrappers for MPI_Waitany ================== */
_EXTERN_C_ int QMPI_Waitany(int count, MPI_Request array_of_requests[], int *index, MPI_Status *status, int level,  vector* v){
  return PMPI_Waitany( count, array_of_requests, index, status);
}
_EXTERN_C_ int MPI_Waitany(int count, MPI_Request array_of_requests[], int *index, MPI_Status *status) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Waitany,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Waitany,&v,count, array_of_requests, index, status);
  return ret;
}
/* ================== C Wrappers for MPI_Waitsome ================== */
_EXTERN_C_ int QMPI_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[], int level,  vector* v){
  return PMPI_Waitsome( incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
}
_EXTERN_C_ int MPI_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[]) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Waitsome,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Waitsome,&v,incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
  return ret;
}
/* ================== C Wrappers for MPI_Win_allocate ================== */
_EXTERN_C_ int QMPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win, int level,  vector* v){
  return PMPI_Win_allocate( size, disp_unit, info, comm, baseptr, win);
}
_EXTERN_C_ int MPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_allocate,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_allocate,&v, size, disp_unit, info, comm, baseptr, win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_allocate_shared ================== */
_EXTERN_C_ int QMPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win, int level,  vector* v){
  return PMPI_Win_allocate_shared( size,  disp_unit, info, comm, baseptr, win);
}
_EXTERN_C_ int MPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_allocate_shared,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_allocate_shared,&v,size,  disp_unit, info, comm, baseptr, win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_attach ================== */
_EXTERN_C_ int QMPI_Win_attach(MPI_Win win, void *base, MPI_Aint size, int level,  vector* v){
  return PMPI_Win_attach( win, base, size);
}
_EXTERN_C_ int MPI_Win_attach(MPI_Win win, void *base, MPI_Aint size) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_attach,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_attach,&v, win, base, size);
  return ret;
}
/* ================== C Wrappers for MPI_Win_call_errhandler ================== */
_EXTERN_C_ int QMPI_Win_call_errhandler(MPI_Win win, int errorcode, int level,  vector* v){
  return PMPI_Win_call_errhandler( win,  errorcode);
}
_EXTERN_C_ int MPI_Win_call_errhandler(MPI_Win win, int errorcode) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_call_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_call_errhandler,&v,win,  errorcode);
  return ret;
}
/* ================== C Wrappers for MPI_Win_complete ================== */
_EXTERN_C_ int QMPI_Win_complete(MPI_Win win, int level,  vector* v){
  return PMPI_Win_complete( win);
}
_EXTERN_C_ int MPI_Win_complete(MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_complete,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_complete,&v, win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_create ================== */
_EXTERN_C_ int QMPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win, int level,  vector* v){
  return PMPI_Win_create( base, size, disp_unit, info, comm, win);
}
_EXTERN_C_ int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_create,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_create,&v,base, size, disp_unit, info, comm, win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_create_dynamic ================== */
_EXTERN_C_ int QMPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win *win, int level,  vector* v){
  return PMPI_Win_create_dynamic( info, comm, win);
}
_EXTERN_C_ int MPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win *win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_create_dynamic,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_create_dynamic,&v,info, comm, win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_create_errhandler ================== */
_EXTERN_C_ int QMPI_Win_create_errhandler(MPI_Win_errhandler_function *function, MPI_Errhandler *errhandler, int level,  vector* v){
  return PMPI_Win_create_errhandler( function, errhandler);
}
_EXTERN_C_ int MPI_Win_create_errhandler(MPI_Win_errhandler_function *function, MPI_Errhandler *errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_create_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_create_errhandler,&v,function, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Win_create_keyval ================== */
_EXTERN_C_ int QMPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state, int level,  vector* v){
  return PMPI_Win_create_keyval( win_copy_attr_fn, win_delete_attr_fn, win_keyval, extra_state);
}
_EXTERN_C_ int MPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_create_keyval,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_create_keyval,&v,win_copy_attr_fn, win_delete_attr_fn, win_keyval, extra_state);
  return ret;
}
/* ================== C Wrappers for MPI_Win_delete_attr ================== */
_EXTERN_C_ int QMPI_Win_delete_attr(MPI_Win win, int win_keyval, int level,  vector* v){
  return PMPI_Win_delete_attr( win,  win_keyval);
}
_EXTERN_C_ int MPI_Win_delete_attr(MPI_Win win, int win_keyval) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_delete_attr,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_delete_attr,&v,win,  win_keyval);
  return ret;
}
/* ================== C Wrappers for MPI_Win_detach ================== */
_EXTERN_C_ int QMPI_Win_detach(MPI_Win win, const void *base, int level,  vector* v){
  return PMPI_Win_detach( win, base);
}
_EXTERN_C_ int MPI_Win_detach(MPI_Win win, const void *base) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_detach,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_detach,&v,win, base);
  return ret;
}
/* ================== C Wrappers for MPI_Win_fence ================== */
_EXTERN_C_ int QMPI_Win_fence(int assert, MPI_Win win, int level,  vector* v){
  return PMPI_Win_fence(assert, win) ;
}
_EXTERN_C_ int MPI_Win_fence(int assert, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_fence,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_fence,&v,assert, win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_flush ================== */
_EXTERN_C_ int QMPI_Win_flush(int rank, MPI_Win win, int level,  vector* v){
  return PMPI_Win_flush( rank,  win);
}
_EXTERN_C_ int MPI_Win_flush(int rank, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_flush,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_flush,&v,rank,  win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_flush_all ================== */
_EXTERN_C_ int QMPI_Win_flush_all(MPI_Win win, int level,  vector* v){
  return PMPI_Win_flush_all( win);
}
_EXTERN_C_ int MPI_Win_flush_all(MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_flush_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_flush_all,&v,win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_flush_local ================== */
_EXTERN_C_ int QMPI_Win_flush_local(int rank, MPI_Win win, int level,  vector* v){
  return PMPI_Win_flush_local( rank,  win);
}
_EXTERN_C_ int MPI_Win_flush_local(int rank, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_flush_local,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_flush_local,&v,rank,  win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_flush_local_all ================== */
_EXTERN_C_ int QMPI_Win_flush_local_all(MPI_Win win, int level,  vector* v){
  return PMPI_Win_flush_local_all( win);
}
_EXTERN_C_ int MPI_Win_flush_local_all(MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_flush_local_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_flush_local_all,&v,win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_free ================== */
_EXTERN_C_ int QMPI_Win_free(MPI_Win *win, int level,  vector* v){
  return PMPI_Win_free(win);
}
_EXTERN_C_ int MPI_Win_free(MPI_Win *win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_free,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_free,&v,win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_free_keyval ================== */
_EXTERN_C_ int QMPI_Win_free_keyval(int *win_keyval, int level,  vector* v){
  return PMPI_Win_free_keyval(win_keyval);
}
_EXTERN_C_ int MPI_Win_free_keyval(int *win_keyval) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_free_keyval,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_free_keyval,&v,win_keyval);
  return ret;
}
/* ================== C Wrappers for MPI_Win_get_attr ================== */
_EXTERN_C_ int QMPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag, int level,  vector* v){
  return PMPI_Win_get_attr( win, win_keyval, attribute_val, flag);
}
_EXTERN_C_ int MPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_get_attr,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_get_attr,&v,win, win_keyval, attribute_val, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Win_get_errhandler ================== */
_EXTERN_C_ int QMPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler, int level,  vector* v){
  return PMPI_Win_get_errhandler( win, errhandler);
}
_EXTERN_C_ int MPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_get_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_get_errhandler,&v, win, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Win_get_group ================== */
_EXTERN_C_ int QMPI_Win_get_group(MPI_Win win, MPI_Group *group, int level,  vector* v){
  return PMPI_Win_get_group( win, group) ;
}
_EXTERN_C_ int MPI_Win_get_group(MPI_Win win, MPI_Group *group) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_get_group,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_get_group,&v, win, group);
  return ret;
}
/* ================== C Wrappers for MPI_Win_get_info ================== */
_EXTERN_C_ int QMPI_Win_get_info(MPI_Win win, MPI_Info *info_used, int level,  vector* v){
  return PMPI_Win_get_info( win, info_used);
}
_EXTERN_C_ int MPI_Win_get_info(MPI_Win win, MPI_Info *info_used) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_get_info,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_get_info,&v, win, info_used);
  return ret;
}
/* ================== C Wrappers for MPI_Win_get_name ================== */
_EXTERN_C_ int QMPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen, int level,  vector* v){
  return PMPI_Win_get_name( win, win_name, resultlen);
}
_EXTERN_C_ int MPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_get_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_get_name,&v,win, win_name, resultlen);
  return ret;
}
/* ================== C Wrappers for MPI_Win_lock ================== */
_EXTERN_C_ int QMPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win, int level,  vector* v){
  return PMPI_Win_lock( lock_type,  rank, assert,  win);
}
_EXTERN_C_ int MPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_lock,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_lock,&v,lock_type,  rank, assert,  win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_lock_all ================== */
_EXTERN_C_ int QMPI_Win_lock_all(int assert, MPI_Win win, int level,  vector* v){
  return PMPI_Win_lock_all( assert,  win);
}
_EXTERN_C_ int MPI_Win_lock_all(int assert, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_lock_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_lock_all,&v,assert,  win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_post ================== */
_EXTERN_C_ int QMPI_Win_post(MPI_Group group, int assert, MPI_Win win, int level,  vector* v){
  return PMPI_Win_post( group,  assert,  win) ;
}
_EXTERN_C_ int MPI_Win_post(MPI_Group group, int assert, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_post,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_post,&v,group,  assert,  win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_set_attr ================== */
_EXTERN_C_ int QMPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val, int level,  vector* v){
  return PMPI_Win_set_attr( win, win_keyval, attribute_val);
}
_EXTERN_C_ int MPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_set_attr,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_set_attr,&v,win, win_keyval, attribute_val);
  return ret;
}
/* ================== C Wrappers for MPI_Win_set_errhandler ================== */
_EXTERN_C_ int QMPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler, int level,  vector* v){
  return PMPI_Win_set_errhandler( win, errhandler);
}
_EXTERN_C_ int MPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_set_errhandler,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_set_errhandler,&v,win, errhandler);
  return ret;
}
/* ================== C Wrappers for MPI_Win_set_info ================== */
_EXTERN_C_ int QMPI_Win_set_info(MPI_Win win, MPI_Info info, int level,  vector* v){
  return PMPI_Win_set_info( win,  info);
}
_EXTERN_C_ int MPI_Win_set_info(MPI_Win win, MPI_Info info) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_set_info,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_set_info,&v, win,  info);
  return ret;
}
/* ================== C Wrappers for MPI_Win_set_name ================== */
_EXTERN_C_ int QMPI_Win_set_name(MPI_Win win, const char *win_name, int level,  vector* v){
  return PMPI_Win_set_name( win, win_name);
}
_EXTERN_C_ int MPI_Win_set_name(MPI_Win win, const char *win_name) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_set_name,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_set_name,&v,win, win_name);
  return ret;
}
/* ================== C Wrappers for MPI_Win_shared_query ================== */
_EXTERN_C_ int QMPI_Win_shared_query(MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr, int level,  vector* v){
  return PMPI_Win_shared_query( win,  rank, size, disp_unit, baseptr);
}
_EXTERN_C_ int MPI_Win_shared_query(MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_shared_query,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_shared_query,&v,win,  rank, size, disp_unit, baseptr);
  return ret;
}
/* ================== C Wrappers for MPI_Win_start ================== */
_EXTERN_C_ int QMPI_Win_start(MPI_Group group, int assert, MPI_Win win, int level,  vector* v){
  return PMPI_Win_start( group, assert, win) ;
}
_EXTERN_C_ int MPI_Win_start(MPI_Group group, int assert, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_start,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_start,&v, group, assert, win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_sync ================== */
_EXTERN_C_ int QMPI_Win_sync(MPI_Win win, int level,  vector* v){
  return PMPI_Win_sync( win) ;
}
_EXTERN_C_ int MPI_Win_sync(MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_sync,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_sync,&v,win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_test ================== */
_EXTERN_C_ int QMPI_Win_test(MPI_Win win, int *flag, int level,  vector* v){
  return PMPI_Win_test( win, flag);
}
_EXTERN_C_ int MPI_Win_test(MPI_Win win, int *flag) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_test,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_test,&v,win, flag);
  return ret;
}
/* ================== C Wrappers for MPI_Win_unlock ================== */
_EXTERN_C_ int QMPI_Win_unlock(int rank, MPI_Win win, int level,  vector* v){
  return PMPI_Win_unlock( rank, win) ;
}
_EXTERN_C_ int MPI_Win_unlock(int rank, MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_unlock,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_unlock,&v,rank, win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_unlock_all ================== */
_EXTERN_C_ int QMPI_Win_unlock_all(MPI_Win win, int level,  vector* v){
  return PMPI_Win_unlock_all( win);
}
_EXTERN_C_ int MPI_Win_unlock_all(MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_unlock_all,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_unlock_all,&v,win);
  return ret;
}
/* ================== C Wrappers for MPI_Win_wait ================== */
_EXTERN_C_ int QMPI_Win_wait(MPI_Win win, int level,  vector* v){
  return PMPI_Win_wait( win);
}
_EXTERN_C_ int MPI_Win_wait(MPI_Win win) { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Win_wait,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Win_wait,&v,win);
  return ret;
}
/* ================== C Wrappers for MPI_Wtick ================== */
_EXTERN_C_ double QMPI_Wtick( int level,  vector* v){
  return PMPI_Wtick();
}
_EXTERN_C_ double MPI_Wtick() { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Wtick,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Wtick,&v);
  return ret;
}
/* ================== C Wrappers for MPI_Wtime ================== */
_EXTERN_C_ double QMPI_Wtime(int level,  vector* v){
  return PMPI_Wtime();
}
_EXTERN_C_ double MPI_Wtime() { 
  void* f_dl=NULL;
  QMPI_Table_query(_MPI_Wtime,&f_dl,(*vector_get(&v, 0)).table );
  int ret=exec_func(f_dl,0,_MPI_Wtime,&v);
  return ret;
}


