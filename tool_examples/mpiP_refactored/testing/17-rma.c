
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define WIN_SIZE 1024
#define TEST_OP !=

int
main (int argc, char **argv)
{
  MPI_Aint win_size = WIN_SIZE;
  MPI_Win win;
  MPI_Group comm_group, group;
  MPI_Request req;
  MPI_Info info;
  char *base, *result;
  int disp_unit = 1;
  int rank, size, target_rank, target_disp = 0;
  int r, i, flag, errlen, *ranks;
  char errmsg[MPI_MAX_ERROR_STRING];

  /*************************************************************/
  /* Init and set values */
  /*************************************************************/
  MPI_Init (&argc, &argv);

  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  target_rank = (rank + 1) % size;
  ranks = (int *) malloc (sizeof (int) * size);

  MPI_Alloc_mem (WIN_SIZE, MPI_INFO_NULL, &base);
  if (NULL == base)
    {
      printf ("failed to alloc %d\n", WIN_SIZE);
      exit (16);
    }

  result = (char *) malloc (WIN_SIZE);
  if (NULL == result)
    {
      printf ("failed to alloc result %d\n", WIN_SIZE);
      exit (16);
    }

  /*************************************************************/
  /* First epoch: Tests Win_create, Put, Get, Accumulate,      */
  /* Get_accumulate                                            */
  /*                                                           */
  /*************************************************************/

  /*************************************************************/
  /* Win_create */
  /*************************************************************/

  r = MPI_Win_create (base, win_size, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);
  if (MPI_SUCCESS TEST_OP r)
    {
      MPI_Error_string (r, errmsg, &errlen);
      printf ("Rank %d failed MPI_Win_create : %s\n", rank, errmsg);
    }

  r = MPI_Win_fence (0, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_fence\n", rank);

  r = MPI_Put (base, WIN_SIZE, MPI_BYTE, target_rank, target_disp,
	       WIN_SIZE, MPI_BYTE, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Put\n", rank);

  r = MPI_Get (base, WIN_SIZE, MPI_BYTE, target_rank, target_disp,
	       WIN_SIZE, MPI_BYTE, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Get\n", rank);

  r =
    MPI_Accumulate (base, WIN_SIZE, MPI_BYTE, target_rank, target_disp,
		    WIN_SIZE, MPI_BYTE, MPI_SUM, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Accumulate\n", rank);

  r =
    MPI_Get_accumulate (base, WIN_SIZE, MPI_BYTE, result, WIN_SIZE, MPI_BYTE,
			target_rank, target_disp, WIN_SIZE, MPI_BYTE, MPI_SUM,
			win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Get_accumulate\n", rank);

  r = MPI_Win_fence (0, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_fence\n", rank);

  r = MPI_Win_free (&win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_free\n", rank);

  //printf ("End of first epoch.\n");


  /*************************************************************/
  /* Second epoch: Tests Post, Start,                          */
  /*              Complete, Wait                               */
  /*************************************************************/

  /* Create rank-specific windows */
  if (rank == 0)
    {
      r =
	MPI_Win_create (base, win_size, 1, MPI_INFO_NULL, MPI_COMM_WORLD,
			&win);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Win_create\n", rank);
    }
  else
    {
      r =
	MPI_Win_create (NULL, 0, sizeof(MPI_INT), MPI_INFO_NULL, MPI_COMM_WORLD,
			&win);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Win_create\n", rank);
    }

  /* Create distinct groups */
  r = MPI_Comm_group (MPI_COMM_WORLD, &comm_group);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Comm_group\n", rank);

  for (i = 0; i < size; i++)
    ranks[i] = i;

  if (rank == 0)
    {
      r = MPI_Group_incl (comm_group, 1, ranks, &group);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Group_incl\n", rank);
    }
  else
    {
      r = MPI_Group_incl (comm_group, size - 1, ranks + 1, &group);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Group_incl\n", rank);
    }

  /*  Communication  */
  if (rank == 0)
    {
      r = MPI_Win_post (group, 0, win);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Win_post\n", rank);
      r = MPI_Win_wait (win);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Win_wait\n", rank);
    }
  else
    {
      r = MPI_Win_start (group, 0, win);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Win_start\n", rank);

      r = MPI_Put (base, WIN_SIZE, MPI_BYTE, 0, target_disp,
		   WIN_SIZE, MPI_BYTE, win);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Put\n", rank);

      r = MPI_Win_complete (win);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Win_complete\n", rank);

    }
  r = MPI_Win_free (&win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_free\n", rank);

  MPI_Group_free (&comm_group);
  MPI_Group_free (&group);
  free (base);

  //printf ("End of second epoch.\n");

  /*************************************************************/
  /* Third epoch: Win_allocate, Win_get_info, Win_set_info, Lock, Unlock, Rput */
  /*************************************************************/
  r =
    MPI_Win_allocate (win_size, 1, MPI_INFO_NULL, MPI_COMM_WORLD, base, &win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_allocate\n", rank);

  r = MPI_Win_get_info (win, &info);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_get_info\n", rank);

  r = MPI_Win_set_info (win, info);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_set_info\n", rank);

  r = MPI_Win_lock (MPI_LOCK_SHARED, target_rank, 0, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_lock\n", rank);

  if (rank == 0)
    {
      r = MPI_Rput (base, WIN_SIZE, MPI_BYTE, target_rank, target_disp,
		   WIN_SIZE, MPI_BYTE, win, &req);
      if (MPI_SUCCESS TEST_OP r)
	printf ("Rank %d failed MPI_Put\n", rank);
    }

  r = MPI_Win_unlock (target_rank, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_unlock\n", rank);

  r = MPI_Win_fence (0, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_fence\n", rank);

  r = MPI_Win_free (&win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_free\n", rank);

  /*************************************************************/
  /* Fourth epoch: Win_create_dynamic, attach, detach */
  /*************************************************************/
  MPI_Alloc_mem (WIN_SIZE, MPI_INFO_NULL, &base);
  if (NULL == base)
    {
      printf ("failed to alloc %d\n", WIN_SIZE);
      exit (16);
    }

  r = MPI_Win_create_dynamic(MPI_INFO_NULL, MPI_COMM_WORLD, &win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_create_dynamic\n", rank);

  r = MPI_Win_attach(win, base, win_size);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_attach\n", rank);

  r = MPI_Win_detach(win, base);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_detach\n", rank);

  r = MPI_Win_attach(win, base, win_size);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_attach\n", rank);

  r = MPI_Win_fence (0, win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_fence\n", rank);

  r = MPI_Win_free (&win);
  if (MPI_SUCCESS TEST_OP r)
    printf ("Rank %d failed MPI_Win_free\n", rank);

  /*************************************************************/
  /* Finalize */
  /*************************************************************/
  free (ranks);

  MPI_Finalize ();
}
