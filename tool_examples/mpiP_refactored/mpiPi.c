/* -*- C -*- 

   mpiP MPI Profiler ( http://llnl.github.io/mpiP )

   Please see COPYRIGHT AND LICENSE information at the end of this file.

   ----- 

   mpiPi.c -- main mpiP internal functions

 */

#ifndef lint
static char *svnid = "$Id$";
#endif

#include <string.h>
#include <float.h>
#include <unistd.h>
#include "mpiPi.h"

/*
static 
char *strdup (const char *s)
{
  size_t len = strlen (s) + 1;
  void *new = malloc (len);
  if (new == NULL)
    return NULL;
  return (char *) memcpy (new, s, len);
}
*/
static int
mpiPi_callsite_stats_pc_hashkey (const void *p,int qmpi_lvl,vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int res = 0;
  int i;
  callsite_stats_t *csp = (callsite_stats_t *) p;
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp);
  for (i = 0; i < gs_ptr->mpiPi.stackDepth; i++)
    {
      res ^= (unsigned) (long) csp->pc[i];
    }
  return 52271 ^ csp->op ^ res ^ csp->rank;
}

static int
mpiPi_callsite_stats_pc_comparator (const void *p1, const void *p2,int qmpi_lvl,vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int i;
  callsite_stats_t *csp_1 = (callsite_stats_t *) p1;
  callsite_stats_t *csp_2 = (callsite_stats_t *) p2;
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp_1);
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp_2);

#define express(f) {if ((csp_1->f) > (csp_2->f)) {return 1;} if ((csp_1->f) < (csp_2->f)) {return -1;}}
  express (op);
  express (rank);

  for (i = 0; i < gs_ptr->mpiPi.stackDepth; i++)
    {
      express (pc[i]);
    }
#undef express

  return 0;
}

static int
mpiPi_callsite_stats_src_hashkey (const void *p,int qmpi_lvl,vector* v)
{
  int res = 0;
  callsite_stats_t *csp = (callsite_stats_t *) p;
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp);
  return 52271 ^ csp->op ^ res ^ csp->rank ^ csp->csid;
}

static int
mpiPi_callsite_stats_src_comparator (const void *p1, const void *p2,int qmpi_lvl,vector* v)
{
  callsite_stats_t *csp_1 = (callsite_stats_t *) p1;
  callsite_stats_t *csp_2 = (callsite_stats_t *) p2;
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp_1);
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp_2);

#define express(f) {if ((csp_1->f) > (csp_2->f)) {return 1;} if ((csp_1->f) < (csp_2->f)) {return -1;}}
  express (op);
  express (csid);
  express (rank);
#undef express

  return 0;
}

static int
mpiPi_callsite_stats_MPI_id_hashkey (const void *p,int qmpi_lvl,vector* v)
{
  callsite_stats_t *csp = (callsite_stats_t *) p;
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp);
  return 52271 ^ csp->op;
}

static int
mpiPi_callsite_stats_src_id_hashkey (const void *p,int qmpi_lvl,vector* v)
{
  int res = 0;
  callsite_stats_t *csp = (callsite_stats_t *) p;
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp);
  return 52271 ^ csp->op ^ res ^ csp->csid;
}

static int
mpiPi_callsite_stats_src_id_comparator (const void *p1, const void *p2,int qmpi_lvl,vector* v)
{
  callsite_stats_t *csp_1 = (callsite_stats_t *) p1;
  callsite_stats_t *csp_2 = (callsite_stats_t *) p2;
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp_1);
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp_2);

#define express(f) {if ((csp_1->f) > (csp_2->f)) {return 1;} if ((csp_1->f) < (csp_2->f)) {return -1;}}
  express (op);
  express (csid);
#undef express

  return 0;
}

#ifndef ENABLE_API_ONLY		/* { */
/* task level init 
   - executed by each MPI task only once immediately after MPI_Init
*/

void
init_histogram (mpiPi_histogram_t * h, int first_bin_max, int size,
		int *intervals)
{
  h->first_bin_max = first_bin_max;
  h->hist_size = size;
  h->bin_intervals = intervals;
}


