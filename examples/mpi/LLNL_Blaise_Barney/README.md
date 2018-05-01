This folder holds the example codes for the [Message Passing Interface (MPI) tutorial](https://computing.llnl.gov/tutorials/mpi), authored by Blaise Barney, Lawrence Livermore National Laboratory.

Note there is a bug in the following codes that can lead to **deadlock**:
* [mpi_contig.c](https://github.com/shawfdong/ams250/blob/master/examples/mpi/LLNL_Blaise_Barney/mpi_contig.c) & [mpi_contig.f](https://github.com/shawfdong/ams250/blob/master/examples/mpi/LLNL_Blaise_Barney/mpi_contig.f)]
* [mpi_vector.c](https://github.com/shawfdong/ams250/blob/master/examples/mpi/LLNL_Blaise_Barney/mpi_vectotr.c) & [mpi_vector.f](https://github.com/shawfdong/ams250/blob/master/examples/mpi/LLNL_Blaise_Barney/mpi_vectotr.f)]
* [mpi_indexed.c](https://github.com/shawfdong/ams250/blob/master/examples/mpi/LLNL_Blaise_Barney/mpi_indexed.c) & [mpi_indexed.f](https://github.com/shawfdong/ams250/blob/master/examples/mpi/LLNL_Blaise_Barney/mpi_indexed.f)]
* [mpi_struct.c](https://github.com/shawfdong/ams250/blob/master/examples/mpi/LLNL_Blaise_Barney/mpi_struct.c) & [mpi_struct.f](https://github.com/shawfdong/ams250/blob/master/examples/mpi/LLNL_Blaise_Barney/mpi_struct.f)]

I've applied some simple fixes to those codes. Here are the links to the fixed versions:
* [mpi_contig_fixed.c](https://github.com/shawfdong/ams250/blob/master/examples/mpi/mpi_contig_fixed.c) & [mpi_contig_fixed.f](https://github.com/shawfdong/ams250/blob/master/examples/mpi/mpi_contig_fixed.f)]
* [mpi_vector_fixed.c](https://github.com/shawfdong/ams250/blob/master/examples/mpi/mpi_vectotr_fixed.c) & [mpi_vector_fixed.f](https://github.com/shawfdong/ams250/blob/master/examples/mpi/mpi_vectotr_fixed.f)]
* [mpi_indexed_fixed.c](https://github.com/shawfdong/ams250/blob/master/examples/mpi/mpi_indexed_fixed.c) & [mpi_indexed_fixed.f](https://github.com/shawfdong/ams250/blob/master/examples/mpi/mpi_indexed_fixed.f)]
* [mpi_struct_fixed.c](https://github.com/shawfdong/ams250/blob/master/examples/mpi/mpi_struct_fixed.c) & [mpi_struct_fixed.f](https://github.com/shawfdong/ams250/blob/master/examples/mpi/mpi_struct_fixed.f)]
