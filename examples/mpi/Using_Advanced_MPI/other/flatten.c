#include "mpi.h"
#include <stdlib.h>

typedef struct {
  MPI_Aint *offsets;
  int *lengths;
  int n;  /*no. of entries in the offsets and lengths arrays*/
  int ref_count; /* reference count */
} flat_struct;

void Flatten_datatype(MPI_Datatype datatype)
{
  flat_struct *flat_dtype;
  int key;

  flat_dtype = (flat_struct *) malloc(sizeof(flat_struct));
  flat_dtype->ref_count = 1;

  /* code for allocating memory for the arrays "offsets" and 
     "lengths" and for flattening the datatype and filling in the
     offsets and lengths arrays goes here */

  MPI_Type_create_keyval(Copy_fn, Delete_fn, &key, (void *) 0);
  MPI_Type_set_attr(datatype, key, flat_dtype);
}