void
mpiPi_init (char *appName, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  if (time (&gs_ptr->mpiPi.start_timeofday) == (time_t) - 1)
    {
      mpiPi_msg_warn (qmpi_lvl,v,"Could not get time of day from time()\n");
    }

  gs_ptr->mpiPi.toolname = "mpiP";
  gs_ptr->mpiPi.comm = MPI_COMM_WORLD;
  gs_ptr->mpiPi.tag = 9821;
  gs_ptr->mpiPi.procID = getpid ();
  gs_ptr->mpiPi.appName = strdup (appName);
  PMPI_Comm_rank (gs_ptr->mpiPi.comm, &gs_ptr->mpiPi.rank);
  PMPI_Comm_size (gs_ptr->mpiPi.comm, &gs_ptr->mpiPi.size);
  PMPI_Get_processor_name (gs_ptr->mpiPi.hostname, &gs_ptr->mpiPi.hostnamelen);
  gs_ptr->mpiPi.stdout_ = stdout;
  gs_ptr->mpiPi.stderr_ = stderr;
  gs_ptr->mpiPi.lookup = mpiPi_lookup;

  gs_ptr->mpiPi.enabled = 1;
  gs_ptr->mpiPi.enabledCount = 1;
  gs_ptr->mpiPi.cumulativeTime = 0.0;
  gs_ptr->mpiPi.global_app_time = 0.0;
  gs_ptr->mpiPi.global_mpi_time = 0.0;
  gs_ptr->mpiPi.global_mpi_size = 0.0;
  gs_ptr->mpiPi.global_mpi_io = 0.0;
  gs_ptr->mpiPi.global_mpi_rma = 0.0;
  gs_ptr->mpiPi.global_mpi_msize_threshold_count = 0;
  gs_ptr->mpiPi.global_mpi_sent_count = 0;
  gs_ptr->mpiPi.global_time_callsite_count = 0;
  gs_ptr->mpiPi.global_task_hostnames = NULL;
  gs_ptr->mpiPi.global_task_app_time = NULL;
  gs_ptr->mpiPi.global_task_mpi_time = NULL;

  /* set some defaults values */
  gs_ptr->mpiPi.collectorRank = 0;
  gs_ptr->mpiPi.tableSize = 256;
  gs_ptr->mpiPi.reportPrintThreshold = 0.0;
  gs_ptr->mpiPi.baseNames = 0;
  gs_ptr->mpiPi.reportFormat = MPIP_REPORT_SCI_FORMAT;
  gs_ptr->mpiPi.calcCOV = 1;
  gs_ptr->mpiPi.inAPIrtb = 0;
  gs_ptr->mpiPi.do_lookup = 1;
  gs_ptr->mpiPi.messageCountThreshold = -1;

  if (DEFAULT_REPORT_FORMAT == mpiPi_style_concise)
    {
      gs_ptr->mpiPi.report_style = mpiPi_style_concise;
      gs_ptr->mpiPi.stackDepth = 0;
      gs_ptr->mpiPi.print_callsite_detail = 0;
    }
  else				// verbose default
    {
      gs_ptr->mpiPi.report_style = mpiPi_style_verbose;
      gs_ptr->mpiPi.stackDepth = 1;
      gs_ptr->mpiPi.print_callsite_detail = 1;
    }

#ifdef COLLECTIVE_REPORT_DEFAULT
  gs_ptr->mpiPi.collective_report = 1;
#else
  gs_ptr->mpiPi.collective_report = 0;
#endif
  gs_ptr->mpiPi.disable_finalize_report = 0;
  gs_ptr->mpiPi.do_collective_stats_report = 0;
  gs_ptr->mpiPi.do_pt2pt_stats_report = 0;
#ifdef SO_LOOKUP
  gs_ptr->mpiPi.so_info = NULL;
#endif
  mpiPi_getenv (qmpi_lvl,v);

  gs_ptr->mpiPi.task_callsite_stats =
    h_open (gs_ptr->mpiPi.tableSize, mpiPi_callsite_stats_pc_hashkey,
	    mpiPi_callsite_stats_pc_comparator);

  if (gs_ptr->mpiPi.do_collective_stats_report == 1)
    {
      init_histogram (&gs_ptr->mpiPi.coll_comm_histogram, 7, 32, NULL);
      init_histogram (&gs_ptr->mpiPi.coll_size_histogram, 7, 32, NULL);
    }

  if (gs_ptr->mpiPi.do_pt2pt_stats_report == 1)
    {
      init_histogram (&gs_ptr->mpiPi.pt2pt_comm_histogram, 7, 32, NULL);
      init_histogram (&gs_ptr->mpiPi.pt2pt_size_histogram, 7, 32, NULL);
    }

  /* -- welcome msg only collector  */
  if (gs_ptr->mpiPi.collectorRank == gs_ptr->mpiPi.rank)
    {
      mpiPi_msg (qmpi_lvl,v,"");
      mpiPi_msg (qmpi_lvl,v,"%s V%d.%d.%d (Build %s/%s)\n", gs_ptr->mpiPi.toolname, mpiPi_vmajor,
		 mpiPi_vminor, mpiPi_vpatch, mpiPi_vdate, mpiPi_vtime);
      mpiPi_msg (qmpi_lvl,v,"Direct questions and errors to %s\n", MPIP_HELP_LIST);
      mpiPi_msg (qmpi_lvl,v,"\n");
    }

  mpiPi_msg_debug (qmpi_lvl,v,"appName is %s\n", appName);
  mpiPi_msg_debug (qmpi_lvl,v,"sizeof(callsite_stats_t) is %d\n",
		   sizeof (callsite_stats_t));
  mpiPi_msg_debug (qmpi_lvl,v,"successful init on %d, %s\n", gs_ptr->mpiPi.rank, gs_ptr->mpiPi.hostname);

  if (gs_ptr->mpiPi.enabled)
    {
      mpiPi_GETTIME (&gs_ptr->mpiPi.startTime);
    }

  return;
}
#endif /* } ifndef ENABLE_API_ONLY */


typedef struct callsite_cache_entry_t
{
  void *pc;
  char *filename;
  char *functname;
  int line;
}
callsite_pc_cache_entry_t;

h_t *callsite_pc_cache = NULL;      ///// TODO :

static int
callsite_pc_cache_comparator (const void *p1, const void *p2,int qmpi_lvl, vector* v)
{
  callsite_pc_cache_entry_t *cs1 = (callsite_pc_cache_entry_t *) p1;
  callsite_pc_cache_entry_t *cs2 = (callsite_pc_cache_entry_t *) p2;

  if ((long) cs1->pc > (long) cs2->pc)
    {
      return 1;
    }
  if ((long) cs1->pc < (long) cs2->pc)
    {
      return -1;
    }
  return 0;
}

static int
callsite_pc_cache_hashkey (const void *p1,int qmpi_lvl, vector* v)
{
  callsite_pc_cache_entry_t *cs1 = (callsite_pc_cache_entry_t *) p1;
  return 662917 ^ ((long) cs1->pc);
}

int
mpiPi_query_pc ( int qmpi_lvl , vector* v, void *pc, char **filename, char **functname, int *lineno)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int rc = 0;
  callsite_pc_cache_entry_t key;
  callsite_pc_cache_entry_t *csp;
  char addr_buf[24];

  key.pc = pc;
  /* do we have a cache entry for this pc? If so, use entry */
  if (h_search (callsite_pc_cache, &key, (void **) &csp,qmpi_lvl,v) == NULL)
    {
      /* no cache entry: create, lookup, and insert */
      csp =
	(callsite_pc_cache_entry_t *)
	malloc (sizeof (callsite_pc_cache_entry_t));
      csp->pc = pc;
#if defined(ENABLE_BFD) || defined(USE_LIBDWARF)
      if (mpiP_find_src_loc (pc, filename, lineno, functname) == 0)
	{
	  if (*filename == NULL || strcmp (*filename, "??") == 0)
	    *filename = "[unknown]";

	  if (*functname == NULL)
	    *functname = "[unknown]";

	  mpiPi_msg_debug
	    (qmpi_lvl,v,"Successful Source lookup for [%s]: %s, %d, %s\n",
	     mpiP_format_address (pc, addr_buf), *filename, *lineno,
	     *functname);

	  csp->filename = strdup (*filename);
	  csp->functname = strdup (*functname);
	  csp->line = *lineno;
	}
      else
	{
	  mpiPi_msg_debug (qmpi_lvl,v,,"Unsuccessful Source lookup for [%s]\n",
			   mpiP_format_address (pc, addr_buf));
	  csp->filename = strdup ("[unknown]");
	  csp->functname = strdup ("[unknown]");
	  csp->line = 0;
	}
#else /* ! ENABLE_BFD || USE_LIBDWARF */
      csp->filename = strdup ("[unknown]");
      csp->functname = strdup ("[unknown]");
      csp->line = 0;
#endif
      h_insert (callsite_pc_cache, csp,qmpi_lvl,v);
    }

  *filename = csp->filename;
  *functname = csp->functname;
  *lineno = csp->line;

  if (*lineno == 0)
    rc = 1;			/* use this value to indicate a failed lookup */

  return rc;
}


