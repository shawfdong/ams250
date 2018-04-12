#!/bin/bash

#PBS -N jobarray
#PBS -q normal
#PBS -l ncpus=1
#PBS -t 101-104
#PBS -l walltime=0:20:00
#PBS -M shaw@ucsc.edu
#PBS -m abe

cd $PBS_O_WORKDIR
./jobarray_hello.x $PBS_ARRAYID
