!     REDUCTION Clause Example
      PROGRAM DOT_PRODUCT

      INTEGER N, CHUNKSIZE, CHUNK, I
      PARAMETER (N=100)
      PARAMETER (CHUNKSIZE=10)
      REAL A(N), B(N), RESULT

!     Some initializations
      DO I = 1, N
        A(I) = I * 1.0
        B(I) = I * 2.0
      ENDDO
      RESULT= 0.0
      CHUNK = CHUNKSIZE

!$OMP  PARALLEL DO
!$OMP& DEFAULT(SHARED) PRIVATE(I)
!$OMP& SCHEDULE(STATIC,CHUNK)
!$OMP& REDUCTION(+:RESULT)

      DO I = 1, N
        RESULT = RESULT + (A(I) * B(I))
      ENDDO

!$OMP  END PARALLEL DO

      PRINT *, 'Final Result= ', RESULT
      END