//h_t *callsite_src_id_cache = NULL;
//int callsite_src_id_counter = 1;

static int
callsite_src_id_cache_comparator (const void *p1, const void *p2, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int i;
  callsite_src_id_cache_entry_t *csp_1 = (callsite_src_id_cache_entry_t *) p1;
  callsite_src_id_cache_entry_t *csp_2 = (callsite_src_id_cache_entry_t *) p2;

#define express(f) {if ((csp_1->f) > (csp_2->f)) {return 1;} if ((csp_1->f) < (csp_2->f)) {return -1;}}
  if (gs_ptr->mpiPi.stackDepth == 0)
    {
      express (id);		/* In cases where the call stack depth is 0, the only unique info may be the id */
      return 0;
    }
  else
    {
      for (i = 0; i < gs_ptr->mpiPi.stackDepth; i++)
	{
	  if (csp_1->filename[i] != NULL && csp_2->filename[i] != NULL)
	    {
	      if (strcmp (csp_1->filename[i], csp_2->filename[i]) > 0)
		{
		  return 1;
		}
	      if (strcmp (csp_1->filename[i], csp_2->filename[i]) < 0)
		{
		  return -1;
		}
	      express (line[i]);
	      if (strcmp (csp_1->functname[i], csp_2->functname[i]) > 0)
		{
		  return 1;
		}
	      if (strcmp (csp_1->functname[i], csp_2->functname[i]) < 0)
		{
		  return -1;
		}
	    }

	  express (pc[i]);
	}
    }
#undef express
  return 0;
}

static int
callsite_src_id_cache_hashkey (const void *p1,int qmpi_lvl, vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int i, j;
  int res = 0;
  callsite_src_id_cache_entry_t *cs1 = (callsite_src_id_cache_entry_t *) p1;
  for (i = 0; i < gs_ptr->mpiPi.stackDepth; i++)
    {
      if (cs1->filename[i] != NULL)
	{
	  for (j = 0; cs1->filename[i][j] != '\0'; j++)
	    {
	      res ^= (unsigned) cs1->filename[i][j];
	    }
	  for (j = 0; cs1->functname[i][j] != '\0'; j++)
	    {
	      res ^= (unsigned) cs1->functname[i][j];
	    }
	}
      res ^= cs1->line[i];
    }
  return 662917 ^ res;
}

/* take a callstats record (the pc) and determine src file, line, if
   possible and assign a callsite id.
 */
int
mpiPi_query_src (callsite_stats_t * p, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END
  int i;
  callsite_src_id_cache_entry_t key;
  callsite_src_id_cache_entry_t *csp;
  assert (p);

  /* Because multiple pcs can map to the same source line, we must
     check that mapping here. If we got unknown, then we assign
     different ids */
  bzero (&key, sizeof (callsite_src_id_cache_entry_t));

  for (i = 0; (i < gs_ptr->mpiPi.stackDepth) && (p->pc[i] != NULL); i++)
    {
      if (gs_ptr->mpiPi.do_lookup == 1)
	mpiPi_query_pc (qmpi_lvl,v, p->pc[i], &(p->filename[i]), &(p->functname[i]),&(p->lineno[i]));
      else
	{
	  p->filename[i] = strdup ("[unknown]");
	  p->functname[i] = strdup ("[unknown]");
	  p->lineno[i] = 0;
	}

      key.filename[i] = p->filename[i];
      key.functname[i] = p->functname[i];
      key.line[i] = p->lineno[i];
      key.pc[i] = p->pc[i];
    }

  /* MPI ID is compared when stack depth is 0 */
  key.id = p->op - mpiPi_BASE;

  /* lookup/generate an ID based on the callstack, not just the callsite pc */
  if (h_search (gs_ptr->callsite_src_id_cache, &key, (void **) &csp,qmpi_lvl,v) == NULL)
    {
      /* create a new entry, and assign an id based on callstack */
      csp =
	(callsite_src_id_cache_entry_t *)
	malloc (sizeof (callsite_src_id_cache_entry_t));
      bzero (csp, sizeof (callsite_src_id_cache_entry_t));

      for (i = 0; (i < gs_ptr->mpiPi.stackDepth) && (p->pc[i] != NULL); i++)
	{
	  csp->filename[i] = strdup (key.filename[i]);
	  csp->functname[i] = strdup (key.functname[i]);
	  csp->line[i] = key.line[i];
	  csp->pc[i] = p->pc[i];
	}
      csp->op = p->op;
      if (gs_ptr->mpiPi.stackDepth == 0)
	csp->id = csp->op - mpiPi_BASE;
      else
	csp->id = gs_ptr->callsite_src_id_counter++;
      h_insert (gs_ptr->callsite_src_id_cache, csp,qmpi_lvl,v);
    }

  /* assign ID to this record */
  p->csid = csp->id;

  return p->csid;
}


static void
mpiPi_merge_individual_callsite_records (callsite_stats_t * a,
					 callsite_stats_t * b)
{
  a->count += b->count;
  a->cumulativeTime += b->cumulativeTime;
  assert (a->cumulativeTime >= 0);
  a->cumulativeTimeSquared += b->cumulativeTimeSquared;
  assert (a->cumulativeTimeSquared >= 0);
  a->maxDur = max (a->maxDur, b->maxDur);
  a->minDur = min (a->minDur, b->minDur);
  a->maxDataSent = max (a->maxDataSent, b->maxDataSent);
  a->minDataSent = min (a->minDataSent, b->minDataSent);
  a->cumulativeDataSent += b->cumulativeDataSent;
  a->maxIO = max (a->maxIO, b->maxIO);
  a->minIO = min (a->minIO, b->minIO);
  a->cumulativeIO += b->cumulativeIO;
  a->cumulativeRMA += b->cumulativeRMA;
  a->arbitraryMessageCount += b->arbitraryMessageCount;
}


