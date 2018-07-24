/* /u/home/bengisu/THESIS/toolchain_test/lib/mpiP-master/wrappers.c */
/* DO NOT EDIT -- AUTOMATICALLY GENERATED! */
/* Timestamp: 20 July 2018 21:46  */
/* Location: i10se5 posix */
/* Creator: bengisu  */


#include "mpiPi.h"
#include "symbols.h"
#include "mpiPi_def.h"
#include "../../src/obj/qmpi.h"
#include "array.h"


extern  char* get_interceptions(int i )
{
        return interceptions[i];
}
/* --------------- MPI_Accumulate --------------- */

static int mpiPif_MPI_Accumulate( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Op  * op, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Accumulate( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * op,  * win);
void* f=NULL;
QMPI_Table_query( 1, &f, (*vector_get(v,i)).table);
exec_func(f,i,1,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*target_datatype, &tsize);
rmaSize = (double)(tsize * *target_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Accumulate");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Accumulate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Accumulate */



extern int TMPI_Accumulate ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Accumulate( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & op,  & win ,i,v);

return rc;
} /* MPI_Accumulate */


extern void F77_MPI_ACCUMULATE(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Fint  * op, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;
MPI_Op c_op;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_op = MPI_Op_f2c(*op);

rc = mpiPif_MPI_Accumulate( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, &c_op, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_accumulate */



/* --------------- MPI_Allgather --------------- */

static int mpiPif_MPI_Allgather( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Allgather( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * comm);
void* f=NULL;
QMPI_Table_query( 6, &f, (*vector_get(v,i)).table);
exec_func(f,i,6,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Allgather");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Allgather, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Allgather, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Allgather */



extern int TMPI_Allgather ( mpip_const_void_t *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Allgather( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & comm ,i,v);

return rc;
} /* MPI_Allgather */


extern void F77_MPI_ALLGATHER(mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Allgather( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_allgather */



/* --------------- MPI_Allgatherv --------------- */

static int mpiPif_MPI_Allgatherv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcounts, mpip_const_int_t  *displs, MPI_Datatype  * recvtype, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Allgatherv( sendbuf,  * sendcount,  * sendtype, recvbuf, recvcounts, displs,  * recvtype,  * comm);
void* f=NULL;
QMPI_Table_query( 7, &f, (*vector_get(v,i)).table);
exec_func(f,i,7,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Allgatherv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Allgatherv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Allgatherv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Allgatherv */



extern int TMPI_Allgatherv ( mpip_const_void_t *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, mpip_const_int_t *recvcounts, mpip_const_int_t *displs, MPI_Datatype recvtype, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Allgatherv( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf, recvcounts, displs,  & recvtype,  & comm ,i,v);

return rc;
} /* MPI_Allgatherv */


extern void F77_MPI_ALLGATHERV(mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcounts, mpip_const_int_t  *displs, MPI_Fint  * recvtype, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Allgatherv( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcounts, displs, &c_recvtype, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_allgatherv */



/* --------------- MPI_Allreduce --------------- */

static int mpiPif_MPI_Allreduce( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Allreduce( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm);
void* f=NULL;
QMPI_Table_query( 9, &f, (*vector_get(v,i)).table);
exec_func(f,i,9,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Allreduce");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Allreduce, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Allreduce, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Allreduce */



extern int TMPI_Allreduce ( mpip_const_void_t *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Allreduce( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm ,i,v);

return rc;
} /* MPI_Allreduce */


extern void F77_MPI_ALLREDUCE(mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Allreduce( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_allreduce */



/* --------------- MPI_Alltoall --------------- */

static int mpiPif_MPI_Alltoall( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Datatype  * recvtype, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Alltoall( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcnt,  * recvtype,  * comm);
void* f=NULL;
QMPI_Table_query( 10, &f, (*vector_get(v,i)).table);
exec_func(f,i,10,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Alltoall");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Alltoall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Alltoall, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Alltoall */



extern int TMPI_Alltoall ( mpip_const_void_t *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcnt, MPI_Datatype recvtype, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Alltoall( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcnt,  & recvtype,  & comm ,i,v);

return rc;
} /* MPI_Alltoall */


extern void F77_MPI_ALLTOALL(mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Fint  * recvtype, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Alltoall( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcnt, &c_recvtype, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_alltoall */



/* --------------- MPI_Alltoallv --------------- */

static int mpiPif_MPI_Alltoallv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, mpip_const_int_t  *sendcnts, mpip_const_int_t  *sdispls, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcnts, mpip_const_int_t  *rdispls, MPI_Datatype  * recvtype, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Alltoallv( sendbuf, sendcnts, sdispls,  * sendtype, recvbuf, recvcnts, rdispls,  * recvtype,  * comm);
void* f=NULL;
QMPI_Table_query( 11, &f, (*vector_get(v,i)).table);
exec_func(f,i,11,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Alltoallv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Alltoallv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Alltoallv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Alltoallv */



extern int TMPI_Alltoallv ( mpip_const_void_t *sendbuf, mpip_const_int_t *sendcnts, mpip_const_int_t *sdispls, MPI_Datatype sendtype, void *recvbuf, mpip_const_int_t *recvcnts, mpip_const_int_t *rdispls, MPI_Datatype recvtype, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Alltoallv( &jbuf, sendbuf, sendcnts, sdispls,  & sendtype, recvbuf, recvcnts, rdispls,  & recvtype,  & comm ,i,v);

return rc;
} /* MPI_Alltoallv */


extern void F77_MPI_ALLTOALLV(mpip_const_void_t  *sendbuf, mpip_const_int_t  *sendcnts, mpip_const_int_t  *sdispls, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcnts, mpip_const_int_t  *rdispls, MPI_Fint  * recvtype, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Alltoallv( &jbuf, sendbuf, sendcnts, sdispls, &c_sendtype, recvbuf, recvcnts, rdispls, &c_recvtype, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_alltoallv */



/* --------------- MPI_Attr_delete --------------- */

static int mpiPif_MPI_Attr_delete( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * keyval,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Attr_delete(  * comm,  * keyval);
void* f=NULL;
QMPI_Table_query( 13, &f, (*vector_get(v,i)).table);
exec_func(f,i,13,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Attr_delete");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Attr_delete, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Attr_delete */



extern int TMPI_Attr_delete ( MPI_Comm comm, int keyval ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Attr_delete( &jbuf,  & comm,  & keyval ,i,v);

return rc;
} /* MPI_Attr_delete */


extern void F77_MPI_ATTR_DELETE(MPI_Fint  * comm, int  * keyval , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Attr_delete( &jbuf, &c_comm, keyval ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_attr_delete */



/* --------------- MPI_Attr_get --------------- */

static int mpiPif_MPI_Attr_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * keyval, void  *attr_value, int  *flag,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Attr_get(  * comm,  * keyval, attr_value, flag);
void* f=NULL;
QMPI_Table_query( 14, &f, (*vector_get(v,i)).table);
exec_func(f,i,14,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Attr_get");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Attr_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Attr_get */



extern int TMPI_Attr_get ( MPI_Comm comm, int keyval, void *attr_value, int *flag ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Attr_get( &jbuf,  & comm,  & keyval, attr_value, flag ,i,v);

return rc;
} /* MPI_Attr_get */


extern void F77_MPI_ATTR_GET(MPI_Fint  * comm, int  * keyval, void  *attr_value, int  *flag , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Attr_get( &jbuf, &c_comm, keyval, attr_value, flag ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_attr_get */



/* --------------- MPI_Attr_put --------------- */

static int mpiPif_MPI_Attr_put( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * keyval, void  *attr_value,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Attr_put(  * comm,  * keyval, attr_value);
void* f=NULL;
QMPI_Table_query( 15, &f, (*vector_get(v,i)).table);
exec_func(f,i,15,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Attr_put");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Attr_put, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Attr_put */



extern int TMPI_Attr_put ( MPI_Comm comm, int keyval, void *attr_value ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Attr_put( &jbuf,  & comm,  & keyval, attr_value ,i,v);

return rc;
} /* MPI_Attr_put */


extern void F77_MPI_ATTR_PUT(MPI_Fint  * comm, int  * keyval, void  *attr_value , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Attr_put( &jbuf, &c_comm, keyval, attr_value ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_attr_put */



/* --------------- MPI_Barrier --------------- */

static int mpiPif_MPI_Barrier( jmp_buf * base_jbuf, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Barrier(  * comm);
void* f=NULL;
QMPI_Table_query( 16, &f, (*vector_get(v,i)).table);
exec_func(f,i,16,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Barrier");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Barrier, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Barrier, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Barrier */



extern int TMPI_Barrier ( MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Barrier( &jbuf,  & comm ,i,v);

return rc;
} /* MPI_Barrier */


extern void F77_MPI_BARRIER(MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Barrier( &jbuf, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_barrier */



/* --------------- MPI_Bcast --------------- */

static int mpiPif_MPI_Bcast( jmp_buf * base_jbuf, void  *buffer, int  * count, MPI_Datatype  * datatype, int  * root, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Bcast( buffer,  * count,  * datatype,  * root,  * comm);
void* f=NULL;
QMPI_Table_query( 17, &f, (*vector_get(v,i)).table);
exec_func(f,i,17,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Bcast");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Bcast, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Bcast, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Bcast */



extern int TMPI_Bcast ( void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Bcast( &jbuf, buffer,  & count,  & datatype,  & root,  & comm ,i,v);

return rc;
} /* MPI_Bcast */


extern void F77_MPI_BCAST(void  *buffer, int  * count, MPI_Fint  * datatype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Bcast( &jbuf, buffer, count, &c_datatype, root, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_bcast */



/* --------------- MPI_Bsend --------------- */

static int mpiPif_MPI_Bsend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Bsend( buf,  * count,  * datatype,  * dest,  * tag,  * comm);
void* f=NULL;
QMPI_Table_query( 18, &f, (*vector_get(v,i)).table);
exec_func(f,i,18,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Bsend");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Bsend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Bsend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Bsend */



extern int TMPI_Bsend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Bsend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm ,i,v);

return rc;
} /* MPI_Bsend */


extern void F77_MPI_BSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Bsend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_bsend */



/* --------------- MPI_Bsend_init --------------- */

static int mpiPif_MPI_Bsend_init( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Bsend_init( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 19, &f, (*vector_get(v,i)).table);
exec_func(f,i,19,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Bsend_init");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Bsend_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Bsend_init */



extern int TMPI_Bsend_init ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Bsend_init( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Bsend_init */


extern void F77_MPI_BSEND_INIT(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Bsend_init( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_bsend_init */



/* --------------- MPI_Buffer_attach --------------- */

static int mpiPif_MPI_Buffer_attach( jmp_buf * base_jbuf, void  *buffer, int  * size,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Buffer_attach( buffer,  * size);
void* f=NULL;
QMPI_Table_query( 20, &f, (*vector_get(v,i)).table);
exec_func(f,i,20,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Buffer_attach");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Buffer_attach, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Buffer_attach */



extern int TMPI_Buffer_attach ( void *buffer, int size ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Buffer_attach( &jbuf, buffer,  & size ,i,v);

return rc;
} /* MPI_Buffer_attach */


extern void F77_MPI_BUFFER_ATTACH(void  *buffer, int  * size , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Buffer_attach( &jbuf, buffer, size ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_buffer_attach */



/* --------------- MPI_Buffer_detach --------------- */

static int mpiPif_MPI_Buffer_detach( jmp_buf * base_jbuf, void  *bufferptr, int  *size,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Buffer_detach( bufferptr, size);
void* f=NULL;
QMPI_Table_query( 21, &f, (*vector_get(v,i)).table);
exec_func(f,i,21,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Buffer_detach");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Buffer_detach, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Buffer_detach */



extern int TMPI_Buffer_detach ( void *bufferptr, int *size ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Buffer_detach( &jbuf, bufferptr, size ,i,v);

return rc;
} /* MPI_Buffer_detach */


extern void F77_MPI_BUFFER_DETACH(void  *bufferptr, int  *size , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Buffer_detach( &jbuf, bufferptr, size ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_buffer_detach */



/* --------------- MPI_Cancel --------------- */

static int mpiPif_MPI_Cancel( jmp_buf * base_jbuf, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cancel( request);
void* f=NULL;
QMPI_Table_query( 22, &f, (*vector_get(v,i)).table);
exec_func(f,i,22,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cancel");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cancel, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cancel */



extern int TMPI_Cancel ( MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cancel( &jbuf, request ,i,v);

return rc;
} /* MPI_Cancel */


extern void F77_MPI_CANCEL(MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Cancel( &jbuf, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cancel */



/* --------------- MPI_Cart_coords --------------- */

static int mpiPif_MPI_Cart_coords( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * rank, int  * maxdims, int  *coords,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cart_coords(  * comm,  * rank,  * maxdims, coords);
void* f=NULL;
QMPI_Table_query( 23, &f, (*vector_get(v,i)).table);
exec_func(f,i,23,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_coords");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cart_coords, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_coords */



extern int TMPI_Cart_coords ( MPI_Comm comm, int rank, int maxdims, int *coords ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_coords( &jbuf,  & comm,  & rank,  & maxdims, coords ,i,v);

return rc;
} /* MPI_Cart_coords */


extern void F77_MPI_CART_COORDS(MPI_Fint  * comm, int  * rank, int  * maxdims, int  *coords , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_coords( &jbuf, &c_comm, rank, maxdims, coords ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_coords */



/* --------------- MPI_Cart_create --------------- */

static int mpiPif_MPI_Cart_create( jmp_buf * base_jbuf, MPI_Comm  * comm_old, int  * ndims, mpip_const_int_t  *dims, mpip_const_int_t  *periods, int  * reorder, MPI_Comm  *comm_cart,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cart_create(  * comm_old,  * ndims, dims, periods,  * reorder, comm_cart);
void* f=NULL;
QMPI_Table_query( 24, &f, (*vector_get(v,i)).table);
exec_func(f,i,24,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_create");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cart_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_create */



extern int TMPI_Cart_create ( MPI_Comm comm_old, int ndims, mpip_const_int_t *dims, mpip_const_int_t *periods, int reorder, MPI_Comm *comm_cart ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_create( &jbuf,  & comm_old,  & ndims, dims, periods,  & reorder, comm_cart ,i,v);

return rc;
} /* MPI_Cart_create */


extern void F77_MPI_CART_CREATE(MPI_Fint  * comm_old, int  * ndims, mpip_const_int_t  *dims, mpip_const_int_t  *periods, int  * reorder, MPI_Fint  *comm_cart , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm_old;
MPI_Comm c_comm_cart;

c_comm_old = MPI_Comm_f2c(*comm_old);

rc = mpiPif_MPI_Cart_create( &jbuf, &c_comm_old, ndims, dims, periods, reorder, &c_comm_cart ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_cart = MPI_Comm_c2f(c_comm_cart);
}
return;
} /* mpi_cart_create */



/* --------------- MPI_Cart_get --------------- */

static int mpiPif_MPI_Cart_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * maxdims, int  *dims, int  *periods, int  *coords,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cart_get(  * comm,  * maxdims, dims, periods, coords);
void* f=NULL;
QMPI_Table_query( 25, &f, (*vector_get(v,i)).table);
exec_func(f,i,25,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_get");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cart_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_get */



extern int TMPI_Cart_get ( MPI_Comm comm, int maxdims, int *dims, int *periods, int *coords ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_get( &jbuf,  & comm,  & maxdims, dims, periods, coords ,i,v);

return rc;
} /* MPI_Cart_get */


extern void F77_MPI_CART_GET(MPI_Fint  * comm, int  * maxdims, int  *dims, int  *periods, int  *coords , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_get( &jbuf, &c_comm, maxdims, dims, periods, coords ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_get */



/* --------------- MPI_Cart_map --------------- */

static int mpiPif_MPI_Cart_map( jmp_buf * base_jbuf, MPI_Comm  * comm_old, int  * ndims, mpip_const_int_t  *dims, mpip_const_int_t  *periods, int  *newrank,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cart_map(  * comm_old,  * ndims, dims, periods, newrank);
void* f=NULL;
QMPI_Table_query( 26, &f, (*vector_get(v,i)).table);
exec_func(f,i,26,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_map");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cart_map, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_map */



extern int TMPI_Cart_map ( MPI_Comm comm_old, int ndims, mpip_const_int_t *dims, mpip_const_int_t *periods, int *newrank ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_map( &jbuf,  & comm_old,  & ndims, dims, periods, newrank ,i,v);

return rc;
} /* MPI_Cart_map */


extern void F77_MPI_CART_MAP(MPI_Fint  * comm_old, int  * ndims, mpip_const_int_t  *dims, mpip_const_int_t  *periods, int  *newrank , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm_old;

c_comm_old = MPI_Comm_f2c(*comm_old);

rc = mpiPif_MPI_Cart_map( &jbuf, &c_comm_old, ndims, dims, periods, newrank ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_map */



/* --------------- MPI_Cart_rank --------------- */

static int mpiPif_MPI_Cart_rank( jmp_buf * base_jbuf, MPI_Comm  * comm, mpip_const_int_t  *coords, int  *rank,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cart_rank(  * comm, coords, rank);
void* f=NULL;
QMPI_Table_query( 27, &f, (*vector_get(v,i)).table);
exec_func(f,i,27,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_rank");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cart_rank, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_rank */



extern int TMPI_Cart_rank ( MPI_Comm comm, mpip_const_int_t *coords, int *rank ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_rank( &jbuf,  & comm, coords, rank ,i,v);

return rc;
} /* MPI_Cart_rank */


extern void F77_MPI_CART_RANK(MPI_Fint  * comm, mpip_const_int_t  *coords, int  *rank , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_rank( &jbuf, &c_comm, coords, rank ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_rank */



/* --------------- MPI_Cart_shift --------------- */

static int mpiPif_MPI_Cart_shift( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * direction, int  * displ, int  *source, int  *dest,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cart_shift(  * comm,  * direction,  * displ, source, dest);
void* f=NULL;
QMPI_Table_query( 28, &f, (*vector_get(v,i)).table);
exec_func(f,i,28,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_shift");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cart_shift, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_shift */



extern int TMPI_Cart_shift ( MPI_Comm comm, int direction, int displ, int *source, int *dest ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_shift( &jbuf,  & comm,  & direction,  & displ, source, dest ,i,v);

return rc;
} /* MPI_Cart_shift */


extern void F77_MPI_CART_SHIFT(MPI_Fint  * comm, int  * direction, int  * displ, int  *source, int  *dest , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_shift( &jbuf, &c_comm, direction, displ, source, dest ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cart_shift */



/* --------------- MPI_Cart_sub --------------- */

static int mpiPif_MPI_Cart_sub( jmp_buf * base_jbuf, MPI_Comm  * comm, mpip_const_int_t  *remain_dims, MPI_Comm  *comm_new,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cart_sub(  * comm, remain_dims, comm_new);
void* f=NULL;
QMPI_Table_query( 29, &f, (*vector_get(v,i)).table);
exec_func(f,i,29,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cart_sub");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cart_sub, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cart_sub */



extern int TMPI_Cart_sub ( MPI_Comm comm, mpip_const_int_t *remain_dims, MPI_Comm *comm_new ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cart_sub( &jbuf,  & comm, remain_dims, comm_new ,i,v);

return rc;
} /* MPI_Cart_sub */


extern void F77_MPI_CART_SUB(MPI_Fint  * comm, mpip_const_int_t  *remain_dims, MPI_Fint  *comm_new , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Comm c_comm_new;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cart_sub( &jbuf, &c_comm, remain_dims, &c_comm_new ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_new = MPI_Comm_c2f(c_comm_new);
}
return;
} /* mpi_cart_sub */



/* --------------- MPI_Cartdim_get --------------- */

static int mpiPif_MPI_Cartdim_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *ndims,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Cartdim_get(  * comm, ndims);
void* f=NULL;
QMPI_Table_query( 30, &f, (*vector_get(v,i)).table);
exec_func(f,i,30,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Cartdim_get");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Cartdim_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Cartdim_get */



extern int TMPI_Cartdim_get ( MPI_Comm comm, int *ndims ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Cartdim_get( &jbuf,  & comm, ndims ,i,v);

return rc;
} /* MPI_Cartdim_get */


extern void F77_MPI_CARTDIM_GET(MPI_Fint  * comm, int  *ndims , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Cartdim_get( &jbuf, &c_comm, ndims ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_cartdim_get */



/* --------------- MPI_Comm_create --------------- */

static int mpiPif_MPI_Comm_create( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Group  * group, MPI_Comm  *comm_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Comm_create(  * comm,  * group, comm_out);
void* f=NULL;
QMPI_Table_query( 36, &f, (*vector_get(v,i)).table);
exec_func(f,i,36,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_create");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Comm_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_create */



extern int TMPI_Comm_create ( MPI_Comm comm, MPI_Group group, MPI_Comm *comm_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_create( &jbuf,  & comm,  & group, comm_out ,i,v);

return rc;
} /* MPI_Comm_create */


extern void F77_MPI_COMM_CREATE(MPI_Fint  * comm, MPI_Fint  * group, MPI_Fint  *comm_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Group c_group;
MPI_Comm c_comm_out;

c_comm = MPI_Comm_f2c(*comm);
c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Comm_create( &jbuf, &c_comm, &c_group, &c_comm_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_comm_create */



/* --------------- MPI_Comm_dup --------------- */

static int mpiPif_MPI_Comm_dup( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Comm  *comm_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Comm_dup(  * comm, comm_out);
void* f=NULL;
QMPI_Table_query( 42, &f, (*vector_get(v,i)).table);
exec_func(f,i,42,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_dup");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Comm_dup, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_dup */



extern int TMPI_Comm_dup ( MPI_Comm comm, MPI_Comm *comm_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_dup( &jbuf,  & comm, comm_out ,i,v);

return rc;
} /* MPI_Comm_dup */


extern void F77_MPI_COMM_DUP(MPI_Fint  * comm, MPI_Fint  *comm_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Comm c_comm_out;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_dup( &jbuf, &c_comm, &c_comm_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_comm_dup */



/* --------------- MPI_Comm_free --------------- */

static int mpiPif_MPI_Comm_free( jmp_buf * base_jbuf, MPI_Comm  *commp,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Comm_free( commp);
void* f=NULL;
QMPI_Table_query( 44, &f, (*vector_get(v,i)).table);
exec_func(f,i,44,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_free");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Comm_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_free */



extern int TMPI_Comm_free ( MPI_Comm *commp ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_free( &jbuf, commp ,i,v);

return rc;
} /* MPI_Comm_free */


extern void F77_MPI_COMM_FREE(MPI_Fint  *commp , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_commp;

c_commp = MPI_Comm_f2c(*commp);

rc = mpiPif_MPI_Comm_free( &jbuf, &c_commp ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*commp = MPI_Comm_c2f(c_commp);
}
return;
} /* mpi_comm_free */



/* --------------- MPI_Comm_group --------------- */

static int mpiPif_MPI_Comm_group( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Group  *group,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Comm_group(  * comm, group);
void* f=NULL;
QMPI_Table_query( 51, &f, (*vector_get(v,i)).table);
exec_func(f,i,51,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_group");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Comm_group, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_group */



extern int TMPI_Comm_group ( MPI_Comm comm, MPI_Group *group ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_group( &jbuf,  & comm, group ,i,v);

return rc;
} /* MPI_Comm_group */


extern void F77_MPI_COMM_GROUP(MPI_Fint  * comm, MPI_Fint  *group , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Group c_group;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_group( &jbuf, &c_comm, &c_group ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group = MPI_Group_c2f(c_group);
}
return;
} /* mpi_comm_group */



/* --------------- MPI_Comm_remote_group --------------- */

static int mpiPif_MPI_Comm_remote_group( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Group  *group,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Comm_remote_group(  * comm, group);
void* f=NULL;
QMPI_Table_query( 55, &f, (*vector_get(v,i)).table);
exec_func(f,i,55,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_remote_group");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Comm_remote_group, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_remote_group */



extern int TMPI_Comm_remote_group ( MPI_Comm comm, MPI_Group *group ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_remote_group( &jbuf,  & comm, group ,i,v);

return rc;
} /* MPI_Comm_remote_group */


extern void F77_MPI_COMM_REMOTE_GROUP(MPI_Fint  * comm, MPI_Fint  *group , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Group c_group;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_remote_group( &jbuf, &c_comm, &c_group ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group = MPI_Group_c2f(c_group);
}
return;
} /* mpi_comm_remote_group */



/* --------------- MPI_Comm_remote_size --------------- */

static int mpiPif_MPI_Comm_remote_size( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *size,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Comm_remote_size(  * comm, size);
void* f=NULL;
QMPI_Table_query( 56, &f, (*vector_get(v,i)).table);
exec_func(f,i,56,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_remote_size");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Comm_remote_size, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_remote_size */



extern int TMPI_Comm_remote_size ( MPI_Comm comm, int *size ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_remote_size( &jbuf,  & comm, size ,i,v);

return rc;
} /* MPI_Comm_remote_size */


extern void F77_MPI_COMM_REMOTE_SIZE(MPI_Fint  * comm, int  *size , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_remote_size( &jbuf, &c_comm, size ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_remote_size */



/* --------------- MPI_Comm_split --------------- */

static int mpiPif_MPI_Comm_split( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * color, int  * key, MPI_Comm  *comm_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Comm_split(  * comm,  * color,  * key, comm_out);
void* f=NULL;
QMPI_Table_query( 62, &f, (*vector_get(v,i)).table);
exec_func(f,i,62,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_split");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Comm_split, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_split */



extern int TMPI_Comm_split ( MPI_Comm comm, int color, int key, MPI_Comm *comm_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_split( &jbuf,  & comm,  & color,  & key, comm_out ,i,v);

return rc;
} /* MPI_Comm_split */


extern void F77_MPI_COMM_SPLIT(MPI_Fint  * comm, int  * color, int  * key, MPI_Fint  *comm_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Comm c_comm_out;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_split( &jbuf, &c_comm, color, key, &c_comm_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_comm_split */



/* --------------- MPI_Comm_test_inter --------------- */

static int mpiPif_MPI_Comm_test_inter( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *flag,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Comm_test_inter(  * comm, flag);
void* f=NULL;
QMPI_Table_query( 64, &f, (*vector_get(v,i)).table);
exec_func(f,i,64,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Comm_test_inter");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Comm_test_inter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Comm_test_inter */



extern int TMPI_Comm_test_inter ( MPI_Comm comm, int *flag ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Comm_test_inter( &jbuf,  & comm, flag ,i,v);

return rc;
} /* MPI_Comm_test_inter */


extern void F77_MPI_COMM_TEST_INTER(MPI_Fint  * comm, int  *flag , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Comm_test_inter( &jbuf, &c_comm, flag ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_comm_test_inter */



/* --------------- MPI_Compare_and_swap --------------- */

static int mpiPif_MPI_Compare_and_swap( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, mpip_const_void_t  *compare_addr, void  *result_addr, MPI_Datatype  * datatype, int  * target_rank, MPI_Aint  * target_disp, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Compare_and_swap( origin_addr, compare_addr, result_addr,  * datatype,  * target_rank,  * target_disp,  * win);
void* f=NULL;
QMPI_Table_query( 65, &f, (*vector_get(v,i)).table);
exec_func(f,i,65,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Compare_and_swap");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Compare_and_swap, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Compare_and_swap */



extern int TMPI_Compare_and_swap ( mpip_const_void_t *origin_addr, mpip_const_void_t *compare_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Compare_and_swap( &jbuf, origin_addr, compare_addr, result_addr,  & datatype,  & target_rank,  & target_disp,  & win ,i,v);

return rc;
} /* MPI_Compare_and_swap */


extern void F77_MPI_COMPARE_AND_SWAP(mpip_const_void_t  *origin_addr, mpip_const_void_t  *compare_addr, void  *result_addr, MPI_Fint  * datatype, int  * target_rank, MPI_Aint  * target_disp, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;

c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Compare_and_swap( &jbuf, origin_addr, compare_addr, result_addr, &c_datatype, target_rank, target_disp, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_compare_and_swap */



/* --------------- MPI_Dims_create --------------- */

static int mpiPif_MPI_Dims_create( jmp_buf * base_jbuf, int  * nnodes, int  * ndims, int  *dims,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Dims_create(  * nnodes,  * ndims, dims);
void* f=NULL;
QMPI_Table_query( 66, &f, (*vector_get(v,i)).table);
exec_func(f,i,66,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Dims_create");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Dims_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Dims_create */



extern int TMPI_Dims_create ( int nnodes, int ndims, int *dims ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Dims_create( &jbuf,  & nnodes,  & ndims, dims ,i,v);

return rc;
} /* MPI_Dims_create */


extern void F77_MPI_DIMS_CREATE(int  * nnodes, int  * ndims, int  *dims , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Dims_create( &jbuf, nnodes, ndims, dims ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_dims_create */



/* --------------- MPI_Error_class --------------- */

static int mpiPif_MPI_Error_class( jmp_buf * base_jbuf, int  * errorcode, int  *errorclass,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Error_class(  * errorcode, errorclass);
void* f=NULL;
QMPI_Table_query( 75, &f, (*vector_get(v,i)).table);
exec_func(f,i,75,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Error_class");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Error_class, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Error_class */



extern int TMPI_Error_class ( int errorcode, int *errorclass ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Error_class( &jbuf,  & errorcode, errorclass ,i,v);

return rc;
} /* MPI_Error_class */


extern void F77_MPI_ERROR_CLASS(int  * errorcode, int  *errorclass , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Error_class( &jbuf, errorcode, errorclass ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_error_class */



/* --------------- MPI_Fetch_and_op --------------- */

static int mpiPif_MPI_Fetch_and_op( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, void  *result_addr, MPI_Datatype  * datatype, int  * target_rank, MPI_Aint  * target_disp, MPI_Op  * op, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Fetch_and_op( origin_addr, result_addr,  * datatype,  * target_rank,  * target_disp,  * op,  * win);
void* f=NULL;
QMPI_Table_query( 78, &f, (*vector_get(v,i)).table);
exec_func(f,i,78,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Fetch_and_op");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Fetch_and_op, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Fetch_and_op */



extern int TMPI_Fetch_and_op ( mpip_const_void_t *origin_addr, void *result_addr, MPI_Datatype datatype, int target_rank, MPI_Aint target_disp, MPI_Op op, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Fetch_and_op( &jbuf, origin_addr, result_addr,  & datatype,  & target_rank,  & target_disp,  & op,  & win ,i,v);

return rc;
} /* MPI_Fetch_and_op */


extern void F77_MPI_FETCH_AND_OP(mpip_const_void_t  *origin_addr, void  *result_addr, MPI_Fint  * datatype, int  * target_rank, MPI_Aint  * target_disp, MPI_Fint  * op, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);

rc = mpiPif_MPI_Fetch_and_op( &jbuf, origin_addr, result_addr, &c_datatype, target_rank, target_disp, &c_op, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_fetch_and_op */



/* --------------- MPI_File_close --------------- */

static int mpiPif_MPI_File_close( jmp_buf * base_jbuf, MPI_File  *fh,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_close( fh);
void* f=NULL;
QMPI_Table_query( 80, &f, (*vector_get(v,i)).table);
exec_func(f,i,80,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_close");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_close, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_close */



extern int TMPI_File_close (MPI_File *fh,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_close( &jbuf, fh ,i,v);

return rc;
} /* MPI_File_close */


extern void F77_MPI_FILE_CLOSE(MPI_Fint  *fh , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_close( &jbuf, &c_fh ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*fh = MPI_File_c2f(c_fh);
}
return;
} /* mpi_file_close */



/* --------------- MPI_File_open --------------- */

static int mpiPif_MPI_File_open( jmp_buf * base_jbuf, MPI_Comm  * comm, mpip_const_char_t  *filename, int  * amode, MPI_Info  * info, MPI_File  *fh,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_open(  * comm, filename,  * amode,  * info, fh);
void* f=NULL;
QMPI_Table_query( 104, &f, (*vector_get(v,i)).table);
exec_func(f,i,104,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_open");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_open, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_open */



extern int TMPI_File_open (MPI_Comm comm, mpip_const_char_t *filename, int amode, MPI_Info info, MPI_File *fh,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_open( &jbuf,  & comm, filename,  & amode,  & info, fh ,i,v);

return rc;
} /* MPI_File_open */


extern void F77_MPI_FILE_OPEN(MPI_Fint  * comm, mpip_const_char_t  *filename, int  * amode, MPI_Fint  * info, MPI_Fint  *fh , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Info c_info;
MPI_File c_fh;

c_comm = MPI_Comm_f2c(*comm);
c_info = MPI_Info_f2c(*info);

rc = mpiPif_MPI_File_open( &jbuf, &c_comm, filename, amode, &c_info, &c_fh ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*fh = MPI_File_c2f(c_fh);
}
return;
} /* mpi_file_open */



/* --------------- MPI_File_preallocate --------------- */

static int mpiPif_MPI_File_preallocate( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * size,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_preallocate(  * fh,  * size);
void* f=NULL;
QMPI_Table_query(105, &f, (*vector_get(v,i)).table);
exec_func(f,i,105,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_preallocate");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_preallocate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_preallocate */



extern int TMPI_File_preallocate (MPI_File fh, MPI_Offset size,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_preallocate( &jbuf,  & fh,  & size ,i,v);

return rc;
} /* MPI_File_preallocate */


extern void F77_MPI_FILE_PREALLOCATE(MPI_Fint  * fh, MPI_Offset  * size , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_preallocate( &jbuf, &c_fh, size ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_preallocate */



/* --------------- MPI_File_read --------------- */

static int mpiPif_MPI_File_read( jmp_buf * base_jbuf, MPI_File  * fh, void  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_read(  * fh, buf,  * count,  * datatype, status);
void* f=NULL;
QMPI_Table_query( 106, &f, (*vector_get(v,i)).table);
exec_func(f,i,106,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_read");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_read, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_read */



extern int TMPI_File_read (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_read( &jbuf,  & fh, buf,  & count,  & datatype, status ,i,v);

return rc;
} /* MPI_File_read */


extern void F77_MPI_FILE_READ(MPI_Fint  * fh, void  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_read( &jbuf, &c_fh, buf, count, &c_datatype, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_read */



/* --------------- MPI_File_read_all --------------- */

static int mpiPif_MPI_File_read_all( jmp_buf * base_jbuf, MPI_File  * fh, void  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_read_all(  * fh, buf,  * count,  * datatype, status);
void* f=NULL;
QMPI_Table_query( 107, &f, (*vector_get(v,i)).table);
exec_func(f,i,107,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_read_all");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_read_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_read_all */



extern int TMPI_File_read_all (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_read_all( &jbuf,  & fh, buf,  & count,  & datatype, status ,i,v);

return rc;
} /* MPI_File_read_all */


extern void F77_MPI_FILE_READ_ALL(MPI_Fint  * fh, void  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_read_all( &jbuf, &c_fh, buf, count, &c_datatype, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_read_all */



/* --------------- MPI_File_read_at --------------- */

static int mpiPif_MPI_File_read_at( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, void  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_read_at(  * fh,  * offset, buf,  * count,  * datatype, status);
void* f=NULL;
QMPI_Table_query( 110, &f, (*vector_get(v,i)).table);
exec_func(f,i,110,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_read_at");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_read_at, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_read_at */



extern int TMPI_File_read_at (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_read_at( &jbuf,  & fh,  & offset, buf,  & count,  & datatype, status ,i,v);

return rc;
} /* MPI_File_read_at */


extern void F77_MPI_FILE_READ_AT(MPI_Fint  * fh, MPI_Offset  * offset, void  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_read_at( &jbuf, &c_fh, offset, buf, count, &c_datatype, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_read_at */



/* --------------- MPI_File_seek --------------- */

static int mpiPif_MPI_File_seek( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, int  * whence,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_seek(  * fh,  * offset,  * whence);
void* f=NULL;
QMPI_Table_query( 118, &f, (*vector_get(v,i)).table);
exec_func(f,i,118,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_seek");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_seek, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_seek */



extern int TMPI_File_seek (MPI_File fh, MPI_Offset offset, int whence,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_seek( &jbuf,  & fh,  & offset,  & whence ,i,v);

return rc;
} /* MPI_File_seek */


extern void F77_MPI_FILE_SEEK(MPI_Fint  * fh, MPI_Offset  * offset, int  * whence , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;

c_fh = MPI_File_f2c(*fh);

rc = mpiPif_MPI_File_seek( &jbuf, &c_fh, offset, whence ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_seek */



/* --------------- MPI_File_set_view --------------- */

static int mpiPif_MPI_File_set_view( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * disp, MPI_Datatype  * etype, MPI_Datatype  * filetype, mpip_const_char_t  *datarep, MPI_Info  * info,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_set_view(  * fh,  * disp,  * etype,  * filetype, datarep,  * info);
void* f=NULL;
QMPI_Table_query( 124, &f, (*vector_get(v,i)).table);
exec_func(f,i,124,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_set_view");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_set_view, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_set_view */



extern int TMPI_File_set_view (MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, mpip_const_char_t *datarep, MPI_Info info,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_set_view( &jbuf,  & fh,  & disp,  & etype,  & filetype, datarep,  & info ,i,v);

return rc;
} /* MPI_File_set_view */


extern void F77_MPI_FILE_SET_VIEW(MPI_Fint  * fh, MPI_Offset  * disp, MPI_Fint  * etype, MPI_Fint  * filetype, mpip_const_char_t  *datarep, MPI_Fint  * info , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_etype;
MPI_Datatype c_filetype;
MPI_Info c_info;

c_fh = MPI_File_f2c(*fh);
c_etype = MPI_Type_f2c(*etype);
c_filetype = MPI_Type_f2c(*filetype);
c_info = MPI_Info_f2c(*info);

rc = mpiPif_MPI_File_set_view( &jbuf, &c_fh, disp, &c_etype, &c_filetype, datarep, &c_info ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_set_view */



/* --------------- MPI_File_write --------------- */

static int mpiPif_MPI_File_write( jmp_buf * base_jbuf, MPI_File  * fh, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_write(  * fh, buf,  * count,  * datatype, status);
void* f=NULL;
QMPI_Table_query( 126, &f, (*vector_get(v,i)).table);
exec_func(f,i,126,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_write");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_write, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_write */



extern int TMPI_File_write (MPI_File fh, mpip_const_void_t *buf, int count, MPI_Datatype datatype, MPI_Status *status,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_write( &jbuf,  & fh, buf,  & count,  & datatype, status ,i,v);

return rc;
} /* MPI_File_write */


extern void F77_MPI_FILE_WRITE(MPI_Fint  * fh, mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_write( &jbuf, &c_fh, buf, count, &c_datatype, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_write */



/* --------------- MPI_File_write_all --------------- */

static int mpiPif_MPI_File_write_all( jmp_buf * base_jbuf, MPI_File  * fh, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_write_all(  * fh, buf,  * count,  * datatype, status);
void* f=NULL;
QMPI_Table_query( 127, &f, (*vector_get(v,i)).table);
exec_func(f,i,127,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_write_all");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_write_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_write_all */



extern int TMPI_File_write_all (MPI_File fh, mpip_const_void_t *buf, int count, MPI_Datatype datatype, MPI_Status *status,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_write_all( &jbuf,  & fh, buf,  & count,  & datatype, status ,i,v);

return rc;
} /* MPI_File_write_all */


extern void F77_MPI_FILE_WRITE_ALL(MPI_Fint  * fh, mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_write_all( &jbuf, &c_fh, buf, count, &c_datatype, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_write_all */



/* --------------- MPI_File_write_at --------------- */

static int mpiPif_MPI_File_write_at( jmp_buf * base_jbuf, MPI_File  * fh, MPI_Offset  * offset, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_File_write_at(  * fh,  * offset, buf,  * count,  * datatype, status);
void* f=NULL;
QMPI_Table_query( 130, &f, (*vector_get(v,i)).table);
exec_func(f,i,130,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*datatype, &tsize);
ioSize = (double)(tsize * *count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_File_write_at");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_File_write_at, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_File_write_at */



extern int TMPI_File_write_at (MPI_File fh, MPI_Offset offset, mpip_const_void_t *buf, int count, MPI_Datatype datatype, MPI_Status *status,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_File_write_at( &jbuf,  & fh,  & offset, buf,  & count,  & datatype, status ,i,v);

return rc;
} /* MPI_File_write_at */


extern void F77_MPI_FILE_WRITE_AT(MPI_Fint  * fh, MPI_Offset  * offset, mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_File c_fh;
MPI_Datatype c_datatype;

c_fh = MPI_File_f2c(*fh);
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_File_write_at( &jbuf, &c_fh, offset, buf, count, &c_datatype, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_file_write_at */



/* --------------- MPI_Gather --------------- */

static int mpiPif_MPI_Gather( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Gather( sendbuf,  * sendcnt,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * root,  * comm);
void* f=NULL;
QMPI_Table_query( 141, &f, (*vector_get(v,i)).table);
exec_func(f,i,141,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcnt);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Gather");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Gather, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Gather, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Gather */



extern int TMPI_Gather ( mpip_const_void_t *sendbuf, int sendcnt, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Gather( &jbuf, sendbuf,  & sendcnt,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & root,  & comm ,i,v);

return rc;
} /* MPI_Gather */


extern void F77_MPI_GATHER(mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Gather( &jbuf, sendbuf, sendcnt, &c_sendtype, recvbuf, recvcount, &c_recvtype, root, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_gather */



/* --------------- MPI_Gatherv --------------- */

static int mpiPif_MPI_Gatherv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcnts, mpip_const_int_t  *displs, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Gatherv( sendbuf,  * sendcnt,  * sendtype, recvbuf, recvcnts, displs,  * recvtype,  * root,  * comm);
void* f=NULL;
QMPI_Table_query( 142, &f, (*vector_get(v,i)).table);
exec_func(f,i,142,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcnt);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Gatherv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Gatherv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Gatherv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Gatherv */



extern int TMPI_Gatherv ( mpip_const_void_t *sendbuf, int sendcnt, MPI_Datatype sendtype, void *recvbuf, mpip_const_int_t *recvcnts, mpip_const_int_t *displs, MPI_Datatype recvtype, int root, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Gatherv( &jbuf, sendbuf,  & sendcnt,  & sendtype, recvbuf, recvcnts, displs,  & recvtype,  & root,  & comm ,i,v);

return rc;
} /* MPI_Gatherv */


extern void F77_MPI_GATHERV(mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t  *recvcnts, mpip_const_int_t  *displs, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Gatherv( &jbuf, sendbuf, sendcnt, &c_sendtype, recvbuf, recvcnts, displs, &c_recvtype, root, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_gatherv */



/* --------------- MPI_Get --------------- */

static int mpiPif_MPI_Get( jmp_buf * base_jbuf, void  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Get( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * win);
void* f=NULL;
QMPI_Table_query( 143, &f, (*vector_get(v,i)).table);
exec_func(f,i,143,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Get");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Get */



extern int TMPI_Get ( void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Get( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & win ,i,v);

return rc;
} /* MPI_Get */


extern void F77_MPI_GET(void  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);

rc = mpiPif_MPI_Get( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_get */



/* --------------- MPI_Get_accumulate --------------- */

static int mpiPif_MPI_Get_accumulate( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, void  *result_addr, int  * result_count, MPI_Datatype  * result_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Op  * op, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Get_accumulate( origin_addr,  * origin_count,  * origin_datatype, result_addr,  * result_count,  * result_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * op,  * win);
void* f=NULL;
QMPI_Table_query( 144, &f, (*vector_get(v,i)).table);
exec_func(f,i,144,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*target_datatype, &tsize);
rmaSize = (double)(tsize * *target_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Get_accumulate");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Get_accumulate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Get_accumulate */



extern int TMPI_Get_accumulate ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Get_accumulate( &jbuf, origin_addr,  & origin_count,  & origin_datatype, result_addr,  & result_count,  & result_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & op,  & win ,i,v);

return rc;
} /* MPI_Get_accumulate */


extern void F77_MPI_GET_ACCUMULATE(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, void  *result_addr, int  * result_count, MPI_Fint  * result_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Fint  * op, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_result_datatype;
MPI_Datatype c_target_datatype;
MPI_Op c_op;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_result_datatype = MPI_Type_f2c(*result_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_op = MPI_Op_f2c(*op);

rc = mpiPif_MPI_Get_accumulate( &jbuf, origin_addr, origin_count, &c_origin_datatype, result_addr, result_count, &c_result_datatype, target_rank, target_disp, target_count, &c_target_datatype, &c_op, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_get_accumulate */



/* --------------- MPI_Graph_create --------------- */

static int mpiPif_MPI_Graph_create( jmp_buf * base_jbuf, MPI_Comm  * comm_old, int  * nnodes, mpip_const_int_t  *index, mpip_const_int_t  *edges, int  * reorder, MPI_Comm  *comm_graph,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Graph_create(  * comm_old,  * nnodes, index, edges,  * reorder, comm_graph);
void* f=NULL;
QMPI_Table_query( 152, &f, (*vector_get(v,i)).table);
exec_func(f,i,152,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_create");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Graph_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_create */



extern int TMPI_Graph_create ( MPI_Comm comm_old, int nnodes, mpip_const_int_t *index, mpip_const_int_t *edges, int reorder, MPI_Comm *comm_graph ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_create( &jbuf,  & comm_old,  & nnodes, index, edges,  & reorder, comm_graph ,i,v);

return rc;
} /* MPI_Graph_create */


extern void F77_MPI_GRAPH_CREATE(MPI_Fint  * comm_old, int  * nnodes, mpip_const_int_t  *index, mpip_const_int_t  *edges, int  * reorder, MPI_Fint  *comm_graph , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm_old;
MPI_Comm c_comm_graph;

c_comm_old = MPI_Comm_f2c(*comm_old);

rc = mpiPif_MPI_Graph_create( &jbuf, &c_comm_old, nnodes, index, edges, reorder, &c_comm_graph ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_graph = MPI_Comm_c2f(c_comm_graph);
}
return;
} /* mpi_graph_create */



/* --------------- MPI_Graph_get --------------- */

static int mpiPif_MPI_Graph_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * maxindex, int  * maxedges, int  *index, int  *edges,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Graph_get(  * comm,  * maxindex,  * maxedges, index, edges);
void* f=NULL;
QMPI_Table_query( 153, &f, (*vector_get(v,i)).table);
exec_func(f,i,153,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_get");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Graph_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_get */



extern int TMPI_Graph_get ( MPI_Comm comm, int maxindex, int maxedges, int *index, int *edges ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_get( &jbuf,  & comm,  & maxindex,  & maxedges, index, edges ,i,v);

return rc;
} /* MPI_Graph_get */


extern void F77_MPI_GRAPH_GET(MPI_Fint  * comm, int  * maxindex, int  * maxedges, int  *index, int  *edges , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Graph_get( &jbuf, &c_comm, maxindex, maxedges, index, edges ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graph_get */



/* --------------- MPI_Graph_map --------------- */

static int mpiPif_MPI_Graph_map( jmp_buf * base_jbuf, MPI_Comm  * comm_old, int  * nnodes, mpip_const_int_t  *index, mpip_const_int_t  *edges, int  *newrank,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Graph_map(  * comm_old,  * nnodes, index, edges, newrank);
void* f=NULL;
QMPI_Table_query( 154, &f, (*vector_get(v,i)).table);
exec_func(f,i,154,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_map");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Graph_map, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_map */



extern int TMPI_Graph_map ( MPI_Comm comm_old, int nnodes, mpip_const_int_t *index, mpip_const_int_t *edges, int *newrank ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_map( &jbuf,  & comm_old,  & nnodes, index, edges, newrank ,i,v);

return rc;
} /* MPI_Graph_map */


extern void F77_MPI_GRAPH_MAP(MPI_Fint  * comm_old, int  * nnodes, mpip_const_int_t  *index, mpip_const_int_t  *edges, int  *newrank , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm_old;

c_comm_old = MPI_Comm_f2c(*comm_old);

rc = mpiPif_MPI_Graph_map( &jbuf, &c_comm_old, nnodes, index, edges, newrank ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graph_map */



/* --------------- MPI_Graph_neighbors --------------- */

static int mpiPif_MPI_Graph_neighbors( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * rank, int  * maxneighbors, int  *neighbors,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Graph_neighbors(  * comm,  * rank,  * maxneighbors, neighbors);
void* f=NULL;
QMPI_Table_query( 155, &f, (*vector_get(v,i)).table);
exec_func(f,i,155,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_neighbors");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Graph_neighbors, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_neighbors */



extern int TMPI_Graph_neighbors ( MPI_Comm comm, int rank, int maxneighbors, int *neighbors ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_neighbors( &jbuf,  & comm,  & rank,  & maxneighbors, neighbors ,i,v);

return rc;
} /* MPI_Graph_neighbors */


extern void F77_MPI_GRAPH_NEIGHBORS(MPI_Fint  * comm, int  * rank, int  * maxneighbors, int  *neighbors , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Graph_neighbors( &jbuf, &c_comm, rank, maxneighbors, neighbors ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graph_neighbors */



/* --------------- MPI_Graph_neighbors_count --------------- */

static int mpiPif_MPI_Graph_neighbors_count( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * rank, int  *nneighbors,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Graph_neighbors_count(  * comm,  * rank, nneighbors);
void* f=NULL;
QMPI_Table_query( 156, &f, (*vector_get(v,i)).table);
exec_func(f,i,156,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graph_neighbors_count");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Graph_neighbors_count, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graph_neighbors_count */



extern int TMPI_Graph_neighbors_count ( MPI_Comm comm, int rank, int *nneighbors ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graph_neighbors_count( &jbuf,  & comm,  & rank, nneighbors ,i,v);

return rc;
} /* MPI_Graph_neighbors_count */


extern void F77_MPI_GRAPH_NEIGHBORS_COUNT(MPI_Fint  * comm, int  * rank, int  *nneighbors , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Graph_neighbors_count( &jbuf, &c_comm, rank, nneighbors ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graph_neighbors_count */



/* --------------- MPI_Graphdims_get --------------- */

static int mpiPif_MPI_Graphdims_get( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *nnodes, int  *nedges,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Graphdims_get(  * comm, nnodes, nedges);
void* f=NULL;
QMPI_Table_query( 157, &f, (*vector_get(v,i)).table);
exec_func(f,i,157,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Graphdims_get");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Graphdims_get, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Graphdims_get */



extern int TMPI_Graphdims_get ( MPI_Comm comm, int *nnodes, int *nedges ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Graphdims_get( &jbuf,  & comm, nnodes, nedges ,i,v);

return rc;
} /* MPI_Graphdims_get */


extern void F77_MPI_GRAPHDIMS_GET(MPI_Fint  * comm, int  *nnodes, int  *nedges , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Graphdims_get( &jbuf, &c_comm, nnodes, nedges ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_graphdims_get */



/* --------------- MPI_Group_compare --------------- */

static int mpiPif_MPI_Group_compare( jmp_buf * base_jbuf, MPI_Group  * group1, MPI_Group  * group2, int  *result,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Group_compare(  * group1,  * group2, result);
void* f=NULL;
QMPI_Table_query( 160, &f, (*vector_get(v,i)).table);
exec_func(f,i,160,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_compare");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Group_compare, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_compare */



extern int TMPI_Group_compare ( MPI_Group group1, MPI_Group group2, int *result ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_compare( &jbuf,  & group1,  & group2, result ,i,v);

return rc;
} /* MPI_Group_compare */


extern void F77_MPI_GROUP_COMPARE(MPI_Fint  * group1, MPI_Fint  * group2, int  *result , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group1;
MPI_Group c_group2;

c_group1 = MPI_Group_f2c(*group1);
c_group2 = MPI_Group_f2c(*group2);

rc = mpiPif_MPI_Group_compare( &jbuf, &c_group1, &c_group2, result ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_group_compare */



/* --------------- MPI_Group_difference --------------- */

static int mpiPif_MPI_Group_difference( jmp_buf * base_jbuf, MPI_Group  * group1, MPI_Group  * group2, MPI_Group  *group_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Group_difference(  * group1,  * group2, group_out);
void* f=NULL;
QMPI_Table_query( 161, &f, (*vector_get(v,i)).table);
exec_func(f,i,161,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_difference");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Group_difference, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_difference */



extern int TMPI_Group_difference ( MPI_Group group1, MPI_Group group2, MPI_Group *group_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_difference( &jbuf,  & group1,  & group2, group_out ,i,v);

return rc;
} /* MPI_Group_difference */


extern void F77_MPI_GROUP_DIFFERENCE(MPI_Fint  * group1, MPI_Fint  * group2, MPI_Fint  *group_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group1;
MPI_Group c_group2;
MPI_Group c_group_out;

c_group1 = MPI_Group_f2c(*group1);
c_group2 = MPI_Group_f2c(*group2);

rc = mpiPif_MPI_Group_difference( &jbuf, &c_group1, &c_group2, &c_group_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group_out = MPI_Group_c2f(c_group_out);
}
return;
} /* mpi_group_difference */



/* --------------- MPI_Group_excl --------------- */

static int mpiPif_MPI_Group_excl( jmp_buf * base_jbuf, MPI_Group  * group, int  * n, mpip_const_int_t  *ranks, MPI_Group  *newgroup,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Group_excl(  * group,  * n, ranks, newgroup);
void* f=NULL;
QMPI_Table_query( 162, &f, (*vector_get(v,i)).table);
exec_func(f,i,162,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_excl");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Group_excl, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_excl */



extern int TMPI_Group_excl ( MPI_Group group, int n, mpip_const_int_t *ranks, MPI_Group *newgroup ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_excl( &jbuf,  & group,  & n, ranks, newgroup ,i,v);

return rc;
} /* MPI_Group_excl */


extern void F77_MPI_GROUP_EXCL(MPI_Fint  * group, int  * n, mpip_const_int_t  *ranks, MPI_Fint  *newgroup , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;
MPI_Group c_newgroup;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Group_excl( &jbuf, &c_group, n, ranks, &c_newgroup ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*newgroup = MPI_Group_c2f(c_newgroup);
}
return;
} /* mpi_group_excl */



/* --------------- MPI_Group_free --------------- */

static int mpiPif_MPI_Group_free( jmp_buf * base_jbuf, MPI_Group  *group,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Group_free( group);
void* f=NULL;
QMPI_Table_query( 163, &f, (*vector_get(v,i)).table);
exec_func(f,i,163,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_free");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Group_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_free */



extern int TMPI_Group_free ( MPI_Group *group ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_free( &jbuf, group ,i,v);

return rc;
} /* MPI_Group_free */


extern void F77_MPI_GROUP_FREE(MPI_Fint  *group , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Group_free( &jbuf, &c_group ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group = MPI_Group_c2f(c_group);
}
return;
} /* mpi_group_free */



/* --------------- MPI_Group_incl --------------- */

static int mpiPif_MPI_Group_incl( jmp_buf * base_jbuf, MPI_Group  * group, int  * n, mpip_const_int_t  *ranks, MPI_Group  *group_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Group_incl(  * group,  * n, ranks, group_out);
void* f=NULL;
QMPI_Table_query( 164, &f, (*vector_get(v,i)).table);
exec_func(f,i,164,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_incl");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Group_incl, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_incl */



extern int TMPI_Group_incl ( MPI_Group group, int n, mpip_const_int_t *ranks, MPI_Group *group_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_incl( &jbuf,  & group,  & n, ranks, group_out ,i,v);

return rc;
} /* MPI_Group_incl */


extern void F77_MPI_GROUP_INCL(MPI_Fint  * group, int  * n, mpip_const_int_t  *ranks, MPI_Fint  *group_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;
MPI_Group c_group_out;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Group_incl( &jbuf, &c_group, n, ranks, &c_group_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group_out = MPI_Group_c2f(c_group_out);
}
return;
} /* mpi_group_incl */



/* --------------- MPI_Group_intersection --------------- */

static int mpiPif_MPI_Group_intersection( jmp_buf * base_jbuf, MPI_Group  * group1, MPI_Group  * group2, MPI_Group  *group_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Group_intersection(  * group1,  * group2, group_out);
void* f=NULL;
QMPI_Table_query( 165, &f, (*vector_get(v,i)).table);
exec_func(f,i,165,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_intersection");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Group_intersection, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_intersection */



extern int TMPI_Group_intersection ( MPI_Group group1, MPI_Group group2, MPI_Group *group_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_intersection( &jbuf,  & group1,  & group2, group_out ,i,v);

return rc;
} /* MPI_Group_intersection */


extern void F77_MPI_GROUP_INTERSECTION(MPI_Fint  * group1, MPI_Fint  * group2, MPI_Fint  *group_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group1;
MPI_Group c_group2;
MPI_Group c_group_out;

c_group1 = MPI_Group_f2c(*group1);
c_group2 = MPI_Group_f2c(*group2);

rc = mpiPif_MPI_Group_intersection( &jbuf, &c_group1, &c_group2, &c_group_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group_out = MPI_Group_c2f(c_group_out);
}
return;
} /* mpi_group_intersection */



/* --------------- MPI_Group_translate_ranks --------------- */

static int mpiPif_MPI_Group_translate_ranks( jmp_buf * base_jbuf, MPI_Group  * group_a, int  * n, mpip_const_int_t  *ranks_a, MPI_Group  * group_b, int  *ranks_b,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Group_translate_ranks(  * group_a,  * n, ranks_a,  * group_b, ranks_b);
void* f=NULL;
QMPI_Table_query( 170, &f, (*vector_get(v,i)).table);
exec_func(f,i,170,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_translate_ranks");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Group_translate_ranks, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_translate_ranks */



extern int TMPI_Group_translate_ranks ( MPI_Group group_a, int n, mpip_const_int_t *ranks_a, MPI_Group group_b, int *ranks_b ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_translate_ranks( &jbuf,  & group_a,  & n, ranks_a,  & group_b, ranks_b ,i,v);

return rc;
} /* MPI_Group_translate_ranks */


extern void F77_MPI_GROUP_TRANSLATE_RANKS(MPI_Fint  * group_a, int  * n, mpip_const_int_t  *ranks_a, MPI_Fint  * group_b, int  *ranks_b , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group_a;
MPI_Group c_group_b;

c_group_a = MPI_Group_f2c(*group_a);
c_group_b = MPI_Group_f2c(*group_b);

rc = mpiPif_MPI_Group_translate_ranks( &jbuf, &c_group_a, n, ranks_a, &c_group_b, ranks_b ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_group_translate_ranks */



/* --------------- MPI_Group_union --------------- */

static int mpiPif_MPI_Group_union( jmp_buf * base_jbuf, MPI_Group  * group1, MPI_Group  * group2, MPI_Group  *group_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Group_union(  * group1,  * group2, group_out);
void* f=NULL;
QMPI_Table_query( 171, &f, (*vector_get(v,i)).table);
exec_func(f,i,171,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Group_union");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Group_union, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Group_union */



extern int TMPI_Group_union ( MPI_Group group1, MPI_Group group2, MPI_Group *group_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Group_union( &jbuf,  & group1,  & group2, group_out ,i,v);

return rc;
} /* MPI_Group_union */


extern void F77_MPI_GROUP_UNION(MPI_Fint  * group1, MPI_Fint  * group2, MPI_Fint  *group_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group1;
MPI_Group c_group2;
MPI_Group c_group_out;

c_group1 = MPI_Group_f2c(*group1);
c_group2 = MPI_Group_f2c(*group2);

rc = mpiPif_MPI_Group_union( &jbuf, &c_group1, &c_group2, &c_group_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*group_out = MPI_Group_c2f(c_group_out);
}
return;
} /* mpi_group_union */



/* --------------- MPI_Iallgather --------------- */

static int mpiPif_MPI_Iallgather( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Iallgather( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * comm, request);
void* f=NULL;
QMPI_Table_query( 172, &f, (*vector_get(v,i)).table);
exec_func(f,i,172,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iallgather");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Iallgather, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Iallgather, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iallgather */



extern int TMPI_Iallgather ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request ,int i,vector * v) 
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iallgather( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & comm, request ,i,v);

return rc;
} /* MPI_Iallgather */


extern void F77_MPI_IALLGATHER(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iallgather( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iallgather */



/* --------------- MPI_Iallgatherv --------------- */

static int mpiPif_MPI_Iallgatherv( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Datatype  * recvtype, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Iallgatherv( sendbuf,  * sendcount,  * sendtype, recvbuf, recvcounts, displs,  * recvtype,  * comm, request);
void* f=NULL;
QMPI_Table_query( 173, &f, (*vector_get(v,i)).table);
exec_func(f,i,173,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iallgatherv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Iallgatherv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Iallgatherv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iallgatherv */



extern int TMPI_Iallgatherv ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request* request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iallgatherv( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf, recvcounts, displs,  & recvtype,  & comm, request ,i,v);

return rc;
} /* MPI_Iallgatherv */


extern void F77_MPI_IALLGATHERV(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Fint  * recvtype, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iallgatherv( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcounts, displs, &c_recvtype, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iallgatherv */



/* --------------- MPI_Iallreduce --------------- */

static int mpiPif_MPI_Iallreduce( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Iallreduce( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm, request);
void* f=NULL;
QMPI_Table_query( 174, &f, (*vector_get(v,i)).table);
exec_func(f,i,174,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iallreduce");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Iallreduce, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Iallreduce, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iallreduce */



extern int TMPI_Iallreduce ( const void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request  ,int i,vector * v )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iallreduce( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm, request ,i,v);

return rc;
} /* MPI_Iallreduce */


extern void F77_MPI_IALLREDUCE(const void  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iallreduce( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iallreduce */



/* --------------- MPI_Ialltoall --------------- */

static int mpiPif_MPI_Ialltoall( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ialltoall( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * comm, request);
void* f=NULL;
QMPI_Table_query( 175, &f, (*vector_get(v,i)).table);
exec_func(f,i,175,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ialltoall");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ialltoall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Ialltoall, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ialltoall */



extern int TMPI_Ialltoall ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request  ,int i,vector * v) 
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ialltoall( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & comm, request ,i,v);

return rc;
} /* MPI_Ialltoall */


extern void F77_MPI_IALLTOALL(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ialltoall( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ialltoall */



/* --------------- MPI_Ialltoallv --------------- */

static int mpiPif_MPI_Ialltoallv( jmp_buf * base_jbuf, const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], MPI_Datatype  * recvtype, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ialltoallv( sendbuf, sendcounts, sdispls,  * sendtype, recvbuf, recvcounts, rdispls,  * recvtype,  * comm, request);
void* f=NULL;
QMPI_Table_query( 176, &f, (*vector_get(v,i)).table);
exec_func(f,i,176,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { 
  int loc_comm_size, i;
  int loc_sent = 0;

  PMPI_Comm_size(*comm, &loc_comm_size);
  PMPI_Type_size(*sendtype, &tsize);
  for ( i = 0; i<loc_comm_size; i++) 
    loc_sent += sendcounts[i];
  messSize = (double)(tsize * loc_sent);
}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ialltoallv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ialltoallv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Ialltoallv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ialltoallv */



extern int TMPI_Ialltoallv ( const void* sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], MPI_Datatype sendtype, void* recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ialltoallv( &jbuf, sendbuf, sendcounts, sdispls,  & sendtype, recvbuf, recvcounts, rdispls,  & recvtype,  & comm, request ,i,v);

return rc;
} /* MPI_Ialltoallv */


extern void F77_MPI_IALLTOALLV(const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], MPI_Fint  * recvtype, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ialltoallv( &jbuf, sendbuf, sendcounts, sdispls, &c_sendtype, recvbuf, recvcounts, rdispls, &c_recvtype, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ialltoallv */



/* --------------- MPI_Ialltoallw --------------- */

static int mpiPif_MPI_Ialltoallw( jmp_buf * base_jbuf, const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], mpip_const_datatype_t sendtypes[], void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], mpip_const_datatype_t recvtypes[], MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ialltoallw( sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes,  * comm, request);
void* f=NULL;
QMPI_Table_query( 177, &f, (*vector_get(v,i)).table);
exec_func(f,i,177,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

  int loc_comm_size, i;
  int loc_sent = 0;

  PMPI_Comm_size(*comm, &loc_comm_size);

  for ( i = 0; i<loc_comm_size; i++) { 
    if ( sendtypes[i] != MPI_DATATYPE_NULL ) { 
      PMPI_Type_size(sendtypes[i], &tsize);
      loc_sent = sendcounts[i];
      messSize += (double)(tsize * loc_sent);
    }
    else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
     mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}
}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ialltoallw");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ialltoallw, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Ialltoallw, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ialltoallw */



extern int TMPI_Ialltoallw ( const void* sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], mpip_const_datatype_t sendtypes[], void* recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], mpip_const_datatype_t recvtypes[], MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ialltoallw( &jbuf, sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes,  & comm, request ,i,v);

return rc;
} /* MPI_Ialltoallw */


extern void F77_MPI_IALLTOALLW(const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t sdispls[], mpip_const_datatype_t sendtypes[], void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t rdispls[], mpip_const_datatype_t recvtypes[], MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Request c_request;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ialltoallw( &jbuf, sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ialltoallw */



/* --------------- MPI_Ibarrier --------------- */

static int mpiPif_MPI_Ibarrier( jmp_buf * base_jbuf, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ibarrier(  * comm, request);
void* f=NULL;
QMPI_Table_query( 178, &f, (*vector_get(v,i)).table);
exec_func(f,i,178,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ibarrier");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ibarrier, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Ibarrier, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ibarrier */



extern int TMPI_Ibarrier ( MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ibarrier( &jbuf,  & comm, request ,i,v);

return rc;
} /* MPI_Ibarrier */


extern void F77_MPI_IBARRIER(MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Request c_request;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ibarrier( &jbuf, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ibarrier */



/* --------------- MPI_Ibcast --------------- */

static int mpiPif_MPI_Ibcast( jmp_buf * base_jbuf, void  *buffer, int  * count, MPI_Datatype  * datatype, int  * root, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ibcast( buffer,  * count,  * datatype,  * root,  * comm, request);
void* f=NULL;
QMPI_Table_query( 179, &f, (*vector_get(v,i)).table);
exec_func(f,i,179,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ibcast");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ibcast, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Ibcast, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ibcast */



extern int TMPI_Ibcast ( void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm, MPI_Request *request ,int i,vector * v )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ibcast( &jbuf, buffer,  & count,  & datatype,  & root,  & comm, request ,i,v);

return rc;
} /* MPI_Ibcast */


extern void F77_MPI_IBCAST(void  *buffer, int  * count, MPI_Fint  * datatype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ibcast( &jbuf, buffer, count, &c_datatype, root, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ibcast */



/* --------------- MPI_Ibsend --------------- */

static int mpiPif_MPI_Ibsend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ibsend( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 180, &f, (*vector_get(v,i)).table);
exec_func(f,i,180,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ibsend");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ibsend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Ibsend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ibsend */



extern int TMPI_Ibsend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ibsend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Ibsend */


extern void F77_MPI_IBSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ibsend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ibsend */



/* --------------- MPI_Iexscan --------------- */

static int mpiPif_MPI_Iexscan( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Iexscan( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm, request);
void* f=NULL;
QMPI_Table_query( 181, &f, (*vector_get(v,i)).table);
exec_func(f,i,181,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iexscan");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Iexscan, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Iexscan, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iexscan */



extern int TMPI_Iexscan ( const void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request ,int i,vector * v) 
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iexscan( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm, request ,i,v);

return rc;
} /* MPI_Iexscan */


extern void F77_MPI_IEXSCAN(const void  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iexscan( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iexscan */



/* --------------- MPI_Igather --------------- */

static int mpiPif_MPI_Igather( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Igather( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * root,  * comm, request);
void* f=NULL;
QMPI_Table_query( 182, &f, (*vector_get(v,i)).table);
exec_func(f,i,182,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Igather");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Igather, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Igather, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Igather */



extern int TMPI_Igather ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request,int i,vector * v) 
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Igather( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & root,  & comm, request ,i,v);

return rc;
} /* MPI_Igather */


extern void F77_MPI_IGATHER(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Igather( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, root, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_igather */



/* --------------- MPI_Igatherv --------------- */

static int mpiPif_MPI_Igatherv( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Igatherv( sendbuf,  * sendcount,  * sendtype, recvbuf, recvcounts, displs,  * recvtype,  * root,  * comm, request);
void* f=NULL;
QMPI_Table_query( 183, &f, (*vector_get(v,i)).table);
exec_func(f,i,183,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Igatherv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Igatherv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Igatherv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Igatherv */



extern int TMPI_Igatherv ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Igatherv( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf, recvcounts, displs,  & recvtype,  & root,  & comm, request ,i,v);

return rc;
} /* MPI_Igatherv */


extern void F77_MPI_IGATHERV(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, mpip_const_int_t recvcounts[], mpip_const_int_t displs[], MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Igatherv( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcounts, displs, &c_recvtype, root, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_igatherv */



/* --------------- MPI_Intercomm_create --------------- */

static int mpiPif_MPI_Intercomm_create( jmp_buf * base_jbuf, MPI_Comm  * local_comm, int  * local_leader, MPI_Comm  * peer_comm, int  * remote_leader, int  * tag, MPI_Comm  *comm_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Intercomm_create(  * local_comm,  * local_leader,  * peer_comm,  * remote_leader,  * tag, comm_out);
void* f=NULL;
QMPI_Table_query( 203, &f, (*vector_get(v,i)).table);
exec_func(f,i,203,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Intercomm_create");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Intercomm_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Intercomm_create */



extern int TMPI_Intercomm_create ( MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm, int remote_leader, int tag, MPI_Comm *comm_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Intercomm_create( &jbuf,  & local_comm,  & local_leader,  & peer_comm,  & remote_leader,  & tag, comm_out ,i,v);

return rc;
} /* MPI_Intercomm_create */


extern void F77_MPI_INTERCOMM_CREATE(MPI_Fint  * local_comm, int  * local_leader, MPI_Fint  * peer_comm, int  * remote_leader, int  * tag, MPI_Fint  *comm_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_local_comm;
MPI_Comm c_peer_comm;
MPI_Comm c_comm_out;

c_local_comm = MPI_Comm_f2c(*local_comm);
c_peer_comm = MPI_Comm_f2c(*peer_comm);

rc = mpiPif_MPI_Intercomm_create( &jbuf, &c_local_comm, local_leader, &c_peer_comm, remote_leader, tag, &c_comm_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_intercomm_create */



/* --------------- MPI_Intercomm_merge --------------- */

static int mpiPif_MPI_Intercomm_merge( jmp_buf * base_jbuf, MPI_Comm  * comm, int  * high, MPI_Comm  *comm_out,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Intercomm_merge(  * comm,  * high, comm_out);
void* f=NULL;
QMPI_Table_query( 204, &f, (*vector_get(v,i)).table);
exec_func(f,i,204,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Intercomm_merge");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Intercomm_merge, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Intercomm_merge */



extern int TMPI_Intercomm_merge ( MPI_Comm comm, int high, MPI_Comm *comm_out ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Intercomm_merge( &jbuf,  & comm,  & high, comm_out ,i,v);

return rc;
} /* MPI_Intercomm_merge */


extern void F77_MPI_INTERCOMM_MERGE(MPI_Fint  * comm, int  * high, MPI_Fint  *comm_out , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;
MPI_Comm c_comm_out;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Intercomm_merge( &jbuf, &c_comm, high, &c_comm_out ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*comm_out = MPI_Comm_c2f(c_comm_out);
}
return;
} /* mpi_intercomm_merge */



/* --------------- MPI_Iprobe --------------- */

static int mpiPif_MPI_Iprobe( jmp_buf * base_jbuf, int  * source, int  * tag, MPI_Comm  * comm, int  *flag, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Iprobe(  * source,  * tag,  * comm, flag, status);
void* f=NULL;
QMPI_Table_query( 205, &f, (*vector_get(v,i)).table);
exec_func(f,i,205,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iprobe");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Iprobe, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Iprobe */



extern int TMPI_Iprobe ( int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iprobe( &jbuf,  & source,  & tag,  & comm, flag, status ,i,v);

return rc;
} /* MPI_Iprobe */


extern void F77_MPI_IPROBE(int  * source, int  * tag, MPI_Fint  * comm, int  *flag, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iprobe( &jbuf, source, tag, &c_comm, flag, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_iprobe */



/* --------------- MPI_Irecv --------------- */

static int mpiPif_MPI_Irecv( jmp_buf * base_jbuf, void  *buf, int  * count, MPI_Datatype  * datatype, int  * source, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Irecv( buf,  * count,  * datatype,  * source,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 206, &f, (*vector_get(v,i)).table);
exec_func(f,i,206,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Irecv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Irecv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Irecv */



extern int TMPI_Irecv ( void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Irecv( &jbuf, buf,  & count,  & datatype,  & source,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Irecv */


extern void F77_MPI_IRECV(void  *buf, int  * count, MPI_Fint  * datatype, int  * source, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Irecv( &jbuf, buf, count, &c_datatype, source, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_irecv */



/* --------------- MPI_Ireduce --------------- */

static int mpiPif_MPI_Ireduce( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, int  * root, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ireduce( sendbuf, recvbuf,  * count,  * datatype,  * op,  * root,  * comm, request);
void* f=NULL;
QMPI_Table_query( 207, &f, (*vector_get(v,i)).table);
exec_func(f,i,207,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ireduce");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ireduce, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Ireduce, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ireduce */



extern int TMPI_Ireduce ( const void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm, MPI_Request *request ,int i,vector * v )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ireduce( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & root,  & comm, request ,i,v);

return rc;
} /* MPI_Ireduce */


extern void F77_MPI_IREDUCE(const void  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ireduce( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, root, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ireduce */



/* --------------- MPI_Ireduce_scatter --------------- */

static int mpiPif_MPI_Ireduce_scatter( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, mpip_const_int_t recvcounts[], MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ireduce_scatter( sendbuf, recvbuf, recvcounts,  * datatype,  * op,  * comm, request);
void* f=NULL;
QMPI_Table_query( 208, &f, (*vector_get(v,i)).table);
exec_func(f,i,208,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { 
  int loc_comm_size, i;
  int loc_sent = 0;

  PMPI_Comm_size(*comm, &loc_comm_size);
  PMPI_Type_size(*datatype, &tsize);
  for ( i = 0; i<loc_comm_size; i++) 
    loc_sent += recvcounts[i];
  messSize = (double)(tsize * loc_sent);
}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ireduce_scatter");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ireduce_scatter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Ireduce_scatter, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ireduce_scatter */



extern int TMPI_Ireduce_scatter ( const void* sendbuf, void* recvbuf, mpip_const_int_t recvcounts[], MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request ,int i,vector * v) 
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ireduce_scatter( &jbuf, sendbuf, recvbuf, recvcounts,  & datatype,  & op,  & comm, request ,i,v);

return rc;
} /* MPI_Ireduce_scatter */


extern void F77_MPI_IREDUCE_SCATTER(const void  *sendbuf, void  *recvbuf, mpip_const_int_t recvcounts[], MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ireduce_scatter( &jbuf, sendbuf, recvbuf, recvcounts, &c_datatype, &c_op, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ireduce_scatter */



/* --------------- MPI_Ireduce_scatter_block --------------- */

static int mpiPif_MPI_Ireduce_scatter_block( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * recvcount, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ireduce_scatter_block( sendbuf, recvbuf,  * recvcount,  * datatype,  * op,  * comm, request);
void* f=NULL;
QMPI_Table_query( 209, &f, (*vector_get(v,i)).table);
exec_func(f,i,209,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *recvcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ireduce_scatter_block");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ireduce_scatter_block, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Ireduce_scatter_block, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ireduce_scatter_block */



extern int TMPI_Ireduce_scatter_block ( const void* sendbuf, void* recvbuf, int recvcount, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request  ,int i,vector * v )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ireduce_scatter_block( &jbuf, sendbuf, recvbuf,  & recvcount,  & datatype,  & op,  & comm, request ,i,v);

return rc;
} /* MPI_Ireduce_scatter_block */


extern void F77_MPI_IREDUCE_SCATTER_BLOCK(const void  *sendbuf, void  *recvbuf, int  * recvcount, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ireduce_scatter_block( &jbuf, sendbuf, recvbuf, recvcount, &c_datatype, &c_op, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ireduce_scatter_block */



/* --------------- MPI_Irsend --------------- */

static int mpiPif_MPI_Irsend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Irsend( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 210, &f, (*vector_get(v,i)).table);
exec_func(f,i,210,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Irsend");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Irsend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Irsend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Irsend */



extern int TMPI_Irsend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Irsend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Irsend */


extern void F77_MPI_IRSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Irsend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_irsend */



/* --------------- MPI_Iscan --------------- */

static int mpiPif_MPI_Iscan( jmp_buf * base_jbuf, const void  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Iscan( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm, request);
void* f=NULL;
QMPI_Table_query( 212, &f, (*vector_get(v,i)).table);
exec_func(f,i,212,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iscan");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Iscan, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Iscan, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iscan */



extern int TMPI_Iscan ( const void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request *request ,int i,vector * v )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iscan( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm, request ,i,v);

return rc;
} /* MPI_Iscan */


extern void F77_MPI_ISCAN(const void  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iscan( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iscan */



/* --------------- MPI_Iscatter --------------- */

static int mpiPif_MPI_Iscatter( jmp_buf * base_jbuf, const void  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Iscatter( sendbuf,  * sendcount,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * root,  * comm, request);
void* f=NULL;
QMPI_Table_query( 213, &f, (*vector_get(v,i)).table);
exec_func(f,i,213,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iscatter");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Iscatter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Iscatter, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iscatter */



extern int TMPI_Iscatter ( const void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request ,int i,vector * v )
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iscatter( &jbuf, sendbuf,  & sendcount,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & root,  & comm, request ,i,v);

return rc;
} /* MPI_Iscatter */


extern void F77_MPI_ISCATTER(const void  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iscatter( &jbuf, sendbuf, sendcount, &c_sendtype, recvbuf, recvcount, &c_recvtype, root, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iscatter */



/* --------------- MPI_Iscatterv --------------- */

static int mpiPif_MPI_Iscatterv( jmp_buf * base_jbuf, const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t displs[], MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Iscatterv( sendbuf, sendcounts, displs,  * sendtype, recvbuf,  * recvcount,  * recvtype,  * root,  * comm, request);
void* f=NULL;
QMPI_Table_query( 214, &f, (*vector_get(v,i)).table);
exec_func(f,i,214,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { 
  int loc_comm_size, i;
  int loc_sent = 0;

  PMPI_Comm_size(*comm, &loc_comm_size);
  PMPI_Type_size(*sendtype, &tsize);
  for ( i = 0; i<loc_comm_size; i++) 
    loc_sent += sendcounts[i];
  messSize = (double)(tsize * loc_sent);
}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Iscatterv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Iscatterv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Iscatterv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Iscatterv */



extern int TMPI_Iscatterv ( const void* sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t displs[], MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Iscatterv( &jbuf, sendbuf, sendcounts, displs,  & sendtype, recvbuf,  & recvcount,  & recvtype,  & root,  & comm, request ,i,v);

return rc;
} /* MPI_Iscatterv */


extern void F77_MPI_ISCATTERV(const void  *sendbuf, mpip_const_int_t sendcounts[], mpip_const_int_t displs[], MPI_Fint  * sendtype, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;
MPI_Request c_request;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Iscatterv( &jbuf, sendbuf, sendcounts, displs, &c_sendtype, recvbuf, recvcount, &c_recvtype, root, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_iscatterv */



/* --------------- MPI_Isend --------------- */

static int mpiPif_MPI_Isend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Isend( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 215, &f, (*vector_get(v,i)).table);
exec_func(f,i,215,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Isend");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Isend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Isend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Isend */



extern int TMPI_Isend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Isend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Isend */


extern void F77_MPI_ISEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Isend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_isend */



/* --------------- MPI_Issend --------------- */

static int mpiPif_MPI_Issend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Issend( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 216, &f, (*vector_get(v,i)).table);
exec_func(f,i,216,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Issend");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Issend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Issend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Issend */



extern int TMPI_Issend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Issend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Issend */


extern void F77_MPI_ISSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Issend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_issend */



/* --------------- MPI_Keyval_create --------------- */

static int mpiPif_MPI_Keyval_create( jmp_buf * base_jbuf, MPI_Copy_function  *copy_fn, MPI_Delete_function  *delete_fn, int  *keyval, void  *extra_state,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Keyval_create( copy_fn, delete_fn, keyval, extra_state);
void* f=NULL;
QMPI_Table_query( 217, &f, (*vector_get(v,i)).table);
exec_func(f,i,217,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Keyval_create");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Keyval_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Keyval_create */



extern int TMPI_Keyval_create ( MPI_Copy_function *copy_fn, MPI_Delete_function *delete_fn, int *keyval, void *extra_state ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Keyval_create( &jbuf, copy_fn, delete_fn, keyval, extra_state ,i,v);

return rc;
} /* MPI_Keyval_create */


extern void F77_MPI_KEYVAL_CREATE(MPI_Copy_function  *copy_fn, MPI_Delete_function  *delete_fn, int  *keyval, void  *extra_state , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Keyval_create( &jbuf, copy_fn, delete_fn, keyval, extra_state ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_keyval_create */



/* --------------- MPI_Keyval_free --------------- */

static int mpiPif_MPI_Keyval_free( jmp_buf * base_jbuf, int  *keyval,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Keyval_free( keyval);
void* f=NULL;
QMPI_Table_query( 218, &f, (*vector_get(v,i)).table);
exec_func(f,i,218,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Keyval_free");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Keyval_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Keyval_free */



extern int TMPI_Keyval_free ( int *keyval ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Keyval_free( &jbuf, keyval ,i,v);

return rc;
} /* MPI_Keyval_free */


extern void F77_MPI_KEYVAL_FREE(int  *keyval , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Keyval_free( &jbuf, keyval ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_keyval_free */



/* --------------- MPI_Pack --------------- */

static int mpiPif_MPI_Pack( jmp_buf * base_jbuf, mpip_const_void_t  *inbuf, int  * incount, MPI_Datatype  * datatype, void  *outbuf, int  * count, int  *position, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Pack( inbuf,  * incount,  * datatype, outbuf,  * count, position,  * comm);
void* f=NULL;
QMPI_Table_query( 231, &f, (*vector_get(v,i)).table);
exec_func(f,i,231,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Pack");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Pack, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Pack */



extern int TMPI_Pack ( mpip_const_void_t *inbuf, int incount, MPI_Datatype datatype, void *outbuf, int count, int *position, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Pack( &jbuf, inbuf,  & incount,  & datatype, outbuf,  & count, position,  & comm ,i,v);

return rc;
} /* MPI_Pack */


extern void F77_MPI_PACK(mpip_const_void_t  *inbuf, int  * incount, MPI_Fint  * datatype, void  *outbuf, int  * count, int  *position, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Pack( &jbuf, inbuf, incount, &c_datatype, outbuf, count, position, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_pack */



/* --------------- MPI_Probe --------------- */

static int mpiPif_MPI_Probe( jmp_buf * base_jbuf, int  * source, int  * tag, MPI_Comm  * comm, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Probe(  * source,  * tag,  * comm, status);
void* f=NULL;
QMPI_Table_query( 236, &f, (*vector_get(v,i)).table);
exec_func(f,i,236,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Probe");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Probe, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Probe */



extern int TMPI_Probe ( int source, int tag, MPI_Comm comm, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Probe( &jbuf,  & source,  & tag,  & comm, status ,i,v);

return rc;
} /* MPI_Probe */


extern void F77_MPI_PROBE(int  * source, int  * tag, MPI_Fint  * comm, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Probe( &jbuf, source, tag, &c_comm, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_probe */



/* --------------- MPI_Put --------------- */

static int mpiPif_MPI_Put( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Put( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * win);
void* f=NULL;
QMPI_Table_query( 238, &f, (*vector_get(v,i)).table);
exec_func(f,i,238,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*origin_datatype, &tsize);
rmaSize = (double)(tsize * *origin_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Put");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Put, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Put */



extern int TMPI_Put ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Put( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & win ,i,v);

return rc;
} /* MPI_Put */


extern void F77_MPI_PUT(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);

rc = mpiPif_MPI_Put( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_put */



/* --------------- MPI_Raccumulate --------------- */

static int mpiPif_MPI_Raccumulate( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Op  * op, MPI_Win  * win, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Raccumulate( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * op,  * win, request);
void* f=NULL;
QMPI_Table_query( 240, &f, (*vector_get(v,i)).table);
exec_func(f,i,240,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*target_datatype, &tsize);
rmaSize = (double)(tsize * *target_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Raccumulate");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Raccumulate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Raccumulate */



extern int TMPI_Raccumulate ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Raccumulate( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & op,  & win, request ,i,v);

return rc;
} /* MPI_Raccumulate */


extern void F77_MPI_RACCUMULATE(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Fint  * op, MPI_Win  * win, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;
MPI_Op c_op;
MPI_Request c_request;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_op = MPI_Op_f2c(*op);
c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Raccumulate( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, &c_op, win, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_raccumulate */



/* --------------- MPI_Recv --------------- */

static int mpiPif_MPI_Recv( jmp_buf * base_jbuf, void  *buf, int  * count, MPI_Datatype  * datatype, int  * source, int  * tag, MPI_Comm  * comm, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Recv( buf,  * count,  * datatype,  * source,  * tag,  * comm, status);
void* f=NULL;
QMPI_Table_query( 241, &f, (*vector_get(v,i)).table);
exec_func(f,i,241,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Recv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Recv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Recv */



extern int TMPI_Recv ( void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Recv( &jbuf, buf,  & count,  & datatype,  & source,  & tag,  & comm, status ,i,v);

return rc;
} /* MPI_Recv */


extern void F77_MPI_RECV(void  *buf, int  * count, MPI_Fint  * datatype, int  * source, int  * tag, MPI_Fint  * comm, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Recv( &jbuf, buf, count, &c_datatype, source, tag, &c_comm, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_recv */



/* --------------- MPI_Recv_init --------------- */

static int mpiPif_MPI_Recv_init( jmp_buf * base_jbuf, void  *buf, int  * count, MPI_Datatype  * datatype, int  * source, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Recv_init( buf,  * count,  * datatype,  * source,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 242, &f, (*vector_get(v,i)).table);
exec_func(f,i,242,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Recv_init");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Recv_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Recv_init */



extern int TMPI_Recv_init ( void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Recv_init( &jbuf, buf,  & count,  & datatype,  & source,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Recv_init */


extern void F77_MPI_RECV_INIT(void  *buf, int  * count, MPI_Fint  * datatype, int  * source, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Recv_init( &jbuf, buf, count, &c_datatype, source, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_recv_init */



/* --------------- MPI_Reduce --------------- */

static int mpiPif_MPI_Reduce( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, int  * root, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Reduce( sendbuf, recvbuf,  * count,  * datatype,  * op,  * root,  * comm);
void* f=NULL;
QMPI_Table_query( 243, &f, (*vector_get(v,i)).table);
exec_func(f,i,243,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Reduce");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Reduce, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Reduce, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Reduce */



extern int TMPI_Reduce ( mpip_const_void_t *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Reduce( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & root,  & comm ,i,v);

return rc;
} /* MPI_Reduce */


extern void F77_MPI_REDUCE(mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, int  * root, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Reduce( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, root, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_reduce */



/* --------------- MPI_Reduce_scatter --------------- */

static int mpiPif_MPI_Reduce_scatter( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, void  *recvbuf, mpip_const_int_t  *recvcnts, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Reduce_scatter( sendbuf, recvbuf, recvcnts,  * datatype,  * op,  * comm);
void* f=NULL;
QMPI_Table_query( 245, &f, (*vector_get(v,i)).table);
exec_func(f,i,245,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Reduce_scatter");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Reduce_scatter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Reduce_scatter, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Reduce_scatter */



extern int TMPI_Reduce_scatter ( mpip_const_void_t *sendbuf, void *recvbuf, mpip_const_int_t *recvcnts, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Reduce_scatter( &jbuf, sendbuf, recvbuf, recvcnts,  & datatype,  & op,  & comm ,i,v);

return rc;
} /* MPI_Reduce_scatter */


extern void F77_MPI_REDUCE_SCATTER(mpip_const_void_t  *sendbuf, void  *recvbuf, mpip_const_int_t  *recvcnts, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Reduce_scatter( &jbuf, sendbuf, recvbuf, recvcnts, &c_datatype, &c_op, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_reduce_scatter */



/* --------------- MPI_Request_free --------------- */

static int mpiPif_MPI_Request_free( jmp_buf * base_jbuf, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Request_free( request);
void* f=NULL;
QMPI_Table_query( 248, &f, (*vector_get(v,i)).table);
exec_func(f,i,248,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Request_free");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Request_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Request_free */



extern int TMPI_Request_free ( MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Request_free( &jbuf, request ,i,v);

return rc;
} /* MPI_Request_free */


extern void F77_MPI_REQUEST_FREE(MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Request_free( &jbuf, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_request_free */



/* --------------- MPI_Rget --------------- */

static int mpiPif_MPI_Rget( jmp_buf * base_jbuf, void  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Win  * win, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Rget( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * win, request);
void* f=NULL;
QMPI_Table_query( 250, &f, (*vector_get(v,i)).table);
exec_func(f,i,250,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*origin_datatype, &tsize);
rmaSize = (double)(tsize * *origin_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rget");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Rget, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Rget */



extern int TMPI_Rget ( void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rget( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & win, request ,i,v);

return rc;
} /* MPI_Rget */


extern void F77_MPI_RGET(void  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Win  * win, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;
MPI_Request c_request;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Rget( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, win, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_rget */



/* --------------- MPI_Rget_accumulate --------------- */

static int mpiPif_MPI_Rget_accumulate( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, void  *result_addr, int  * result_count, MPI_Datatype  * result_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Op  * op, MPI_Win  * win, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Rget_accumulate( origin_addr,  * origin_count,  * origin_datatype, result_addr,  * result_count,  * result_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * op,  * win, request);
void* f=NULL;
QMPI_Table_query( 251, &f, (*vector_get(v,i)).table);
exec_func(f,i,251,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*target_datatype, &tsize);
rmaSize = (double)(tsize * *target_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rget_accumulate");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Rget_accumulate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Rget_accumulate */



extern int TMPI_Rget_accumulate ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, void *result_addr, int result_count, MPI_Datatype result_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rget_accumulate( &jbuf, origin_addr,  & origin_count,  & origin_datatype, result_addr,  & result_count,  & result_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & op,  & win, request ,i,v);

return rc;
} /* MPI_Rget_accumulate */


extern void F77_MPI_RGET_ACCUMULATE(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, void  *result_addr, int  * result_count, MPI_Fint  * result_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Fint  * op, MPI_Win  * win, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_result_datatype;
MPI_Datatype c_target_datatype;
MPI_Op c_op;
MPI_Request c_request;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_result_datatype = MPI_Type_f2c(*result_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_op = MPI_Op_f2c(*op);
c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Rget_accumulate( &jbuf, origin_addr, origin_count, &c_origin_datatype, result_addr, result_count, &c_result_datatype, target_rank, target_disp, target_count, &c_target_datatype, &c_op, win, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_rget_accumulate */



/* --------------- MPI_Rput --------------- */

static int mpiPif_MPI_Rput( jmp_buf * base_jbuf, mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Datatype  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Datatype  * target_datatype, MPI_Win  * win, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Rput( origin_addr,  * origin_count,  * origin_datatype,  * target_rank,  * target_disp,  * target_count,  * target_datatype,  * win, request);
void* f=NULL;
QMPI_Table_query( 252, &f, (*vector_get(v,i)).table);
exec_func(f,i,252,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

PMPI_Type_size(*origin_datatype, &tsize);
rmaSize = (double)(tsize * *origin_count);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rput");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Rput, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Rput */



extern int TMPI_Rput ( mpip_const_void_t *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rput( &jbuf, origin_addr,  & origin_count,  & origin_datatype,  & target_rank,  & target_disp,  & target_count,  & target_datatype,  & win, request ,i,v);

return rc;
} /* MPI_Rput */


extern void F77_MPI_RPUT(mpip_const_void_t  *origin_addr, int  * origin_count, MPI_Fint  * origin_datatype, int  * target_rank, MPI_Aint  * target_disp, int  * target_count, MPI_Fint  * target_datatype, MPI_Win  * win, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_origin_datatype;
MPI_Datatype c_target_datatype;
MPI_Request c_request;

c_origin_datatype = MPI_Type_f2c(*origin_datatype);
c_target_datatype = MPI_Type_f2c(*target_datatype);
c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Rput( &jbuf, origin_addr, origin_count, &c_origin_datatype, target_rank, target_disp, target_count, &c_target_datatype, win, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_rput */



/* --------------- MPI_Rsend --------------- */

static int mpiPif_MPI_Rsend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Rsend( buf,  * count,  * datatype,  * dest,  * tag,  * comm);
void* f=NULL;
QMPI_Table_query( 253, &f, (*vector_get(v,i)).table);
exec_func(f,i,253,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rsend");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Rsend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Rsend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Rsend */



extern int TMPI_Rsend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rsend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm ,i,v);

return rc;
} /* MPI_Rsend */


extern void F77_MPI_RSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Rsend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_rsend */



/* --------------- MPI_Rsend_init --------------- */

static int mpiPif_MPI_Rsend_init( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Rsend_init( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 254, &f, (*vector_get(v,i)).table);
exec_func(f,i,254,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Rsend_init");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Rsend_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Rsend_init */



extern int TMPI_Rsend_init ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Rsend_init( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Rsend_init */


extern void F77_MPI_RSEND_INIT(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Rsend_init( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_rsend_init */



/* --------------- MPI_Scan --------------- */

static int mpiPif_MPI_Scan( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Datatype  * datatype, MPI_Op  * op, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Scan( sendbuf, recvbuf,  * count,  * datatype,  * op,  * comm);
void* f=NULL;
QMPI_Table_query( 255, &f, (*vector_get(v,i)).table);
exec_func(f,i,255,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Scan");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Scan, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Scan */



extern int TMPI_Scan ( mpip_const_void_t *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Scan( &jbuf, sendbuf, recvbuf,  & count,  & datatype,  & op,  & comm ,i,v);

return rc;
} /* MPI_Scan */


extern void F77_MPI_SCAN(mpip_const_void_t  *sendbuf, void  *recvbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * op, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Op c_op;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_op = MPI_Op_f2c(*op);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Scan( &jbuf, sendbuf, recvbuf, count, &c_datatype, &c_op, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_scan */



/* --------------- MPI_Scatter --------------- */

static int mpiPif_MPI_Scatter( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Scatter( sendbuf,  * sendcnt,  * sendtype, recvbuf,  * recvcnt,  * recvtype,  * root,  * comm);
void* f=NULL;
QMPI_Table_query( 256, &f, (*vector_get(v,i)).table);
exec_func(f,i,256,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcnt);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Scatter");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Scatter, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Scatter, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Scatter */



extern int TMPI_Scatter ( mpip_const_void_t *sendbuf, int sendcnt, MPI_Datatype sendtype, void *recvbuf, int recvcnt, MPI_Datatype recvtype, int root, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Scatter( &jbuf, sendbuf,  & sendcnt,  & sendtype, recvbuf,  & recvcnt,  & recvtype,  & root,  & comm ,i,v);

return rc;
} /* MPI_Scatter */


extern void F77_MPI_SCATTER(mpip_const_void_t  *sendbuf, int  * sendcnt, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Scatter( &jbuf, sendbuf, sendcnt, &c_sendtype, recvbuf, recvcnt, &c_recvtype, root, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_scatter */



/* --------------- MPI_Scatterv --------------- */

static int mpiPif_MPI_Scatterv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, mpip_const_int_t  *sendcnts, mpip_const_int_t  *displs, MPI_Datatype  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Datatype  * recvtype, int  * root, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Scatterv( sendbuf, sendcnts, displs,  * sendtype, recvbuf,  * recvcnt,  * recvtype,  * root,  * comm);
void* f=NULL;
QMPI_Table_query( 257, &f, (*vector_get(v,i)).table);
exec_func(f,i,257,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Scatterv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Scatterv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_collective_stats_report) { mpiPi_update_collective_stats(mpiPi_MPI_Scatterv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Scatterv */



extern int TMPI_Scatterv ( mpip_const_void_t *sendbuf, mpip_const_int_t *sendcnts, mpip_const_int_t *displs, MPI_Datatype sendtype, void *recvbuf, int recvcnt, MPI_Datatype recvtype, int root, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Scatterv( &jbuf, sendbuf, sendcnts, displs,  & sendtype, recvbuf,  & recvcnt,  & recvtype,  & root,  & comm ,i,v);

return rc;
} /* MPI_Scatterv */


extern void F77_MPI_SCATTERV(mpip_const_void_t  *sendbuf, mpip_const_int_t  *sendcnts, mpip_const_int_t  *displs, MPI_Fint  * sendtype, void  *recvbuf, int  * recvcnt, MPI_Fint  * recvtype, int  * root, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Scatterv( &jbuf, sendbuf, sendcnts, displs, &c_sendtype, recvbuf, recvcnt, &c_recvtype, root, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_scatterv */



/* --------------- MPI_Send --------------- */

static int mpiPif_MPI_Send( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Send( buf,  * count,  * datatype,  * dest,  * tag,  * comm);
void* f=NULL;
QMPI_Table_query( 258, &f, (*vector_get(v,i)).table);
exec_func(f,i,258,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Send");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Send, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Send, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Send */



extern int TMPI_Send ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Send( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm ,i,v);

return rc;
} /* MPI_Send */


extern void F77_MPI_SEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Send( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_send */



/* --------------- MPI_Send_init --------------- */

static int mpiPif_MPI_Send_init( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Send_init( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 259, &f, (*vector_get(v,i)).table);
exec_func(f,i,259,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Send_init");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Send_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Send_init */



extern int TMPI_Send_init ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Send_init( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Send_init */


extern void F77_MPI_SEND_INIT(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Send_init( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_send_init */



/* --------------- MPI_Sendrecv --------------- */

static int mpiPif_MPI_Sendrecv( jmp_buf * base_jbuf, mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Datatype  * sendtype, int  * dest, int  * sendtag, void  *recvbuf, int  * recvcount, MPI_Datatype  * recvtype, int  * source, int  * recvtag, MPI_Comm  * comm, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Sendrecv( sendbuf,  * sendcount,  * sendtype,  * dest,  * sendtag, recvbuf,  * recvcount,  * recvtype,  * source,  * recvtag,  * comm, status);
void* f=NULL;
QMPI_Table_query( 260, &f, (*vector_get(v,i)).table);
exec_func(f,i,260,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *sendtype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*sendtype, &tsize);
messSize = (double)(tsize * *sendcount);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Sendrecv");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Sendrecv, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Sendrecv, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Sendrecv */



extern int TMPI_Sendrecv ( mpip_const_void_t *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Sendrecv( &jbuf, sendbuf,  & sendcount,  & sendtype,  & dest,  & sendtag, recvbuf,  & recvcount,  & recvtype,  & source,  & recvtag,  & comm, status ,i,v);

return rc;
} /* MPI_Sendrecv */


extern void F77_MPI_SENDRECV(mpip_const_void_t  *sendbuf, int  * sendcount, MPI_Fint  * sendtype, int  * dest, int  * sendtag, void  *recvbuf, int  * recvcount, MPI_Fint  * recvtype, int  * source, int  * recvtag, MPI_Fint  * comm, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_sendtype;
MPI_Datatype c_recvtype;
MPI_Comm c_comm;

c_sendtype = MPI_Type_f2c(*sendtype);
c_recvtype = MPI_Type_f2c(*recvtype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Sendrecv( &jbuf, sendbuf, sendcount, &c_sendtype, dest, sendtag, recvbuf, recvcount, &c_recvtype, source, recvtag, &c_comm, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_sendrecv */



/* --------------- MPI_Sendrecv_replace --------------- */

static int mpiPif_MPI_Sendrecv_replace( jmp_buf * base_jbuf, void  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * sendtag, int  * source, int  * recvtag, MPI_Comm  * comm, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Sendrecv_replace( buf,  * count,  * datatype,  * dest,  * sendtag,  * source,  * recvtag,  * comm, status);
void* f=NULL;
QMPI_Table_query( 261, &f, (*vector_get(v,i)).table);
exec_func(f,i,261,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Sendrecv_replace");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Sendrecv_replace, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Sendrecv_replace, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Sendrecv_replace */



extern int TMPI_Sendrecv_replace ( void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Sendrecv_replace( &jbuf, buf,  & count,  & datatype,  & dest,  & sendtag,  & source,  & recvtag,  & comm, status ,i,v);

return rc;
} /* MPI_Sendrecv_replace */


extern void F77_MPI_SENDRECV_REPLACE(void  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * sendtag, int  * source, int  * recvtag, MPI_Fint  * comm, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Sendrecv_replace( &jbuf, buf, count, &c_datatype, dest, sendtag, source, recvtag, &c_comm, status ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_sendrecv_replace */



/* --------------- MPI_Ssend --------------- */

static int mpiPif_MPI_Ssend( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ssend( buf,  * count,  * datatype,  * dest,  * tag,  * comm);
void* f=NULL;
QMPI_Table_query( 262, &f, (*vector_get(v,i)).table);
exec_func(f,i,262,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( *datatype != MPI_DATATYPE_NULL ) { PMPI_Type_size(*datatype, &tsize);
messSize = (double)(tsize * *count);}
else { mpiPi_msg_warn("MPI_DATATYPE_NULL encountered.  MPI_IN_PLACE not supported.\n");
mpiPi_msg_warn("Values for %s may be invalid for rank %d.\n", &(__func__)[7], mpiPi.rank);}

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ssend");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ssend, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);

if (mpiPi.do_pt2pt_stats_report) { mpiPi_update_pt2pt_stats(mpiPi_MPI_Ssend, dur, (double)messSize, comm); }
}

return rc;
} /* MPI_Ssend */



extern int TMPI_Ssend ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ssend( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm ,i,v);

return rc;
} /* MPI_Ssend */


extern void F77_MPI_SSEND(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ssend( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_ssend */



/* --------------- MPI_Ssend_init --------------- */

static int mpiPif_MPI_Ssend_init( jmp_buf * base_jbuf, mpip_const_void_t  *buf, int  * count, MPI_Datatype  * datatype, int  * dest, int  * tag, MPI_Comm  * comm, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Ssend_init( buf,  * count,  * datatype,  * dest,  * tag,  * comm, request);
void* f=NULL;
QMPI_Table_query( 263, &f, (*vector_get(v,i)).table);
exec_func(f,i,263,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Ssend_init");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Ssend_init, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Ssend_init */



extern int TMPI_Ssend_init ( mpip_const_void_t *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Ssend_init( &jbuf, buf,  & count,  & datatype,  & dest,  & tag,  & comm, request ,i,v);

return rc;
} /* MPI_Ssend_init */


extern void F77_MPI_SSEND_INIT(mpip_const_void_t  *buf, int  * count, MPI_Fint  * datatype, int  * dest, int  * tag, MPI_Fint  * comm, MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;
MPI_Request c_request;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Ssend_init( &jbuf, buf, count, &c_datatype, dest, tag, &c_comm, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_ssend_init */



/* --------------- MPI_Start --------------- */

static int mpiPif_MPI_Start( jmp_buf * base_jbuf, MPI_Request  *request,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Start( request);
void* f=NULL;
QMPI_Table_query( 264, &f, (*vector_get(v,i)).table);
exec_func(f,i,264,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Start");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Start, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Start */



extern int TMPI_Start ( MPI_Request *request ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Start( &jbuf, request ,i,v);

return rc;
} /* MPI_Start */


extern void F77_MPI_START(MPI_Fint  *request , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Start( &jbuf, &c_request ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_start */



/* --------------- MPI_Startall --------------- */

static int mpiPif_MPI_Startall( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Startall(  * count, array_of_requests);
void* f=NULL;
QMPI_Table_query( 265, &f, (*vector_get(v,i)).table);
exec_func(f,i,265,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Startall");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Startall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Startall */



extern int TMPI_Startall ( int count, MPI_Request *array_of_requests ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Startall( &jbuf,  & count, array_of_requests ,i,v);

return rc;
} /* MPI_Startall */


extern void F77_MPI_STARTALL(int  * count, MPI_Fint  *array_of_requests , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Startall");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Startall( &jbuf, count, c_array_of_requests ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *count; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
}
free(c_array_of_requests);
return;
} /* mpi_startall */



/* --------------- MPI_Test --------------- */

static int mpiPif_MPI_Test( jmp_buf * base_jbuf, MPI_Request  *request, int  *flag, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Test( request, flag, status);
void* f=NULL;
QMPI_Table_query( 269, &f, (*vector_get(v,i)).table);
exec_func(f,i,269,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Test");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Test, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Test */



extern int TMPI_Test ( MPI_Request *request, int *flag, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Test( &jbuf, request, flag, status ,i,v);

return rc;
} /* MPI_Test */


extern void F77_MPI_TEST(MPI_Fint  *request, int  *flag, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Test( &jbuf, &c_request, flag, status ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_test */



/* --------------- MPI_Testall --------------- */

static int mpiPif_MPI_Testall( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests, int  *flag, MPI_Status  *array_of_statuses,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Testall(  * count, array_of_requests, flag, array_of_statuses);
void* f=NULL;
QMPI_Table_query( 271, &f, (*vector_get(v,i)).table);
exec_func(f,i,271,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Testall");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Testall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Testall */



extern int TMPI_Testall ( int count, MPI_Request *array_of_requests, int *flag, MPI_Status *array_of_statuses ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Testall( &jbuf,  & count, array_of_requests, flag, array_of_statuses ,i,v);

return rc;
} /* MPI_Testall */


extern void F77_MPI_TESTALL(int  * count, MPI_Fint  *array_of_requests, int  *flag, MPI_Status  *array_of_statuses , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Testall");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Testall( &jbuf, count, c_array_of_requests, flag, array_of_statuses ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *count; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
}
free(c_array_of_requests);
return;
} /* mpi_testall */



/* --------------- MPI_Testany --------------- */

static int mpiPif_MPI_Testany( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests, int  *index, int  *flag, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Testany(  * count, array_of_requests, index, flag, status);
void* f=NULL;
QMPI_Table_query( 272, &f, (*vector_get(v,i)).table);
exec_func(f,i,272,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Testany");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Testany, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Testany */



extern int TMPI_Testany ( int count, MPI_Request *array_of_requests, int *index, int *flag, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Testany( &jbuf,  & count, array_of_requests, index, flag, status ,i,v);

return rc;
} /* MPI_Testany */


extern void F77_MPI_TESTANY(int  * count, MPI_Fint  *array_of_requests, int  *index, int  *flag, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Testany");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Testany( &jbuf, count, c_array_of_requests, index, flag, status ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
array_of_requests[*index] = MPI_Request_c2f(c_array_of_requests[*index]);
if ( *index >= 0 ) (*index)++;
}
free(c_array_of_requests);
return;
} /* mpi_testany */



/* --------------- MPI_Testsome --------------- */

static int mpiPif_MPI_Testsome( jmp_buf * base_jbuf, int  * incount, MPI_Request  *array_of_requests, int  *count, int  *array_of_indices, MPI_Status  *array_of_statuses,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Testsome(  * incount, array_of_requests, count, array_of_indices, array_of_statuses);
void* f=NULL;
QMPI_Table_query( 273, &f, (*vector_get(v,i)).table);
exec_func(f,i,273,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Testsome");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Testsome, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Testsome */



extern int TMPI_Testsome ( int incount, MPI_Request *array_of_requests, int *count, int *array_of_indices, MPI_Status *array_of_statuses ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Testsome( &jbuf,  & incount, array_of_requests, count, array_of_indices, array_of_statuses ,i,v);

return rc;
} /* MPI_Testsome */


extern void F77_MPI_TESTSOME(int  * incount, MPI_Fint  *array_of_requests, int  *count, int  *array_of_indices, MPI_Status  *array_of_statuses , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*incount));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Testsome");
{
  int i; 
  for (i = 0; i < *incount; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Testsome( &jbuf, incount, c_array_of_requests, count, array_of_indices, array_of_statuses ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *incount; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
{ int i; for ( i = 0; i < *count; i++)  array_of_indices[i]++;}
}
free(c_array_of_requests);
return;
} /* mpi_testsome */



/* --------------- MPI_Topo_test --------------- */

static int mpiPif_MPI_Topo_test( jmp_buf * base_jbuf, MPI_Comm  * comm, int  *top_type,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Topo_test(  * comm, top_type);
void* f=NULL;
QMPI_Table_query( 274, &f, (*vector_get(v,i)).table);
exec_func(f,i,274,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Topo_test");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Topo_test, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Topo_test */



extern int TMPI_Topo_test ( MPI_Comm comm, int *top_type ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Topo_test( &jbuf,  & comm, top_type ,i,v);

return rc;
} /* MPI_Topo_test */


extern void F77_MPI_TOPO_TEST(MPI_Fint  * comm, int  *top_type , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Comm c_comm;

c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Topo_test( &jbuf, &c_comm, top_type ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_topo_test */



/* --------------- MPI_Type_commit --------------- */

static int mpiPif_MPI_Type_commit( jmp_buf * base_jbuf, MPI_Datatype  *datatype,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Type_commit( datatype);
void* f=NULL;
QMPI_Table_query( 275, &f, (*vector_get(v,i)).table);
exec_func(f,i,275,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Type_commit");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Type_commit, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Type_commit */



extern int TMPI_Type_commit ( MPI_Datatype *datatype ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Type_commit( &jbuf, datatype ,i,v);

return rc;
} /* MPI_Type_commit */


extern void F77_MPI_TYPE_COMMIT(MPI_Fint  *datatype , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;

c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Type_commit( &jbuf, &c_datatype ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*datatype = MPI_Type_c2f(c_datatype);
}
return;
} /* mpi_type_commit */



/* --------------- MPI_Type_free --------------- */

static int mpiPif_MPI_Type_free( jmp_buf * base_jbuf, MPI_Datatype  *datatype,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Type_free( datatype);
void* f=NULL;
QMPI_Table_query( 292, &f, (*vector_get(v,i)).table);
exec_func(f,i,292,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Type_free");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Type_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Type_free */



extern int TMPI_Type_free ( MPI_Datatype *datatype ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Type_free( &jbuf, datatype ,i,v);

return rc;
} /* MPI_Type_free */


extern void F77_MPI_TYPE_FREE(MPI_Fint  *datatype , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;

c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Type_free( &jbuf, &c_datatype ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*datatype = MPI_Type_c2f(c_datatype);
}
return;
} /* mpi_type_free */



/* --------------- MPI_Type_get_contents --------------- */

static int mpiPif_MPI_Type_get_contents( jmp_buf * base_jbuf, MPI_Datatype  * datatype, int  * max_integers, int  * max_addresses, int  * max_datatypes, int  *array_of_integers, MPI_Aint  *array_of_addresses, MPI_Datatype  *array_of_datatypes,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Type_get_contents(  * datatype,  * max_integers,  * max_addresses,  * max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);
void* f=NULL;
QMPI_Table_query( 295, &f, (*vector_get(v,i)).table);
exec_func(f,i,295,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Type_get_contents");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Type_get_contents, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Type_get_contents */



extern int TMPI_Type_get_contents ( MPI_Datatype datatype, int max_integers, int max_addresses, int max_datatypes, int *array_of_integers, MPI_Aint *array_of_addresses, MPI_Datatype *array_of_datatypes ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Type_get_contents( &jbuf,  & datatype,  & max_integers,  & max_addresses,  & max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes ,i,v);

return rc;
} /* MPI_Type_get_contents */


extern void F77_MPI_TYPE_GET_CONTENTS(MPI_Fint  * datatype, int  * max_integers, int  * max_addresses, int  * max_datatypes, int  *array_of_integers, MPI_Aint  *array_of_addresses, MPI_Fint  *array_of_datatypes , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Datatype *c_array_of_datatypes;

c_array_of_datatypes = (MPI_Datatype*)malloc(sizeof(MPI_Datatype)*(*max_integers));
if ( c_array_of_datatypes == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Type_get_contents");
c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Type_get_contents( &jbuf, &c_datatype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, c_array_of_datatypes ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *max_integers; i++) { 
    array_of_datatypes[i] = MPI_Type_c2f(c_array_of_datatypes[i]);
  }
}
}
free(c_array_of_datatypes);
return;
} /* mpi_type_get_contents */



/* --------------- MPI_Type_get_envelope --------------- */

static int mpiPif_MPI_Type_get_envelope( jmp_buf * base_jbuf, MPI_Datatype  * datatype, int  *num_integers, int  *num_addresses, int  *num_datatypes, int  *combiner,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Type_get_envelope(  * datatype, num_integers, num_addresses, num_datatypes, combiner);
void* f=NULL;
QMPI_Table_query( 296, &f, (*vector_get(v,i)).table);
exec_func(f,i,296,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Type_get_envelope");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Type_get_envelope, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Type_get_envelope */



extern int TMPI_Type_get_envelope ( MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Type_get_envelope( &jbuf,  & datatype, num_integers, num_addresses, num_datatypes, combiner ,i,v);

return rc;
} /* MPI_Type_get_envelope */


extern void F77_MPI_TYPE_GET_ENVELOPE(MPI_Fint  * datatype, int  *num_integers, int  *num_addresses, int  *num_datatypes, int  *combiner , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;

c_datatype = MPI_Type_f2c(*datatype);

rc = mpiPif_MPI_Type_get_envelope( &jbuf, &c_datatype, num_integers, num_addresses, num_datatypes, combiner ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_type_get_envelope */



/* --------------- MPI_Unpack --------------- */

static int mpiPif_MPI_Unpack( jmp_buf * base_jbuf, mpip_const_void_t  *inbuf, int  * insize, int  *position, void  *outbuf, int  * count, MPI_Datatype  * datatype, MPI_Comm  * comm,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Unpack( inbuf,  * insize, position, outbuf,  * count,  * datatype,  * comm);
void* f=NULL;
QMPI_Table_query( 314, &f, (*vector_get(v,i)).table);
exec_func(f,i,314,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Unpack");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Unpack, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Unpack */



extern int TMPI_Unpack ( mpip_const_void_t *inbuf, int insize, int *position, void *outbuf, int count, MPI_Datatype datatype, MPI_Comm comm ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Unpack( &jbuf, inbuf,  & insize, position, outbuf,  & count,  & datatype,  & comm ,i,v);

return rc;
} /* MPI_Unpack */


extern void F77_MPI_UNPACK(mpip_const_void_t  *inbuf, int  * insize, int  *position, void  *outbuf, int  * count, MPI_Fint  * datatype, MPI_Fint  * comm , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Datatype c_datatype;
MPI_Comm c_comm;

c_datatype = MPI_Type_f2c(*datatype);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Unpack( &jbuf, inbuf, insize, position, outbuf, count, &c_datatype, &c_comm ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_unpack */



/* --------------- MPI_Wait --------------- */

static int mpiPif_MPI_Wait( jmp_buf * base_jbuf, MPI_Request  *request, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Wait( request, status);
void* f=NULL;
QMPI_Table_query( 317, &f, (*vector_get(v,i)).table);
exec_func(f,i,317,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Wait");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Wait, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Wait */



extern int TMPI_Wait ( MPI_Request *request, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Wait( &jbuf, request, status ,i,v);

return rc;
} /* MPI_Wait */


extern void F77_MPI_WAIT(MPI_Fint  *request, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request c_request;

c_request = MPI_Request_f2c(*request);

rc = mpiPif_MPI_Wait( &jbuf, &c_request, status ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
*request = MPI_Request_c2f(c_request);
}
return;
} /* mpi_wait */



/* --------------- MPI_Waitall --------------- */

static int mpiPif_MPI_Waitall( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests, MPI_Status  *array_of_statuses,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Waitall(  * count, array_of_requests, array_of_statuses);
void* f=NULL;
QMPI_Table_query( 318, &f, (*vector_get(v,i)).table);
exec_func(f,i,318,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Waitall");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Waitall, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Waitall */



extern int TMPI_Waitall ( int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Waitall( &jbuf,  & count, array_of_requests, array_of_statuses ,i,v);

return rc;
} /* MPI_Waitall */


extern void F77_MPI_WAITALL(int  * count, MPI_Fint  *array_of_requests, MPI_Status  *array_of_statuses , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Waitall");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Waitall( &jbuf, count, c_array_of_requests, array_of_statuses ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *count; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
}
free(c_array_of_requests);
return;
} /* mpi_waitall */



/* --------------- MPI_Waitany --------------- */

static int mpiPif_MPI_Waitany( jmp_buf * base_jbuf, int  * count, MPI_Request  *array_of_requests, int  *index, MPI_Status  *status,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Waitany(  * count, array_of_requests, index, status);
void* f=NULL;
QMPI_Table_query( 319, &f, (*vector_get(v,i)).table);
exec_func(f,i,319,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Waitany");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Waitany, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Waitany */



extern int TMPI_Waitany ( int count, MPI_Request *array_of_requests, int *index, MPI_Status *status ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Waitany( &jbuf,  & count, array_of_requests, index, status ,i,v);

return rc;
} /* MPI_Waitany */


extern void F77_MPI_WAITANY(int  * count, MPI_Fint  *array_of_requests, int  *index, MPI_Status  *status , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*count));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Waitany");
{
  int i; 
  for (i = 0; i < *count; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Waitany( &jbuf, count, c_array_of_requests, index, status ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
array_of_requests[*index] = MPI_Request_c2f(c_array_of_requests[*index]);
if ( *index >= 0 ) (*index)++;
}
free(c_array_of_requests);
return;
} /* mpi_waitany */



/* --------------- MPI_Waitsome --------------- */

static int mpiPif_MPI_Waitsome( jmp_buf * base_jbuf, int  * incount, MPI_Request  *array_of_requests, int  *count, int  *array_of_indices, MPI_Status  *array_of_statuses,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Waitsome(  * incount, array_of_requests, count, array_of_indices, array_of_statuses);
void* f=NULL;
QMPI_Table_query( 320, &f, (*vector_get(v,i)).table);
exec_func(f,i,320,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Waitsome");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Waitsome, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Waitsome */



extern int TMPI_Waitsome ( int incount, MPI_Request *array_of_requests, int *count, int *array_of_indices, MPI_Status *array_of_statuses ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Waitsome( &jbuf,  & incount, array_of_requests, count, array_of_indices, array_of_statuses ,i,v);

return rc;
} /* MPI_Waitsome */


extern void F77_MPI_WAITSOME(int  * incount, MPI_Fint  *array_of_requests, int  *count, int  *array_of_indices, MPI_Status  *array_of_statuses , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Request *c_array_of_requests;

c_array_of_requests = (MPI_Request*)malloc(sizeof(MPI_Request)*(*incount));
if ( c_array_of_requests == NULL ) mpiPi_abort("Failed to allocate memory in MPI_Waitsome");
{
  int i; 
  for (i = 0; i < *incount; i++) { 
    c_array_of_requests[i] = MPI_Request_f2c(array_of_requests[i]);
  }
}

rc = mpiPif_MPI_Waitsome( &jbuf, incount, c_array_of_requests, count, array_of_indices, array_of_statuses ,i,v);

*ierr = (MPI_Fint)rc;
if ( rc == MPI_SUCCESS ) { 
{
  int i; 
  for (i = 0; i < *incount; i++) { 
    array_of_requests[i] = MPI_Request_c2f(c_array_of_requests[i]);
  }
}
{ int i; for ( i = 0; i < *count; i++)  array_of_indices[i]++;}
}
free(c_array_of_requests);
return;
} /* mpi_waitsome */



/* --------------- MPI_Win_allocate --------------- */

static int mpiPif_MPI_Win_allocate( jmp_buf * base_jbuf, MPI_Aint  * size, int  * disp_unit, MPI_Info  * info, MPI_Comm  * comm, void  *baseptr, MPI_Win  *win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_allocate(  * size,  * disp_unit,  * info,  * comm, baseptr, win);
void* f=NULL;
QMPI_Table_query( 321, &f, (*vector_get(v,i)).table);
exec_func(f,i,321,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_allocate");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_allocate, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_allocate */



extern int TMPI_Win_allocate ( MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_allocate( &jbuf,  & size,  & disp_unit,  & info,  & comm, baseptr, win ,i,v);

return rc;
} /* MPI_Win_allocate */


extern void F77_MPI_WIN_ALLOCATE(MPI_Aint  * size, int  * disp_unit, MPI_Fint  * info, MPI_Fint  * comm, void  *baseptr, MPI_Win  *win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;
MPI_Comm c_comm;

c_info = MPI_Info_f2c(*info);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Win_allocate( &jbuf, size, disp_unit, &c_info, &c_comm, baseptr, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_allocate */



/* --------------- MPI_Win_allocate_shared --------------- */

static int mpiPif_MPI_Win_allocate_shared( jmp_buf * base_jbuf, MPI_Aint  * size, int  * disp_unit, MPI_Info  * info, MPI_Comm  * comm, void  *baseptr, MPI_Win  *win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_allocate_shared(  * size,  * disp_unit,  * info,  * comm, baseptr, win);
void* f=NULL;
QMPI_Table_query( 322, &f, (*vector_get(v,i)).table);
exec_func(f,i,322,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_allocate_shared");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_allocate_shared, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_allocate_shared */



extern int TMPI_Win_allocate_shared ( MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void *baseptr, MPI_Win *win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_allocate_shared( &jbuf,  & size,  & disp_unit,  & info,  & comm, baseptr, win ,i,v);

return rc;
} /* MPI_Win_allocate_shared */


extern void F77_MPI_WIN_ALLOCATE_SHARED(MPI_Aint  * size, int  * disp_unit, MPI_Fint  * info, MPI_Fint  * comm, void  *baseptr, MPI_Win  *win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;
MPI_Comm c_comm;

c_info = MPI_Info_f2c(*info);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Win_allocate_shared( &jbuf, size, disp_unit, &c_info, &c_comm, baseptr, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_allocate_shared */



/* --------------- MPI_Win_attach --------------- */

static int mpiPif_MPI_Win_attach( jmp_buf * base_jbuf, MPI_Win  * win, void  *base, MPI_Aint  * size,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_attach(  * win, base,  * size);
void* f=NULL;
QMPI_Table_query( 323, &f, (*vector_get(v,i)).table);
exec_func(f,i,323,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_attach");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_attach, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_attach */



extern int TMPI_Win_attach ( MPI_Win win, void *base, MPI_Aint size ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_attach( &jbuf,  & win, base,  & size ,i,v);

return rc;
} /* MPI_Win_attach */


extern void F77_MPI_WIN_ATTACH(MPI_Win  * win, void  *base, MPI_Aint  * size , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_attach( &jbuf, win, base, size ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_attach */



/* --------------- MPI_Win_complete --------------- */

static int mpiPif_MPI_Win_complete( jmp_buf * base_jbuf, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_complete(  * win);
void* f=NULL;
QMPI_Table_query( 325, &f, (*vector_get(v,i)).table);
exec_func(f,i,325,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_complete");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_complete, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_complete */



extern int TMPI_Win_complete ( MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_complete( &jbuf,  & win ,i,v);

return rc;
} /* MPI_Win_complete */


extern void F77_MPI_WIN_COMPLETE(MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_complete( &jbuf, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_complete */



/* --------------- MPI_Win_create --------------- */

static int mpiPif_MPI_Win_create( jmp_buf * base_jbuf, void  *base, MPI_Aint  * size, int  * disp_unit, MPI_Info  * info, MPI_Comm  * comm, MPI_Win  *win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_create( base,  * size,  * disp_unit,  * info,  * comm, win);
void* f=NULL;
QMPI_Table_query( 326, &f, (*vector_get(v,i)).table);
exec_func(f,i,326,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_create");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_create, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_create */



extern int TMPI_Win_create ( void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_create( &jbuf, base,  & size,  & disp_unit,  & info,  & comm, win ,i,v);

return rc;
} /* MPI_Win_create */


extern void F77_MPI_WIN_CREATE(void  *base, MPI_Aint  * size, int  * disp_unit, MPI_Fint  * info, MPI_Fint  * comm, MPI_Win  *win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;
MPI_Comm c_comm;

c_info = MPI_Info_f2c(*info);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Win_create( &jbuf, base, size, disp_unit, &c_info, &c_comm, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_create */



/* --------------- MPI_Win_create_dynamic --------------- */

static int mpiPif_MPI_Win_create_dynamic( jmp_buf * base_jbuf, MPI_Info  * info, MPI_Comm  * comm, MPI_Win  *win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_create_dynamic(  * info,  * comm, win);
void* f=NULL;
QMPI_Table_query( 327, &f, (*vector_get(v,i)).table);
exec_func(f,i,327,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_create_dynamic");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_create_dynamic, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_create_dynamic */



extern int TMPI_Win_create_dynamic ( MPI_Info info, MPI_Comm comm, MPI_Win *win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_create_dynamic( &jbuf,  & info,  & comm, win ,i,v);

return rc;
} /* MPI_Win_create_dynamic */


extern void F77_MPI_WIN_CREATE_DYNAMIC(MPI_Fint  * info, MPI_Fint  * comm, MPI_Win  *win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;
MPI_Comm c_comm;

c_info = MPI_Info_f2c(*info);
c_comm = MPI_Comm_f2c(*comm);

rc = mpiPif_MPI_Win_create_dynamic( &jbuf, &c_info, &c_comm, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_create_dynamic */



/* --------------- MPI_Win_detach --------------- */

static int mpiPif_MPI_Win_detach( jmp_buf * base_jbuf, MPI_Win  * win, mpip_const_void_t  *base,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_detach(  * win, base);
void* f=NULL;
QMPI_Table_query( 331, &f, (*vector_get(v,i)).table);
exec_func(f,i,331,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_detach");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_detach, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_detach */



extern int TMPI_Win_detach ( MPI_Win win, mpip_const_void_t *base ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_detach( &jbuf,  & win, base ,i,v);

return rc;
} /* MPI_Win_detach */


extern void F77_MPI_WIN_DETACH(MPI_Win  * win, mpip_const_void_t  *base , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_detach( &jbuf, win, base ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_detach */



/* --------------- MPI_Win_fence --------------- */

static int mpiPif_MPI_Win_fence( jmp_buf * base_jbuf, int  * assert, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_fence(  * assert,  * win);
void* f=NULL;
QMPI_Table_query( 332, &f, (*vector_get(v,i)).table);
exec_func(f,i,332,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_fence");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_fence, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_fence */



extern int TMPI_Win_fence ( int assert, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_fence( &jbuf,  & assert,  & win ,i,v);

return rc;
} /* MPI_Win_fence */


extern void F77_MPI_WIN_FENCE(int  * assert, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_fence( &jbuf, assert, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_fence */



/* --------------- MPI_Win_flush --------------- */

static int mpiPif_MPI_Win_flush( jmp_buf * base_jbuf, int  * rank, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_flush(  * rank,  * win);
void* f=NULL;
QMPI_Table_query( 333, &f, (*vector_get(v,i)).table);
exec_func(f,i,333,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_flush");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_flush, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_flush */



extern int TMPI_Win_flush ( int rank, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_flush( &jbuf,  & rank,  & win ,i,v);

return rc;
} /* MPI_Win_flush */


extern void F77_MPI_WIN_FLUSH(int  * rank, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_flush( &jbuf, rank, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_flush */



/* --------------- MPI_Win_flush_all --------------- */

static int mpiPif_MPI_Win_flush_all( jmp_buf * base_jbuf, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_flush_all(  * win);
void* f=NULL;
QMPI_Table_query( 334, &f, (*vector_get(v,i)).table);
exec_func(f,i,334,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_flush_all");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_flush_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_flush_all */



extern int TMPI_Win_flush_all ( MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_flush_all( &jbuf,  & win ,i,v);

return rc;
} /* MPI_Win_flush_all */


extern void F77_MPI_WIN_FLUSH_ALL(MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_flush_all( &jbuf, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_flush_all */



/* --------------- MPI_Win_flush_local --------------- */

static int mpiPif_MPI_Win_flush_local( jmp_buf * base_jbuf, int  * rank, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_flush_local(  * rank,  * win);
void* f=NULL;
QMPI_Table_query( 335, &f, (*vector_get(v,i)).table);
exec_func(f,i,335,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_flush_local");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_flush_local, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_flush_local */



extern int TMPI_Win_flush_local ( int rank, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_flush_local( &jbuf,  & rank,  & win ,i,v);

return rc;
} /* MPI_Win_flush_local */


extern void F77_MPI_WIN_FLUSH_LOCAL(int  * rank, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_flush_local( &jbuf, rank, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_flush_local */



/* --------------- MPI_Win_flush_local_all --------------- */

static int mpiPif_MPI_Win_flush_local_all( jmp_buf * base_jbuf, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_flush_local_all(  * win);
void* f=NULL;
QMPI_Table_query( 336, &f, (*vector_get(v,i)).table);
exec_func(f,i,336,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_flush_local_all");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_flush_local_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_flush_local_all */



extern int TMPI_Win_flush_local_all ( MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_flush_local_all( &jbuf,  & win ,i,v);

return rc;
} /* MPI_Win_flush_local_all */


extern void F77_MPI_WIN_FLUSH_LOCAL_ALL(MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_flush_local_all( &jbuf, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_flush_local_all */



/* --------------- MPI_Win_free --------------- */

static int mpiPif_MPI_Win_free( jmp_buf * base_jbuf, MPI_Win  *win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_free( win);
void* f=NULL;
QMPI_Table_query( 337, &f, (*vector_get(v,i)).table);
exec_func(f,i,337,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_free");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_free, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_free */



extern int TMPI_Win_free ( MPI_Win *win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_free( &jbuf, win ,i,v);

return rc;
} /* MPI_Win_free */


extern void F77_MPI_WIN_FREE(MPI_Win  *win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_free( &jbuf, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_free */



/* --------------- MPI_Win_get_group --------------- */

static int mpiPif_MPI_Win_get_group( jmp_buf * base_jbuf, MPI_Win  * win, MPI_Group  *group,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_get_group(  * win, group);
void* f=NULL;
QMPI_Table_query( 341, &f, (*vector_get(v,i)).table);
exec_func(f,i,341,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_get_group");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_get_group, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_get_group */



extern int TMPI_Win_get_group ( MPI_Win win, MPI_Group *group ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_get_group( &jbuf,  & win, group ,i,v);

return rc;
} /* MPI_Win_get_group */


extern void F77_MPI_WIN_GET_GROUP(MPI_Win  * win, MPI_Fint  *group , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Win_get_group( &jbuf, win, &c_group ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_get_group */



/* --------------- MPI_Win_get_info --------------- */

static int mpiPif_MPI_Win_get_info( jmp_buf * base_jbuf, MPI_Win  * win, MPI_Info  *info_used,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_get_info(  * win, info_used);
void* f=NULL;
QMPI_Table_query( 342, &f, (*vector_get(v,i)).table);
exec_func(f,i,342,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_get_info");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_get_info, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_get_info */



extern int TMPI_Win_get_info ( MPI_Win win, MPI_Info *info_used ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_get_info( &jbuf,  & win, info_used ,i,v);

return rc;
} /* MPI_Win_get_info */


extern void F77_MPI_WIN_GET_INFO(MPI_Win  * win, MPI_Fint  *info_used , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Info c_info_used;

c_info_used = MPI_Info_f2c(*info_used);

rc = mpiPif_MPI_Win_get_info( &jbuf, win, &c_info_used ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_get_info */



/* --------------- MPI_Win_lock --------------- */

static int mpiPif_MPI_Win_lock( jmp_buf * base_jbuf, int  * lock_type, int  * rank, int  * assert, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_lock(  * lock_type,  * rank,  * assert,  * win);
void* f=NULL;
QMPI_Table_query( 344, &f, (*vector_get(v,i)).table);
exec_func(f,i,344,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_lock");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_lock, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_lock */



extern int TMPI_Win_lock ( int lock_type, int rank, int assert, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_lock( &jbuf,  & lock_type,  & rank,  & assert,  & win ,i,v);

return rc;
} /* MPI_Win_lock */


extern void F77_MPI_WIN_LOCK(int  * lock_type, int  * rank, int  * assert, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_lock( &jbuf, lock_type, rank, assert, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_lock */



/* --------------- MPI_Win_lock_all --------------- */

static int mpiPif_MPI_Win_lock_all( jmp_buf * base_jbuf, int  * assert, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_lock_all(  * assert,  * win);
void* f=NULL;
QMPI_Table_query( 345, &f, (*vector_get(v,i)).table);
exec_func(f,i,345,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_lock_all");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_lock_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_lock_all */



extern int TMPI_Win_lock_all ( int assert, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_lock_all( &jbuf,  & assert,  & win ,i,v);

return rc;
} /* MPI_Win_lock_all */


extern void F77_MPI_WIN_LOCK_ALL(int  * assert, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_lock_all( &jbuf, assert, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_lock_all */



/* --------------- MPI_Win_post --------------- */

static int mpiPif_MPI_Win_post( jmp_buf * base_jbuf, MPI_Group  * group, int  * assert, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_post(  * group,  * assert,  * win);
void* f=NULL;
QMPI_Table_query( 346, &f, (*vector_get(v,i)).table);
exec_func(f,i,346,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_post");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_post, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_post */



extern int TMPI_Win_post ( MPI_Group group, int assert, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_post( &jbuf,  & group,  & assert,  & win ,i,v);

return rc;
} /* MPI_Win_post */


extern void F77_MPI_WIN_POST(MPI_Fint  * group, int  * assert, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Win_post( &jbuf, &c_group, assert, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_post */



/* --------------- MPI_Win_set_info --------------- */

static int mpiPif_MPI_Win_set_info( jmp_buf * base_jbuf, MPI_Win  * win, MPI_Info  * info,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_set_info(  * win,  * info);
void* f=NULL;
QMPI_Table_query( 349, &f, (*vector_get(v,i)).table);
exec_func(f,i,349,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_set_info");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_set_info, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_set_info */



extern int TMPI_Win_set_info ( MPI_Win win, MPI_Info info ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_set_info( &jbuf,  & win,  & info ,i,v);

return rc;
} /* MPI_Win_set_info */


extern void F77_MPI_WIN_SET_INFO(MPI_Win  * win, MPI_Fint  * info , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Info c_info;

c_info = MPI_Info_f2c(*info);

rc = mpiPif_MPI_Win_set_info( &jbuf, win, &c_info ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_set_info */



/* --------------- MPI_Win_shared_query --------------- */

static int mpiPif_MPI_Win_shared_query( jmp_buf * base_jbuf, MPI_Win  * win, int  * rank, MPI_Aint  *size, int  *disp_unit, void  *baseptr,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_shared_query(  * win,  * rank, size, disp_unit, baseptr);
void* f=NULL;
QMPI_Table_query( 351, &f, (*vector_get(v,i)).table);
exec_func(f,i,351,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_shared_query");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_shared_query, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_shared_query */



extern int TMPI_Win_shared_query ( MPI_Win win, int rank, MPI_Aint *size, int *disp_unit, void *baseptr,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_shared_query( &jbuf,  & win,  & rank, size, disp_unit, baseptr ,i,v);

return rc;
} /* MPI_Win_shared_query */


extern void F77_MPI_WIN_SHARED_QUERY(MPI_Win  * win, int  * rank, MPI_Aint  *size, int  *disp_unit, void  *baseptr , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_shared_query( &jbuf, win, rank, size, disp_unit, baseptr ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_shared_query */



/* --------------- MPI_Win_start --------------- */

static int mpiPif_MPI_Win_start( jmp_buf * base_jbuf, MPI_Group  * group, int  * assert, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_start(  * group,  * assert,  * win);
void* f=NULL;
QMPI_Table_query( 352, &f, (*vector_get(v,i)).table);
exec_func(f,i,352,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_start");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_start, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_start */



extern int TMPI_Win_start ( MPI_Group group, int assert, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_start( &jbuf,  & group,  & assert,  & win ,i,v);

return rc;
} /* MPI_Win_start */


extern void F77_MPI_WIN_START(MPI_Fint  * group, int  * assert, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;
MPI_Group c_group;

c_group = MPI_Group_f2c(*group);

rc = mpiPif_MPI_Win_start( &jbuf, &c_group, assert, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_start */



/* --------------- MPI_Win_sync --------------- */

static int mpiPif_MPI_Win_sync( jmp_buf * base_jbuf, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_sync(  * win);
void* f=NULL;
QMPI_Table_query( 353, &f, (*vector_get(v,i)).table);
exec_func(f,i,353,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_sync");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_sync, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_sync */



extern int TMPI_Win_sync ( MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_sync( &jbuf,  & win ,i,v);

return rc;
} /* MPI_Win_sync */


extern void F77_MPI_WIN_SYNC(MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_sync( &jbuf, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_sync */



/* --------------- MPI_Win_test --------------- */

static int mpiPif_MPI_Win_test( jmp_buf * base_jbuf, MPI_Win  * win, int  *flag,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_test(  * win, flag);
void* f=NULL;
QMPI_Table_query( 354, &f, (*vector_get(v,i)).table);
exec_func(f,i,354,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_test");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_test, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_test */



extern int TMPI_Win_test ( MPI_Win win, int *flag,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_test( &jbuf,  & win, flag ,i,v);

return rc;
} /* MPI_Win_test */


extern void F77_MPI_WIN_TEST(MPI_Win  * win, int  *flag , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_test( &jbuf, win, flag ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_test */



/* --------------- MPI_Win_unlock --------------- */

static int mpiPif_MPI_Win_unlock( jmp_buf * base_jbuf, int  * rank, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_unlock(  * rank,  * win);
void* f=NULL;
QMPI_Table_query( 355, &f, (*vector_get(v,i)).table);
exec_func(f,i,355,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_unlock");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_unlock, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_unlock */



extern int TMPI_Win_unlock ( int rank, MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_unlock( &jbuf,  & rank,  & win ,i,v);

return rc;
} /* MPI_Win_unlock */


extern void F77_MPI_WIN_UNLOCK(int  * rank, MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_unlock( &jbuf, rank, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_unlock */



/* --------------- MPI_Win_unlock_all --------------- */

static int mpiPif_MPI_Win_unlock_all( jmp_buf * base_jbuf, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_unlock_all(  * win);
void* f=NULL;
QMPI_Table_query( 356, &f, (*vector_get(v,i)).table);
exec_func(f,i,356,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_unlock_all");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_unlock_all, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_unlock_all */



extern int TMPI_Win_unlock_all ( MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_unlock_all( &jbuf,  & win ,i,v);

return rc;
} /* MPI_Win_unlock_all */


extern void F77_MPI_WIN_UNLOCK_ALL(MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_unlock_all( &jbuf, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_unlock_all */



/* --------------- MPI_Win_wait --------------- */

static int mpiPif_MPI_Win_wait( jmp_buf * base_jbuf, MPI_Win  * win,int i, vector* v)
{
 int rc, enabledState;
 double dur;
 int tsize;
 double messSize = 0.;
 double ioSize = 0.;
 double rmaSize =0.;
 mpiPi_TIME start, end;
 void *call_stack[MPIP_CALLSITE_STACK_DEPTH_MAX] = { NULL };

if (mpiPi.enabled) {
mpiPi_GETTIME (&start);
if ( mpiPi.stackDepth > 0 ) mpiPi_RecordTraceBack((*base_jbuf), call_stack, MPIP_CALLSITE_STACK_DEPTH);
}

enabledState = mpiPi.enabled;
mpiPi.enabled = 0;

//rc = PMPI_Win_wait(  * win);
void* f=NULL;
QMPI_Table_query( 357, &f, (*vector_get(v,i)).table);
exec_func(f,i,357,v);
//CHANGED ABOVE  ---------------------//
mpiPi.enabled = enabledState;
if (mpiPi.enabled) {

mpiPi_GETTIME (&end);
dur = mpiPi_GETTIMEDIFF (&end, &start);

if ( dur < 0 )
  mpiPi_msg_warn("Rank %5d : Negative time difference : %11.9f in %s\n", mpiPi.rank, dur, "MPI_Win_wait");
else
  mpiPi_update_callsite_stats(mpiPi_MPI_Win_wait, mpiPi.rank, call_stack, dur, (double)messSize,(double)ioSize,(double)rmaSize);
}

return rc;
} /* MPI_Win_wait */



extern int TMPI_Win_wait ( MPI_Win win ,int i,vector * v)
{
int rc;
jmp_buf jbuf;

rc = mpiPif_MPI_Win_wait( &jbuf,  & win ,i,v);

return rc;
} /* MPI_Win_wait */


extern void F77_MPI_WIN_WAIT(MPI_Win  * win , MPI_Fint *ierr, int i, vector* v) {
int rc;
jmp_buf jbuf;


rc = mpiPif_MPI_Win_wait( &jbuf, win ,i,v);

*ierr = (MPI_Fint)rc;
return;
} /* mpi_win_wait */


/* eof */
