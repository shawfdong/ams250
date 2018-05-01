  subroutine exchng1(a, nx, s, e, comm1d, nbrbottom, nbrtop)
  use mpi
  integer nx, s, e, comm1d, nbrbottom, nbrtop
  double precision a(0:nx+1,s-1:e+1)
  integer ierr

  call MPI_BSEND(a(1,e), nx, MPI_DOUBLE_PRECISION, nbrtop, &
                 0, comm1d, ierr)
  call MPI_RECV(a(1,s-1), nx, MPI_DOUBLE_PRECISION, nbrbottom, &
                0, comm1d, MPI_STATUS_IGNORE, ierr)
  call MPI_BSEND(a(1,s), nx, MPI_DOUBLE_PRECISION, nbrbottom, &
                 1, comm1d, ierr)
  call MPI_RECV(a(1,e+1), nx, MPI_DOUBLE_PRECISION, nbrtop, &
                1, comm1d, MPI_STATUS_IGNORE, ierr)
  return
  end
