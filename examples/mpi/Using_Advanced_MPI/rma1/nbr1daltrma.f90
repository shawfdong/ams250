 subroutine exchng1(a, nx, s, e, win, &
                    bottom_nbr, top_nbr)
 use mpi
 integer nx, s, e, win, bottom_nbr, top_nbr
 integer (kind=MPI_ADDRESS_KIND) offset
 double precision a(0:nx+1,s-1:e+1)
 integer ierr

 call MPI_WIN_FENCE(0, win, ierr)
 ! Get top edge from top neighbor's cells after the ghost cells
 offset = nx + 3
 call MPI_GET(a(1,e+1), nx, MPI_DOUBLE_PRECISION, top_nbr, &
              offset, nx, MPI_DOUBLE_PRECISION, win, ierr)
 ! Put top edge into top neighbor's ghost cell row
 offset = 1
 call MPI_PUT(a(1,e), nx, MPI_DOUBLE_PRECISION, top_nbr, &
              offset, nx, MPI_DOUBLE_PRECISION, win, ierr)
 call MPI_WIN_FENCE(0, win, ierr)

 return
 end
