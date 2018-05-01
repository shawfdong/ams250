 integer win, sizedouble, ierr
 integer (kind=MPI_ADDRESS_KIND) right_ghost_disp, &
         left_ghost_disp, top_ghost_disp
 integer (kind=MPI_ADDRESS_KIND) my_right_Ghost_disp, &
         my_left_Ghost_disp, myTopghost_disp
 double precision a(sx-1:ex+1,sy-1:ey+1)

 ! nx is the number of (non-ghost) values in x, ny in y
 nx = ex - sx + 1
 ny = ey - sy + 1
 call MPI_SIZEOF(A(sx-1,sy-1), sizedouble, ierr)
 call MPI_WIN_CREATE(a, (ex-sx+3)*(ey-sy+3)*sizedouble, &
                     sizedouble, MPI_INFO_NULL, MPI_COMM_WORLD, &
                     win, ierr)
 ! Exchange information on the offsets
 ! Compute the displacement into my right ghost cells
 my_right_Ghost_disp = 2*(nx+2)-1
 call MPI_SENDRECV(my_right_Ghost_disp, 1, MPI_AINT, right_nbr, &
                   0, right_ghost_disp, 1, MPI_AINT, left_nbr, &
                   0, MPI_COMM_WORLD, MPI_STATUS_IGNORE, ierr)
 ! Compute the displacement into my top ghost cells
 myTopghost_disp = (nx + 2)*(ny + 1) + 1
 call MPI_SENDRECV(myTopghost_disp, 1, MPI_AINT, top_nbr, 0, &
                   top_ghost_disp, 1, MPI_AINT, bottom_nbr, 0, &
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE, ierr)
 ! Compute the displacement into my left ghost cells
 my_left_Ghost_disp = nx + 2
 call MPI_SENDRECV(my_left_Ghost_disp, 1, MPI_AINT, left_nbr, 0,&
                   left_ghost_disp, 1, MPI_AINT, right_nbr, 0, &
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE, ierr)
 integer coltype, left_coltype, right_coltype

 ! Vector type used on origin
 call MPI_TYPE_VECTOR(1, ny, nx+2, MPI_DOUBLE_PRECISION, &
                      coltype, ierr)
 call MPI_TYPE_COMMIT(coltype, ierr)

 ! Exchange stride information needed to build the left and right
 ! coltypes
 call MPI_SENDRECV(nx, 1, MPI_INTEGER, left_nbr, 2, &
                   right_nx, 1, MPI_INTEGER, right_nbr, 2, &
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE, ierr)
 call MPI_SENDRECV(nx, 1, MPI_INTEGER, right_nbr, 3, &
                   left_nx, 1, MPI_INTEGER, left_nbr, 3, &
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE, ierr)
 call MPI_TYPE_VECTOR(1, ny, left_nx + 2, MPI_DOUBLE_PRECISION, &
                      left_coltype, ierr)
 call MPI_TYPE_COMMIT(left_coltype, ierr)
 call MPI_TYPE_VECTOR(1, ny, right_nx + 2, MPI_DOUBLE_PRECISION, &
                      right_coltype, ierr)
 call MPI_TYPE_COMMIT(right_coltype, ierr)
