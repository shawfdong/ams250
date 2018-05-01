!
! Perform a Jacobi sweep for a 2-d decomposition
!
      subroutine sweep2d( a, f, n, sx, ex, sy, ey, b )
      integer n, sx, ex, sy, ey
      double precision a(sx-1:ex+1, sy-1:ey+1), f(sx-1:ex+1, sy-1:ey+1), &
                       b(sx-1:ex+1, sy-1:ey+1)
!
      integer i, j
      double precision h
!
      h = 1.0d0 / dble(n+1)
      do j=sy, ey
         do i=sx, ex
            b(i,j) = 0.25 * (a(i-1,j)+a(i,j+1)+a(i,j-1)+a(i+1,j)) - &
                     h * h * f(i,j)
         enddo
      enddo
      return
      end
