#!/bin/bash -l

#SBATCH –J mpi
#SBATCH –p regular
#SBATCH –c haswell
#SBATCH –N 2
#SBATCH –t 4:00:00
#SBATCH –L SCRATCH
#SBATCH –-mail-user=shaw@ucsc.edu
#SBATCH –-mail-type=ALL

srun -n 64 ./mpi_hello.x
