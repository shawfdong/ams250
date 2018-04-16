!     PARALLEL DO Directive Example
      PROGRAM VEC_ADD_DO

      INTEGER N, I, CHUNKSIZE, CHUNK
      PARAMETER (N=1000)
      PARAMETER (CHUNKSIZE=100)
      REAL A(N), B(N), C(N)

!     Some initializations
      DO I = 1, N
        A(I) = I * 1.0
        B(I) = A(I)
      ENDDO
      CHUNK = CHUNKSIZE

!$OMP PARALLEL DO
!$OMP& SHARED(A,B,C,CHUNK) PRIVATE(I)
!$OMP& SCHEDULE(STATIC,CHUNK)

      DO I = 1, N
        C(I) = A(I) + B(I)
      ENDDO

!$OMP END PARALLEL DO

      END
