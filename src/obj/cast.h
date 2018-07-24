#include "qmpi.h"
#ifndef CAST_H
#define CAST_H

int Cast_Init(void* func_ptr,vector* v,int level,va_list argp);
int Cast_Comm_rank(void* func_ptr,vector* v,int level,va_list argp);
int Cast_Finalize(void* func_ptr,vector* v,int level,va_list argp);
int Cast_Comm_size(void* func_ptr,vector* v,int level,va_list argp);


#endif
