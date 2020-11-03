/**
    Copyright (C) 2018 Technische Universitaet Muenchen
                       Chair of Computer Architecture and 
                                Parallel Systems
    Author: Bengisu Elis
    
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>

#ifndef QMPI_H
#define QMPI_H

#define NUM_MPI_FUNCS 360
#define VECTOR_INIT_CAPACITY 4
#define QMPI_LEVEL 0

#define QMPI_TABLE_QUERY(func_index, func_ptr, table) QMPI_Table_query(func_index, func_ptr, table)
#define QMPI_SET_CONTEXT(v,i,c,sz) QMPI_Set_context( v, i,c,sz)
#define MPI_TABLE_QUERY(func_index, func_ptr, table) MPI_Table_query(func_index, func_ptr, table)
#define EXEC_FUNC(func_ptr,level ,func_index,v ,...) exec_func(func_ptr,level ,func_index,v ,##__VA_ARGS__)
#define QMPI_GET_CONTEXT(v,index) (( (index) >= (0) && (index) < ((*v).total) ) ? (((*v).items[index])->context) : (NULL) )
#define VECTOR_GET(v,index)   (( (index) >= (0) && (index) < ((*v).total) ) ? ((*v).items[index]) : (NULL) )
#define QMPI_GET_LEVEL(index, func_index, v) (( (index) >= (0) && (index) < ((*v).total) ) ? ((( (*v).items[index])->table[func_index]).level) : (0) )

typedef enum {
_MPI_Abort	 =	0	,
_MPI_Accumulate	 =	1	,
_MPI_Add_error_class	 =	2	,
_MPI_Add_error_code	 =	3	,
_MPI_Add_error_string	 =	4	,
//_MPI_Address	 =	5	,
_MPI_Allgather	 =	6	,
_MPI_Allgatherv	 =	7	,
_MPI_Alloc_mem	 =	8	,
_MPI_Allreduce	 =	9	,
_MPI_Alltoall	 =	10	,
_MPI_Alltoallv	 =	11	,
_MPI_Alltoallw	 =	12	,
_MPI_Attr_delete	 =	13	,
_MPI_Attr_get	 =	14	,
_MPI_Attr_put	 =	15	,
_MPI_Barrier	 =	16	,
_MPI_Bcast	 =	17	,
_MPI_Bsend	 =	18	,
_MPI_Bsend_init	 =	19	,
_MPI_Buffer_attach	 =	20	,
_MPI_Buffer_detach	 =	21	,
_MPI_Cancel	 =	22	,
_MPI_Cart_coords	 =	23	,
_MPI_Cart_create	 =	24	,
_MPI_Cart_get	 =	25	,
_MPI_Cart_map	 =	26	,
_MPI_Cart_rank	 =	27	,
_MPI_Cart_shift	 =	28	,
_MPI_Cart_sub	 =	29	,
_MPI_Cartdim_get	 =	30	,
_MPI_Close_port	 =	31	,
_MPI_Comm_accept	 =	32	,
_MPI_Comm_call_errhandler	 =	33	,
_MPI_Comm_compare	 =	34	,
_MPI_Comm_connect	 =	35	,
_MPI_Comm_create	 =	36	,
_MPI_Comm_create_errhandler	 =	37	,
_MPI_Comm_create_group	 =	38	,
_MPI_Comm_create_keyval	 =	39	,
_MPI_Comm_delete_attr	 =	40	,
_MPI_Comm_disconnect	 =	41	,
_MPI_Comm_dup	 =	42	,
_MPI_Comm_dup_with_info	 =	43	,
_MPI_Comm_free	 =	44	,
_MPI_Comm_free_keyval	 =	45	,
_MPI_Comm_get_attr	 =	46	,
_MPI_Comm_get_errhandler	 =	47	,
_MPI_Comm_get_info	 =	48	,
_MPI_Comm_get_name	 =	49	,
_MPI_Comm_get_parent	 =	50	,
_MPI_Comm_group	 =	51	,
_MPI_Comm_idup	 =	52	,
_MPI_Comm_join	 =	53	,
_MPI_Comm_rank	 =	54	,
_MPI_Comm_remote_group	 =	55	,
_MPI_Comm_remote_size	 =	56	,
_MPI_Comm_set_attr	 =	57	,
_MPI_Comm_set_errhandler	 =	58	,
_MPI_Comm_set_info	 =	59	,
_MPI_Comm_set_name	 =	60	,
_MPI_Comm_size	 =	61	,
_MPI_Comm_split	 =	62	,
_MPI_Comm_split_type	 =	63	,
_MPI_Comm_test_inter	 =	64	,
_MPI_Compare_and_swap	 =	65	,
_MPI_Dims_create	 =	66	,
_MPI_Dist_graph_create	 =	67	,
_MPI_Dist_graph_create_adjacent	 =	68	,
_MPI_Dist_graph_neighbors	 =	69	,
_MPI_Dist_graph_neighbors_count	 =	70	,
_MPI_Errhandler_create	 =	71	,
_MPI_Errhandler_free	 =	72	,
_MPI_Errhandler_get	 =	73	,
_MPI_Errhandler_set	 =	74	,
_MPI_Error_class	 =	75	,
_MPI_Error_string	 =	76	,
_MPI_Exscan	 =	77	,
_MPI_Fetch_and_op	 =	78	,
_MPI_File_call_errhandler	 =	79	,
_MPI_File_close	 =	80	,
_MPI_File_create_errhandler	 =	81	,
_MPI_File_delete	 =	82	,
_MPI_File_get_amode	 =	83	,
_MPI_File_get_atomicity	 =	84	,
_MPI_File_get_byte_offset	 =	85	,
_MPI_File_get_errhandler	 =	86	,
_MPI_File_get_group	 =	87	,
_MPI_File_get_info	 =	88	,
_MPI_File_get_position	 =	89	,
_MPI_File_get_position_shared	 =	90	,
_MPI_File_get_size	 =	91	,
_MPI_File_get_type_extent	 =	92	,
_MPI_File_get_view	 =	93	,
_MPI_File_iread	 =	94	,
_MPI_File_iread_all	 =	95	,
_MPI_File_iread_at	 =	96	,
_MPI_File_iread_at_all	 =	97	,
_MPI_File_iread_shared	 =	98	,
_MPI_File_iwrite	 =	99	,
_MPI_File_iwrite_all	 =	100	,
_MPI_File_iwrite_at	 =	101	,
_MPI_File_iwrite_at_all	 =	102	,
_MPI_File_iwrite_shared	 =	103	,
_MPI_File_open	 =	104	,
_MPI_File_preallocate	 =	105	,
_MPI_File_read	 =	106	,
_MPI_File_read_all	 =	107	,
_MPI_File_read_all_begin	 =	108	,
_MPI_File_read_all_end	 =	109	,
_MPI_File_read_at	 =	110	,
_MPI_File_read_at_all	 =	111	,
_MPI_File_read_at_all_begin	 =	112	,
_MPI_File_read_at_all_end	 =	113	,
_MPI_File_read_ordered	 =	114	,
_MPI_File_read_ordered_begin	 =	115	,
_MPI_File_read_ordered_end	 =	116	,
_MPI_File_read_shared	 =	117	,
_MPI_File_seek	 =	118	,
_MPI_File_seek_shared	 =	119	,
_MPI_File_set_atomicity	 =	120	,
_MPI_File_set_errhandler	 =	121	,
_MPI_File_set_info	 =	122	,
_MPI_File_set_size	 =	123	,
_MPI_File_set_view	 =	124	,
_MPI_File_sync	 =	125	,
_MPI_File_write	 =	126	,
_MPI_File_write_all	 =	127	,
_MPI_File_write_all_begin	 =	128	,
_MPI_File_write_all_end	 =	129	,
_MPI_File_write_at	 =	130	,
_MPI_File_write_at_all	 =	131	,
_MPI_File_write_at_all_begin	 =	132	,
_MPI_File_write_at_all_end	 =	133	,
_MPI_File_write_ordered	 =	134	,
_MPI_File_write_ordered_begin	 =	135	,
_MPI_File_write_ordered_end	 =	136	,
_MPI_File_write_shared	 =	137	,
_MPI_Finalize	 =	138	,
_MPI_Finalized	 =	139	,
_MPI_Free_mem	 =	140	,
_MPI_Gather	 =	141	,
_MPI_Gatherv	 =	142	,
_MPI_Get	 =	143	,
_MPI_Get_accumulate	 =	144	,
_MPI_Get_address	 =	145	,
_MPI_Get_count	 =	146	,
_MPI_Get_elements	 =	147	,
_MPI_Get_elements_x	 =	148	,
_MPI_Get_library_version	 =	149	,
_MPI_Get_processor_name	 =	150	,
_MPI_Get_version	 =	151	,
_MPI_Graph_create	 =	152	,
_MPI_Graph_get	 =	153	,
_MPI_Graph_map	 =	154	,
_MPI_Graph_neighbors	 =	155	,
_MPI_Graph_neighbors_count	 =	156	,
_MPI_Graphdims_get	 =	157	,
_MPI_Grequest_complete	 =	158	,
_MPI_Grequest_start	 =	159	,
_MPI_Group_compare	 =	160	,
_MPI_Group_difference	 =	161	,
_MPI_Group_excl	 =	162	,
_MPI_Group_free	 =	163	,
_MPI_Group_incl	 =	164	,
_MPI_Group_intersection	 =	165	,
_MPI_Group_range_excl	 =	166	,
_MPI_Group_range_incl	 =	167	,
_MPI_Group_rank	 =	168	,
_MPI_Group_size	 =	169	,
_MPI_Group_translate_ranks	 =	170	,
_MPI_Group_union	 =	171	,
_MPI_Iallgather	 =	172	,
_MPI_Iallgatherv	 =	173	,
_MPI_Iallreduce	 =	174	,
_MPI_Ialltoall	 =	175	,
_MPI_Ialltoallv	 =	176	,
_MPI_Ialltoallw	 =	177	,
_MPI_Ibarrier	 =	178	,
_MPI_Ibcast	 =	179	,
_MPI_Ibsend	 =	180	,
_MPI_Iexscan	 =	181	,
_MPI_Igather	 =	182	,
_MPI_Igatherv	 =	183	,
_MPI_Improbe	 =	184	,
_MPI_Imrecv	 =	185	,
_MPI_Ineighbor_allgather	 =	186	,
_MPI_Ineighbor_allgatherv	 =	187	,
_MPI_Ineighbor_alltoall	 =	188	,
_MPI_Ineighbor_alltoallv	 =	189	,
_MPI_Ineighbor_alltoallw	 =	190	,
_MPI_Info_create	 =	191	,
_MPI_Info_delete	 =	192	,
_MPI_Info_dup	 =	193	,
_MPI_Info_free	 =	194	,
_MPI_Info_get	 =	195	,
_MPI_Info_get_nkeys	 =	196	,
_MPI_Info_get_nthkey	 =	197	,
_MPI_Info_get_valuelen	 =	198	,
_MPI_Info_set	 =	199	,
_MPI_Init	 =	200	,
_MPI_Init_thread	 =	201	,
_MPI_Initialized	 =	202	,
_MPI_Intercomm_create	 =	203	,
_MPI_Intercomm_merge	 =	204	,
_MPI_Iprobe	 =	205	,
_MPI_Irecv	 =	206	,
_MPI_Ireduce	 =	207	,
_MPI_Ireduce_scatter	 =	208	,
_MPI_Ireduce_scatter_block	 =	209	,
_MPI_Irsend	 =	210	,
_MPI_Is_thread_main	 =	211	,
_MPI_Iscan	 =	212	,
_MPI_Iscatter	 =	213	,
_MPI_Iscatterv	 =	214	,
_MPI_Isend	 =	215	,
_MPI_Issend	 =	216	,
_MPI_Keyval_create	 =	217	,
_MPI_Keyval_free	 =	218	,
_MPI_Lookup_name	 =	219	,
_MPI_Mprobe	 =	220	,
_MPI_Mrecv	 =	221	,
_MPI_Neighbor_allgather	 =	222	,
_MPI_Neighbor_allgatherv	 =	223	,
_MPI_Neighbor_alltoall	 =	224	,
_MPI_Neighbor_alltoallv	 =	225	,
_MPI_Neighbor_alltoallw	 =	226	,
_MPI_Op_commutative	 =	227	,
_MPI_Op_create	 =	228	,
_MPI_Op_free	 =	229	,
_MPI_Open_port	 =	230	,
_MPI_Pack	 =	231	,
_MPI_Pack_external	 =	232	,
_MPI_Pack_external_size	 =	233	,
_MPI_Pack_size	 =	234	,
_MPI_Pcontrol	 =	235	,
_MPI_Probe	 =	236	,
_MPI_Publish_name	 =	237	,
_MPI_Put	 =	238	,
_MPI_Query_thread	 =	239	,
_MPI_Raccumulate	 =	240	,
_MPI_Recv	 =	241	,
_MPI_Recv_init	 =	242	,
_MPI_Reduce	 =	243	,
_MPI_Reduce_local	 =	244	,
_MPI_Reduce_scatter	 =	245	,
_MPI_Reduce_scatter_block	 =	246	,
_MPI_Register_datarep	 =	247	,
_MPI_Request_free	 =	248	,
_MPI_Request_get_status	 =	249	,
_MPI_Rget	 =	250	,
_MPI_Rget_accumulate	 =	251	,
_MPI_Rput	 =	252	,
_MPI_Rsend	 =	253	,
_MPI_Rsend_init	 =	254	,
_MPI_Scan	 =	255	,
_MPI_Scatter	 =	256	,
_MPI_Scatterv	 =	257	,
_MPI_Send	 =	258	,
_MPI_Send_init	 =	259	,
_MPI_Sendrecv	 =	260	,
_MPI_Sendrecv_replace	 =	261	,
_MPI_Ssend	 =	262	,
_MPI_Ssend_init	 =	263	,
_MPI_Start	 =	264	,
_MPI_Startall	 =	265	,
_MPI_Status_set_cancelled	 =	266	,
_MPI_Status_set_elements	 =	267	,
_MPI_Status_set_elements_x	 =	268	,
_MPI_Test	 =	269	,
_MPI_Test_cancelled	 =	270	,
_MPI_Testall	 =	271	,
_MPI_Testany	 =	272	,
_MPI_Testsome	 =	273	,
_MPI_Topo_test	 =	274	,
_MPI_Type_commit	 =	275	,
_MPI_Type_contiguous	 =	276	,
_MPI_Type_create_darray	 =	277	,
_MPI_Type_create_f90_complex	 =	278	,
_MPI_Type_create_f90_integer	 =	279	,
_MPI_Type_create_f90_real	 =	280	,
_MPI_Type_create_hindexed	 =	281	,
_MPI_Type_create_hindexed_block	 =	282	,
_MPI_Type_create_hvector	 =	283	,
_MPI_Type_create_indexed_block	 =	284	,
_MPI_Type_create_keyval	 =	285	,
_MPI_Type_create_resized	 =	286	,
_MPI_Type_create_struct	 =	287	,
_MPI_Type_create_subarray	 =	288	,
_MPI_Type_delete_attr	 =	289	,
_MPI_Type_dup	 =	290	,
_MPI_Type_extent	 =	291	,
_MPI_Type_free	 =	292	,
_MPI_Type_free_keyval	 =	293	,
_MPI_Type_get_attr	 =	294	,
_MPI_Type_get_contents	 =	295	,
_MPI_Type_get_envelope	 =	296	,
_MPI_Type_get_extent	 =	297	,
_MPI_Type_get_extent_x	 =	298	,
_MPI_Type_get_name	 =	299	,
_MPI_Type_get_true_extent	 =	300	,
_MPI_Type_get_true_extent_x	 =	301	,
_MPI_Type_hindexed	 =	302	,
_MPI_Type_hvector	 =	303	,
_MPI_Type_indexed	 =	304	,
_MPI_Type_lb	 =	305	,
_MPI_Type_match_size	 =	306	,
_MPI_Type_set_attr	 =	307	,
_MPI_Type_set_name	 =	308	,
_MPI_Type_size	 =	309	,
_MPI_Type_size_x	 =	310	,
_MPI_Type_struct	 =	311	,
_MPI_Type_ub	 =	312	,
_MPI_Type_vector	 =	313	,
_MPI_Unpack	 =	314	,
_MPI_Unpack_external	 =	315	,
_MPI_Unpublish_name	 =	316	,
_MPI_Wait	 =	317	,
_MPI_Waitall	 =	318	,
_MPI_Waitany	 =	319	,
_MPI_Waitsome	 =	320	,
_MPI_Win_allocate	 =	321	,
_MPI_Win_allocate_shared	 =	322	,
_MPI_Win_attach	 =	323	,
_MPI_Win_call_errhandler	 =	324	,
_MPI_Win_complete	 =	325	,
_MPI_Win_create	 =	326	,
_MPI_Win_create_dynamic	 =	327	,
_MPI_Win_create_errhandler	 =	328	,
_MPI_Win_create_keyval	 =	329	,
_MPI_Win_delete_attr	 =	330	,
_MPI_Win_detach	 =	331	,
_MPI_Win_fence	 =	332	,
_MPI_Win_flush	 =	333	,
_MPI_Win_flush_all	 =	334	,
_MPI_Win_flush_local	 =	335	,
_MPI_Win_flush_local_all	 =	336	,
_MPI_Win_free	 =	337	,
_MPI_Win_free_keyval	 =	338	,
_MPI_Win_get_attr	 =	339	,
_MPI_Win_get_errhandler	 =	340	,
_MPI_Win_get_group	 =	341	,
_MPI_Win_get_info	 =	342	,
_MPI_Win_get_name	 =	343	,
_MPI_Win_lock	 =	344	,
_MPI_Win_lock_all	 =	345	,
_MPI_Win_post	 =	346	,
_MPI_Win_set_attr	 =	347	,
_MPI_Win_set_errhandler	 =	348	,
_MPI_Win_set_info	 =	349	,
_MPI_Win_set_name	 =	350	,
_MPI_Win_shared_query	 =	351	,
_MPI_Win_start	 =	352	,
_MPI_Win_sync	 =	353	,
_MPI_Win_test	 =	354	,
_MPI_Win_unlock	 =	355	,
_MPI_Win_unlock_all	 =	356	,
_MPI_Win_wait	 =	357	,
_MPI_Wtick	 =	358	,
_MPI_Wtime	 =	359	
}_MPI_funcs;


typedef struct vector {
    struct dynamic_lib **items;
    int capacity;
    int total;
} vector;


typedef struct cell {
    void* func_ptr;
    int level;
   // void* next;
}cell;

typedef char* (*mpi_func)(int i);

void vector_init(vector *);
int vector_total(vector *);
static void vector_resize(vector *, int);
void vector_add(vector *, struct dynamic_lib *);
void vector_set(vector *, int, struct dynamic_lib *); 
struct dynamic_lib *vector_get(vector *, int); 
void vector_delete(vector *, int);
void vector_free(vector * );


typedef void* dynamic_lib_handle;

struct dynamic_lib {
	//TODO: fix this path variable (fixed size array )
    char                            path[100];
//  char*                         path;
    dynamic_lib_handle              handle;
    char*                           mpi_interceptions[NUM_MPI_FUNCS ];
	cell				table[NUM_MPI_FUNCS];
	void*				context;
};


void* 			QMPI_Get_context	    (vector* v, int i);
void 			QMPI_Set_context	    (vector *v, int index, void* cntxt, size_t sz);
int 			End_Tool 		        (int *argc,char ***argv,int i,vector* v);
dynamic_lib_handle 	load_lib 		    (const char* path);
void*   		get_func_ptr		    ( const dynamic_lib_handle handle, char* func_name );
int  			exec_func               (void* func_ptr, int level ,_MPI_funcs func_index,vector* v, ...);
void    		get_tool_interceptions  ( struct dynamic_lib* l );
int 			QMPI_Table_query	    (_MPI_funcs func_index, void** func_ptr, cell table[]);
int 			MPI_Table_query		    (_MPI_funcs func_index, void** func_ptr,  cell table[]);
int 			split 			        (char* paths, int next);
int             init_qmpi_struct        (void);

/* ================== C Wrappers for MPI_Send ================== */
    int QMPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level ,vector* v);
