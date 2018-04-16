#-----------------------------------------------------------------------
# This file contains the compiler options for the Sun Studio compilers
# on Solaris and Linux.
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
CC      = cc
FTN     = f95

#-----------------------------------------------------------------------
# General options, shared across Fortran and C
#-----------------------------------------------------------------------
OPT       = -xO3
C_OMP     = -xopenmp -xloopinfo 
FTN_OMP   = -xopenmp -xloopinfo

#-----------------------------------------------------------------------
# Options specific to C
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# Options specific to Fortran
#-----------------------------------------------------------------------
FORMAT    = 

#-----------------------------------------------------------------------
# No changes needed below this line
#-----------------------------------------------------------------------
CFLAGS  = $(OPT)
FFLAGS  = $(OPT) $(FORMAT)
LDFLAGS = $(OPT)
LIBS    = 
