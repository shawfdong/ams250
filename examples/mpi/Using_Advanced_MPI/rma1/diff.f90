!
!  The rest of the 1-d program
!
      double precision function diff( a, b, nx, s, e )
      integer nx, s, e
      double precision a(0:nx+1, s-1:e+1), b(0:nx+1, s-1:e+1)
!
      double precision sum
      integer i, j
!
      sum = 0.0d0
      do j=s,e
         do i=1,nx
            sum = sum + (a(i,j) - b(i,j)) ** 2
         enddo
      enddo
!
      diff = sum
      return
      end
