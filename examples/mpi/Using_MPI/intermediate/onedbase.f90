      subroutine onedinit( a, b, f, nx, s, e )
      integer nx, s, e
      double precision a(0:nx+1, s-1:e+1), b(0:nx+1, s-1:e+1), &
                       f(0:nx+1, s-1:e+1)
!
      integer i, j
!
      do j=s-1,e+1
         do i=0,nx+1
            a(i,j) = 0.0d0
            b(i,j) = 0.0d0
            f(i,j) = 0.0d0
         enddo
      enddo
!
!    Handle boundary conditions
!
      do j=s,e
         a(0,j) = 1.0d0
         b(0,j) = 1.0d0
         a(nx+1,j) = 0.0d0
         b(nx+1,j) = 0.0d0
      enddo
      if (s .eq. 1) then
         do i=1,nx
            a(i,0) = 1.0d0
            b(i,0) = 1.0d0
         enddo
      endif
!
      return
      end

