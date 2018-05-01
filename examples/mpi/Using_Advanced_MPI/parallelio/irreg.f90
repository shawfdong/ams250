SUBROUTINE write_irreg_array(buf, map, bufsize)
  use mpi
 
  integer bufsize
  double precision buf(bufsize)
  integer map(bufsize), fh, filetype, status(MPI_STATUS_SIZE)
  integer (kind=MPI_OFFSET_KIND) disp
  integer i, ierr
  
  call MPI_FILE_OPEN(MPI_COMM_WORLD, '/pfs/datafile', &
                     MPI_MODE_CREATE + MPI_MODE_RDWR, &
                     MPI_INFO_NULL, fh, ierr)

  call MPI_TYPE_CREATE_INDEXED_BLOCK(bufsize, 1, map, &
                        MPI_DOUBLE_PRECISION, filetype, ierr)
  call MPI_TYPE_COMMIT(filetype, ierr)
  disp = 0
  call MPI_FILE_SET_VIEW(fh, disp, MPI_DOUBLE_PRECISION, &
                         filetype, 'native', MPI_INFO_NULL, ierr)

  call MPI_FILE_WRITE_ALL(fh, buf, bufsize, &
                          MPI_DOUBLE_PRECISION, status, ierr)

  call MPI_FILE_CLOSE(fh, ierr)
  
  return
END SUBROUTINE write_irreg_array