static int
mpiPi_insert_callsite_records (callsite_stats_t * p, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  callsite_stats_t *csp = NULL;

  mpiPi_query_src (p, qmpi_lvl, v);		/* sets the file/line in p */

  /* If exists, accumulate, otherwise insert. This is
     specifically for optimizations that have multiple PCs for
     one src line. We aggregate across rank after this. 

     The collective_report reporting approach does not aggregate individual 
     process callsite information at the collector process.
   */
  if (gs_ptr->mpiPi.collective_report == 0)
    {
      if (NULL == h_search (gs_ptr->mpiPi.global_callsite_stats, p, (void **) &csp,qmpi_lvl,v))
	{
	  callsite_stats_t *newp = NULL;
	  newp = (callsite_stats_t *) malloc (sizeof (callsite_stats_t));

	  memcpy (newp, p, sizeof (callsite_stats_t));
	  /* insert new record into global */
	  h_insert (gs_ptr->mpiPi.global_callsite_stats, newp,qmpi_lvl,v);
	}
      else
	mpiPi_merge_individual_callsite_records (csp, p);
    }

  /* Collect aggregate callsite summary information indpendent of rank. */
  if (NULL == h_search (gs_ptr->mpiPi.global_callsite_stats_agg, p, (void **) &csp,qmpi_lvl,v))
    {
      callsite_stats_t *newp = NULL;
      newp = (callsite_stats_t *) malloc (sizeof (callsite_stats_t));

      memcpy (newp, p, sizeof (callsite_stats_t));
      newp->rank = -1;

      if (gs_ptr->mpiPi.calcCOV)
	{
	  newp->siteData = (double *) malloc (gs_ptr->mpiPi.size * sizeof (double));
	  newp->siteData[0] = p->cumulativeTime;
	  newp->siteDataIdx = 1;
	}

      /* insert new record into global */
      h_insert (gs_ptr->mpiPi.global_callsite_stats_agg, newp,qmpi_lvl,v);
    }
  else
    {
      mpiPi_merge_individual_callsite_records (csp, p);

      if (gs_ptr->mpiPi.calcCOV)
	{
	  csp->siteData[csp->siteDataIdx] = p->cumulativeTime;
	  csp->siteDataIdx += 1;
	}
    }

  /* Do global accumulation while we are iterating through individual callsites */
  gs_ptr->mpiPi.global_task_mpi_time[p->rank] += p->cumulativeTime;

  gs_ptr->mpiPi.global_mpi_time += p->cumulativeTime;
  assert (gs_ptr->mpiPi.global_mpi_time >= 0);
  gs_ptr->mpiPi.global_mpi_size += p->cumulativeDataSent;
  gs_ptr->mpiPi.global_mpi_io += p->cumulativeIO;
  gs_ptr->mpiPi.global_mpi_rma += p->cumulativeRMA;
  if (p->cumulativeTime > 0)
    gs_ptr->mpiPi.global_time_callsite_count++;

  if (p->cumulativeDataSent > 0)
    {
      gs_ptr->mpiPi.global_mpi_msize_threshold_count += p->arbitraryMessageCount;
      gs_ptr->mpiPi.global_mpi_sent_count += p->count;
    }

  return 1;
}

static int
callsite_sort_by_MPI_op (const void *a, const void *b)
{
  callsite_stats_t **a1 = (callsite_stats_t **) a;
  callsite_stats_t **b1 = (callsite_stats_t **) b;

  /* NOTE: want descending sort, so compares are reveresed */
  if ((*a1)->op < (*b1)->op)
    {
      return 1;
    }
  if ((*a1)->op > (*b1)->op)
    {
      return -1;
    }
  return 0;
}

static int
mpiPi_callsite_stats_op_comparator (const void *p1, const void *p2,int qmpi_lvl, vector *v)
{
  callsite_stats_t *csp_1 = (callsite_stats_t *) p1;
  callsite_stats_t *csp_2 = (callsite_stats_t *) p2;
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp_1);
  MPIP_CALLSITE_STATS_COOKIE_ASSERT (csp_2);

#define express(f) {if ((csp_1->f) > (csp_2->f)) {return 1;} if ((csp_1->f) < (csp_2->f)) {return -1;}}
  express (op);
#undef express

  return 0;
}


/*  Aggregate individual MPI call data by iterating through call sites.  */
static int
mpiPi_insert_MPI_records ( int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  callsite_stats_t *csp = NULL;
  int i, ac;
  callsite_stats_t **av;
  callsite_stats_t *p;

  if (gs_ptr->mpiPi.rank == gs_ptr->mpiPi.collectorRank)
    {
      /*  Open hash table for MPI call data.  */
      gs_ptr->mpiPi.global_MPI_stats_agg = h_open (gs_ptr->mpiPi.tableSize,
					   mpiPi_callsite_stats_MPI_id_hashkey,
					   mpiPi_callsite_stats_op_comparator);

      /*  Get individual call data.  */
      h_gather_data (gs_ptr->mpiPi.global_callsite_stats_agg, &ac, (void ***) &av);

      /*  Sort by MPI op.  */
      qsort (av, ac, sizeof (void *), callsite_sort_by_MPI_op);

      /*  For each call site, add call site info to hash table entry for MPI op, independent of rank.  */
      for (i = 0; i < ac; i++)
	{
	  p = av[i];

	  /* Check if there is already an entry for the MPI op. */
	  if (NULL ==
	      h_search (gs_ptr->mpiPi.global_MPI_stats_agg, p, (void **) &csp,qmpi_lvl,v))
	    {
	      callsite_stats_t *newp = NULL;
	      newp = (callsite_stats_t *) malloc (sizeof (callsite_stats_t));
	      memcpy (newp, p, sizeof (callsite_stats_t));
	      newp->rank = -1;
	      newp->csid = p->op - mpiPi_BASE;

	      /* insert new record into global */
	      h_insert (gs_ptr->mpiPi.global_MPI_stats_agg, newp,qmpi_lvl,v);
	    }
	  else
	    {
	      mpiPi_merge_individual_callsite_records (csp, p);
	    }
	}
    }

  return 1;
}

#ifndef ENABLE_API_ONLY		/* { */

