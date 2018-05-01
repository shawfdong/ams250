  ...
  MPI_Win_create_dynamic(MPI_INFO_NULL, MPI_COMM_WORLD, &listwin);

  MPI_Win_create_keyval(MPI_WIN_NULL_COPY_FN,
                        MPI_WIN_NULL_DELETE_FN,
			&MPE_LISTWIN_KEY_RANK, (void*)0);
  MPI_Win_set_attr(listwin, MPE_LISTWIN_KEY_RANK,
                   (void*)(MPI_Aint)wrank);

  headDptr.rank = 0;
  if (wrank == 0) {
    ListElm *headLptr;
    MPI_Alloc_mem(sizeof(ListElm), MPI_INFO_NULL, &headLptr);
    MPI_Get_address(headLptr, &headDptr.disp);
    headLptr->next.rank = -1;
    headLptr->next.disp = (MPI_Aint)MPI_BOTTOM;
    MPI_Win_attach(listwin, headLptr, sizeof(ListElm));
  }
  MPI_Bcast(&headDptr.disp, 1, MPI_AINT, 0, MPI_COMM_WORLD);
