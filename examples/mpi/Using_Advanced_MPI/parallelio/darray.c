gsizes[0] = m;    /* no. of rows in global array */
gsizes[1] = n;    /* no. of columns in global array*/

distribs[0] = MPI_DISTRIBUTE_BLOCK;  /* block distribution */
distribs[1] = MPI_DISTRIBUTE_BLOCK;  /* block distribution */

dargs[0] = MPI_DISTRIBUTE_DFLT_DARG; /* default block size */
dargs[1] = MPI_DISTRIBUTE_DFLT_DARG; /* default block size */

psizes[0] = 2;  /* no. of processes in vertical dimension 
                   of process grid */
psizes[1] = 3;  /* no. of processes in horizontal dimension 
                   of process grid */

MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Type_create_darray(6, rank, 2, gsizes, distribs, dargs, 
                       psizes, MPI_ORDER_C, MPI_FLOAT, &filetype);
MPI_Type_commit(&filetype);

MPI_File_open(MPI_COMM_WORLD, "/pfs/datafile", 
              MPI_MODE_CREATE | MPI_MODE_WRONLY, 
              MPI_INFO_NULL, &fh);

MPI_File_set_view(fh, 0, MPI_FLOAT, filetype, "native", 
                  MPI_INFO_NULL);

local_array_size = num_local_rows * num_local_cols;
MPI_File_write_all(fh, local_array, local_array_size, 
		   MPI_FLOAT, &status);

MPI_File_close(&fh);