static int
mpiPi_mergeResults ( int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END
  int ac;
  callsite_stats_t **av;
  int totalCount = 0;
  int maxCount = 0;
  int retval = 1, sendval;

  /* gather local task data */
  h_gather_data (gs_ptr->mpiPi.task_callsite_stats, &ac, (void ***) &av);

  /* determine size of space necessary on collector */
  PMPI_Allreduce (&ac, &totalCount, 1, MPI_INT, MPI_SUM, gs_ptr->mpiPi.comm);
  PMPI_Reduce (&ac, &maxCount, 1, MPI_INT, MPI_MAX, gs_ptr->mpiPi.collectorRank,
	       gs_ptr->mpiPi.comm);

  if (totalCount < 1)
    {
      if (gs_ptr->mpiPi.rank == gs_ptr->mpiPi.collectorRank)
	mpiPi_msg_warn
	  (qmpi_lvl,v,"Collector found no records to merge. Omitting report.\n");

      return 0;
    }

  /* gather global data at collector */
  if (gs_ptr->mpiPi.rank == gs_ptr->mpiPi.collectorRank)
    {
      int i;
      int ndx = 0;

#ifdef ENABLE_BFD
      if (gs_ptr->mpiPi.appFullName != NULL)
	{
	  if (open_bfd_executable (gs_ptr->mpiPi.appFullName) == 0)
	    gs_ptr->mpiPi.do_lookup = 0;
	}
#elif defined(USE_LIBDWARF)
      if (gs_ptr->mpiPi.appFullName != NULL)
	{
	  if (open_dwarf_executable (gs_ptr->mpiPi.appFullName) == 0)
	    gs_ptr->mpiPi.do_lookup = 0;
	}
#endif
#if defined(ENABLE_BFD) || defined(USE_LIBDWARF)
      else
	{
	  mpiPi_msg_warn
	    ("Failed to open executable.  The mpiP -x runtime flag may address this issue.\n");
	  gs_ptr->mpiPi.do_lookup = 0;
	}
#endif

      /* Open call site hash tables.  */
      gs_ptr->mpiPi.global_callsite_stats = h_open (gs_ptr->mpiPi.tableSize,
					    mpiPi_callsite_stats_src_hashkey,
					    mpiPi_callsite_stats_src_comparator);
      gs_ptr->mpiPi.global_callsite_stats_agg = h_open (gs_ptr->mpiPi.tableSize,
						mpiPi_callsite_stats_src_id_hashkey,
						mpiPi_callsite_stats_src_id_comparator);
      if (callsite_pc_cache == NULL)
	{
	  callsite_pc_cache = h_open (gs_ptr->mpiPi.tableSize,
				      callsite_pc_cache_hashkey,
				      callsite_pc_cache_comparator);
	}
      if (gs_ptr->callsite_src_id_cache == NULL)
	{
	  gs_ptr->callsite_src_id_cache = h_open ( (gs_ptr->mpiPi).tableSize,
					  callsite_src_id_cache_hashkey,
					  callsite_src_id_cache_comparator);

	}
      /* Try to allocate space for max count of callsite info from all tasks  */
      gs_ptr->mpiPi.rawCallsiteData =
	(callsite_stats_t *) calloc (maxCount, sizeof (callsite_stats_t));
      if (gs_ptr->mpiPi.rawCallsiteData == NULL)
	{
	  mpiPi_msg_warn
	    (qmpi_lvl,v,"Failed to allocate memory to collect callsite info");
	  retval = 0;
	}

      /* Clear global_mpi_time and global_mpi_size before accumulation in mpiPi_insert_callsite_records */
      gs_ptr->mpiPi.global_mpi_time = 0.0;
      gs_ptr->mpiPi.global_mpi_size = 0.0;

      if (retval == 1)
	{
	  /* Insert collector callsite data into global and task-specific hash tables */
	  for (ndx = 0; ndx < ac; ndx++)
	    {
	      mpiPi_insert_callsite_records (av[ndx],qmpi_lvl,v);
	    }
	  ndx = 0;
	  for (i = 1; i < gs_ptr->mpiPi.size; i++)	/* n-1 */
	    {
	      MPI_Status status;
	      int count;
	      int j;

	      /* okay in any order */
	      PMPI_Probe (MPI_ANY_SOURCE, gs_ptr->mpiPi.tag, gs_ptr->mpiPi.comm, &status);
	      PMPI_Get_count (&status, MPI_CHAR, &count);
	      PMPI_Recv (&(gs_ptr->mpiPi.rawCallsiteData[ndx]), count, MPI_CHAR,
			 status.MPI_SOURCE, gs_ptr->mpiPi.tag, gs_ptr->mpiPi.comm, &status);
	      count /= sizeof (callsite_stats_t);


	      for (j = 0; j < count; j++)
		{
		  mpiPi_insert_callsite_records (&(gs_ptr->mpiPi.rawCallsiteData[j]),qmpi_lvl,v);
		}
	    }
	  free (gs_ptr->mpiPi.rawCallsiteData);
	}
    }
  else
    {
      int ndx;
      char *sbuf = (char *) malloc (ac * sizeof (callsite_stats_t));
      for (ndx = 0; ndx < ac; ndx++)
	{
	  bcopy (av[ndx],
		 &(sbuf[ndx * sizeof (callsite_stats_t)]),
		 sizeof (callsite_stats_t));
	}
      PMPI_Send (sbuf, ac * sizeof (callsite_stats_t),
		 MPI_CHAR, gs_ptr->mpiPi.collectorRank, gs_ptr->mpiPi.tag, gs_ptr->mpiPi.comm);
      free (sbuf);
    }
  if (gs_ptr->mpiPi.rank == gs_ptr->mpiPi.collectorRank && retval == 1)
    {
      if (gs_ptr->mpiPi.collective_report == 0)
	mpiPi_msg_debug
	  (qmpi_lvl,v,"MEMORY : Allocated for global_callsite_stats     : %13ld\n",
	   h_count (gs_ptr->mpiPi.global_callsite_stats) * sizeof (callsite_stats_t));
      mpiPi_msg_debug
	(qmpi_lvl,v,"MEMORY : Allocated for global_callsite_stats_agg : %13ld\n",
	 h_count (gs_ptr->mpiPi.global_callsite_stats_agg) * sizeof (callsite_stats_t));

    }

  /* TODO: need to free all these pointers as well. */
  free (av);

  if (gs_ptr->mpiPi.rank == gs_ptr->mpiPi.collectorRank)
    {
      if (gs_ptr->mpiPi.do_lookup == 1)
	{
#ifdef ENABLE_BFD
	  /* clean up */
	  close_bfd_executable ();
#elif defined(USE_LIBDWARF)
	  close_dwarf_executable ();
#endif
	}
    }

  /*  Quadrics MPI does not appear to support MPI_IN_PLACE   */
  sendval = retval;
  PMPI_Allreduce (&sendval, &retval, 1, MPI_INT, MPI_MIN, gs_ptr->mpiPi.comm);
  return retval;
}