/* ================== C Wrappers for MPI_Recv ================== */
    int QMPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status, int level ,vector* v);

/* ================== C Wrappers for MPI_Abort ================== */
    int QMPI_Abort(MPI_Comm comm, int errorcode, int level ,vector* v);

/* ================== C Wrappers for MPI_Accumulate ================== */
    int QMPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, int level ,vector* v);

/* ================== C Wrappers for MPI_Add_error_class ================== */
    int QMPI_Add_error_class(int *errorclass, int level ,vector* v);

/* ================== C Wrappers for MPI_Add_error_code ================== */
    int QMPI_Add_error_code(int errorclass, int *errorcode, int level ,vector* v);

/* ================== C Wrappers for MPI_Add_error_string ================== */
    int QMPI_Add_error_string(int errorcode, const char *string, int level ,vector* v);

/* ================== C Wrappers for MPI_Address ================== */
    //int QMPI_Address(void *location, MPI_Aint *address, int level ,vector* v);

/* ================== C Wrappers for MPI_Allgather ================== */
    int QMPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);

/* ================== C Wrappers for MPI_Allgatherv ================== */
    int QMPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);

/* ================== C Wrappers for MPI_Alloc_mem ================== */
    int QMPI_Alloc_mem(MPI_Aint size, MPI_Info info, void *baseptr, int level ,vector* v);

