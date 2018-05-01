!
!  The rest of the 2-d program
!
      double precision function diff2d( a, b, nx, sx, ex, sy, ey )
      integer nx, sx, ex, sy, ey
      double precision a(sx-1:ex+1, sy-1:ey+1), b(sx-1:ex+1, sy-1:ey+1)
!
      double precision sum
      integer i, j
!
      sum = 0.0d0
      do j=sy,ey
         do i=sx,ex
            sum = sum + (a(i,j) - b(i,j)) ** 2
         enddo
      enddo
!
      diff2d = sum
      return
      end