static int
mpiPi_mergeCollectiveStats ( int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int matrix_size;
  int all_call_count;
  double *coll_time_results, *coll_time_local;
  int i, x, y, z;

  if (gs_ptr->mpiPi.do_collective_stats_report)
    {
      all_call_count = mpiPi_DEF_END - mpiPi_BASE + 1;
      matrix_size =
	all_call_count * gs_ptr->mpiPi.coll_comm_histogram.hist_size *
	gs_ptr->mpiPi.coll_size_histogram.hist_size;
      mpiPi_msg_debug (qmpi_lvl,v,"matrix_size is %d, histogram data is %d\n",
		       matrix_size, sizeof (gs_ptr->mpiPi.coll_time_stats));
      coll_time_local = (double *) malloc (matrix_size * sizeof (double));
      coll_time_results = (double *) malloc (matrix_size * sizeof (double));

      i = 0;
      for (x = 0; x < mpiPi_DEF_END - mpiPi_BASE; x++)
	for (y = 0; y < 32; y++)
	  for (z = 0; z < 32; z++)
	    coll_time_local[i++] = gs_ptr->mpiPi.coll_time_stats[x][y][z];

      /*  Collect Collective statistic data were used  */
      PMPI_Reduce (coll_time_local, coll_time_results, matrix_size,
		   MPI_DOUBLE, MPI_SUM, gs_ptr->mpiPi.collectorRank, gs_ptr->mpiPi.comm);

      i = 0;
      for (x = 0; x < mpiPi_DEF_END - mpiPi_BASE; x++)
	for (y = 0; y < 32; y++)
	  for (z = 0; z < 32; z++)
	    gs_ptr->mpiPi.coll_time_stats[x][y][z] = coll_time_results[i++];

      free (coll_time_local);
      free (coll_time_results);
    }

  return 1;
}


static int
mpiPi_mergept2ptStats ( int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int matrix_size;
  int all_call_count;
  double *pt2pt_send_results, *pt2pt_send_local;
  int i, x, y, z;

  if (gs_ptr->mpiPi.do_pt2pt_stats_report)
    {
      all_call_count = mpiPi_DEF_END - mpiPi_BASE + 1;
      matrix_size =
	all_call_count * gs_ptr->mpiPi.pt2pt_comm_histogram.hist_size *
	gs_ptr->mpiPi.pt2pt_size_histogram.hist_size;
      mpiPi_msg_debug (qmpi_lvl,v,"matrix_size is %d, histogram data is %d\n",
		       matrix_size, sizeof (gs_ptr->mpiPi.pt2pt_send_stats));
      pt2pt_send_local = (double *) malloc (matrix_size * sizeof (double));
      pt2pt_send_results = (double *) malloc (matrix_size * sizeof (double));

      i = 0;
      for (x = 0; x < mpiPi_DEF_END - mpiPi_BASE; x++)
	for (y = 0; y < 32; y++)
	  for (z = 0; z < 32; z++)
	    pt2pt_send_local[i++] = gs_ptr->mpiPi.pt2pt_send_stats[x][y][z];

      /*  Collect Collective statistic data were used  */
      PMPI_Reduce (pt2pt_send_local, pt2pt_send_results, matrix_size,
		   MPI_DOUBLE, MPI_SUM, gs_ptr->mpiPi.collectorRank, gs_ptr->mpiPi.comm);

      i = 0;
      for (x = 0; x < mpiPi_DEF_END - mpiPi_BASE; x++)
	for (y = 0; y < 32; y++)
	  for (z = 0; z < 32; z++)
	    gs_ptr->mpiPi.pt2pt_send_stats[x][y][z] = pt2pt_send_results[i++];

      free (pt2pt_send_local);
      free (pt2pt_send_results);
    }

  return 1;
}


static void
mpiPi_publishResults (int report_style, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  FILE *fp = NULL;
  static int printCount = 0;

  if (gs_ptr->mpiPi.collectorRank == gs_ptr->mpiPi.rank)
    {

      /* Generate output filename, and open */
      do
	{
	  printCount++;
	  snprintf (gs_ptr->mpiPi.oFilename, 256, "%s/%s.%d.%d.%d.mpiP",
		    gs_ptr->mpiPi.outputDir, gs_ptr->mpiPi.appName, gs_ptr->mpiPi.size, gs_ptr->mpiPi.procID,
		    printCount);
	}
      while (access (gs_ptr->mpiPi.oFilename, F_OK) == 0);

      fp = fopen (gs_ptr->mpiPi.oFilename, "w");

      if (fp == NULL)
	{
	  mpiPi_msg_warn (qmpi_lvl,v,"Could not open [%s], writing to stdout\n",
			  gs_ptr->mpiPi.oFilename);
	  fp = stdout;
	}
      else
	{
	  mpiPi_msg (qmpi_lvl,v,"\n");
	  mpiPi_msg (qmpi_lvl,v,"Storing mpiP output in [%s].\n", gs_ptr->mpiPi.oFilename);
	  mpiPi_msg (qmpi_lvl,v,"\n");
	}
    }
  mpiPi_profile_print (fp, report_style,qmpi_lvl,v);
  PMPI_Barrier (gs_ptr->mpiPi.comm);
  if (fp != stdout && fp != NULL)
    {
      fclose (fp);
    }
}


/*
 * mpiPi_collect_basics() - all tasks send their basic info to the
 * collectorRank.
 */
static void
mpiPi_collect_basics (int report_style, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  mpiPi_msg_debug (qmpi_lvl,v,"Collect Basics\n");

  if (gs_ptr->mpiPi.rank == gs_ptr->mpiPi.collectorRank)
    {
      /* In the case where multiple reports are generated per run,
         only allocate memory for global_task_info once */
      if (gs_ptr->mpiPi.global_task_app_time == NULL)
	{
	  gs_ptr->mpiPi.global_task_app_time =
	    (double *) calloc (gs_ptr->mpiPi.size, sizeof (double));

	  if (gs_ptr->mpiPi.global_task_app_time == NULL)
	    mpiPi_abort
	      (qmpi_lvl,v,"Failed to allocate memory for global_task_app_time");

	  mpiPi_msg_debug
	    (qmpi_lvl,v,"MEMORY : Allocated for global_task_app_time :          %13ld\n",
	     gs_ptr->mpiPi.size * sizeof (double));
	}

      bzero (gs_ptr->mpiPi.global_task_app_time, gs_ptr->mpiPi.size * sizeof (double));

      if (gs_ptr->mpiPi.global_task_mpi_time == NULL)
	{
	  gs_ptr->mpiPi.global_task_mpi_time =
	    (double *) calloc (gs_ptr->mpiPi.size, sizeof (double));

	  if (gs_ptr->mpiPi.global_task_mpi_time == NULL)
	    mpiPi_abort
	      (qmpi_lvl,v,"Failed to allocate memory for global_task_mpi_time");

	  mpiPi_msg_debug
	    (qmpi_lvl,v,"MEMORY : Allocated for global_task_mpi_time :          %13ld\n",
	     gs_ptr->mpiPi.size * sizeof (double));
	}

      bzero (gs_ptr->mpiPi.global_task_mpi_time, gs_ptr->mpiPi.size * sizeof (double));

      //  Only allocate hostname storage if we are doing a verbose report
      if (gs_ptr->mpiPi.global_task_hostnames == NULL
	  && (report_style == mpiPi_style_verbose
	      || report_style == mpiPi_style_both))
	{
	  gs_ptr->mpiPi.global_task_hostnames =
	    (mpiPi_hostname_t *) calloc (gs_ptr->mpiPi.size,
					 sizeof (char) *
					 MPIPI_HOSTNAME_LEN_MAX);

	  if (gs_ptr->mpiPi.global_task_hostnames == NULL)
	    mpiPi_abort
	      (qmpi_lvl,v,"Failed to allocate memory for global_task_hostnames");

	  mpiPi_msg_debug
	    (qmpi_lvl,v,"MEMORY : Allocated for global_task_hostnames :          %13ld\n",
	     gs_ptr->mpiPi.size * sizeof (char) * MPIPI_HOSTNAME_LEN_MAX);
	}

      if (gs_ptr->mpiPi.global_task_hostnames != NULL)
	bzero (gs_ptr->mpiPi.global_task_hostnames,
	       gs_ptr->mpiPi.size * sizeof (char) * MPIPI_HOSTNAME_LEN_MAX);
    }

  PMPI_Gather (&gs_ptr->mpiPi.cumulativeTime, 1, MPI_DOUBLE,
	       gs_ptr->mpiPi.global_task_app_time, 1, MPI_DOUBLE,
	       gs_ptr->mpiPi.collectorRank, gs_ptr->mpiPi.comm);

  if (report_style == mpiPi_style_verbose || report_style == mpiPi_style_both)
    {
      PMPI_Gather (gs_ptr->mpiPi.hostname, MPIPI_HOSTNAME_LEN_MAX, MPI_CHAR,
		   gs_ptr->mpiPi.global_task_hostnames, MPIPI_HOSTNAME_LEN_MAX,
		   MPI_CHAR, gs_ptr->mpiPi.collectorRank, gs_ptr->mpiPi.comm);
    }

  return;
}


