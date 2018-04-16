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

      integer:: TID, signal, newdata, localdata

!$    call OMP_SET_DYNAMIC(.false.)
!$    if (OMP_GET_DYNAMIC()) print *,'Warning: dynamic adjustment of threads has been set'
!$    call OMP_SET_NUM_THREADS(2)

      newdata = -1
      signal  = 0

!$OMP PARALLEL DEFAULT(NONE) SHARED(signal,newdata) &
!$OMP PRIVATE(TID,localdata) 

      TID = OMP_GET_THREAD_NUM()

      if (TID == 0 ) then
         newdata = 10
         print *,'In TID = ',TID,': set variable newdata to ',newdata

!-- This emulates some work is done

         call system("sleep 5")

!$OMP FLUSH(newdata,signal)
         signal = 1
         print *,'In TID = ',TID,': changed variable signal to ',signal
!$OMP FLUSH(signal)

       else

!-- Wait for signal to change value

      print *,'In TID = ',TID,': waiting for signal to change'

!$OMP FLUSH(signal)
         do while (signal == 0 )
!$OMP FLUSH(signal)
         end do

!-- Ensure the modified value of newdata is picked up here

!$OMP FLUSH(newdata)
         localdata = newdata
         print *,'In TID = ',TID,': localdata = ',localdata
      end if

!$OMP END PARALLEL

      stop
      end
