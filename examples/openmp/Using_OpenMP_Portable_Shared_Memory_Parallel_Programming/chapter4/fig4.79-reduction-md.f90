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

!$    use OMP_LIB

      implicit none

      real(kind=8):: dotprod

      integer, parameter:: nparticles = 10
      integer, parameter:: nd         = 5

      integer(kind=4)   :: i, j, k, d

      real(kind=8)      :: f(1:nd,1:nparticles)
      real(kind=8)      :: vel(1:nd,1:nparticles)
      real(kind=8)      :: v(1:nparticles)
      real(kind=8)      :: dv(1:nparticles)
      real(kind=8)      :: rij(1:nd)
      integer(kind=4)   :: pos(1:1,1:nparticles)
      real(kind=8)      :: box, mass, pot, kin

      real(kind=8)      :: correct_pot, correct_kin

      pot  = 0.0
      kin  = 0.0

      box  = 1.0
      mass = 2.0

      v(1:nparticles)        = 1.0
      dv(1:nparticles)       = 2.0
      vel(1:nd,1:nparticles) = 4.0
      pos(1:1,1:nparticles)  = 1

      correct_pot = 0.5*nparticles*(nparticles-1)*v(1)
      correct_kin = 0.5*mass*nparticles*nd*vel(1,1)*vel(1,1)

!$    call OMP_SET_DYNAMIC(.false.)
!$    if (OMP_GET_DYNAMIC()) print *,'Warning: dynamic adjustment of threads has been set'
!$    call OMP_SET_NUM_THREADS(3)

! The force computation for each particle is performed in parallel 
!$OMP  PARALLEL DO                &
!$OMP  DEFAULT(shared)            &
!$OMP  PRIVATE(i,j,k,rij,d)       &
!$OMP  REDUCTION(+ : pot, kin)    
      do i=1,nparticles
        ! compute potential energy and forces
        f(1:nd,i) = 0.0
        do j=1,nparticles
             if (i .ne. j) then
               call distance(nd,box,pos(1,i),pos(1,j),rij,d)
               ! result is saved in variable d 
               pot = pot + 0.5*v(d)
               do k=1,nd
                 f(k,i) = f(k,i) - rij(k)*dv(d)/d
               enddo
             endif
        enddo
        ! compute kinetic energy
        kin = kin + dotprod(nd,vel(1,i),vel(1,i))
      enddo
!$OMP END PARALLEL DO
      kin = kin*0.5*mass
  
      print 9010, "pot", pot, correct_pot
      print 9010, "kin", kin, correct_kin

      stop
 9010 format((A),' = ',F5.1,' (correct value = ',F5.1,')')
      end program main

      real(kind=8) function dotprod(n,x,y)

      implicit none

      integer:: n
      real(kind=8):: x(1:n), y(1:n)

      integer:: i

      dotprod = 0.0
      do i = 1, n
         dotprod = dotprod + x(i)*y(i)
      end do
      return

      end function dotprod

      subroutine distance(nd,box,posi,posj,rij,d)

      implicit none

      integer(kind=4):: nd, posi, posj, d
      real(kind=8)   :: box, rij(1:nd)

!-- These are fake computations, just to get some results

      rij(1:nd) = 3.0
      d         = 1

      return
      end subroutine distance
