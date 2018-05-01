      subroutine twodinit( a, b, f, nx, sx, ex, sy, ey )
      integer nx, sx, ex, sy, ey
      double precision a(sx-1:ex+1, sy-1:ey+1), b(sx-1:ex+1, sy-1:ey+1), &
                       f(sx-1:ex+1, sy-1:ey+1)
!
      integer i, j
!
      do j=sy-1,ey+1
         do i=sx-1,ex+1
            a(i,j) = 0.0d0
            b(i,j) = 0.0d0
            f(i,j) = 0.0d0
         enddo
      enddo
!
!    Handle boundary conditions
!
      if (sx .eq. 1) then
         do j=sy,ey
            a(0,j) = 1.0d0
            b(0,j) = 1.0d0
         enddo
      endif
      if (ex .eq. nx) then
         do j=sy,ey
            a(nx+1,j) = 0.0d0
            b(nx+1,j) = 0.0d0
         enddo
      endif
      if (sy .eq. 1) then
         do i=sx,ex
            a(i,0) = 1.0d0
            b(i,0) = 1.0d0
         enddo
      endif
!
      return
      end

