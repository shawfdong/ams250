!*******************************************************************
!   oned.f90 - a solution to the Poisson problem using Jacobi
!   interation on a 1-d decomposition
!
!   The size of the domain is read by processor 0 and broadcast to
!   all other processors.  The Jacobi iteration is run until the
!   change in successive elements is small or a maximum number of
!   iterations is reached.  The difference is printed out at each
!   step.
!*******************************************************************
      program main
!
      use mpi
      integer maxn
      parameter (maxn = 1024+2)
      double precision  a(maxn,maxn), b(maxn,maxn), f(maxn,maxn)
      integer nx, ny
      integer myid, numprocs, ierr
      integer comm1d, nbrbottom, nbrtop, s, e, it
      double precision diff, diffnorm, dwork
      double precision t1, t2
      external diff

      call MPI_INIT( ierr )
      call MPI_COMM_RANK( MPI_COMM_WORLD, myid, ierr )
      call MPI_COMM_SIZE( MPI_COMM_WORLD, numprocs, ierr )
!
      if (myid .eq. 0) then
!
!         Get the size of the problem
!
!          print *, 'Enter nx'
!          read *, nx
           nx = 1024
      endif
      call MPI_BCAST(nx,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
      ny   = nx
!
! Get a new communicator for a decomposition of the domain
!
      call MPI_CART_CREATE( MPI_COMM_WORLD, 1, numprocs, .false., &
                            .true., comm1d, ierr )
!
! Get my position in this communicator, and my neighbors
!
      call MPI_COMM_RANK( comm1d, myid, ierr )
      call MPI_Cart_shift( comm1d, 0,  1, nbrbottom, nbrtop, ierr )
!
! Compute the actual decomposition
!
      call MPE_DECOMP1D( ny, numprocs, myid, s, e )
!
! Initialize the right-hand-side (f) and the initial solution guess (a)
!
      call onedinit( a, b, f, nx, s, e )
!
! Actually do the computation.  Note the use of a collective operation to
! check for convergence, and a do-loop to bound the number of iterations.
!
      call MPI_BARRIER( MPI_COMM_WORLD, ierr )
      t1 = MPI_WTIME()
      do it=1, 100
!      do it=1, 2
	call exchng1( a, nx, s, e, comm1d, nbrbottom, nbrtop )
	call sweep1d( a, f, nx, s, e, b )
	call exchng1( b, nx, s, e, comm1d, nbrbottom, nbrtop )
	call sweep1d( b, f, nx, s, e, a )
	dwork = diff( a, b, nx, s, e )
	call MPI_Allreduce( dwork, diffnorm, 1, MPI_DOUBLE_PRECISION, &
                            MPI_SUM, comm1d, ierr )
        if (diffnorm .lt. 1.0e-5) exit
!        if (myid .eq. 0) print *, 2*it, ' Difference is ', diffnorm
      enddo
      if (myid .eq. 0 .and. it .gt. 100) print *, 'Failed to converge'
      t2 = MPI_WTIME()
      if (myid .eq. 0) then
         print *, 'Converged after ', 2*it, ' Iterations in ', t2 - t1, &
             ' secs '
      endif
!
      call MPI_FINALIZE(ierr)
      end