/* ================== C Wrappers for MPI_Allreduce ================== */
    int QMPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level ,vector* v);

/* ================== C Wrappers for MPI_Alltoall ================== */
    int QMPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);

/* ================== C Wrappers for MPI_Alltoallv ================== */
    int QMPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int level ,vector* v);

/* ================== C Wrappers for MPI_Alltoallw ================== */
    int QMPI_Alltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, int level ,vector* v);

/* ================== C Wrappers for MPI_Attr_delete ================== */
    int QMPI_Attr_delete(MPI_Comm comm, int keyval, int level ,vector* v);

/* ================== C Wrappers for MPI_Attr_get ================== */
    int QMPI_Attr_get(MPI_Comm comm, int keyval, void *attribute_val, int *flag, int level ,vector* v);

/* ================== C Wrappers for MPI_Attr_put ================== */
    int QMPI_Attr_put(MPI_Comm comm, int keyval, void *attribute_val, int level ,vector* v);

/* ================== C Wrappers for MPI_Barrier ================== */
    int QMPI_Barrier(MPI_Comm comm, int level ,vector* v);

/* ================== C Wrappers for MPI_Bcast ================== */
    int QMPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, int level ,vector* v);

/* ================== C Wrappers for MPI_Bsend ================== */
    int QMPI_Bsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Bsend_init ================== */
    int QMPI_Bsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Buffer_attach ================== */
    int QMPI_Buffer_attach(void *buffer, int size, int level,  vector* v);

