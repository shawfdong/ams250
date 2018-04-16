!! DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
!!
!! Copyright 2009 Sun Microsystems, Inc. All rights reserved.
!!
!! The contents of this file are subject to the terms of the BSD License("BSD")(the "License").
!! You can obtain a copy of the License at: http://www.opensparc.net/pubs/t1/licenses/BSD+_License.txt
!!
!! The BSD License
!!
!! Redistribution and use in source and binary forms, with or without 
!! modification, are permitted provided that the following conditions are met:
!!
!!     * Redistribution of source code must retain the above copyright 
!!       notice, this list of conditions and the following disclaimer.
!!     * Redistribution in binary form must reproduce the above copyright 
!!       notice, this list of conditions and the following disclaimer in 
!!       the documentation and/or other materials provided with the 
!!       distribution.
!!     * Neither the name of Sun Microsystems, Inc. or the names of 
!!       contributors may be used to endorse or promote products derived 
!!       from this software without specific prior written permission.
!!
!! This software is provided "AS IS," without a warranty of any kind. ALL 
!! EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY 
!! IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR 
!! NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN MICROSYSTEMS, INC. ("SUN") AND 
!! ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A 
!! RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES. 
!! IN NO EVENT WILL SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT 
!! OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR 
!! PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, 
!! ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF SUN HAS 
!! BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
!!
!! You acknowledge that this software is not designed, licensed or intended for 
!! use in the design, construction, operation or maintenance of any nuclear facility. 

      program main

      interface
         subroutine mxv(m, n, a, b, c)
            integer(kind=4), intent(in)   :: m, n
            real   (kind=8), intent(in)   :: b(1:m,1:n), c(1:n)
            real   (kind=8), intent(inout):: a(1:m)
         end subroutine mxv
      end interface

      real(kind=8), allocatable:: a(:), b(:,:), c(:)
      integer(kind=4)          :: m ,n, i, memstat

      print *, 'Please give m and n:'; read(*,*) m, n

      allocate ( a(1:m), stat=memstat )
      if ( memstat /= 0 ) stop 'Fatal error in memory allocation for a'
      allocate ( b(1:m,1:n), stat=memstat )
      if ( memstat /= 0 ) stop 'Fatal error in memory allocation for b'
      allocate ( c(1:n), stat=memstat )
      if ( memstat /= 0 ) stop 'Fatal error in memory allocation for c'

      print *, 'Initializing matrix B and vector c'
      c(1:n) = 1.0
      do i = 1, m
         b(i,1:n) = i
      end do

      print *, 'Executing mxv routine for m = ',m,' n = ',n
      call mxv(m, n, a, b, c)

      if ( allocated(a) )   deallocate(a,stat=memstat)
      if ( allocated(b) )   deallocate(b,stat=memstat)
      if ( allocated(c) )   deallocate(c,stat=memstat)

      stop

      end program main

      subroutine mxv(m, n, a, b, c)

      implicit none

      integer(kind=4):: m , n
      real   (kind=8):: a(1:m), b(1:m,1:n), c(1:n)
      integer(kind=4):: i, j

      do i = 1, m
         a(i) = 0.0
         do j = 1, n
            a(i) = a(i) + b(i,j)*c(j)
         end do
      end do

      return
      end subroutine mxv
