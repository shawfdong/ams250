#-----------------------------------------------------------------------
# This file contains the compiler options for the PGI C and Fortran
# compilers on Linux, Mac OS and Windows.
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
CC      = pgcc
FTN     = pgf90

#-----------------------------------------------------------------------
# General options, shared across Fortran and C
#-----------------------------------------------------------------------
OPT       = -fastsse
C_OMP     = -mp -Minfo
FTN_OMP   = -mp -Minfo

#-----------------------------------------------------------------------
# Options specific to C
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# Options specific to Fortran
#-----------------------------------------------------------------------
FORMAT    = -Mfree

#-----------------------------------------------------------------------
# No changes needed below this line
#-----------------------------------------------------------------------
CFLAGS  = $(OPT)
FFLAGS  = $(OPT) $(FORMAT)
LDFLAGS = $(OPT)
LIBS    = 