/* ================== C Wrappers for MPI_Buffer_detach ================== */
    int QMPI_Buffer_detach(void *buffer, int *size, int level,  vector* v);

/* ================== C Wrappers for MPI_Cancel ================== */
    int QMPI_Cancel(MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Cart_coords ================== */
    int QMPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[], int level,  vector* v);

/* ================== C Wrappers for MPI_Cart_create ================== */
    int QMPI_Cart_create(MPI_Comm old_comm, int ndims, const int dims[], const int periods[], int reorder, MPI_Comm *comm_cart, int level,  vector* v);

/* ================== C Wrappers for MPI_Cart_get ================== */
    int QMPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[], int level,  vector* v);

/* ================== C Wrappers for MPI_Cart_map ================== */
    int QMPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int *newrank, int level,  vector* v);

/* ================== C Wrappers for MPI_Cart_rank ================== */
    int QMPI_Cart_rank(MPI_Comm comm, const int coords[], int *rank, int level,  vector* v);

/* ================== C Wrappers for MPI_Cart_shift ================== */
    int QMPI_Cart_shift(MPI_Comm comm, int direction, int disp, int *rank_source, int *rank_dest, int level,  vector* v);

/* ================== C Wrappers for MPI_Cart_sub ================== */
    int QMPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm *new_comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Cartdim_get ================== */
    int QMPI_Cartdim_get(MPI_Comm comm, int *ndims, int level,  vector* v);

