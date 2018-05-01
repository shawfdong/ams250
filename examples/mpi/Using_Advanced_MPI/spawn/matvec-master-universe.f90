! Matrix-vector multiply, with spawning of workers
PROGRAM main
    use mpi
    integer MAX_ROWS, MAX_COLS
    parameter (MAX_ROWS = 1000, MAX_COLS = 1000)
    double precision a(MAX_ROWS,MAX_COLS), b(MAX_COLS), c(MAX_COLS)
    double precision buffer(MAX_COLS), ans
    integer workercomm

    integer ierr, stat(MPI_STATUS_SIZE)
    integer i, j, numsent, numrcvd, sender, numworkers
    integer anstype, rows, cols

    integer softinfo
    integer (kind=MPI_ADDRESS_KIND) universe_size
    logical universe_size_flag
    integer usize, errcodes(10)

    call MPI_INIT(ierr)

    call MPI_COMM_GET_ATTR(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE, &
                  universe_size, universe_size_flag, ierr)
    if (universe_size_flag) then
        usize = universe_size - 1
        call MPI_COMM_SPAWN('matvec-worker', MPI_ARGV_NULL, usize, &
                             MPI_INFO_NULL, 0, MPI_COMM_WORLD, &
                             workercomm, errcodes, ierr)
    else
        call MPI_INFO_CREATE(softinfo, ierr)
        call MPI_INFO_SET(softinfo, 'soft', '1:10', ierr)
        call MPI_COMM_SPAWN('matvec-worker', MPI_ARGV_NULL, 10, &
                            softinfo, 0, MPI_COMM_WORLD, &
                            workercomm, errcodes, ierr)
        call MPI_INFO_FREE(softinfo, ierr)
    endif
    call MPI_COMM_REMOTE_SIZE(workercomm, numworkers, ierr)
    do i=1, 10
        if (errcodes(i) .ne. MPI_SUCCESS) then
            print *, 'worker ', i, ' did not start'
        endif
    enddo
    print *, 'number of workers = ', numworkers
!     master initializes and then dispatches
      rows   = 100
      cols   = 100
!     initialize a and b
      do i = 1,cols
         b(i) = 1
         do j = 1,rows
            a(i,j) = i
         enddo
      enddo
      numsent = 0
      numrcvd = 0
!     send b to each worker
      call MPI_BCAST(b, cols, MPI_DOUBLE_PRECISION, MPI_ROOT, &
                     workercomm, ierr)

!     send a row to each worker; tag with row number
      do i = 1,numworkers
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
                       workercomm, stat, ierr)
         sender     = stat(MPI_SOURCE)
         anstype    = stat(MPI_TAG)
         c(anstype) = ans
         if (numsent .lt. rows) then
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

!     print out the answer
      do i = 1,cols
         print *, "c(", i, ") = ", c(i)
      enddo
      call MPI_COMM_FREE(workercomm, ierr)
      call MPI_FINALIZE(ierr)
END PROGRAM main