void
mpiPi_generateReport (int report_style, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  mpiP_TIMER dur;
  mpiPi_TIME timer_start, timer_end;
  int mergeResult;

  mpiPi_GETTIME (&gs_ptr->mpiPi.endTime);

  if (gs_ptr->mpiPi.enabled)
    {
      dur =
	(mpiPi_GETTIMEDIFF (&gs_ptr->mpiPi.endTime, &gs_ptr->mpiPi.startTime) / 1000000.0);
      gs_ptr->mpiPi.cumulativeTime += dur;
      assert (gs_ptr->mpiPi.cumulativeTime >= 0);
      mpiPi_GETTIME (&gs_ptr->mpiPi.startTime);
    }

  if (time (&gs_ptr->mpiPi.stop_timeofday) == (time_t) - 1)
    {
      mpiPi_msg_warn (qmpi_lvl,v,"Could not get time of day from time()\n");
    }

  /* collect results and publish */
  mpiPi_msg_debug0(qmpi_lvl,v,"starting collect_basics\n");

  mpiPi_GETTIME (&timer_start);
  mpiPi_collect_basics (report_style,qmpi_lvl , v);
  mpiPi_GETTIME (&timer_end);
  dur = (mpiPi_GETTIMEDIFF (&timer_end, &timer_start) / 1000000.0);

  mpiPi_msg_debug0(qmpi_lvl,v,"TIMING : collect_basics_time is %12.6f\n", dur);

  mpiPi_msg_debug0(qmpi_lvl,v,"starting mergeResults\n");

  mpiPi_GETTIME (&timer_start);
  mergeResult = mpiPi_mergeResults (qmpi_lvl , v);
  if (mergeResult == 1 && gs_ptr->mpiPi.stackDepth == 0)
    mergeResult = mpiPi_insert_MPI_records (qmpi_lvl , v);
  if (mergeResult == 1)
    mergeResult = mpiPi_mergeCollectiveStats (qmpi_lvl , v);
  if (mergeResult == 1)
    mergeResult = mpiPi_mergept2ptStats (qmpi_lvl , v);
  mpiPi_GETTIME (&timer_end);
  dur = (mpiPi_GETTIMEDIFF (&timer_end, &timer_start) / 1000000.0);

  mpiPi_msg_debug0(qmpi_lvl,v,"TIMING : merge time is          %12.6f\n", dur);
  mpiPi_msg_debug0(qmpi_lvl,v,"starting publishResults\n");

  if (mergeResult == 1)
    {
      mpiPi_GETTIME (&timer_start);
      if (gs_ptr->mpiPi.report_style == mpiPi_style_both)
	{
	  mpiPi_publishResults (mpiPi_style_concise, qmpi_lvl , v);
	  mpiPi_publishResults (mpiPi_style_verbose, qmpi_lvl , v);
	}
      else
	mpiPi_publishResults (report_style,qmpi_lvl , v);
      mpiPi_GETTIME (&timer_end);
      dur = (mpiPi_GETTIMEDIFF (&timer_end, &timer_start) / 1000000.0);
      mpiPi_msg_debug0(qmpi_lvl,v,"TIMING : publish time is        %12.6f\n", dur);
    }
}


void
mpiPi_finalize ( int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  if (gs_ptr->mpiPi.disable_finalize_report == 0)
    mpiPi_generateReport (gs_ptr->mpiPi.report_style, qmpi_lvl , v);

  /* clean up data structures, etc */
  h_close (gs_ptr->mpiPi.task_callsite_stats);

  if (gs_ptr->mpiPi.global_task_app_time != NULL)
    free (gs_ptr->mpiPi.global_task_app_time);

  if (gs_ptr->mpiPi.global_task_mpi_time != NULL)
    free (gs_ptr->mpiPi.global_task_mpi_time);

  if (gs_ptr->mpiPi.global_task_hostnames != NULL)
    free (gs_ptr->mpiPi.global_task_hostnames);

  /*  Could do a lot of housekeeping before calling PMPI_Finalize()
   *  but is it worth the additional work?
   *  For instance:
   h_gather_data (gs_ptr->mpiPi.global_callsite_stats_agg, &ac, (void ***) &av);
   for (i = 0; (i < 20) && (i < ac); i++)
   {
   if (av[i]->siteData != NULL )
   free (av[i]->siteData);
   }
   */

  return;
}


