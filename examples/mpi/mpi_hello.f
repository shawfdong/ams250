      PROGRAM HELLO

      implicit none
      include "mpif.h"
      integer ierr, rank, size

      call MPI_INIT(ierr)
      call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
      call MPI_COMM_SIZE(MPI_COMM_WORLD, size, ierr)
      print *, "Hello, world! I am process ", rank, " of ", size
      call MPI_FINALIZE(ierr)

      stop
      END
