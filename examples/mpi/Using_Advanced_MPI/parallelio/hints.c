MPI_File fh;  MPI_Info info;

MPI_Info_create(&info);

/* FOLLOWING HINTS ARE PREDEFINED IN MPI */

/* no. of I/O devices across which the file should be striped */
MPI_Info_set(info, "striping_factor", "16");

/* the striping unit in bytes */
MPI_Info_set(info, "striping_unit", "1048576");

/* buffer size for collective I/O */
MPI_Info_set(info, "cb_buffer_size", "8388608");

/* no. of processes that should perform disk accesses 
   during collective I/O */
MPI_Info_set(info, "cb_nodes", "16");

/* FOLLOWING ARE ADDITIONAL HINTS SUPPORTED BY ROMIO */

/* buffer size for data sieving in independent reads */
MPI_Info_set(info, "ind_rd_buffer_size", "2097152");

/* buffer size for data sieving in independent writes */
MPI_Info_set(info, "ind_wr_buffer_size", "1048576");

/* NOW OPEN THE FILE WITH THIS INFO OBJECT */
MPI_File_open(MPI_COMM_WORLD, "/pfs/datafile", 
	      MPI_MODE_CREATE | MPI_MODE_RDWR, info, &fh);

MPI_Info_free(&info);  /* free the info object */
