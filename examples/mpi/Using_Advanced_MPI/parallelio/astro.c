MPI_File_open(MPI_COMM_WORLD, "/pfs/restartfile", 
              MPI_MODE_CREATE | MPI_MODE_WRONLY, 
              MPI_INFO_NULL, &fh);

MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
if (rank == 0) 
    MPI_File_write(fh, header, 6, MPI_FLOAT, &status);

for (i=0; i<3; i++) {
    gsizes[i] = global_size_in_each_dim;
    distribs[i] = MPI_DISTRIBUTE_BLOCK;
    dargs[i] = MPI_DISTRIBUTE_DFLT_DARG;
    psizes[i] = 0;
}
MPI_Dims_create(nprocs, 3, psizes);
MPI_Type_create_darray(nprocs, rank, 3, gsizes, distribs, dargs,
                       psizes, MPI_ORDER_FORTRAN, MPI_FLOAT, 
                       &filetype);
MPI_Type_commit(&filetype);

MPI_File_set_view(fh, 6*sizeof(float), MPI_FLOAT, filetype, 
                  "native", MPI_INFO_NULL);

MPI_File_write_all(fh, array1, local_array_size, MPI_FLOAT, 
		   MPI_STATUS_IGNORE);
MPI_File_write_all(fh, array2, local_array_size, MPI_FLOAT, 
		   MPI_STATUS_IGNORE);
MPI_File_write_all(fh, array3, local_array_size, MPI_FLOAT, 
		   MPI_STATUS_IGNORE);
MPI_File_write_all(fh, array4, local_array_size, MPI_FLOAT, 
		   MPI_STATUS_IGNORE);
MPI_File_write_all(fh, array5, local_array_size, MPI_FLOAT, 
		   MPI_STATUS_IGNORE);
MPI_File_write_all(fh, array6, local_array_size, MPI_FLOAT, 
		   MPI_STATUS_IGNORE);
MPI_File_close(&fh);
