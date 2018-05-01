 subroutine exchng1(a, nx, s, e, win, &
                    bottom_nbr, top_nbr)
 use mpi
 integer nx, s, e, win, bottom_nbr, top_nbr
 double precision a(0:nx+1,s-1:e+1)
 integer ierr
 integer(kind=MPI_ADDRESS_KIND) bottom_ghost_disp, top_ghost_disp

 call MPI_WIN_FENCE(0, win, ierr)
 ! Put bottom edge into bottom neighbor's top ghost cells
 ! See text about top_ghost_disp
 top_ghost_disp = 1 + (nx+2)*(e-s+2)
 call MPI_PUT(a(1,s), nx, MPI_DOUBLE_PRECISION, &
              bottom_nbr, top_ghost_disp, nx, &
              MPI_DOUBLE_PRECISION, win, ierr)
 ! Put top edge into top neighbor's bottom ghost cells
 bottom_ghost_disp = 1
 call MPI_PUT(a(1,e), nx, MPI_DOUBLE_PRECISION, &
              top_nbr, bottom_ghost_disp, nx, &
              MPI_DOUBLE_PRECISION, win, ierr)
 call MPI_WIN_FENCE(0, win, ierr)
 return
 end

