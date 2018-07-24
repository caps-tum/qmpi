#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../qmpi.h"


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
