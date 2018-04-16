!     THREADPRIVATE Directive Example
      PROGRAM THREADPRIV

      INTEGER A, B, I, TID, OMP_GET_THREAD_NUM
      REAL*4 X
      COMMON /C1/ A

!$OMP THREADPRIVATE(/C1/, X)

!     Explicitly turn off dynamic threads
      CALL OMP_SET_DYNAMIC(.FALSE.)

      PRINT *, '1st Parallel Region:'
!$OMP PARALLEL PRIVATE(B, TID)
      TID = OMP_GET_THREAD_NUM()
      A = TID
      B = TID
      X = 1.1 * TID + 1.0
      PRINT *, 'Thread',TID,':   A,B,X=',A,B,X
!$OMP END PARALLEL

      PRINT *, '************************************'
      PRINT *, 'Master thread doing serial work here'
      PRINT *, '************************************'

      PRINT *, '2nd Parallel Region: '
!$OMP PARALLEL PRIVATE(TID)
      TID = OMP_GET_THREAD_NUM()
      PRINT *, 'Thread',TID,':   A,B,X=',A,B,X
!$OMP END PARALLEL

      END
