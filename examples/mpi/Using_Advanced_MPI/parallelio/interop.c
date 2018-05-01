MPI_Aint lb, extent, extent_in_file;
MPI_Datatype etype, filetype, contig;
MPI_Offset disp;
MPI_File fh;
int buf[1000];

MPI_File_open(MPI_COMM_WORLD, "/pfs/datafile", 
              MPI_MODE_CREATE | MPI_MODE_RDWR, 
              MPI_INFO_NULL, &fh);

MPI_File_set_view(fh, 0, MPI_BYTE, MPI_BYTE, "external32", 
                  MPI_INFO_NULL);
MPI_File_get_type_extent(fh, MPI_INT, &extent_in_file);

MPI_Type_contiguous(2, MPI_INT, &contig);
lb = 0;
extent = 6 * extent_in_file;
MPI_Type_create_resized(contig, lb, extent, &filetype);
MPI_Type_commit(&filetype);

disp = 5 * extent_in_file;
etype = MPI_INT;

MPI_File_set_view(fh, disp, etype, filetype, "external32", 
                  MPI_INFO_NULL);
MPI_File_write(fh, buf, 1000, MPI_INT, MPI_STATUS_IGNORE);
