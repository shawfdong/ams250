  subroutine exchng2(a, sx, ex, sy, ey,  &
                     comm2d, stridetype, &
                     nbrleft, nbrright, nbrtop, nbrbottom )
  use mpi
  integer sx, ex, sy, ey, stridetype
  double precision a(sx-1:ex+1, sy-1:ey+1)
  integer nbrleft, nbrright, nbrtop, nbrbottom, comm2d
  integer ierr, nx
!
  nx = ex - sx + 1
!  These are just like the 1-d versions, except for less data
  call MPI_SENDRECV(a(sx,ey),  nx, MPI_DOUBLE_PRECISION,    &
                    nbrtop, 0,                              &
                    a(sx,sy-1), nx, MPI_DOUBLE_PRECISION,   &
                    nbrbottom, 0, comm2d, MPI_STATUS_IGNORE, ierr)
  call MPI_SENDRECV(a(sx,sy),  nx, MPI_DOUBLE_PRECISION,   &
                    nbrbottom, 1,                          &
                    a(sx,ey+1), nx, MPI_DOUBLE_PRECISION,  &
                    nbrtop, 1, comm2d, MPI_STATUS_IGNORE, ierr)
!
! This uses the vector datatype stridetype
  call MPI_SENDRECV(a(ex,sy),  1, stridetype, nbrright, 0, &
                    a(sx-1,sy), 1, stridetype, nbrleft, 0, &
                    comm2d, MPI_STATUS_IGNORE, ierr)
  call MPI_SENDRECV(a(sx,sy),  1, stridetype, nbrleft,   1,&
                    a(ex+1,sy), 1, stridetype, nbrright, 1,&
                    comm2d, MPI_STATUS_IGNORE, ierr)
  return
  end
