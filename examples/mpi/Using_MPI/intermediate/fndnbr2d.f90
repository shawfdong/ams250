!
! This routine show how to determine the neighbors in a 2-d decomposition of
! the domain. This assumes that MPI_Cart_create has already been called
!
      subroutine fnd2dnbrs( comm2d, &
                            nbrleft, nbrright, nbrtop, nbrbottom )
      integer comm2d, nbrleft, nbrright, nbrtop, nbrbottom
!
      integer ierr
!
      call MPI_Cart_shift( comm2d, 0,  1, nbrleft,   nbrright, ierr )
      call MPI_Cart_shift( comm2d, 1,  1, nbrbottom, nbrtop,   ierr )
!
      return
      end
!
      subroutine fnd2ddecomp( comm2d, n, sx, ex, sy, ey )
      integer comm2d
      integer n, sx, ex, sy, ey
      integer dims(2), coords(2), ierr
      logical periods(2)
!
      call MPI_Cart_get( comm2d, 2, dims, periods, coords, ierr )

      call MPE_DECOMP1D( n, dims(1), coords(1), sx, ex )
      call MPE_DECOMP1D( n, dims(2), coords(2), sy, ey )
!
      return
      end


