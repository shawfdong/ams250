#----------------------------------------------------
# This is the make file for the example programs
# in Chapter 3 of the book 'Using OpenMP'
#----------------------------------------------------

include ../include/make.inc

#include ../include/gnu-compilers.h
#include ../include/ibm-compilers.h
#include ../include/intel-compilers-linux.h
#include ../include/intel-compilers-macos.h
#include ../include/pgi-compilers.h
#include ../include/sun-studio-compilers.h

#-----------------------------------------------------------------------
# Make file for the source examples given in Chapter 3 of the book
# "Using OpenMP"
#-----------------------------------------------------------------------

.IGNORE:

.SUFFIXES: .f90 .c .o 

M_DIM = 1000
N_DIM = 1000
NTHREADS = 2

OBJ-FIG3.5  = fig3.5-mxv-serial.o
OBJ-FIG3.10 = fig3.10-mxv-omp.o

EXE-FIG3.5  = fig3.5.exe
EXE-FIG3.10 = fig3.10.exe

OBJ-FIG3.6  = fig3.6-mxv-serial.o
OBJ-FIG3.11 = fig3.11-mxv-omp.o

EXE-FIG3.6  = fig3.6.exe
EXE-FIG3.11 = fig3.11.exe

OBJ-FIG3.12 = fig3.12-conditional-comp.o
EXE-FIG3.12 = fig3.12.exe

OBJ-FIG3.16 = fig3.16-conditional-comp.o
EXE-FIG3.16 = fig3.16.exe

help:
	@echo "Command to build all example programs:"
	@echo "    make build"
	@echo
	@echo Command to run all example programs:
	@echo "    make run"
	@echo
	@echo "Targets to build individual examples:"
	@echo "   $(EXE-FIG3.5)  - Sequential version of MXV in C"
	@echo "   $(EXE-FIG3.6)  - Sequential version of MXV in Fortran"
	@echo "   $(EXE-FIG3.10) - OpenMP version in C"
	@echo "   $(EXE-FIG3.11) - OpenMP version in Fortran"
	@echo "   $(EXE-FIG3.12) - Conditional compilation in C"
	@echo "   $(EXE-FIG3.16) - Conditional compilation in Fortran"
	@echo
	@echo "Targets to run individual examples:"
	@echo "    run-$(EXE-FIG3.5)"
	@echo "    run-$(EXE-FIG3.6)"
	@echo "    run-$(EXE-FIG3.10)"
	@echo "    run-$(EXE-FIG3.11)"
	@echo "    run-$(EXE-FIG3.12)"
	@echo "    run-$(EXE-FIG3.16)"
	@echo 
	@echo "Command to remove all objects and executables:"
	@echo "    make clean"

build: $(EXE-FIG3.5)  \
       $(EXE-FIG3.6)  \
       $(EXE-FIG3.10) \
       $(EXE-FIG3.11) \
       $(EXE-FIG3.12) \
       $(EXE-FIG3.16)

run: run-$(EXE-FIG3.5)  \
     run-$(EXE-FIG3.6)  \
     run-$(EXE-FIG3.10) \
     run-$(EXE-FIG3.11) \
     run-$(EXE-FIG3.12) \
     run-$(EXE-FIG3.16)

$(EXE-FIG3.5): $(OBJ-FIG3.5)
	$(CC) -o $(EXE-FIG3.5) $(OBJ-FIG3.5) $(LDFLAGS)
$(EXE-FIG3.10): $(OBJ-FIG3.10)
	$(CC) -o $(EXE-FIG3.10) $(OBJ-FIG3.10) $(LDFLAGS) $(C_OMP)
$(EXE-FIG3.12): $(OBJ-FIG3.12)
	$(CC) -o $(EXE-FIG3.12) $(OBJ-FIG3.12) $(LDFLAGS) $(C_OMP)

$(EXE-FIG3.6): $(OBJ-FIG3.6)
	$(FTN) -o $(EXE-FIG3.6) $(OBJ-FIG3.6) $(LDFLAGS)
$(EXE-FIG3.11): $(OBJ-FIG3.11)
	$(FTN) -o $(EXE-FIG3.11) $(OBJ-FIG3.11) $(LDFLAGS) $(FTN_OMP)
$(EXE-FIG3.16): $(OBJ-FIG3.16)
	$(FTN) -o $(EXE-FIG3.16) $(OBJ-FIG3.16) $(LDFLAGS) $(FTN_OMP)

run-$(EXE-FIG3.5):
	@(OMP_NUM_THREADS=1; export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-FIG3.5) < INPUT ;\
	  /bin/rm INPUT)

run-$(EXE-FIG3.6):
	@(OMP_NUM_THREADS=1; export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-FIG3.6) < INPUT ;\
	  /bin/rm INPUT)

run-$(EXE-FIG3.10):
	@(OMP_NUM_THREADS=$(NTHREADS); export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-FIG3.10) < INPUT ;\
	  /bin/rm INPUT)

run-$(EXE-FIG3.11):
	@(OMP_NUM_THREADS=$(NTHREADS); export OMP_NUM_THREADS;\
	  echo "$(M_DIM) $(N_DIM)" > INPUT ;\
	  ./$(EXE-FIG3.11) < INPUT ;\
	  /bin/rm INPUT)

run-$(EXE-FIG3.12):
	@./$(EXE-FIG3.12)

run-$(EXE-FIG3.16):
	@./$(EXE-FIG3.16)

fig3.5-mxv-serial.o: fig3.5-mxv-serial.c
	$(CC) -c $(CFLAGS) $*.c
fig3.6-mxv-serial.o: fig3.6-mxv-serial.f90
	$(FTN) -c $(FFLAGS) $*.f90

.c.o: 
	$(CC) -c $(CFLAGS) $(C_OMP) $*.c
.f90.o:
	$(FTN) -c $(FFLAGS) $(FTN_OMP) $*.f90

clean:
	@/bin/rm -f $(OBJ-FIG3.5)  $(EXE-FIG3.5)
	@/bin/rm -f $(OBJ-FIG3.6)  $(EXE-FIG3.6)
	@/bin/rm -f $(OBJ-FIG3.10) $(EXE-FIG3.10)
	@/bin/rm -f $(OBJ-FIG3.11) $(EXE-FIG3.11)
	@/bin/rm -f $(OBJ-FIG3.12) $(EXE-FIG3.12)
	@/bin/rm -f $(OBJ-FIG3.16) $(EXE-FIG3.16)
