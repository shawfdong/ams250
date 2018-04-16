C******************************************************************************
C FILE: omp_bug5.f
C DESCRIPTION:
C   Using SECTIONS, two threads initialize their own array and then add
C   it to the other's array, however a deadlock occurs.
C AUTHOR: Blaise Barney  01/09/04
C LAST REVISED: 08/15/11
C******************************************************************************

      PROGRAM BUG5

      INTEGER*8 LOCKA, LOCKB
      INTEGER NTHREADS, TID, I,
     +        OMP_GET_NUM_THREADS, OMP_GET_THREAD_NUM
      PARAMETER (N=1000000)
      REAL A(N), B(N), PI, DELTA
      PARAMETER (PI=3.1415926535)
      PARAMETER (DELTA=.01415926535)

C     Initialize the locks
      CALL OMP_INIT_LOCK(LOCKA)
      CALL OMP_INIT_LOCK(LOCKB)

C     Initialize the arrays
      DO I = 1, N
         A(I) = 0
         B(I) = 0
      ENDDO

C     Fork a team of threads giving them their own copies of variables
!$OMP PARALLEL SHARED(A, B, NTHREADS, LOCKA, LOCKB) PRIVATE(TID, I)

C     Obtain thread number and number of threads
      TID = OMP_GET_THREAD_NUM()
!$OMP MASTER
      NTHREADS = OMP_GET_NUM_THREADS()
      PRINT *, 'Number of threads = ', NTHREADS
!$OMP END MASTER
      PRINT *, 'Thread', TID, 'starting...'
!$OMP BARRIER

!$OMP SECTIONS

!$OMP SECTION
      CALL OMP_SET_LOCK(LOCKA)
      PRINT *, 'Thread', TID, ' updating A()'
      DO I = 1, N
         A(I) = A(I) + (DELTA * I)
      ENDDO
      CALL OMP_SET_LOCK(LOCKB)
      PRINT *, 'Thread', TID, ' updating B()'
      DO I = 1, N
         B(I) = B(I) + (DELTA + I)
      ENDDO
      CALL OMP_UNSET_LOCK(LOCKB)
      CALL OMP_UNSET_LOCK(LOCKA)

!$OMP SECTION
      CALL OMP_SET_LOCK(LOCKB)
      PRINT *, 'Thread', TID, ' updating B()'
      DO I = 1, N
         B(I) = B(I) + (PI * I)
      ENDDO
      CALL OMP_SET_LOCK(LOCKA)
      PRINT *, 'Thread', TID, ' updating A()'
      DO I = 1, N
         A(I) = A(I) + (PI + I)
      ENDDO
      CALL OMP_UNSET_LOCK(LOCKA)
      CALL OMP_UNSET_LOCK(LOCKB)

!$OMP END SECTIONS NOWAIT

!$OMP END PARALLEL

      WRITE (*,100) A(1), B(1), A(1000000), B(1000000)
 100  FORMAT('Sample results:'F12.2, F12.2, F12.2, F12.2)

      END
