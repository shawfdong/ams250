!**********************************************************************
!   twod.f90 - a solution to the Poisson problem by using Jacobi
!   interation on a 2-d decomposition
!
!   .... the rest of this is from pi3.f to show the style ...
!
!   Each node:
!    1) receives the number of rectangles used in the approximation.
!    2) calculates the areas of it's rectangles.
!    3) Synchronizes for a global summation.
!   Node 0 prints the result.
!
!  Variables:
!
!    pi  the calculated result
!    n   number of points of integration.
!    x           midpoint of each rectangle's interval
!    f           function to integrate
!    sum,pi      area of rectangles
!    tmp         temporary scratch space for global summation
!    i           do loop index
!
!     This code is included (without the prints) because one version of
!     MPICH SEGV'ed (probably because of errors in handling send/recv of
!     MPI_PROC_NULL source/destination).
!
!****************************************************************************
      program main
      use mpi
      integer maxn
      parameter (maxn = 128)
      double precision  a(maxn,maxn), b(maxn,maxn), f(maxn,maxn)
      integer nx, ny
      integer myid, numprocs, it, rc, comm2d, ierr, stride
      integer nbrleft, nbrright, nbrtop, nbrbottom
      integer sx, ex, sy, ey
      integer dims(2)
      logical periods(2)
      double precision diff2d, diffnorm, dwork
      double precision t1, t2
      external diff2d
      data periods/2*.false./

      call MPI_INIT( ierr )
      call MPI_COMM_RANK( MPI_COMM_WORLD, myid, ierr )
      call MPI_COMM_SIZE( MPI_COMM_WORLD, numprocs, ierr )
!      print *, "Process ", myid, " of ", numprocs, " is alive"
      if (myid .eq. 0) then
!
!         Get the size of the problem
!
!          print *, 'Enter nx'
!          read *, nx
           nx = 10
      endif
!      print *, 'About to do bcast on ', myid
      call MPI_BCAST(nx,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
      ny   = nx
!
! Get a new communicator for a decomposition of the domain.  Let MPI
! find a "good" decomposition
!
      dims(1) = 0
      dims(2) = 0
      call MPI_DIMS_CREATE( numprocs, 2, dims, ierr )
      call MPI_CART_CREATE( MPI_COMM_WORLD, 2, dims, periods, .true., &
                            comm2d, ierr )
!
! Get my position in this communicator
!
      call MPI_COMM_RANK( comm2d, myid, ierr )
!      print *, "Process ", myid, " of ", numprocs, " is alive"
!
! My neighbors are now +/- 1 with my rank.  Handle the case of the
! boundaries by using MPI_PROCNULL.
      call fnd2dnbrs( comm2d, nbrleft, nbrright, nbrtop, nbrbottom )
!      print *, "Process ", myid, ":",
!     *     nbrleft, nbrright, nbrtop, nbrbottom
!
! Compute the decomposition
!
      call fnd2ddecomp( comm2d, nx, sx, ex, sy, ey )
!      print *, "Process ", myid, ":", sx, ex, sy, ey
!
! Create a new, "strided" datatype for the exchange in the "non-contiguous"
! direction
!
      call mpi_Type_vector( ey-sy+1, 1, ex-sx+3, &
                            MPI_DOUBLE_PRECISION, stride, ierr )
      call mpi_Type_commit( stride, ierr )
!
!
! Initialize the right-hand-side (f) and the initial solution guess (a)
!
      call twodinit( a, b, f, nx, sx, ex, sy, ey )
!
! Actually do the computation.  Note the use of a collective operation to
! check for convergence, and a do-loop to bound the number of iterations.
!
      call MPI_BARRIER( MPI_COMM_WORLD, ierr )
      t1 = MPI_WTIME()
      do it=1, 100
	call exchng2( b, sx, ex, sy, ey, comm2d, stride, &
                      nbrleft, nbrright, nbrtop, nbrbottom )
	call sweep2d( b, f, nx, sx, ex, sy, ey, a )
	call exchng2( a, sx, ex, sy, ey, comm2d, stride, &
                      nbrleft, nbrright, nbrtop, nbrbottom )
	call sweep2d( a, f, nx, sx, ex, sy, ey, b )
	dwork = diff2d( a, b, nx, sx, ex, sy, ey )
	call MPI_Allreduce( dwork, diffnorm, 1, MPI_DOUBLE_PRECISION, &
                            MPI_SUM, comm2d, ierr )
        if (diffnorm .lt. 1.0e-5) exit
        if (myid .eq. 0) print *, 2*it, ' Difference is ', diffnorm
      enddo
      t2 = MPI_WTIME()
      if (myid .eq. 0 .and. it .gt. 100) print *, 'Failed to converge'
!      if (myid .eq. 0) then
!         print *, 'Converged after ', 2*it, ' Iterations in ', t2 - t1,
!     $        ' secs '
!      endif
!
      call MPI_Type_free( stride, ierr )
      call MPI_Comm_free( comm2d, ierr )
      call MPI_FINALIZE(rc)
      end
