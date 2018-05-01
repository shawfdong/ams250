      subroutine matvec(n, m, lmatrix, lx, ly, counts, comm)
      use mpi
      integer n, m, comm, counts(*)
      real lmatrix(n,m), lx(m), ly(m)
      integer i, j
      real sum
      real, allocatable :: tmp(:)

      allocate (tmp(n))

      ! Perform the local matrix-vector multiply
      ! Should use the level-2 BLAS routine SGEMV
      do i=1,n
         sum = 0
         do j=1,m
            sum = sum + lmatrix(i,j)*lx(j)
         enddo
         tmp(i) = sum
      enddo

      ! Perform the local matrix-vector product
      call MPI_REDUCE_SCATTER(tmp, ly, counts, &
                              MPI_REAL, MPI_SUM, comm, ierr)
      deallocate (tmp)

      ! We're done!
      end
