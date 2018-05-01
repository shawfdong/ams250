!  matmat.f - matrix - matrix multiply,
!  simple self-scheduling version
   program main
   use mpi
   integer MAX_AROWS, MAX_ACOLS, MAX_BCOLS
   parameter (MAX_AROWS = 20, MAX_ACOLS = 1000, MAX_BCOLS = 20)
   double precision a(MAX_AROWS,MAX_ACOLS), b(MAX_ACOLS,MAX_BCOLS)
   double precision c(MAX_AROWS,MAX_BCOLS)
   double precision buffer(MAX_ACOLS), ans(MAX_BCOLS)
   double precision starttime, stoptime
   integer myid, master, numprocs, ierr, status(MPI_STATUS_SIZE)
   integer i, j, numsent, sender
   integer anstype, row, arows, acols, brows, bcols, crows, ccols
   call MPI_INIT(ierr)
   call MPI_COMM_RANK(MPI_COMM_WORLD, myid, ierr)
   call MPI_COMM_SIZE(MPI_COMM_WORLD, numprocs, ierr)
   arows  = 10
   acols  = 20
   brows  = 20
   bcols  = 10
   crows  = arows
   ccols  = bcols
   master = 0
   ierr = MPE_INIT_LOG()
   if (myid .eq. 0) then
      ierr = MPE_DESCRIBE_STATE(1, 2, "Bcast", "red:vlines3")
      ierr = MPE_DESCRIBE_STATE(3, 4, "Compute","blue:gray3")
      ierr = MPE_DESCRIBE_STATE(5, 6, "Send",  "green:light_gray")
      ierr = MPE_DESCRIBE_STATE(7, 8, "Recv",  "yellow:gray")
   endif
   if (myid .eq. 0) then
!     master initializes and then dispatches
!     initialize a and b
      do i = 1,acols
         do j = 1,arows
            a(j,i) = i
         enddo
      enddo
      do i = 1,bcols
         do j = 1,brows
            b(j,i) = i
         enddo
      enddo
      numsent = 0
!     send a row of a to each other process; tag with row number
!     For simplicity, assume arows .ge. numprocs - 1
      do i = 1,numprocs-1
         do j = 1,acols
            buffer(j) = a(i,j)
         enddo
         ierr = MPE_LOG_EVENT(5, i, "send")
         call MPI_SEND(buffer, acols, MPI_DOUBLE_PRECISION, i, &
                       i, MPI_COMM_WORLD, ierr)
         ierr = MPE_LOG_EVENT(6, i, "sent")
         numsent = numsent+1
      enddo
      do i = 1,crows
         ierr = MPE_LOG_EVENT(7, i, "recv")
         call MPI_RECV(ans, ccols, MPI_DOUBLE_PRECISION, &
                       MPI_ANY_SOURCE, MPI_ANY_TAG, &
    	               MPI_COMM_WORLD, status, ierr)
         sender     = status(MPI_SOURCE)
         anstype    = status(MPI_TAG)
         ierr = MPE_LOG_EVENT(8, anstype, "recvd")
         do j = 1,ccols
            c(anstype,j) = ans(j)
         enddo
         if (numsent .lt. arows) then
            do j = 1,acols
               buffer(j) = a(numsent+1,j)
            enddo
            ierr = MPE_LOG_EVENT(5, i, "send")
            call MPI_SEND(buffer, acols, MPI_DOUBLE_PRECISION, &
                          sender, numsent+1, MPI_COMM_WORLD, ierr)
            ierr = MPE_LOG_EVENT(6, i, "sent")
            numsent = numsent+1
         else
            ierr = MPE_LOG_EVENT(5, 0, "send")
            call MPI_SEND(1.0, 1, MPI_DOUBLE_PRECISION, sender, &
                          0, MPI_COMM_WORLD, ierr)
            ierr = MPE_LOG_EVENT(6, 0, "sent")
         endif
      enddo
   else
!     slaves receive b, then compute rows of c until done message
      ierr = MPE_LOG_EVENT(1, 0, "bstart")
      do i = 1,bcols
         call MPI_BCAST(b(1,i), brows, MPI_DOUBLE_PRECISION, &
                        master, MPI_COMM_WORLD, ierr)
      enddo
      ierr = MPE_LOG_EVENT(2, 0, "bend")
      ierr = MPE_LOG_EVENT(7, i, "recv")
      do
         call MPI_RECV(buffer, acols, MPI_DOUBLE_PRECISION, master, &
                       MPI_ANY_TAG, MPI_COMM_WORLD, status, ierr)
         if (status(MPI_TAG) .eq. 0) exit
         row = status(MPI_TAG)
         ierr = MPE_LOG_EVENT(8, row, "recvd")
         ierr = MPE_LOG_EVENT(3, row, "compute")
         do i = 1,bcols
            ans(i) = 0.0
            do j = 1,acols
               ans(i) = ans(i) + buffer(j)*b(j,i)
            enddo
         enddo
         ierr = MPE_LOG_EVENT(4, row, "computed")
         ierr = MPE_LOG_EVENT(5, row, "send")
         call MPI_SEND(ans, bcols, MPI_DOUBLE_PRECISION, master, &
                       row, MPI_COMM_WORLD, ierr)
         ierr = MPE_LOG_EVENT(6, row, "sent")
      enddo
   endif
   ierr = MPE_FINISH_LOG("pmatmat.log")
   call MPI_FINALIZE(ierr)
   end
