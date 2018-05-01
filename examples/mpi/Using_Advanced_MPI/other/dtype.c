#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

void is_type_hvector(MPI_Datatype datatype)
{
 int nints, nadds, ntypes, combiner, *ints;
 MPI_Aint *adds;
 MPI_Datatype *types;

 MPI_Type_get_envelope(datatype, &nints, &nadds, &ntypes,
 	  &combiner);
 
 if (combiner != MPI_COMBINER_HVECTOR)
  printf("not type_hvector\n");
 else {
  printf("is type_hvector\n");
  ints = (int *) malloc(nints*sizeof(int));
  adds = (MPI_Aint *) malloc(nadds*sizeof(MPI_Aint));
  types = (MPI_Datatype *) malloc(ntypes*sizeof(MPI_Datatype));

  MPI_Type_get_contents(datatype, nints, nadds, ntypes, 
            ints, adds, types);
  printf("count = %d, blocklength = %d, stride = %ld\n", 
         ints[0], ints[1], adds[0]);
  free(ints);
  free(adds);
  free(types);
 }
}
