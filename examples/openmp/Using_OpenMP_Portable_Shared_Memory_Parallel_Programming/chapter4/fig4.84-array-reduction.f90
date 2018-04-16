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

      program array_reduction

!$    use OMP_LIB

      implicit none

      integer:: i, j, n, memstat
      integer, allocatable:: a(:), b(:,:), c(:), indx(:), ref(:)

      n = 9

!$    call OMP_SET_DYNAMIC(.false.)
!$    if (OMP_GET_DYNAMIC()) print *,'Warning: dynamic adjustment of threads has been set'
!$    call OMP_SET_NUM_THREADS(4)

      allocate(a(1:n), STAT=memstat)
      if (memstat /= 0) stop 'Fatal error in memory allocation for A'

      allocate(b(1:n,1:n), STAT=memstat)
      if (memstat /= 0) stop 'Fatal error in memory allocation for B'

      allocate(c(1:n), STAT=memstat)
      if (memstat /= 0) stop 'Fatal error in memory allocation for C'

      allocate(indx(1:n), STAT=memstat)
      if (memstat /= 0) stop 'Fatal error in memory allocation for INDX'

      allocate(ref(1:n), STAT=memstat)
      if (memstat /= 0) stop 'Fatal error in memory allocation for REF'

      do i = 1, n
         indx(i) = i
      end do

      do j = 1, n
         b(1:n,j) = indx(1:n)
      end do
      c(1:n) = indx(1:n) + 1

      ref(1:n) = 0
      do j = 1, n
         ref(1:n) = ref(1:n) + b(1:n,j)*c(j)
      end do

      call mxv(n, a, b, c)

      print *,'After MXV:'
      print *,'Result array a is   :',a(1:n)
      print *,'Reference solution  :',ref(1:n)
      print *,'Difference a - ref  :',a(1:n)-ref(1:n)

      if (allocated(a)) deallocate(a)
      if (allocated(b)) deallocate(b)
      if (allocated(c)) deallocate(c)
      if (allocated(c)) deallocate(indx)

      end program array_reduction

      subroutine mxv(n, a, b, c)
      implicit none
      integer:: n, a(1:n), b(1:n,1:n), c(1:n)

      integer:: j

!$OMP PARALLEL WORKSHARE
      a(1:n) = 0.0
!$OMP END PARALLEL WORKSHARE      

!$OMP PARALLEL DO DEFAULT(NONE) PRIVATE(j) SHARED(n,b,c) &
!$OMP          REDUCTION(+:a)
      do j = 1, n
         a(1:n) = a(1:n) + b(1:n,j)*c(j)
      end do
!$OMP END PARALLEL DO

      return
      end