void
mpiPi_update_callsite_stats (unsigned op, unsigned rank, void **pc,
			     double dur, double sendSize, double ioSize,
			     double rmaSize, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int i;
  callsite_stats_t *csp = NULL;
  callsite_stats_t key;

  if (!gs_ptr->mpiPi.enabled)
    return;

  assert (gs_ptr->mpiPi.task_callsite_stats != NULL);
  assert (dur >= 0);


  key.op = op;
  key.rank = rank;
  key.cookie = MPIP_CALLSITE_STATS_COOKIE;
  for (i = 0; i < gs_ptr->mpiPi.stackDepth; i++)
    {
      key.pc[i] = pc[i];
    }

  if (NULL == h_search (gs_ptr->mpiPi.task_callsite_stats, &key, (void **) &csp,qmpi_lvl,v))
    {
      /* create and insert */
      csp = (callsite_stats_t *) malloc (sizeof (callsite_stats_t));
      bzero (csp, sizeof (callsite_stats_t));
      csp->op = op;
      csp->rank = rank;
      for (i = 0; i < gs_ptr->mpiPi.stackDepth; i++)
	{
	  csp->pc[i] = pc[i];
	}
      csp->cookie = MPIP_CALLSITE_STATS_COOKIE;
      csp->cumulativeTime = 0;
      csp->minDur = DBL_MAX;
      csp->minDataSent = DBL_MAX;
      csp->minIO = DBL_MAX;
      csp->arbitraryMessageCount = 0;
      h_insert (gs_ptr->mpiPi.task_callsite_stats, csp,qmpi_lvl,v);
    }
  /* ASSUME: csp cannot be deleted from list */
  csp->count++;
  csp->cumulativeTime += dur;
  assert (csp->cumulativeTime >= 0);
  csp->cumulativeTimeSquared += (dur * dur);
  assert (csp->cumulativeTimeSquared >= 0);
  csp->maxDur = max (csp->maxDur, dur);
  csp->minDur = min (csp->minDur, dur);
  csp->cumulativeDataSent += sendSize;
  csp->cumulativeIO += ioSize;
  csp->cumulativeRMA += rmaSize;

  csp->maxDataSent = max (csp->maxDataSent, sendSize);
  csp->minDataSent = min (csp->minDataSent, sendSize);

  csp->maxIO = max (csp->maxIO, ioSize);
  csp->minIO = min (csp->minIO, ioSize);

  csp->maxRMA = max (csp->maxRMA, rmaSize);
  csp->minRMA = min (csp->minRMA, rmaSize);

  if (gs_ptr->mpiPi.messageCountThreshold > -1
      && sendSize >= (double) gs_ptr->mpiPi.messageCountThreshold)
    csp->arbitraryMessageCount++;

#if 0
  mpiPi_msg_debug (qmpi_lvl,v,,"gs_ptr->mpiPi.messageCountThreshold is %d\n",
		   gs_ptr->mpiPi.messageCountThreshold);
  mpiPi_msg_debug (qmpi_lvl,v,,"sendSize is %f\n", sendSize);
  mpiPi_msg_debug (qmpi_lvl,v,,"csp->arbitraryMessageCount is %lld\n",
		   csp->arbitraryMessageCount);
#endif

  return;
}


static int
get_histogram_bin (mpiPi_histogram_t * h, int val)
{
  int wv = val;
  int bin;

  bin = 0;

  if (h->bin_intervals == NULL)
    {
      while (wv > h->first_bin_max && bin < h->hist_size)
	{
	  wv >>= 1;
	  bin++;
	}
    }
  else				/* Add code for custom intervals later */
    {
    }

  return bin;
}


void
mpiPi_update_collective_stats (int op, double dur, double size,
			       MPI_Comm * comm, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int op_idx, comm_size, comm_bin, size_bin;

  PMPI_Comm_size (*comm, &comm_size);

  op_idx = op - mpiPi_BASE;

  comm_bin = get_histogram_bin (&gs_ptr->mpiPi.coll_comm_histogram, comm_size);
  size_bin = get_histogram_bin (&gs_ptr->mpiPi.coll_size_histogram, size);

  mpiPi_msg_debug
    (qmpi_lvl,v,"Adding %.0f time to entry mpiPi.collective_stats[%d][%d][%d] value of %.0f\n",
     dur, op_idx, comm_bin, size_bin,
     gs_ptr->mpiPi.coll_time_stats[op_idx][comm_bin][size_bin]);

  gs_ptr->mpiPi.coll_time_stats[op_idx][comm_bin][size_bin] += dur;
}


void
mpiPi_update_pt2pt_stats (int op, double dur, double size, MPI_Comm * comm, int qmpi_lvl , vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,qmpi_lvl)).context));
	// CHANGE END

  int op_idx, comm_size, comm_bin, size_bin;

  PMPI_Comm_size (*comm, &comm_size);

  op_idx = op - mpiPi_BASE;

  comm_bin = get_histogram_bin (&gs_ptr->mpiPi.pt2pt_comm_histogram, comm_size);
  size_bin = get_histogram_bin (&gs_ptr->mpiPi.pt2pt_size_histogram, size);

  mpiPi_msg_debug
    (qmpi_lvl,v,"Adding %.0f send size to entry mpiPi.pt2pt_stats[%d][%d][%d] value of %.0f\n",
     size, op_idx, comm_bin, size_bin,
     gs_ptr->mpiPi.pt2pt_send_stats[op_idx][comm_bin][size_bin]);

  gs_ptr->mpiPi.pt2pt_send_stats[op_idx][comm_bin][size_bin] += size;
}


#endif /* } ifndef ENABLE_API_ONLY */



/* 

<license>

Copyright (c) 2006, The Regents of the University of California. 
Produced at the Lawrence Livermore National Laboratory 
Written by Jeffery Vetter and Christopher Chambreau. 
UCRL-CODE-223450. 
All rights reserved. 
 
This file is part of mpiP.  For details, see http://llnl.github.io/mpiP. 
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
 
* Redistributions of source code must retain the above copyright
notice, this list of conditions and the disclaimer below.

* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the disclaimer (as noted below) in
the documentation and/or other materials provided with the
distribution.

* Neither the name of the UC/LLNL nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OF
THE UNIVERSITY OF CALIFORNIA, THE U.S. DEPARTMENT OF ENERGY OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 
Additional BSD Notice 
 
1. This notice is required to be provided under our contract with the
U.S. Department of Energy (DOE).  This work was produced at the
University of California, Lawrence Livermore National Laboratory under
Contract No. W-7405-ENG-48 with the DOE.
 
2. Neither the United States Government nor the University of
California nor any of their employees, makes any warranty, express or
implied, or assumes any liability or responsibility for the accuracy,
completeness, or usefulness of any information, apparatus, product, or
process disclosed, or represents that its use would not infringe
privately-owned rights.
 
3.  Also, reference herein to any specific commercial products,
process, or services by trade name, trademark, manufacturer or
otherwise does not necessarily constitute or imply its endorsement,
recommendation, or favoring by the United States Government or the
University of California.  The views and opinions of authors expressed
herein do not necessarily state or reflect those of the United States
Government or the University of California, and shall not be used for
advertising or product endorsement purposes.

</license>

*/


/* eof */

