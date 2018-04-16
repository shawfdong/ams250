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

      use OMP_LIB

      implicit none

      integer(kind=omp_lock_kind):: lck
      integer(kind=4)            :: tid
      character*8                :: tid_date ! format yyyymmdd
      character*10               :: tid_time ! format hhmmss.ss

      call OMP_SET_DYNAMIC(.false.)
      if (OMP_GET_DYNAMIC()) print *,'Warning: dynamic adjustment of threads has been set'
      call OMP_SET_NUM_THREADS(3)

      call OMP_INIT_LOCK(lck)

!$OMP PARALLEL SHARED(lck) PRIVATE(tid)

      tid = OMP_GET_THREAD_NUM()

      do while ( .not. OMP_TEST_LOCK(lck) )

         call date_and_time(tid_date,tid_time)
       
         print 9010,tid_time(1:2),tid_time(3:4),tid_time(5:10),tid

         call work_while_wait(tid)
      end do

      call date_and_time(tid_date,tid_time)

      print 9020,tid_time(1:2),tid_time(3:4),tid_time(5:10),tid

 9010 format(1X,'At ',A2,' hours ',A2,' minutes and ',A5, &
             ' seconds thread ',I3,' waits for the lock to be released')
 9020 format(1X,'At ',A2,' hours ',A2,' minutes and ',A5, &
             ' seconds thread ',I3,' has acquired the lock')

      call do_work(tid)

      call OMP_UNSET_LOCK(lck)

!$OMP END PARALLEL

      call OMP_DESTROY_LOCK(lck)

      end program main

      subroutine work_while_wait(tid)
      implicit none
      integer(kind=4):: tid
      real(kind=8)   :: dummy

!-----------------------------------------------------------------------
! You can use this instead of the call below if your system supports it
!      call system("sleep 2")
!-----------------------------------------------------------------------

      call simulate_some_work(tid,dummy)

      return
      end subroutine work_while_wait

      subroutine do_work(tid)
      implicit none
      integer(kind=4):: tid
      real(kind=8)   :: dummy

      print 9010, tid

!-----------------------------------------------------------------------
! You can use this instead of the call below if your system supports it
!      call system("sleep 5")
!-----------------------------------------------------------------------

      call simulate_some_work(tid,dummy)

      print 9020, tid

      return
 9010 format(3X,'Thread ',I3,' has the lock and performs the work')
 9020 format(3X,'Thread ',I3,' has completed the work')
      end subroutine do_work

      subroutine simulate_some_work(tid,x)
      implicit none
      integer(kind=4):: tid
      real(kind=8)   :: x

      integer(kind=4), parameter:: incr = 10000000
      integer(kind=4)           :: i

      x = 1.0
      do i = 1+tid*incr, (tid+1)*incr
         x = cos(x/i) * sin(x/i)
      end do

      end subroutine simulate_some_work
