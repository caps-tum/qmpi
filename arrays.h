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

#include "qmpi.h"
#include <mpi.h>
void* QMPI_Array[]={  
  
        &QMPI_Abort,                   &QMPI_Accumulate,                   &QMPI_Add_error_class
   ,    &QMPI_Add_error_code,          &QMPI_Add_error_string/*,             &QMPI_Address*/
   ,    &QMPI_Allgather,               &QMPI_Allgatherv,                   &QMPI_Alloc_mem
   ,    &QMPI_Allreduce,               &QMPI_Alltoall   ,                  &QMPI_Alltoallv
   ,    &QMPI_Alltoallw,               &QMPI_Attr_delete,                  &QMPI_Attr_get
   ,    &QMPI_Attr_put,                &QMPI_Barrier,                      &QMPI_Bcast
   ,    &QMPI_Bsend,                   &QMPI_Bsend_init,                   &QMPI_Buffer_attach
   ,    &QMPI_Buffer_detach,           &QMPI_Cancel,                       &QMPI_Cart_coords
   ,    &QMPI_Cart_create,             &QMPI_Cart_get,                     &QMPI_Cart_map
   ,    &QMPI_Cart_rank,               &QMPI_Cart_shift,                   &QMPI_Cart_sub
   ,    &QMPI_Cartdim_get,             &QMPI_Close_port,                   &QMPI_Comm_accept
   ,    &QMPI_Comm_call_errhandler,    &QMPI_Comm_compare,                 &QMPI_Comm_connect   
   ,    &QMPI_Comm_create,             &QMPI_Comm_create_errhandler,       &QMPI_Comm_create_group
   ,    &QMPI_Comm_create_keyval,      &QMPI_Comm_delete_attr,             &QMPI_Comm_disconnect
   ,    &QMPI_Comm_dup,                &QMPI_Comm_dup_with_info,           &QMPI_Comm_free
   ,    &QMPI_Comm_free_keyval,        &QMPI_Comm_get_attr,                &QMPI_Comm_get_errhandler
   ,    &QMPI_Comm_get_info,           &QMPI_Comm_get_name,                &QMPI_Comm_get_parent
   ,    &QMPI_Comm_group,              &QMPI_Comm_idup,                    &QMPI_Comm_join
   ,    &QMPI_Comm_rank,               &QMPI_Comm_remote_group,            &QMPI_Comm_remote_size
   ,    &QMPI_Comm_set_attr,           &QMPI_Comm_set_errhandler,          &QMPI_Comm_set_info
   ,    &QMPI_Comm_set_name,           &QMPI_Comm_size,                    &QMPI_Comm_split
   ,    &QMPI_Comm_split_type,         &QMPI_Comm_test_inter,              &QMPI_Compare_and_swap
   ,    &QMPI_Dims_create,             &QMPI_Dist_graph_create,            &QMPI_Dist_graph_create_adjacent
   ,    &QMPI_Dist_graph_neighbors,    &QMPI_Dist_graph_neighbors_count/*,   &QMPI_Errhandler_create*/
   ,    &QMPI_Errhandler_free/*,         &QMPI_Errhandler_get*//*,               &QMPI_Errhandler_set*/
   ,    &QMPI_Error_class,             &QMPI_Error_string,                 &QMPI_Exscan
   ,    &QMPI_Fetch_and_op,            &QMPI_File_call_errhandler,         &QMPI_File_close
   ,    &QMPI_File_create_errhandler,  &QMPI_File_delete,                  &QMPI_File_get_amode
   ,    &QMPI_File_get_atomicity,      &QMPI_File_get_byte_offset,         &QMPI_File_get_errhandler
   ,    &QMPI_File_get_group,          &QMPI_File_get_info,                &QMPI_File_get_position
   ,    &QMPI_File_get_position_shared,&QMPI_File_get_size,                &QMPI_File_get_type_extent
   ,    &QMPI_File_get_view,           &QMPI_File_iread,                   &QMPI_File_iread_all
   ,    &QMPI_File_iread_at,           &QMPI_File_iread_at_all,            &QMPI_File_iread_shared
   ,    &QMPI_File_iwrite,             &QMPI_File_iwrite_all,              &QMPI_File_iwrite_at
   ,    &QMPI_File_iwrite_at_all,      &QMPI_File_iwrite_shared,           &QMPI_File_open
   ,    &QMPI_File_preallocate,        &QMPI_File_read,                    &QMPI_File_read_all
   ,    &QMPI_File_read_all_begin,     &QMPI_File_read_all_end,            &QMPI_File_read_at
   ,    &QMPI_File_read_at_all,        &QMPI_File_read_at_all_begin,       &QMPI_File_read_at_all_end
   ,    &QMPI_File_read_ordered,       &QMPI_File_read_ordered_begin,      &QMPI_File_read_ordered_end
   ,    &QMPI_File_read_shared,        &QMPI_File_seek,                    &QMPI_File_seek_shared
   ,    &QMPI_File_set_atomicity,      &QMPI_File_set_errhandler,          &QMPI_File_set_info
   ,    &QMPI_File_set_size,           &QMPI_File_set_view,                &QMPI_File_sync
   ,    &QMPI_File_write,              &QMPI_File_write_all,               &QMPI_File_write_all_begin
   ,    &QMPI_File_write_all_end,      &QMPI_File_write_at,                &QMPI_File_write_at_all
   ,    &QMPI_File_write_at_all_begin, &QMPI_File_write_at_all_end,        &QMPI_File_write_ordered
   ,    &QMPI_File_write_ordered_begin,&QMPI_File_write_ordered_end,       &QMPI_File_write_shared
   ,    &QMPI_Finalize,                &QMPI_Finalized,                    &QMPI_Free_mem
   ,    &QMPI_Gather,                  &QMPI_Gatherv,                      &QMPI_Get
   ,    &QMPI_Get_accumulate,          &QMPI_Get_address,                  &QMPI_Get_count
   ,    &QMPI_Get_elements,            &QMPI_Get_elements_x,               &QMPI_Get_library_version
   ,    &QMPI_Get_processor_name,      &QMPI_Get_version,                  &QMPI_Graph_create
   ,    &QMPI_Graph_get,               &QMPI_Graph_map,                    &QMPI_Graph_neighbors 
   ,    &QMPI_Graph_neighbors_count,   &QMPI_Graphdims_get,                &QMPI_Grequest_complete
   ,    &QMPI_Grequest_start,          &QMPI_Group_compare,                &QMPI_Group_difference
   ,    &QMPI_Group_excl,              &QMPI_Group_free,                   &QMPI_Group_incl
   ,    &QMPI_Group_intersection,      &QMPI_Group_range_excl,             &QMPI_Group_range_incl
   ,    &QMPI_Group_rank,              &QMPI_Group_size,                   &QMPI_Group_translate_ranks
   ,    &QMPI_Group_union,             &QMPI_Iallgather,                   &QMPI_Iallgatherv
   ,    &QMPI_Iallreduce,              &QMPI_Ialltoall,                    &QMPI_Ialltoallv
   ,    &QMPI_Ialltoallw,              &QMPI_Ibarrier,                     &QMPI_Ibcast
   ,    &QMPI_Ibsend,                  &QMPI_Iexscan,                      &QMPI_Igather
   ,    &QMPI_Igatherv,                &QMPI_Improbe, 		           &QMPI_Imrecv
   ,    &QMPI_Ineighbor_allgather,     &QMPI_Ineighbor_allgatherv,         &QMPI_Ineighbor_alltoall
   ,    &QMPI_Ineighbor_alltoallv,     &QMPI_Ineighbor_alltoallw,          &QMPI_Info_create
   ,    &QMPI_Info_delete,             &QMPI_Info_dup,                     &QMPI_Info_free
   ,    &QMPI_Info_get,                &QMPI_Info_get_nkeys,               &QMPI_Info_get_nthkey
   ,    &QMPI_Info_get_valuelen,       &QMPI_Info_set,                     &QMPI_Init
   ,    &QMPI_Init_thread,             &QMPI_Initialized,                  &QMPI_Intercomm_create
   ,    &QMPI_Intercomm_merge,         &QMPI_Iprobe,                       &QMPI_Irecv
   ,    &QMPI_Ireduce,                 &QMPI_Ireduce_scatter,              &QMPI_Ireduce_scatter_block
   ,    &QMPI_Irsend,                  &QMPI_Is_thread_main,               &QMPI_Iscan
   ,    &QMPI_Iscatter,                &QMPI_Iscatterv,                    &QMPI_Isend
   ,    &QMPI_Issend,                  &QMPI_Keyval_create,                &QMPI_Keyval_free
   ,    &QMPI_Lookup_name,             &QMPI_Mprobe,                       &QMPI_Mrecv
   ,    &QMPI_Neighbor_allgather,      &QMPI_Neighbor_allgatherv,          &QMPI_Neighbor_alltoall
   ,    &QMPI_Neighbor_alltoallv,      &QMPI_Neighbor_alltoallw,           &QMPI_Op_commutative
   ,    &QMPI_Op_create,               &QMPI_Op_free,                      &QMPI_Open_port
   ,    &QMPI_Pack,                    &QMPI_Pack_external,                &QMPI_Pack_external_size
   ,    &QMPI_Pack_size,               &QMPI_Pcontrol,                     &QMPI_Probe
   ,    &QMPI_Publish_name,            &QMPI_Put,                          &QMPI_Query_thread
   ,    &QMPI_Raccumulate,             &QMPI_Recv,                         &QMPI_Recv_init
   ,    &QMPI_Reduce,                  &QMPI_Reduce_local,                 &QMPI_Reduce_scatter
   ,    &QMPI_Reduce_scatter_block,    &QMPI_Register_datarep,             &QMPI_Request_free
   ,    &QMPI_Request_get_status,      &QMPI_Rget,                         &QMPI_Rget_accumulate
   ,    &QMPI_Rput,                    &QMPI_Rsend,                        &QMPI_Rsend_init
   ,    &QMPI_Scan,                    &QMPI_Scatter,                      &QMPI_Scatterv
   ,    &QMPI_Send,                    &QMPI_Send_init,                    &QMPI_Sendrecv
   ,    &QMPI_Sendrecv_replace,        &QMPI_Ssend,                        &QMPI_Ssend_init
   ,    &QMPI_Start,                   &QMPI_Startall,                     &QMPI_Status_set_cancelled
   ,    &QMPI_Status_set_elements,     &QMPI_Status_set_elements_x,        &QMPI_Test
   ,    &QMPI_Test_cancelled,          &QMPI_Testall,                      &QMPI_Testany
   ,    &QMPI_Testsome,                &QMPI_Topo_test,                    &QMPI_Type_commit
   ,    &QMPI_Type_contiguous,	       &QMPI_Type_create_darray,           &QMPI_Type_create_f90_complex
   ,    &QMPI_Type_create_f90_integer, &QMPI_Type_create_f90_real,         &QMPI_Type_create_hindexed
   ,    &QMPI_Type_create_hindexed_block,&QMPI_Type_create_hvector,        &QMPI_Type_create_indexed_block
   ,    &QMPI_Type_create_keyval,      &QMPI_Type_create_resized,          &QMPI_Type_create_struct
   ,    &QMPI_Type_create_subarray,    &QMPI_Type_delete_attr,             &QMPI_Type_dup
   ,    &QMPI_Type_extent,             &QMPI_Type_free,                    &QMPI_Type_free_keyval
   ,    &QMPI_Type_get_attr,           &QMPI_Type_get_contents,            &QMPI_Type_get_envelope
   ,    &QMPI_Type_get_extent,         &QMPI_Type_get_extent_x,            &QMPI_Type_get_name
   ,    &QMPI_Type_get_true_extent,    &QMPI_Type_get_true_extent_x/*,       &QMPI_Type_hindexed*/
   /*,    &QMPI_Type_hvector*/,            &QMPI_Type_indexed,                 &QMPI_Type_lb
   ,    &QMPI_Type_match_size,         &QMPI_Type_set_attr,                &QMPI_Type_set_name
   ,    &QMPI_Type_size,               &QMPI_Type_size_x/*,                  &QMPI_Type_struct*/
   ,    &QMPI_Type_ub,                 &QMPI_Type_vector,                  &QMPI_Unpack
   ,    &QMPI_Unpack_external,         &QMPI_Unpublish_name,               &QMPI_Wait
   ,    &QMPI_Waitall,                 &QMPI_Waitany,                      &QMPI_Waitsome
   ,    &QMPI_Win_allocate,            &QMPI_Win_allocate_shared,          &QMPI_Win_attach
   ,    &QMPI_Win_call_errhandler,     &QMPI_Win_complete,                 &QMPI_Win_create
   ,    &QMPI_Win_create_dynamic,      &QMPI_Win_create_errhandler,        &QMPI_Win_create_keyval
   ,    &QMPI_Win_delete_attr,         &QMPI_Win_detach,                   &QMPI_Win_fence   
   ,    &QMPI_Win_flush,               &QMPI_Win_flush_all,                &QMPI_Win_flush_local
   ,    &QMPI_Win_flush_local_all,     &QMPI_Win_free,                     &QMPI_Win_free_keyval
   ,    &QMPI_Win_get_attr,            &QMPI_Win_get_errhandler,           &QMPI_Win_get_group
   ,    &QMPI_Win_get_info,            &QMPI_Win_get_name,                 &QMPI_Win_lock
   ,    &QMPI_Win_lock_all,            &QMPI_Win_post,                     &QMPI_Win_set_attr
   ,    &QMPI_Win_set_errhandler,      &QMPI_Win_set_info,                 &QMPI_Win_set_name
   ,    &QMPI_Win_shared_query,        &QMPI_Win_start,                    &QMPI_Win_sync
   ,    &QMPI_Win_test,                &QMPI_Win_unlock,                   &QMPI_Win_unlock_all
   ,    &QMPI_Win_wait,                &QMPI_Wtick,                        &QMPI_Wtime

   };




