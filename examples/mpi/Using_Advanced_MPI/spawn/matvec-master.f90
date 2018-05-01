! Matrix-vector multiply, with spawning of workers
PROGRAM main
      use mpi
      integer MAX_ROWS, MAX_COLS
      parameter (MAX_ROWS = 1000, MAX_COLS = 1000)
      double precision a(MAX_ROWS,MAX_COLS), b(MAX_COLS), c(MAX_ROWS)
      double precision buffer(MAX_COLS), ans
      integer workercomm

      integer ierr, status(MPI_STATUS_SIZE)
      integer i, j, numsent, sender, numworkers
      integer anstype, rows, cols

      call MPI_INIT(ierr)
!     master decides how many workers to spawn, say 10
      numworkers = 10
      call MPI_COMM_SPAWN('matvec-worker', MPI_ARGV_NULL, numworkers, &
                   MPI_INFO_NULL, 0, MPI_COMM_WORLD, &
                   workercomm, MPI_ERRCODES_IGNORE, ierr)
!     master initializes and then dispatches
      rows   = 100
      cols   = 100
!     initialize a and b
      do j = 1,cols
         b(j) = 1
         do i = 1,rows
            a(i,j) = i
         enddo
      enddo
      numsent = 0
!     send b to each worker
      call MPI_BCAST(b, cols, MPI_DOUBLE_PRECISION, MPI_ROOT, &
                     workercomm, ierr)

!     send a row to each worker; tag with row number
      do i = 1,min(numworkers,rows)
         do j = 1,cols
            buffer(j) = a(i,j)
         enddo
         call MPI_SEND(buffer, cols, MPI_DOUBLE_PRECISION, i-1, &
                       i, workercomm, ierr)
         numsent = numsent+1
      enddo
      do i = 1,rows
         call MPI_RECV(ans, 1, MPI_DOUBLE_PRECISION, &
                       MPI_ANY_SOURCE, MPI_ANY_TAG, &
                       workercomm, status, ierr)
         sender     = status(MPI_SOURCE)
         anstype    = status(MPI_TAG)	! row is tag value
         c(anstype) = ans
         if (numsent .lt. rows) then	! send another row
            do j = 1,cols
               buffer(j) = a(numsent+1,j)
            enddo
            call MPI_SEND(buffer, cols, MPI_DOUBLE_PRECISION, &
                          sender, numsent+1, workercomm, ierr)
            numsent = numsent+1
         else
            call MPI_SEND(buffer, 0, MPI_DOUBLE_PRECISION, sender, &
                          0, workercomm, ierr)
         endif
      enddo

!     print the answer
      do i = 1,rows
         print *, "c(", i, ") = ", c(i)
      enddo
      call MPI_COMM_FREE(workercomm, ierr)
      call MPI_FINALIZE(ierr)
END PROGRAM main

