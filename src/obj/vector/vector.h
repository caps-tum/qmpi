#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 4
#define NUM_FUNCS 3


typedef void* dynamic_lib_handle;

struct dynamic_lib {

        char                            path[100];
        //char*                         path;
        dynamic_lib_handle              handle;
        char*                           mpi_interceptions[NUM_FUNCS ];
        void*                           table[NUM_FUNCS];

};

//#include "../qmpi.h"
typedef struct vector {
    struct dynamic_lib **items;
    int capacity;
    int total;
} vector;

void vector_init(vector *);
int vector_total(vector *);
static void vector_resize(vector *, int);
void vector_add(vector *, struct dynamic_lib *);
void vector_set(vector *, int, struct dynamic_lib *);
struct dynamic_lib *vector_get(vector *, int);
void vector_delete(vector *, int);
void vector_free(vector * );

#endif
