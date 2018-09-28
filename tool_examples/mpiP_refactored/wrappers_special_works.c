/* -*- C -*- 

   mpiP MPI Profiler ( http://llnl.github.io/mpiP )

   Please see COPYRIGHT AND LICENSE information at the end of this file.

   ----- 

   wrappers_special.c -- wrappers that demand special attention

 */

#ifndef lint
static char *svnid =
  "$Id$";
#endif

#include "mpiPconfig.h"
#include "mpiPi.h"
#include "symbols.h"
#include "../../src/qmpi.h"
#ifdef ENABLE_FORTRAN_WEAK_SYMS
#include "weak-symbols-special.h"
#endif
#include <string.h>


/* ----- INIT -------------------------------------------------- */

static int mpiPif_MPI_Init (int *argc, char ***argv, int i , vector * v)
{
	//CHANGE BEGIN
	 gst* gs_ptr = (( gst*)((*VECTOR_GET(v,i)).context));
	 printf("(Init)context ptr tool name= %s\n",gs_ptr->mpiPi.toolname );
	  // CHANGE END

  int rc = 0;
  int enabledStatus;

  enabledStatus =  gs_ptr->mpiPi.enabled;
   gs_ptr->mpiPi.enabled = 0;

  //rc = PMPI_Init (argc, argv);
  void* f =NULL;
  QMPI_Table_query(200,&f,(*vector_get(v,i)).table);
  rc = exec_func(f,i,200,v,argc,argv);
  printf("In MPIP Init  !\n");
   gs_ptr->mpiPi.enabled = enabledStatus;

#if defined(Linux) && ! defined(ppc64)
   gs_ptr->mpiPi.appFullName = getProcExeLink (i,v);
  mpiPi_msg_debug (i,v,"appFullName is %s\n",  gs_ptr->mpiPi.appFullName);
  mpiPi_init (GetBaseAppName ( gs_ptr->mpiPi.appFullName)/*,i,v)*/,i,v);
#else
  if (argv != NULL && *argv != NULL && **argv != NULL)
    {
      mpiPi_init (GetBaseAppName (**argv)/*,i,v)*/,i,v);
       gs_ptr->mpiPi.appFullName = strdup (**argv);
    }
  else
    {
      mpiPi_init ("Unknown",i,v);
      mpiPi_msg_debug (i,v,"argv is NULL\n");
    }
#endif

  return rc;
}

extern int
TMPI_Init (int *argc, char ***argv, int i , vector* v)
{
  int rc = 0;

	//CHANGE BEGIN
  /*if( ((*VECTOR_GET(v,i)).context)  == NULL )
  {*/
	  	gst gs ;
		size_t sz =sizeof(gst);
  		QMPI_SET_CONTEXT(v,i,&gs,sz);
  //}
  gst* gs_ptr=(( gst*)((*VECTOR_GET(v,i)).context));
  // CHANGE END

   gs_ptr->mpiPi.toolname = "mpiP";

  rc = mpiPif_MPI_Init (argc, argv,i,v);

  if (argc != NULL && argv != NULL)
    mpiPi_copy_given_args (&( gs_ptr->mpiPi.ac),  gs_ptr->mpiPi.av, 32, *argc, *argv);
  else
    {
#ifdef Linux
      getProcCmdLine (&( gs_ptr->mpiPi.ac),  gs_ptr->mpiPi.av);
#else
       gs_ptr->mpiPi.ac = 0;
#endif
    }

  return rc;
}

extern void
F77_MPI_INIT (int *ierr, int i ,vector* v)
{
	//CHANGE BEGIN
    if( ((*VECTOR_GET(v,i)).context)  == NULL )
    {
    	        gst gs ;
                size_t sz =sizeof(gst);
                QMPI_SET_CONTEXT(v,i,&gs,sz);
    		
    }
    gst* gs_ptr=(( gst*)((*VECTOR_GET(v,i)).context));
    // CHANGE END

  int rc = 0;
  char **tmp_argv;

   gs_ptr->mpiPi.toolname = "mpiP";
#ifdef Linux
  getProcCmdLine (&( gs_ptr->mpiPi.ac),  gs_ptr->mpiPi.av);
#else
  mpiPi_copy_args (&( gs_ptr->mpiPi.ac),  gs_ptr->mpiPi.av, 32);
#endif

  tmp_argv =  gs_ptr->mpiPi.av;
  rc = mpiPif_MPI_Init (&( gs_ptr->mpiPi.ac), (char ***) &tmp_argv,i ,v);
  *ierr = rc;

  return;
}


/* ----- INIT_thread -------------------------------------------------- */

