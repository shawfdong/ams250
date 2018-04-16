#-----------------------------------------------------------------------
# This file contains the compiler options for the IBM C and Fortran
# compilers on AIX and Linux.
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
CC      = xlc_r
FTN     = xlf90_r

#-----------------------------------------------------------------------
# General options, shared across Fortran and C
#-----------------------------------------------------------------------
OPT       =
C_OMP     = -qsmp=omp
FTN_OMP   = -qsmp=omp

#-----------------------------------------------------------------------
# Options specific to C
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# Options specific to Fortran
#-----------------------------------------------------------------------
#FORMAT    = -qfixed (for fixed form) or -qfree (for free form)
FORMAT    = -qfree=f90

#-----------------------------------------------------------------------
# No changes needed below this line
#-----------------------------------------------------------------------
CFLAGS  = $(OPT)
FFLAGS  = $(OPT) $(FORMAT)
LDFLAGS = $(OPT)
LIBS    =