void* PMPI_Array[]={  
  
        &PMPI_Abort,                   &PMPI_Accumulate,                   &PMPI_Add_error_class
   ,    &PMPI_Add_error_code,          &PMPI_Add_error_string/*,             &PMPI_Address*/
   ,    &PMPI_Allgather,               &PMPI_Allgatherv,                   &PMPI_Alloc_mem
   ,    &PMPI_Allreduce,               &PMPI_Alltoall   ,                  &PMPI_Alltoallv
   ,    &PMPI_Alltoallw,               &PMPI_Attr_delete,                  &PMPI_Attr_get
   ,    &PMPI_Attr_put,                &PMPI_Barrier,                      &PMPI_Bcast
   ,    &PMPI_Bsend,                   &PMPI_Bsend_init,                   &PMPI_Buffer_attach
   ,    &PMPI_Buffer_detach,           &PMPI_Cancel,                       &PMPI_Cart_coords
   ,    &PMPI_Cart_create,             &PMPI_Cart_get,                     &PMPI_Cart_map
   ,    &PMPI_Cart_rank,               &PMPI_Cart_shift,                   &PMPI_Cart_sub
   ,    &PMPI_Cartdim_get,             &PMPI_Close_port,                   &PMPI_Comm_accept
   ,    &PMPI_Comm_call_errhandler,    &PMPI_Comm_compare,                 &PMPI_Comm_connect   
   ,    &PMPI_Comm_create,             &PMPI_Comm_create_errhandler,       &PMPI_Comm_create_group
   ,    &PMPI_Comm_create_keyval,      &PMPI_Comm_delete_attr,             &PMPI_Comm_disconnect
   ,    &PMPI_Comm_dup,                &PMPI_Comm_dup_with_info,           &PMPI_Comm_free
   ,    &PMPI_Comm_free_keyval,        &PMPI_Comm_get_attr,                &PMPI_Comm_get_errhandler
   ,    &PMPI_Comm_get_info,           &PMPI_Comm_get_name,                &PMPI_Comm_get_parent
   ,    &PMPI_Comm_group,              &PMPI_Comm_idup,                    &PMPI_Comm_join
   ,    &PMPI_Comm_rank,               &PMPI_Comm_remote_group,            &PMPI_Comm_remote_size
   ,    &PMPI_Comm_set_attr,           &PMPI_Comm_set_errhandler,          &PMPI_Comm_set_info
   ,    &PMPI_Comm_set_name,           &PMPI_Comm_size,                    &PMPI_Comm_split
   ,    &PMPI_Comm_split_type,         &PMPI_Comm_test_inter,              &PMPI_Compare_and_swap
   ,    &PMPI_Dims_create,             &PMPI_Dist_graph_create,            &PMPI_Dist_graph_create_adjacent
   ,    &PMPI_Dist_graph_neighbors,    &PMPI_Dist_graph_neighbors_count/*,   &PMPI_Errhandler_create*/
   ,    &PMPI_Errhandler_free/*,       &PMPI_Errhandler_get*//*,               &PMPI_Errhandler_set*/
   ,    &PMPI_Error_class,             &PMPI_Error_string,                 &PMPI_Exscan
   ,    &PMPI_Fetch_and_op,            &PMPI_File_call_errhandler,         &PMPI_File_close
   ,    &PMPI_File_create_errhandler,  &PMPI_File_delete,                  &PMPI_File_get_amode
   ,    &PMPI_File_get_atomicity,      &PMPI_File_get_byte_offset,         &PMPI_File_get_errhandler
   ,    &PMPI_File_get_group,          &PMPI_File_get_info,                &PMPI_File_get_position
   ,    &PMPI_File_get_position_shared,&PMPI_File_get_size,                &PMPI_File_get_type_extent
   ,    &PMPI_File_get_view,           &PMPI_File_iread,                   &PMPI_File_iread_all
   ,    &PMPI_File_iread_at,           &PMPI_File_iread_at_all,            &PMPI_File_iread_shared
   ,    &PMPI_File_iwrite,             &PMPI_File_iwrite_all,              &PMPI_File_iwrite_at
   ,    &PMPI_File_iwrite_at_all,      &PMPI_File_iwrite_shared,           &PMPI_File_open
   ,    &PMPI_File_preallocate,        &PMPI_File_read,                    &PMPI_File_read_all
   ,    &PMPI_File_read_all_begin,     &PMPI_File_read_all_end,            &PMPI_File_read_at
   ,    &PMPI_File_read_at_all,        &PMPI_File_read_at_all_begin,       &PMPI_File_read_at_all_end
   ,    &PMPI_File_read_ordered,       &PMPI_File_read_ordered_begin,      &PMPI_File_read_ordered_end
   ,    &PMPI_File_read_shared,        &PMPI_File_seek,                    &PMPI_File_seek_shared
   ,    &PMPI_File_set_atomicity,      &PMPI_File_set_errhandler,          &PMPI_File_set_info
   ,    &PMPI_File_set_size,           &PMPI_File_set_view,                &PMPI_File_sync
   ,    &PMPI_File_write,              &PMPI_File_write_all,               &PMPI_File_write_all_begin
   ,    &PMPI_File_write_all_end,      &PMPI_File_write_at,                &PMPI_File_write_at_all
   ,    &PMPI_File_write_at_all_begin, &PMPI_File_write_at_all_end,        &PMPI_File_write_ordered
   ,    &PMPI_File_write_ordered_begin,&PMPI_File_write_ordered_end,       &PMPI_File_write_shared
   ,    &PMPI_Finalize,                &PMPI_Finalized,                    &PMPI_Free_mem
   ,    &PMPI_Gather,                  &PMPI_Gatherv,                      &PMPI_Get
   ,    &PMPI_Get_accumulate,          &PMPI_Get_address,                  &PMPI_Get_count
   ,    &PMPI_Get_elements,            &PMPI_Get_elements_x,               &PMPI_Get_library_version
   ,    &PMPI_Get_processor_name,      &PMPI_Get_version,                  &PMPI_Graph_create
   ,    &PMPI_Graph_get,               &PMPI_Graph_map,                    &PMPI_Graph_neighbors 
   ,    &PMPI_Graph_neighbors_count,   &PMPI_Graphdims_get,                &PMPI_Grequest_complete
   ,    &PMPI_Grequest_start,          &PMPI_Group_compare,                &PMPI_Group_difference
   ,    &PMPI_Group_excl,              &PMPI_Group_free,                   &PMPI_Group_incl
   ,    &PMPI_Group_intersection,      &PMPI_Group_range_excl,             &PMPI_Group_range_incl
   ,    &PMPI_Group_rank,              &PMPI_Group_size,                   &PMPI_Group_translate_ranks
   ,    &PMPI_Group_union,             &PMPI_Iallgather,                   &PMPI_Iallgatherv
   ,    &PMPI_Iallreduce,              &PMPI_Ialltoall,                    &PMPI_Ialltoallv
   ,    &PMPI_Ialltoallw,              &PMPI_Ibarrier,                     &PMPI_Ibcast
   ,    &PMPI_Ibsend,                  &PMPI_Iexscan,                      &PMPI_Igather
   ,    &PMPI_Igatherv,                &PMPI_Improbe,                      &PMPI_Imrecv
   ,    &PMPI_Ineighbor_allgather,     &PMPI_Ineighbor_allgatherv,         &PMPI_Ineighbor_alltoall
   ,    &PMPI_Ineighbor_alltoallv,     &PMPI_Ineighbor_alltoallw,          &PMPI_Info_create
   ,    &PMPI_Info_delete,             &PMPI_Info_dup,                     &PMPI_Info_free
   ,    &PMPI_Info_get,                &PMPI_Info_get_nkeys,               &PMPI_Info_get_nthkey
   ,    &PMPI_Info_get_valuelen,       &PMPI_Info_set,                     &PMPI_Init
   ,    &PMPI_Init_thread,             &PMPI_Initialized,                  &PMPI_Intercomm_create
   ,    &PMPI_Intercomm_merge,         &PMPI_Iprobe,                       &PMPI_Irecv
   ,    &PMPI_Ireduce,                 &PMPI_Ireduce_scatter,              &PMPI_Ireduce_scatter_block
   ,    &PMPI_Irsend,                  &PMPI_Is_thread_main,               &PMPI_Iscan
   ,    &PMPI_Iscatter,                &PMPI_Iscatterv,                    &PMPI_Isend
   ,    &PMPI_Issend,                  &PMPI_Keyval_create,                &PMPI_Keyval_free
   ,    &PMPI_Lookup_name,             &PMPI_Mprobe,                       &PMPI_Mrecv
   ,    &PMPI_Neighbor_allgather,      &PMPI_Neighbor_allgatherv,          &PMPI_Neighbor_alltoall
   ,    &PMPI_Neighbor_alltoallv,      &PMPI_Neighbor_alltoallw,           &PMPI_Op_commutative
   ,    &PMPI_Op_create,               &PMPI_Op_free,                      &PMPI_Open_port
   ,    &PMPI_Pack,                    &PMPI_Pack_external,                &PMPI_Pack_external_size
   ,    &PMPI_Pack_size,               &PMPI_Pcontrol,                     &PMPI_Probe
   ,    &PMPI_Publish_name,            &PMPI_Put,                          &PMPI_Query_thread
   ,    &PMPI_Raccumulate,             &PMPI_Recv,                         &PMPI_Recv_init
   ,    &PMPI_Reduce,                  &PMPI_Reduce_local,                 &PMPI_Reduce_scatter
   ,    &PMPI_Reduce_scatter_block,    &PMPI_Register_datarep,             &PMPI_Request_free
   ,    &PMPI_Request_get_status,      &PMPI_Rget,                         &PMPI_Rget_accumulate
   ,    &PMPI_Rput,                    &PMPI_Rsend,                        &PMPI_Rsend_init
   ,    &PMPI_Scan,                    &PMPI_Scatter,                      &PMPI_Scatterv
   ,    &PMPI_Send,                    &PMPI_Send_init,                    &PMPI_Sendrecv
   ,    &PMPI_Sendrecv_replace,        &PMPI_Ssend,                        &PMPI_Ssend_init
   ,    &PMPI_Start,                   &PMPI_Startall,                     &PMPI_Status_set_cancelled
   ,    &PMPI_Status_set_elements,     &PMPI_Status_set_elements_x,        &PMPI_Test
   ,    &PMPI_Test_cancelled,          &PMPI_Testall,                      &PMPI_Testany
   ,    &PMPI_Testsome,                &PMPI_Topo_test,                    &PMPI_Type_commit
   ,    &PMPI_Type_contiguous,         &PMPI_Type_create_darray,           &PMPI_Type_create_f90_complex
   ,    &PMPI_Type_create_f90_integer, &PMPI_Type_create_f90_real,         &PMPI_Type_create_hindexed
   ,    &PMPI_Type_create_hindexed_block,&PMPI_Type_create_hvector,        &PMPI_Type_create_indexed_block
   ,    &PMPI_Type_create_keyval,      &PMPI_Type_create_resized,          &PMPI_Type_create_struct
   ,    &PMPI_Type_create_subarray,    &PMPI_Type_delete_attr,             &PMPI_Type_dup
   ,    &PMPI_Type_extent,             &PMPI_Type_free,                    &PMPI_Type_free_keyval
   ,    &PMPI_Type_get_attr,           &PMPI_Type_get_contents,            &PMPI_Type_get_envelope
   ,    &PMPI_Type_get_extent,         &PMPI_Type_get_extent_x,            &PMPI_Type_get_name
   ,    &PMPI_Type_get_true_extent,    &PMPI_Type_get_true_extent_x/*,       &PMPI_Type_hindexed*/
   /*,    &PMPI_Type_hvector*/,            &PMPI_Type_indexed,                 &PMPI_Type_lb
   ,    &PMPI_Type_match_size,         &PMPI_Type_set_attr,                &PMPI_Type_set_name
   ,    &PMPI_Type_size,               &PMPI_Type_size_x/*,                  &PMPI_Type_struct */
   ,    &PMPI_Type_ub,                 &PMPI_Type_vector,                  &PMPI_Unpack
   ,    &PMPI_Unpack_external,         &PMPI_Unpublish_name,               &PMPI_Wait
   ,    &PMPI_Waitall,                 &PMPI_Waitany,                      &PMPI_Waitsome
   ,    &PMPI_Win_allocate,            &PMPI_Win_allocate_shared,          &PMPI_Win_attach
   ,    &PMPI_Win_call_errhandler,     &PMPI_Win_complete,                 &PMPI_Win_create
   ,    &PMPI_Win_create_dynamic,      &PMPI_Win_create_errhandler,        &PMPI_Win_create_keyval
   ,    &PMPI_Win_delete_attr,         &PMPI_Win_detach,                   &PMPI_Win_fence   
   ,    &PMPI_Win_flush,               &PMPI_Win_flush_all,                &PMPI_Win_flush_local
   ,    &PMPI_Win_flush_local_all,     &PMPI_Win_free,                     &PMPI_Win_free_keyval
   ,    &PMPI_Win_get_attr,            &PMPI_Win_get_errhandler,           &PMPI_Win_get_group
   ,    &PMPI_Win_get_info,            &PMPI_Win_get_name,                 &PMPI_Win_lock
   ,    &PMPI_Win_lock_all,            &PMPI_Win_post,                     &PMPI_Win_set_attr
   ,    &PMPI_Win_set_errhandler,      &PMPI_Win_set_info,                 &PMPI_Win_set_name
   ,    &PMPI_Win_shared_query,        &PMPI_Win_start,                    &PMPI_Win_sync
   ,    &PMPI_Win_test,                &PMPI_Win_unlock,                   &PMPI_Win_unlock_all
   ,    &PMPI_Win_wait,                &PMPI_Wtick,                        &PMPI_Wtime

   };
