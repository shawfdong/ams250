! write to a common file using file view
PROGRAM main
  use mpi
  integer FILESIZE, ierr, i, rank, size, intsize, nints, fh
  parameter (FILESIZE=1048756)
  integer buf(FILESIZE)
  integer(kind=MPI_OFFSET_KIND) disp
  call MPI_INIT(ierr)
  call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
  call MPI_COMM_SIZE(MPI_COMM_WORLD, size, ierr)
  call MPI_TYPE_SIZE(MPI_INTEGER, intsize, ierr)
  nints = FILESIZE/(size*intsize)
  do i = 1, nints
    buf(i) = rank * nints + i - 1
  enddo
  call MPI_FILE_OPEN(MPI_COMM_WORLD, 'datafile', &
                     MPI_MODE_WRONLY + MPI_MODE_CREATE, MPI_INFO_NULL, fh, ierr)
  disp = rank * nints * intsize
  call MPI_FILE_SET_VIEW(fh, disp, MPI_INTEGER, MPI_INTEGER, 'native', &
                         MPI_INFO_NULL, ierr)
  call MPI_FILE_WRITE(fh, buf, nints, MPI_INTEGER, MPI_STATUS_IGNORE, ierr)
  call MPI_FILE_CLOSE(fh, ierr)
  call MPI_FINALIZE(ierr)
END PROGRAM main
