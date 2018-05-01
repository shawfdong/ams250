gsizes[0] = m;    gsizes[1] = n;    
/* no. of rows and columns in global array*/
psizes[0] = 2;    psizes[1] = 3;    
/* no. of processes in vertical and horizontal dimensions 
   of process grid */
lsizes[0] = m/psizes[0];   /* no. of rows in local array */
lsizes[1] = n/psizes[1];   /* no. of columns in local array */
dims[0] = 2;   dims[1] = 3;
periods[0] = periods[1] = 1;
MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm);
MPI_Comm_rank(comm, &rank);
MPI_Cart_coords(comm, rank, 2, coords);
/* global indices of the first element of the local array */
start_indices[0] = coords[0] * lsizes[0];
start_indices[1] = coords[1] * lsizes[1];
MPI_Type_create_subarray(2, gsizes, lsizes, start_indices, 
                         MPI_ORDER_C, MPI_FLOAT, &filetype);
MPI_Type_commit(&filetype);
MPI_File_open(comm, "/pfs/datafile", 
              MPI_MODE_CREATE | MPI_MODE_WRONLY, 
	      MPI_INFO_NULL, &fh);
MPI_File_set_view(fh, 0, MPI_FLOAT, filetype, "native", 
		  MPI_INFO_NULL);
/* create a derived datatype that describes the layout of the 
   local array in the memory buffer that includes the ghost 
   area. This is another subarray datatype! */
memsizes[0] = lsizes[0] + 8; /* no. of rows in allocated array */
memsizes[1] = lsizes[1] + 8; /* no. of cols in allocated array */
start_indices[0] = start_indices[1] = 4; 
/* indices of the first element of the local array in the
   allocated array */
MPI_Type_create_subarray(2, memsizes, lsizes, start_indices, 
                         MPI_ORDER_C, MPI_FLOAT, &memtype);
MPI_Type_commit(&memtype);
MPI_File_write_all(fh, local_array, 1, memtype, &status);
MPI_File_close(&fh);
