#-----------------------------------------------------------------------
# This file contains the compiler options for the GNU C and Fortran
# compilers on Linux.
#
# Make variables are used to set up the following variables that are
# used to compile and link the various programs:
#
# CFLAGS    - Serial options for the C compiler
# FFLAGS    - Serial options for the Fortran compiler
# C_OMP     - Option(s) to activate OpenMP in the C compiler
# FTN_OMP   - Option(s) to activate OpenMP in the Fortran compiler
# LDFLAGS   - Serial options for the loader
#
# Ruud van der Pas, Sun Microsystems
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# Names of compilers. The default search path is assumed to include the
# C and Fortran compilers.
#-----------------------------------------------------------------------
CC      = gcc
FTN     = gfortran

#-----------------------------------------------------------------------
# General options, shared across Fortran and C
#-----------------------------------------------------------------------
OPT       = -O
C_OMP     = -fopenmp 
FTN_OMP   = -fopenmp

#-----------------------------------------------------------------------
# Options specific to C
#-----------------------------------------------------------------------
STD       = -std=gnu9x # C99 plus GNU extensions (needed for getopt)

#-----------------------------------------------------------------------
# Options specific to Fortran
#-----------------------------------------------------------------------
FORMAT    = 

#-----------------------------------------------------------------------
# No changes needed below this line
#-----------------------------------------------------------------------
CFLAGS  = $(OPT) $(STD)
FFLAGS  = $(OPT) $(FORMAT)
LDFLAGS = $(OPT)
LIBS    = 
