#----------------------------------------------------
# This is the make file for the example programs
# in Chapter 7 of the book 'Using OpenMP'
#----------------------------------------------------

include ../include/make.inc

#include ../include/gnu-compilers.h
#include ../include/ibm-compilers.h
#include ../include/intel-compilers-linux.h
#include ../include/intel-compilers-macos.h
#include ../include/pgi-compilers.h
#include ../include/sun-studio-compilers.h

#-----------------------------------------------------------------------
# Make file for the source examples given in Chapter 7 of the book
# "Using OpenMP"
#-----------------------------------------------------------------------

.IGNORE:

.SUFFIXES: .f90 .c .o

OBJ-FIG7.7  = fig7.7-first-lastprivate.o
EXE-FIG7.7  = fig7.7.exe
OBJ-FIG7.11 = fig7.11-nested-parallel.o
EXE-FIG7.11 = fig7.11.exe
OBJ-FIG7.20 = fig7.20-flush.o
EXE-FIG7.20 = fig7.20.exe

help:
	@echo Command to build all example programs:
	@echo "   "make build
	@echo
	@echo Command to run all example programs:
	@echo "   "make run
	@echo
	@echo Targets to build individual examples:
	@echo "   $(EXE-FIG7.7)  - Correst use of firstpriate and lastprivate"
	@echo "   $(EXE-FIG7.11) - Correst use of nested parallelism"
	@echo "   $(EXE-FIG7.20) - Correst use of the flush directive"
	@echo
	@echo "Targets to run individual examples:"
	@echo "    run-$(EXE-FIG7.7)"
	@echo "    run-$(EXE-FIG7.11)"
	@echo "    run-$(EXE-FIG7.20)"
	@echo 
	@echo Command to remove all objects and executables:
	@echo "   "make clean

build: \
    $(EXE-FIG7.7)  \
    $(EXE-FIG7.11) \
    $(EXE-FIG7.20)

run: \
    run-$(EXE-FIG7.7)  \
    run-$(EXE-FIG7.11) \
    run-$(EXE-FIG7.20)

$(EXE-FIG7.7): $(OBJ-FIG7.7)
	$(CC) -o $(EXE-FIG7.7) $(OBJ-FIG7.7) $(LDFLAGS) $(C_OMP)
$(EXE-FIG7.11): $(OBJ-FIG7.11)
	$(CC) -o $(EXE-FIG7.11) $(OBJ-FIG7.11) $(LDFLAGS) $(C_OMP)
$(EXE-FIG7.20): $(OBJ-FIG7.20)
	$(FTN) -o $(EXE-FIG7.20) $(OBJ-FIG7.20) $(LDFLAGS) $(FTN_OMP)

run-$(EXE-FIG7.7):
	@./$(EXE-FIG7.7)
run-$(EXE-FIG7.11):
	@./$(EXE-FIG7.11)
run-$(EXE-FIG7.20):
	@./$(EXE-FIG7.20)

.c.o: 
	$(CC) -c $(CFLAGS) $(C_OMP) $*.c
.f90.o:
	$(FTN) -c $(FFLAGS) $(FTN_OMP) $*.f90

clean:
	@/bin/rm -f $(OBJ-FIG7.7)  $(EXE-FIG7.7)
	@/bin/rm -f $(OBJ-FIG7.11) $(EXE-FIG7.11)
	@/bin/rm -f $(OBJ-FIG7.20) $(EXE-FIG7.20)
