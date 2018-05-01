#include "mpi.h"
#include <stdlib.h>
/* We make GA a pointer to this structure so that users always
   have a pointer, never the actual structure */
typedef struct _GA {
    MPI_Win      ga_win;
    MPI_Win      lock_win;
    /* Datatype and size */
    MPI_Datatype dtype;
    int          dtype_size;
    /* sizes of the global array */
    int          dim1, dim2, chunk2;
} *GA;
