call MPI_WIN_FENCE(0, winbuf, ierr)
! Put bottom edge into bottom neighbor's ghost cells
nx = ex - sx + 1
call MPI_PUT(a(sx,sy), nx, MPI_DOUBLE_PRECISION, &
           bottom_nbr, 0, nx, MPI_DOUBLE_PRECISION, winbuf, ierr)
! Put top edge into top neighbor's ghost cells
call MPI_PUT(a(sx,ey), nx, MPI_DOUBLE_PRECISION, &
           top_nbr, nx, nx, MPI_DOUBLE_PRECISION, winbuf, ierr)
! Put left edge into left neighbor's ghost cells
ny = ey - sy + 1
do i=sy,ey
    buf1(i-sy+1) = a(sx,i)
enddo
call MPI_PUT(buf1, ny, MPI_DOUBLE_PRECISION, &
             left_nbr, 2*nx, ny, MPI_DOUBLE_PRECISION, &
             winbuf, ierr)
! Put right edge into right neighbor's ghost cells
do i=sy,ey
    buf2(i-sy+1) = a(ex,i)
enddo
call MPI_PUT(buf2, ny, MPI_DOUBLE_PRECISION, &
             right_nbr, 2*nx+ny, ny, MPI_DOUBLE_PRECISION, &
             winbuf, ierr)
call MPI_WIN_FENCE(0, winbuf, ierr)
! ... use data in aghost ...
