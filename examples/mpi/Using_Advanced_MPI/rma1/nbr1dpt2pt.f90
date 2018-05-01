 subroutine exchng1(a, nx, s, e, comm1d, &
                     bottom_nbr, top_nbr)
 use mpi
 integer nx, s, e, comm1d, bottom_nbr, top_nbr
 double precision a(0:nx+1,s-1:e+1)
 integer ierr, req(4)

 call MPI_IRECV (&
      a(1,s-1), nx, MPI_DOUBLE_PRECISION, bottom_nbr, 0, &
      comm1d, req(1), ierr)
 call MPI_ISEND (&
      a(1,e), nx, MPI_DOUBLE_PRECISION, top_nbr, 0, &
      comm1d, req(3), ierr)
 call MPI_IRECV (&
      a(1,e+1), nx, MPI_DOUBLE_PRECISION, top_nbr, 1, &
      comm1d, req(2), ierr)
 call MPI_ISEND (&
      a(1,s), nx, MPI_DOUBLE_PRECISION, bottom_nbr, 1, &
      comm1d, req(4), ierr)

 call MPI_WAITALL (4, req, MPI_STATUSES_IGNORE, ierr)
 return
 end
