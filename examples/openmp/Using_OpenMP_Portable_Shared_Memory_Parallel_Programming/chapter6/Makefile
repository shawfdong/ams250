#----------------------------------------------------
# This is the make file for the example programs
# in Chapter 6 of the book 'Using OpenMP'
#----------------------------------------------------

include ../include/make.inc

#include ../include/gnu-compilers.h
#include ../include/ibm-compilers.h
#include ../include/intel-compilers-linux.h
#include ../include/intel-compilers-macos.h
#include ../include/pgi-compilers.h
#include ../include/sun-studio-compilers.h

#-----------------------------------------------------------------------
# Make file for the source examples given in Chapter 6 of the book
# "Using OpenMP"
#-----------------------------------------------------------------------

.IGNORE:

.SUFFIXES: .c .o

OBJ-FIG6.22 = fig6.22-overlap-comp-io.o
EXE-FIG6.22 = fig6.22.exe

help:
	@echo Command to build all example programs:
	@echo "   "make build
	@echo
	@echo Command to run all example programs:
	@echo "   "make run
	@echo
	@echo Targets to build individual examples:
	@echo "   $(EXE-FIG6.22)  - Overlap parallel computations and I/O (use the -h option for more info)"
	@echo
	@echo Targets to run individual examples:
	@echo "    run-$(EXE-FIG6.22)"
	@echo 
	@echo Command to remove all objects and executables:
	@echo "   "make clean

build: \
    $(EXE-FIG6.22)

run: \
    run-$(EXE-FIG6.22)

$(EXE-FIG6.22): $(OBJ-FIG6.22)
	$(CC) -o $(EXE-FIG6.22) $(OBJ-FIG6.22) $(LDFLAGS) $(C_OMP)

run-$(EXE-FIG6.22):
	@./$(EXE-FIG6.22)

.c.o: 
	$(CC) -c $(CFLAGS) $(C_OMP) $*.c
.f.o:
	$(FTN) -c $(FFLAGS) $(FTN_OMP) $*.f

clean:
	@/bin/rm -f $(OBJ-FIG6.22) $(EXE-FIG6.22) *file-io.bin