static int
mpiPif_MPI_Init_thread (int *argc, char ***argv, int required, int *provided,int i,vector * v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,i)).context));
	printf("( Init_Thread ) context ptr tool name= %s\n",gs_ptr->mpiPi.toolname );
	 // CHANGE END

  int rc = 0;
  int enabledStatus;

  enabledStatus =  gs_ptr->mpiPi.enabled;
   gs_ptr->mpiPi.enabled = 0;

  //rc = PMPI_Init_thread (argc, argv, required, provided);
  void* f =NULL;
  QMPI_Table_query(201,&f,(*vector_get(v,i)).table);
  rc= exec_func(f,i,201,v,argc, argv, required, provided);
   gs_ptr->mpiPi.enabled = enabledStatus;

#if defined(Linux) && ! defined(ppc64)
   gs_ptr->mpiPi.appFullName = getProcExeLink (i,v);
  mpiPi_msg_debug (i,v,"appFullName is %s\n",  gs_ptr->mpiPi.appFullName);
  mpiPi_init (GetBaseAppName ( gs_ptr->mpiPi.appFullName)/*,i,v)*/,i,v);
#else
  if (argv != NULL && *argv != NULL && **argv != NULL)
    {
      mpiPi_init (GetBaseAppName (**argv)/*,i,v)*/,i,v);
       gs_ptr->mpiPi.appFullName = strdup (**argv);
    }
  else
    {
      mpiPi_init ("Unknown",i,v);
      mpiPi_msg_debug (i,v,"argv is NULL\n");
    }
#endif

  return rc;
}

extern int
TMPI_Init_thread (int *argc, char ***argv, int required, int *provided, int i , vector* v)
{
	//CHANGE BEGIN
    if( ((*VECTOR_GET(v,i)).context)  == NULL )
    {
    		gst gs ;
                size_t sz =sizeof(gst);
                QMPI_SET_CONTEXT(v,i,&gs,sz);
    }
    gst* gs_ptr=(( gst*)((*VECTOR_GET(v,i)).context));
    gs_ptr->mpiPi.toolname = "hello";
    // CHANGE END

  int rc = 0;

   gs_ptr->mpiPi.toolname = "mpiP";

  rc = mpiPif_MPI_Init_thread (argc, argv, required, provided, i,v);

  if (argc != NULL && argv != NULL)
    mpiPi_copy_given_args (&( gs_ptr->mpiPi.ac),  gs_ptr->mpiPi.av, 32, *argc, *argv);
  else
    {
#ifdef Linux
      getProcCmdLine (&( gs_ptr->mpiPi.ac),  gs_ptr->mpiPi.av);
#else
       gs_ptr->mpiPi.ac = 0;
#endif
    }

  return rc;
}

extern void
F77_MPI_INIT_THREAD (int *required, int *provided, int *ierr, int i, vector * v)
{
	//CHANGE BEGIN
    if( ((*VECTOR_GET(v,i)).context)  == NULL )
    {
    	        gst gs ;
                size_t sz =sizeof(gst);
                QMPI_SET_CONTEXT(v,i,&gs,sz);
    
    }
    gst* gs_ptr=(( gst*)((*VECTOR_GET(v,i)).context));
    gs_ptr->mpiPi.toolname = "hello";
    // CHANGE END

  int rc = 0;
  char **tmp_argv;

   gs_ptr->mpiPi.toolname = "mpiP";
#ifdef Linux
  getProcCmdLine (&( gs_ptr->mpiPi.ac),  gs_ptr->mpiPi.av);
#else
  mpiPi_copy_args (&( gs_ptr->mpiPi.ac),  gs_ptr->mpiPi.av, 32);
#endif

  tmp_argv =  gs_ptr->mpiPi.av;
  rc =   mpiPif_MPI_Init_thread (&( gs_ptr->mpiPi.ac), (char ***) &tmp_argv, *required, provided, i, v);
  *ierr = rc;

  return;
}


/* ----- FINALIZE -------------------------------------------------- */

static int
mpiPif_MPI_Finalize (int i, vector* v)
{
	//CHANGE BEGIN
	gst* gs_ptr = (( gst*)((*VECTOR_GET(v,i)).context));
	// CHANGE END

  int rc = 0;

  mpiPi_finalize (i,v);
   gs_ptr->mpiPi.enabled = 0;
  mpiPi_msg_debug (i,v,"calling PMPI_Finalize\n");
  //rc = PMPI_Finalize ();
  void * f=NULL;
  QMPI_Table_query( 138, &f, (*vector_get(v,i)).table);
  rc = exec_func(f,i,138,v);
  printf("In MPIP Finalize  !\n");
  mpiPi_msg_debug (i,v,"returning from PMPI_Finalize\n");

  return rc;
}

extern int
TMPI_Finalize (int i , vector* v)
{
  int rc = 0;

  rc = mpiPif_MPI_Finalize (i,v);

  return rc;
}

extern void
F77_MPI_FINALIZE (int *ierr, int i , vector* v)
{
  int rc = 0;

  rc = mpiPif_MPI_Finalize (i,v);
  *ierr = rc;

  return;
}



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

