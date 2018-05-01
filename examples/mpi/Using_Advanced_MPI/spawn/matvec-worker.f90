! worker program for matrix-vector multiplication
PROGRAM main
      use mpi
      integer MAX_COLS
      parameter (MAX_COLS = 1000)
      double precision b(MAX_COLS)
      double precision buffer(MAX_COLS), ans

      integer i, ierr, status(MPI_STATUS_SIZE)
      integer row, cols, rows, rank
      integer parentcomm

      call MPI_INIT(ierr)
      call MPI_COMM_GET_PARENT(parentcomm, ierr)
!     the master is now rank 0 in the remote group of the
!     parent intercommunicator.
!     workers receive b, then compute dot products until
!     done message received
      rows = 100
      cols = 100
      call MPI_BCAST(b, cols, MPI_DOUBLE_PRECISION, 0, &
                     parentcomm, ierr)
      call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
      if (rank .lt. rows) then
         ! skip if more processes than work
         do
            call MPI_RECV(buffer, cols, MPI_DOUBLE_PRECISION, 0, &
                          MPI_ANY_TAG, parentcomm, status, ierr)
            if (status(MPI_TAG) .eq. 0) exit
            row = status(MPI_TAG)
            ans = 0.0
            do i = 1,cols
               ans = ans+buffer(i)*b(i)
            enddo
            call MPI_SEND(ans, 1, MPI_DOUBLE_PRECISION, 0, row, &
                          parentcomm, ierr)
         enddo
      endif
      call MPI_COMM_FREE(parentcomm, ierr)
      call MPI_FINALIZE(ierr)
END PROGRAM main
