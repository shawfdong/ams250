      program contiguous
      include 'mpif.h'

      integer SIZE
      parameter(SIZE=4)
      integer numtasks, rank, source, dest, tag, i,  ierr
      real*4 a(0:SIZE-1,0:SIZE-1), b(0:SIZE-1)
      integer req, stat(MPI_STATUS_SIZE), columntype

C     Fortran stores this array in column major order
      data a  /1.0, 2.0, 3.0, 4.0,
     &         5.0, 6.0, 7.0, 8.0,
     &         9.0, 10.0, 11.0, 12.0,
     &         13.0, 14.0, 15.0, 16.0 /

      call MPI_INIT(ierr)
      call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
      call MPI_COMM_SIZE(MPI_COMM_WORLD, numtasks, ierr)

      call MPI_TYPE_CONTIGUOUS(SIZE, MPI_REAL, columntype, ierr)
      call MPI_TYPE_COMMIT(columntype, ierr)

      tag = 1
      if (numtasks .eq. SIZE) then
         source = 0
         call MPI_IRECV(b, SIZE, MPI_REAL, source, tag,
     &                  MPI_COMM_WORLD, req, ierr)

         if (rank .eq. 0) then
            do i=0, numtasks-1
               call MPI_SEND(a(0,i), 1, columntype, i, tag,
     &                       MPI_COMM_WORLD,ierr)
            enddo
         endif

         call MPI_WAIT(req, stat, ierr)
         print *, 'rank= ', rank, ' b= ', b

      else
         print *, 'Must specify', SIZE, ' processors.  Terminating.'
      endif

      call MPI_TYPE_FREE(columntype, ierr)
      call MPI_FINALIZE(ierr)

      end
