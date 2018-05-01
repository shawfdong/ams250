!
! Perform a Jacobi sweep for a 1-d decomposition.
! Sweep from a into b
!
      subroutine sweep1d( a, f, nx, s, e, b )
      integer nx, s, e
      double precision a(0:nx+1,s-1:e+1), f(0:nx+1,s-1:e+1), &
                       b(0:nx+1,s-1:e+1)
!
      integer i, j
      double precision h
!
      h = 1.0d0 / dble(nx+1)
      do j=s, e
         do i=1, nx
            b(i,j) = 0.25 * (a(i-1,j)+a(i,j+1)+a(i,j-1)+a(i+1,j)) - &
                     h * h * f(i,j)
         enddo
      enddo
      return
      end
