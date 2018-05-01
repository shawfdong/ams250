/* query the default values of hints being used */
#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int i, nkeys, flag, rank;
    MPI_File fh;
    MPI_Info info_used;
    char key[MPI_MAX_INFO_KEY], value[MPI_MAX_INFO_VAL];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_File_open(MPI_COMM_WORLD, "/pfs/datafile",
		  MPI_MODE_CREATE | MPI_MODE_RDWR,
                  MPI_INFO_NULL, &fh);

    MPI_File_get_info(fh, &info_used);
    MPI_Info_get_nkeys(info_used, &nkeys);

    for (i=0; i<nkeys; i++) {
	MPI_Info_get_nthkey(info_used, i, key);
	MPI_Info_get(info_used, key, MPI_MAX_INFO_VAL,
                     value, &flag);
	printf("Process %d, Default: key = %s, value = %s\n",
               rank, key, value);
    }

    MPI_File_close(&fh);
    MPI_Info_free(&info_used);

    MPI_Finalize();
    return 0;
}