/* ================== C Wrappers for MPI_Close_port ================== */
    int QMPI_Close_port(const char *port_name, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_accept ================== */
    int QMPI_Comm_accept(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_call_errhandler ================== */
    int QMPI_Comm_call_errhandler(MPI_Comm comm, int errorcode, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_compare ================== */
    int QMPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_connect ================== */
    int QMPI_Comm_connect(const char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_create ================== */
    int QMPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_create_errhandler ================== */
    int QMPI_Comm_create_errhandler(MPI_Comm_errhandler_function *function, MPI_Errhandler *errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_create_group ================== */
    int QMPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_create_keyval ================== */
    int QMPI_Comm_create_keyval(MPI_Comm_copy_attr_function *comm_copy_attr_fn, MPI_Comm_delete_attr_function *comm_delete_attr_fn, int *comm_keyval, void *extra_state, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_delete_attr ================== */
    int QMPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_disconnect ================== */
    int QMPI_Comm_disconnect(MPI_Comm *comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_dup ================== */
    int QMPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_dup_with_info ================== */
    int QMPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_free ================== */
    int QMPI_Comm_free(MPI_Comm *comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_free_keyval ================== */
    int QMPI_Comm_free_keyval(int *comm_keyval, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_get_attr ================== */
    int QMPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_get_errhandler ================== */
    int QMPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler *erhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_get_info ================== */
    int QMPI_Comm_get_info(MPI_Comm comm, MPI_Info *info_used, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_get_name ================== */
    int QMPI_Comm_get_name(MPI_Comm comm, char *comm_name, int *resultlen, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_get_parent ================== */
    int QMPI_Comm_get_parent(MPI_Comm *parent, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_group ================== */
    int QMPI_Comm_group(MPI_Comm comm, MPI_Group *group, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_idup ================== */
    int QMPI_Comm_idup(MPI_Comm comm, MPI_Comm *newcomm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_join ================== */
    int QMPI_Comm_join(int fd, MPI_Comm *intercomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_rank ================== */
    int QMPI_Comm_rank(MPI_Comm comm,int *rank,  int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_remote_group ================== */
    int QMPI_Comm_remote_group(MPI_Comm comm, MPI_Group *group, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_remote_size ================== */
    int QMPI_Comm_remote_size(MPI_Comm comm, int *size, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_set_attr ================== */
    int QMPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void *attribute_val, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_set_errhandler ================== */
    int QMPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_set_info ================== */
    int QMPI_Comm_set_info(MPI_Comm comm, MPI_Info info, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_set_name ================== */
    int QMPI_Comm_set_name(MPI_Comm comm, const char *comm_name, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_size ================== */
    int QMPI_Comm_size(MPI_Comm comm, int *size,  int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_split ================== */
    int QMPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_split_type ================== */
    int QMPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Comm_test_inter ================== */
    int QMPI_Comm_test_inter(MPI_Comm comm, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Compare_and_swap ================== */
    int QMPI_Compare_and_swap(const void *origin_addr, const void *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Dims_create ================== */
    int QMPI_Dims_create(int nnodes, int ndims, int dims[], int level,  vector* v);

/* ================== C Wrappers for MPI_Dist_graph_create ================== */
    int QMPI_Dist_graph_create(MPI_Comm comm_old, int n, const int nodes[], const int degrees[], const int targets[], const int weights[], MPI_Info info, int reorder, MPI_Comm *newcomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Dist_graph_create_adjacent ================== */
    int QMPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[], const int sourceweights[], int outdegree, const int destinations[], const int destweights[], MPI_Info info, int reorder, MPI_Comm *comm_dist_graph, int level,  vector* v);

/* ================== C Wrappers for MPI_Dist_graph_neighbors ================== */
    int QMPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[], int maxoutdegree, int destinations[], int destweights[], int level,  vector* v);

/* ================== C Wrappers for MPI_Dist_graph_neighbors_count ================== */
    int QMPI_Dist_graph_neighbors_count(MPI_Comm comm, int *inneighbors, int *outneighbors, int *weighted, int level,  vector* v);

/* ================== C Wrappers for MPI_Errhandler_create ================== */
    int QMPI_Errhandler_create(MPI_Handler_function *function, MPI_Errhandler *errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Errhandler_free ================== */
    int QMPI_Errhandler_free(MPI_Errhandler *errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Errhandler_get ================== */
    int QMPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler *errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Errhandler_set ================== */
    int QMPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Error_class ================== */
    int QMPI_Error_class(int errorcode, int *errorclass, int level,  vector* v);

/* ================== C Wrappers for MPI_Error_string ================== */
    int QMPI_Error_string(int errorcode, char *string, int *resultlen, int level,  vector* v);

/* ================== C Wrappers for MPI_Exscan ================== */
    int QMPI_Exscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Fetch_and_op ================== */
    int QMPI_Fetch_and_op(const void *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_File_call_errhandler ================== */
    int QMPI_File_call_errhandler(MPI_File fh, int errorcode, int level,  vector* v);

/* ================== C Wrappers for MPI_File_close ================== */
    int QMPI_File_close(MPI_File *fh, int level,  vector* v);

/* ================== C Wrappers for MPI_File_create_errhandler ================== */
    int QMPI_File_create_errhandler(MPI_File_errhandler_function *function, MPI_Errhandler *errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_File_delete ================== */
    int QMPI_File_delete(const char *filename, MPI_Info info, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_amode ================== */
    int QMPI_File_get_amode(MPI_File fh, int *amode, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_atomicity ================== */
    int QMPI_File_get_atomicity(MPI_File fh, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_byte_offset ================== */
    int QMPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_errhandler ================== */
    int QMPI_File_get_errhandler(MPI_File file, MPI_Errhandler *errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_group ================== */
    int QMPI_File_get_group(MPI_File fh, MPI_Group *group, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_info ================== */
    int QMPI_File_get_info(MPI_File fh, MPI_Info *info_used, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_position ================== */
    int QMPI_File_get_position(MPI_File fh, MPI_Offset *offset, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_position_shared ================== */
    int QMPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_size ================== */
    int QMPI_File_get_size(MPI_File fh, MPI_Offset *size, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_type_extent ================== */
    int QMPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, MPI_Aint *extent, int level,  vector* v);

/* ================== C Wrappers for MPI_File_get_view ================== */
    int QMPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iread ================== */
    int QMPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iread_all ================== */
    int QMPI_File_iread_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iread_at ================== */
    int QMPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iread_at_all ================== */
    int QMPI_File_iread_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iread_shared ================== */
    int QMPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iwrite ================== */
    int QMPI_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iwrite_all ================== */
    int QMPI_File_iwrite_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iwrite_at ================== */
    int QMPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iwrite_at_all ================== */
    int QMPI_File_iwrite_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_iwrite_shared ================== */
    int QMPI_File_iwrite_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_File_open ================== */
    int QMPI_File_open(MPI_Comm comm, const char *filename, int amode, MPI_Info info, MPI_File *fh, int level,  vector* v);

/* ================== C Wrappers for MPI_File_preallocate ================== */
    int QMPI_File_preallocate(MPI_File fh, MPI_Offset size, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read ================== */
    int QMPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_all ================== */
    int QMPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_all_begin ================== */
    int QMPI_File_read_all_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_all_end ================== */
    int QMPI_File_read_all_end(MPI_File fh, void *buf, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_at ================== */
    int QMPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_at_all ================== */
    int QMPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_at_all_begin ================== */
    int QMPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_at_all_end ================== */
    int QMPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_ordered ================== */
    int QMPI_File_read_ordered(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_ordered_begin ================== */
    int QMPI_File_read_ordered_begin(MPI_File fh, void *buf, int count, MPI_Datatype datatype, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_ordered_end ================== */
    int QMPI_File_read_ordered_end(MPI_File fh, void *buf, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_read_shared ================== */
    int QMPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_seek ================== */
    int QMPI_File_seek(MPI_File fh, MPI_Offset offset, int whence, int level,  vector* v);

/* ================== C Wrappers for MPI_File_seek_shared ================== */
    int QMPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int whence, int level,  vector* v);

/* ================== C Wrappers for MPI_File_set_atomicity ================== */
    int QMPI_File_set_atomicity(MPI_File fh, int flag, int level,  vector* v);

/* ================== C Wrappers for MPI_File_set_errhandler ================== */
    int QMPI_File_set_errhandler(MPI_File file, MPI_Errhandler errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_File_set_info ================== */
    int QMPI_File_set_info(MPI_File fh, MPI_Info info, int level,  vector* v);

/* ================== C Wrappers for MPI_File_set_size ================== */
    int QMPI_File_set_size(MPI_File fh, MPI_Offset size, int level,  vector* v);

/* ================== C Wrappers for MPI_File_set_view ================== */
    int QMPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, const char *datarep, MPI_Info info, int level,  vector* v);

/* ================== C Wrappers for MPI_File_sync ================== */
    int QMPI_File_sync(MPI_File fh, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write ================== */
    int QMPI_File_write(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_all ================== */
    int QMPI_File_write_all(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_all_begin ================== */
    int QMPI_File_write_all_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_all_end ================== */
    int QMPI_File_write_all_end(MPI_File fh, const void *buf, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_at ================== */
    int QMPI_File_write_at(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_at_all ================== */
    int QMPI_File_write_at_all(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_at_all_begin ================== */
    int QMPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, const void *buf, int count, MPI_Datatype datatype, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_at_all_end ================== */
    int QMPI_File_write_at_all_end(MPI_File fh, const void *buf, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_ordered ================== */
    int QMPI_File_write_ordered(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_ordered_begin ================== */
    int QMPI_File_write_ordered_begin(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_ordered_end ================== */
    int QMPI_File_write_ordered_end(MPI_File fh, const void *buf, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_File_write_shared ================== */
    int QMPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Finalize ================== */
    int QMPI_Finalize(  int level,  vector* v);

/* ================== C Wrappers for MPI_Finalized ================== */
    int QMPI_Finalized(int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Free_mem ================== */
    int QMPI_Free_mem(void *base, int level,  vector* v);

/* ================== C Wrappers for MPI_Gather ================== */
    int QMPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Gatherv ================== */
    int QMPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Get ================== */
    int QMPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Get_accumulate ================== */
    int QMPI_Get_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Get_address ================== */
    int QMPI_Get_address(const void *location, MPI_Aint *address, int level,  vector* v);

/* ================== C Wrappers for MPI_Get_count ================== */
    int QMPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count, int level,  vector* v);

/* ================== C Wrappers for MPI_Get_elements ================== */
    int QMPI_Get_elements(const MPI_Status *status, MPI_Datatype datatype, int *count, int level,  vector* v);

/* ================== C Wrappers for MPI_Get_elements_x ================== */
    int QMPI_Get_elements_x(const MPI_Status *status, MPI_Datatype datatype, MPI_Count *count, int level,  vector* v);

/* ================== C Wrappers for MPI_Get_library_version ================== */
    int QMPI_Get_library_version(char *version, int *resultlen, int level,  vector* v);

/* ================== C Wrappers for MPI_Get_processor_name ================== */
    int QMPI_Get_processor_name(char *name, int *resultlen, int level,  vector* v);

/* ================== C Wrappers for MPI_Get_version ================== */
    int QMPI_Get_version(int *version, int *subversion, int level,  vector* v);

/* ================== C Wrappers for MPI_Graph_create ================== */
    int QMPI_Graph_create(MPI_Comm comm_old, int nnodes, const int index[], const int edges[], int reorder, MPI_Comm *comm_graph, int level,  vector* v);

/* ================== C Wrappers for MPI_Graph_get ================== */
    int QMPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int index[], int edges[], int level,  vector* v);

/* ================== C Wrappers for MPI_Graph_map ================== */
    int QMPI_Graph_map(MPI_Comm comm, int nnodes, const int index[], const int edges[], int *newrank, int level,  vector* v);

/* ================== C Wrappers for MPI_Graph_neighbors ================== */
    int QMPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[], int level,  vector* v);

/* ================== C Wrappers for MPI_Graph_neighbors_count ================== */
    int QMPI_Graph_neighbors_count(MPI_Comm comm, int rank, int *nneighbors, int level,  vector* v);

/* ================== C Wrappers for MPI_Graphdims_get ================== */
    int QMPI_Graphdims_get(MPI_Comm comm, int *nnodes, int *nedges, int level,  vector* v);

/* ================== C Wrappers for MPI_Grequest_complete ================== */
    int QMPI_Grequest_complete(MPI_Request request, int level,  vector* v);

/* ================== C Wrappers for MPI_Grequest_start ================== */
    int QMPI_Grequest_start(MPI_Grequest_query_function *query_fn, MPI_Grequest_free_function *free_fn, MPI_Grequest_cancel_function *cancel_fn, void *extra_state, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_compare ================== */
    int QMPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_difference ================== */
    int QMPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_excl ================== */
    int QMPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_free ================== */
    int QMPI_Group_free(MPI_Group *group, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_incl ================== */
    int QMPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_intersection ================== */
    int QMPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_range_excl ================== */
    int QMPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_range_incl ================== */
    int QMPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], MPI_Group *newgroup, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_rank ================== */
    int QMPI_Group_rank(MPI_Group group, int *rank, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_size ================== */
    int QMPI_Group_size(MPI_Group group, int *size, int level,  vector* v);

/* ================== C Wrappers for MPI_Group_translate_ranks ================== */
    int QMPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2, int ranks2[], int level,  vector* v);

/* ================== C Wrappers for MPI_Group_union ================== */
    int QMPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup, int level,  vector* v);

/* ================== C Wrappers for MPI_Iallgather ================== */
    int QMPI_Iallgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Iallgatherv ================== */
    int QMPI_Iallgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Iallreduce ================== */
    int QMPI_Iallreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ialltoall ================== */
    int QMPI_Ialltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ialltoallv ================== */
    int QMPI_Ialltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ialltoallw ================== */
    int QMPI_Ialltoallw(const void *sendbuf, const int sendcounts[], const int sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ibarrier ================== */
    int QMPI_Ibarrier(MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ibcast ================== */
    int QMPI_Ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ibsend ================== */
    int QMPI_Ibsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Iexscan ================== */
    int QMPI_Iexscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Igather ================== */
    int QMPI_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Igatherv ================== */
    int QMPI_Igatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Improbe ================== */
    int QMPI_Improbe(int source, int tag, MPI_Comm comm, int *flag, MPI_Message *message, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Imrecv ================== */
    int QMPI_Imrecv(void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ineighbor_allgather ================== */
    int QMPI_Ineighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ineighbor_allgatherv ================== */
    int QMPI_Ineighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ineighbor_alltoall ================== */
    int QMPI_Ineighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ineighbor_alltoallv ================== */
    int QMPI_Ineighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ineighbor_alltoallw ================== */
    int QMPI_Ineighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Info_create ================== */
    int QMPI_Info_create(MPI_Info *info, int level,  vector* v); 

/* ================== C Wrappers for MPI_Info_delete ================== */
    int QMPI_Info_delete(MPI_Info info, const char *key, int level,  vector* v);

/* ================== C Wrappers for MPI_Info_dup ================== */
    int QMPI_Info_dup(MPI_Info info, MPI_Info *newinfo, int level,  vector* v);

/* ================== C Wrappers for MPI_Info_free ================== */
    int QMPI_Info_free(MPI_Info *info, int level,  vector* v);

/* ================== C Wrappers for MPI_Info_get ================== */
    int QMPI_Info_get(MPI_Info info, const char *key, int valuelen, char *value, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Info_get_nkeys ================== */
    int QMPI_Info_get_nkeys(MPI_Info info, int *nkeys, int level,  vector* v);

/* ================== C Wrappers for MPI_Info_get_nthkey ================== */
    int QMPI_Info_get_nthkey(MPI_Info info, int n, char *key, int level,  vector* v);

/* ================== C Wrappers for MPI_Info_get_valuelen ================== */
    int QMPI_Info_get_valuelen(MPI_Info info, const char *key, int *valuelen, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Info_set ================== */
    int QMPI_Info_set(MPI_Info info, const char *key, const char *value, int level,  vector* v);

/* ================== C Wrappers for MPI_Init ================== */
    int QMPI_Init(int *argc, char ***argv, int level,  vector* v);

/* ================== C Wrappers for MPI_Init_thread ================== */
    int QMPI_Init_thread(int *argc, char ***argv, int required, int *provided, int level,  vector* v);

/* ================== C Wrappers for MPI_Initialized ================== */
    int QMPI_Initialized(int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Intercomm_create ================== */
    int QMPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm bridge_comm, int remote_leader, int tag, MPI_Comm *newintercomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Intercomm_merge ================== */
    int QMPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintercomm, int level,  vector* v);

/* ================== C Wrappers for MPI_Iprobe ================== */
    int QMPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Irecv ================== */
    int QMPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ireduce ================== */
    int QMPI_Ireduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ireduce_scatter ================== */
    int QMPI_Ireduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Ireduce_scatter_block ================== */
    int QMPI_Ireduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Irsend ================== */
    int QMPI_Irsend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Is_thread_main ================== */
    int QMPI_Is_thread_main(int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Iscan ================== */
    int QMPI_Iscan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Iscatter ================== */
    int QMPI_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Iscatterv ================== */
    int QMPI_Iscatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Isend ================== */
    int QMPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Issend ================== */
    int QMPI_Issend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Keyval_create ================== */
    int QMPI_Keyval_create(MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state, int level,  vector* v);

/* ================== C Wrappers for MPI_Keyval_free ================== */
    int QMPI_Keyval_free(int *keyval, int level,  vector* v);

/* ================== C Wrappers for MPI_Lookup_name ================== */
    int QMPI_Lookup_name(const char *service_name, MPI_Info info, char *port_name, int level,  vector* v);

/* ================== C Wrappers for MPI_Mprobe ================== */
    int QMPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message *message, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Mrecv ================== */
    int QMPI_Mrecv(void *buf, int count, MPI_Datatype type, MPI_Message *message, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Neighbor_allgather ================== */
    int QMPI_Neighbor_allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Neighbor_allgatherv ================== */
    int QMPI_Neighbor_allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int displs[], MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Neighbor_alltoall ================== */
    int QMPI_Neighbor_alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Neighbor_alltoallv ================== */
    int QMPI_Neighbor_alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype, void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Neighbor_alltoallw ================== */
    int QMPI_Neighbor_alltoallw(const void *sendbuf, const int sendcounts[], const MPI_Aint sdispls[], const MPI_Datatype sendtypes[], void *recvbuf, const int recvcounts[], const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Op_commutative ================== */
    int QMPI_Op_commutative(MPI_Op op, int *commute, int level,  vector* v);

/* ================== C Wrappers for MPI_Op_create ================== */
    int QMPI_Op_create(MPI_User_function *function, int commute, MPI_Op *op, int level,  vector* v);

/* ================== C Wrappers for MPI_Op_free ================== */
    int QMPI_Op_free(MPI_Op *op, int level,  vector* v);

/* ================== C Wrappers for MPI_Open_port ================== */
    int QMPI_Open_port(MPI_Info info, char *port_name, int level,  vector* v);

/* ================== C Wrappers for MPI_Pack ================== */
    int QMPI_Pack(const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int outsize, int *position, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Pack al ================== */
    int QMPI_Pack_external(const char datarep[], const void *inbuf, int incount, MPI_Datatype datatype, void *outbuf, MPI_Aint outsize, MPI_Aint *position, int level,  vector* v);

/* ================== C Wrappers for MPI_Pack al_size ================== */
    int QMPI_Pack_external_size(const char datarep[], int incount, MPI_Datatype datatype, MPI_Aint *size, int level,  vector* v);

/* ================== C Wrappers for MPI_Pack_size ================== */
    int QMPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int *size, int level,  vector* v);

/* ================== C Wrappers for MPI_Pcontrol ================== */
    int QMPI_Pcontrol(const int level, int levl,  vector* v);

/* ================== C Wrappers for MPI_Probe ================== */
    int QMPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Publish_name ================== */
    int QMPI_Publish_name(const char *service_name, MPI_Info info, const char *port_name, int level,  vector* v);

/* ================== C Wrappers for MPI_Put ================== */
    int QMPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Query_thread ================== */
    int QMPI_Query_thread(int *provided, int level,  vector* v);

/* ================== C Wrappers for MPI_Raccumulate ================== */
    int QMPI_Raccumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Recv_init ================== */
    int QMPI_Recv_init(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Reduce ================== */
    int QMPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Reduce_local ================== */
    int QMPI_Reduce_local(const void *inbuf, void *inoutbuf, int count, MPI_Datatype datatype, MPI_Op op, int level,  vector* v);

/* ================== C Wrappers for MPI_Reduce_scatter ================== */
    int QMPI_Reduce_scatter(const void *sendbuf, void *recvbuf, const int recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Reduce_scatter_block ================== */
    int QMPI_Reduce_scatter_block(const void *sendbuf, void *recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Register_datarep ================== */
    int QMPI_Register_datarep(const char *datarep, MPI_Datarep_conversion_function *read_conversion_fn, MPI_Datarep_conversion_function *write_conversion_fn, MPI_Datarep_extent_function *dtype_file_extent_fn, void *extra_state, int level,  vector* v);

/* ================== C Wrappers for MPI_Request_free ================== */
    int QMPI_Request_free(MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Request_get_status ================== */
    int QMPI_Request_get_status(MPI_Request request, int *flag, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Rget ================== */
    int QMPI_Rget(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Rget_accumulate ================== */
    int QMPI_Rget_accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Rput ================== */
    int QMPI_Rput(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_cout, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Rsend ================== */
    int QMPI_Rsend(const void *ibuf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Rsend_init ================== */
    int QMPI_Rsend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Scan ================== */
    int QMPI_Scan(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Scatter ================== */
    int QMPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Scatterv ================== */
    int QMPI_Scatterv(const void *sendbuf, const int sendcounts[], const int displs[], MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Send_init ================== */
    int QMPI_Send_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Sendrecv ================== */
    int QMPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Sendrecv_replace ================== */
    int QMPI_Sendrecv_replace(void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Ssend ================== */
    int QMPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Ssend_init ================== */
    int QMPI_Ssend_init(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Start ================== */
    int QMPI_Start(MPI_Request *request, int level,  vector* v);

/* ================== C Wrappers for MPI_Startall ================== */
    int QMPI_Startall(int count, MPI_Request array_of_requests[], int level,  vector* v);

/* ================== C Wrappers for MPI_Status_set_cancelled ================== */
    int QMPI_Status_set_cancelled(MPI_Status *status, int flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Status_set_elements ================== */
    int QMPI_Status_set_elements(MPI_Status *status, MPI_Datatype datatype, int count, int level,  vector* v);

/* ================== C Wrappers for MPI_Status_set_elements_x ================== */
    int QMPI_Status_set_elements_x(MPI_Status *status, MPI_Datatype datatype, MPI_Count count, int level,  vector* v);

/* ================== C Wrappers for MPI_Test ================== */
    int QMPI_Test(MPI_Request *request, int *flag, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Test_cancelled ================== */
    int QMPI_Test_cancelled(const MPI_Status *status, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Testall ================== */
    int QMPI_Testall(int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[], int level,  vector* v);

/* ================== C Wrappers for MPI_Testany ================== */
    int QMPI_Testany(int count, MPI_Request array_of_requests[], int *index, int *flag, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Testsome ================== */
    int QMPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[], int level,  vector* v);

/* ================== C Wrappers for MPI_Topo_test ================== */
    int QMPI_Topo_test(MPI_Comm comm, int *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_commit ================== */
    int QMPI_Type_commit(MPI_Datatype *type, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_contiguous ================== */
    int QMPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_darray ================== */
    int QMPI_Type_create_darray(int size, int rank, int ndims, const int gsize_array[], const int distrib_array[], const int darg_array[], const int psize_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_f90_complex ================== */
    int QMPI_Type_create_f90_complex(int p, int r, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_f90_integer ================== */
    int QMPI_Type_create_f90_integer(int r, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_f90_real ================== */
    int QMPI_Type_create_f90_real(int p, int r, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_hindexed ================== */
    int QMPI_Type_create_hindexed(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_hindexed_block ================== */
    int QMPI_Type_create_hindexed_block(int count, int blocklength, const MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_hvector ================== */
    int QMPI_Type_create_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_indexed_block ================== */
    int QMPI_Type_create_indexed_block(int count, int blocklength, const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_keyval ================== */
    int QMPI_Type_create_keyval(MPI_Type_copy_attr_function *type_copy_attr_fn, MPI_Type_delete_attr_function *type_delete_attr_fn, int *type_keyval, void *extra_state, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_resized ================== */
    int QMPI_Type_create_resized(MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_struct ================== */
    int QMPI_Type_create_struct(int count, const int array_of_block_lengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_create_subarray ================== */
    int QMPI_Type_create_subarray(int ndims, const int size_array[], const int subsize_array[], const int start_array[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_delete_attr ================== */
    int QMPI_Type_delete_attr(MPI_Datatype type, int type_keyval, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_dup ================== */
    int QMPI_Type_dup(MPI_Datatype type, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_extent ================== */
    int QMPI_Type_extent(MPI_Datatype type, MPI_Aint *extent, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_free ================== */
    int QMPI_Type_free(MPI_Datatype *type, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_free_keyval ================== */
    int QMPI_Type_free_keyval(int *type_keyval, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_get_attr ================== */
    int QMPI_Type_get_attr(MPI_Datatype type, int type_keyval, void *attribute_val, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_get_contents ================== */
    int QMPI_Type_get_contents(MPI_Datatype mtype, int max_integers, int max_addresses, int max_datatypes, int array_of_integers[], MPI_Aint array_of_addresses[], MPI_Datatype array_of_datatypes[], int level,  vector* v);

/* ================== C Wrappers for MPI_Type_get_envelope ================== */
    int QMPI_Type_get_envelope(MPI_Datatype type, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_get_extent ================== */
    int QMPI_Type_get_extent(MPI_Datatype type, MPI_Aint *lb, MPI_Aint *extent, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_get_extent_x ================== */
    int QMPI_Type_get_extent_x(MPI_Datatype type, MPI_Count *lb, MPI_Count *extent, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_get_name ================== */
    int QMPI_Type_get_name(MPI_Datatype type, char *type_name, int *resultlen, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_get_true_extent ================== */
    int QMPI_Type_get_true_extent(MPI_Datatype datatype, MPI_Aint *true_lb, MPI_Aint *true_extent, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_get_true_extent_x ================== */
    int QMPI_Type_get_true_extent_x(MPI_Datatype datatype, MPI_Count *true_lb, MPI_Count *true_extent, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_hindexed ================== */
    int QMPI_Type_hindexed(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_hvector ================== */
    int QMPI_Type_hvector(int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_indexed ================== */
    int QMPI_Type_indexed(int count, const int array_of_blocklengths[], const int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_lb ================== */
    int QMPI_Type_lb(MPI_Datatype type, MPI_Aint *lb, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_match_size ================== */
    int QMPI_Type_match_size(int typeclass, int size, MPI_Datatype *type, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_set_attr ================== */
    int QMPI_Type_set_attr(MPI_Datatype type, int type_keyval, void *attr_val, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_set_name ================== */
    int QMPI_Type_set_name(MPI_Datatype type, const char *type_name, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_size ================== */
    int QMPI_Type_size(MPI_Datatype type, int *size, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_size_x ================== */
    int QMPI_Type_size_x(MPI_Datatype type, MPI_Count *size, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_struct ================== */
    int QMPI_Type_struct(int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_ub ================== */
    int QMPI_Type_ub(MPI_Datatype mtype, MPI_Aint *ub, int level,  vector* v);

/* ================== C Wrappers for MPI_Type_vector ================== */
    int QMPI_Type_vector(int count, int blocklength, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype, int level,  vector* v);

/* ================== C Wrappers for MPI_Unpack ================== */
    int QMPI_Unpack(const void *inbuf, int insize, int *position, void *outbuf, int outcount, MPI_Datatype datatype, MPI_Comm comm, int level,  vector* v);

/* ================== C Wrappers for MPI_Unpack al ================== */
    int QMPI_Unpack_external(const char datarep[], const void *inbuf, MPI_Aint insize, MPI_Aint *position, void *outbuf, int outcount, MPI_Datatype datatype, int level,  vector* v);

/* ================== C Wrappers for MPI_Unpublish_name ================== */
    int QMPI_Unpublish_name(const char *service_name, MPI_Info info, const char *port_name, int level,  vector* v);

/* ================== C Wrappers for MPI_Wait ================== */
    int QMPI_Wait(MPI_Request *request, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Waitall ================== */
    int QMPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status *array_of_statuses, int level,  vector* v);

/* ================== C Wrappers for MPI_Waitany ================== */
    int QMPI_Waitany(int count, MPI_Request array_of_requests[], int *index, MPI_Status *status, int level,  vector* v);

/* ================== C Wrappers for MPI_Waitsome ================== */
    int QMPI_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount, int array_of_indices[], MPI_Status array_of_statuses[], int level,  vector* v);

/* ================== C Wrappers for MPI_Win_allocate ================== */
    int QMPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_allocate_shared ================== */
    int QMPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_attach ================== */
    int QMPI_Win_attach(MPI_Win win, void *base, MPI_Aint size, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_call_errhandler ================== */
    int QMPI_Win_call_errhandler(MPI_Win win, int errorcode, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_complete ================== */
    int QMPI_Win_complete(MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_create ================== */
    int QMPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_create_dynamic ================== */
    int QMPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win *win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_create_errhandler ================== */
    int QMPI_Win_create_errhandler(MPI_Win_errhandler_function *function, MPI_Errhandler *errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_create_keyval ================== */
    int QMPI_Win_create_keyval(MPI_Win_copy_attr_function *win_copy_attr_fn, MPI_Win_delete_attr_function *win_delete_attr_fn, int *win_keyval, void *extra_state, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_delete_attr ================== */
    int QMPI_Win_delete_attr(MPI_Win win, int win_keyval, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_detach ================== */
    int QMPI_Win_detach(MPI_Win win, const void *base, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_fence ================== */
    int QMPI_Win_fence(int assert, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_flush ================== */
    int QMPI_Win_flush(int rank, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_flush_all ================== */
    int QMPI_Win_flush_all(MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_flush_local ================== */
    int QMPI_Win_flush_local(int rank, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_flush_local_all ================== */
    int QMPI_Win_flush_local_all(MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_free ================== */
    int QMPI_Win_free(MPI_Win *win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_free_keyval ================== */
    int QMPI_Win_free_keyval(int *win_keyval, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_get_attr ================== */
    int QMPI_Win_get_attr(MPI_Win win, int win_keyval, void *attribute_val, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_get_errhandler ================== */
    int QMPI_Win_get_errhandler(MPI_Win win, MPI_Errhandler *errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_get_group ================== */
    int QMPI_Win_get_group(MPI_Win win, MPI_Group *group, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_get_info ================== */
    int QMPI_Win_get_info(MPI_Win win, MPI_Info *info_used, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_get_name ================== */
    int QMPI_Win_get_name(MPI_Win win, char *win_name, int *resultlen, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_lock ================== */
    int QMPI_Win_lock(int lock_type, int rank, int assert, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_lock_all ================== */
    int QMPI_Win_lock_all(int assert, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_post ================== */
    int QMPI_Win_post(MPI_Group group, int assert, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_set_attr ================== */
    int QMPI_Win_set_attr(MPI_Win win, int win_keyval, void *attribute_val, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_set_errhandler ================== */
    int QMPI_Win_set_errhandler(MPI_Win win, MPI_Errhandler errhandler, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_set_info ================== */
    int QMPI_Win_set_info(MPI_Win win, MPI_Info info, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_set_name ================== */
    int QMPI_Win_set_name(MPI_Win win, const char *win_name, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_shared_query ================== */
    int QMPI_Win_shared_query(MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_start ================== */
    int QMPI_Win_start(MPI_Group group, int assert, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_sync ================== */
    int QMPI_Win_sync(MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_test ================== */
    int QMPI_Win_test(MPI_Win win, int *flag, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_unlock ================== */
    int QMPI_Win_unlock(int rank, MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_unlock_all ================== */
    int QMPI_Win_unlock_all(MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Win_wait ================== */
    int QMPI_Win_wait(MPI_Win win, int level,  vector* v);

/* ================== C Wrappers for MPI_Wtick ================== */
    double QMPI_Wtick( int level,  vector* v);

/* ================== C Wrappers for MPI_Wtime ================== */
    double QMPI_Wtime( int level,  vector* v);
#endif

