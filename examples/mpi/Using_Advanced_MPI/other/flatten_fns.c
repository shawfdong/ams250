int Copy_fn(MPI_Datatype datatype, int key, void *extra_state,
	    void *attr_val_in, void *attr_val_out, int *flag)
{
  ((flat_struct *) attr_val_in)->ref_count += 1;
  *((flat_struct **) attr_val_out) = (flat_struct *) attr_val_in;
  *flag = 1;
  return MPI_SUCCESS;
}

int Delete_fn(MPI_Datatype datatype, int key, void *attr_val, 
	      void *extra_state)
{
  flat_struct *flat_dtype;

  flat_dtype = (flat_struct *) attr_val;
  flat_dtype->ref_count -= 1;
  if (flat_dtype->ref_count == 0) {
    free(flat_dtype->offsets);
    free(flat_dtype->lengths);
    free(flat_dtype);
  }
  return MPI_SUCCESS;
}
