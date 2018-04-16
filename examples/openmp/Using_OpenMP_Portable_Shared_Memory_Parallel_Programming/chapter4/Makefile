#----------------------------------------------------
# This is the make file for the example programs
# in Chapter 4 of the book 'Using OpenMP'
#----------------------------------------------------

include ../include/make.inc

#include ../include/gnu-compilers.h
#include ../include/ibm-compilers.h
#include ../include/intel-compilers-linux.h
#include ../include/intel-compilers-macos.h
#include ../include/pgi-compilers.h
#include ../include/sun-studio-compilers.h

#-----------------------------------------------------------------------
# Make file for the source examples given in Chapter 4 of the book
# "Using OpenMP"
#-----------------------------------------------------------------------

.IGNORE:

.SUFFIXES: .f90 .c .o

OBJ-FIG4.3  = fig4.3-parallel-region.o
EXE-FIG4.3  = fig4.3.exe
OBJ-FIG4.10 = fig4.10-for-loop.o
EXE-FIG4.10 = fig4.10.exe
OBJ-FIG4.12 = fig4.12-two-for-loops.o
EXE-FIG4.12 = fig4.12.exe
OBJ-FIG4.16 = fig4.16-sections.o
EXE-FIG4.16 = fig4.16.exe
OBJ-FIG4.22 = fig4.22-single.o
EXE-FIG4.22 = fig4.22.exe
OBJ-FIG4.26 = fig4.26-workshare.o
EXE-FIG4.26 = fig4.26.exe
OBJ-FIG4.31 = fig4.31-shared-clause.o
EXE-FIG4.31 = fig4.31.exe
OBJ-FIG4.32 = fig4.32-private-clause.o
EXE-FIG4.32 = fig4.32.exe
OBJ-FIG4.34 = fig4.34-lastprivate-clause.o
EXE-FIG4.34 = fig4.34.exe
OBJ-FIG4.36 = fig4.36-lastprivate-alternative.o
EXE-FIG4.36 = fig4.36.exe
OBJ-FIG4.37 = fig4.37-firstprivate-clause.o
EXE-FIG4.37 = fig4.37.exe
OBJ-FIG4.39 = fig4.39-firstprivate-alternative.o
EXE-FIG4.39 = fig4.39.exe
OBJ-FIG4.43 = fig4.43-schedule-clause.o
EXE-FIG4.43 = fig4.43.exe
OBJ-FIG4.47 = fig4.47-barrier.o
EXE-FIG4.47 = fig4.47.exe
OBJ-FIG4.55 = fig4.55-critical-region.o
EXE-FIG4.55 = fig4.55.exe
OBJ-FIG4.57 = fig4.57-critical-region-print.o
EXE-FIG4.57 = fig4.57.exe
OBJ-FIG4.58 = fig4.58-critical-region-minval.o
EXE-FIG4.58 = fig4.58.exe
OBJ-FIG4.61 = fig4.61-atomic.o
EXE-FIG4.61 = fig4.61.exe
OBJ-FIG4.62 = fig4.62-atomic-func.o
EXE-FIG4.62 = fig4.62.exe
OBJ-FIG4.65 = fig4.65-locks.o
EXE-FIG4.65 = fig4.65.exe
OBJ-FIG4.68 = fig4.68-master.o
EXE-FIG4.68 = fig4.68.exe
OBJ-FIG4.70 = fig4.70-if-clause.o
EXE-FIG4.70 = fig4.70.exe
OBJ-FIG4.72 = fig4.72-num-threads-clause.o
EXE-FIG4.72 = fig4.72.exe
OBJ-FIG4.74 = fig4.74-ordered.o
EXE-FIG4.74 = fig4.74.exe
OBJ-FIG4.77 = fig4.77-reduction.o
EXE-FIG4.77 = fig4.77.exe
OBJ-FIG4.79 = fig4.79-reduction-md.o
EXE-FIG4.79 = fig4.79.exe
OBJ-FIG4.84 = fig4.84-array-reduction.o
EXE-FIG4.84 = fig4.84.exe
OBJ-FIG4.85 = fig4.85-nested-parallel.o
EXE-FIG4.85 = fig4.85.exe
OBJ-FIG4.87 = fig4.87-nested-parallel-mod.o
EXE-FIG4.87 = fig4.87.exe
OBJ-FIG4.96 = fig4.96-global-data.o
EXE-FIG4.96 = fig4.96.exe
OBJ-FIG4.98 = fig4.98-threadprivate.o
EXE-FIG4.98 = fig4.98.exe

help:
	@echo Command to build all example programs:
	@echo "   "make build
	@echo
	@echo Command to run all example programs:
	@echo "   "make run
	@echo
	@echo Targets to build individual examples:
	@echo "   $(EXE-FIG4.3)  - Parallel region"
	@echo "   $(EXE-FIG4.10) - Parallel for loop"
	@echo "   $(EXE-FIG4.12) - Two for loops in one parallel region"
	@echo "   $(EXE-FIG4.16) - Parallel sections"
	@echo "   $(EXE-FIG4.22) - Single construct"
	@echo "   $(EXE-FIG4.26) - Fortran workshare construct"
	@echo "   $(EXE-FIG4.31) - Shared clause"
	@echo "   $(EXE-FIG4.32) - Private clause"
	@echo "   $(EXE-FIG4.34) - Lastprivate clause"
	@echo "   $(EXE-FIG4.36) - Lastprivate alternative solution (not recommended)"
	@echo "   $(EXE-FIG4.37) - Firstprivate clause"
	@echo "   $(EXE-FIG4.39) - Firstprivate alternative solution"
	@echo "   $(EXE-FIG4.43) - Schedule clause (executed for various schedules)"
	@echo "   $(EXE-FIG4.47) - Barrier"
	@echo "   $(EXE-FIG4.55) - Critical region"
	@echo "   $(EXE-FIG4.57) - Critical region with print statement"
	@echo "   $(EXE-FIG4.58) - Critical region to compute the minimum value"
	@echo "   $(EXE-FIG4.61) - Atomic update"
	@echo "   $(EXE-FIG4.62) - Atomic update with function call"
	@echo "   $(EXE-FIG4.65) - Locking"
	@echo "   $(EXE-FIG4.68) - Master construct"
	@echo "   $(EXE-FIG4.70) - If clause"
	@echo "   $(EXE-FIG4.72) - Num_threads clause"
	@echo "   $(EXE-FIG4.74) - Ordered construct"
	@echo "   $(EXE-FIG4.77) - Reduction clause"
	@echo "   $(EXE-FIG4.79) - Reduction clause - MD example"
	@echo "   $(EXE-FIG4.84) - Fortran array reduction"
	@echo "   $(EXE-FIG4.85) - Nested parallelism"
	@echo "   $(EXE-FIG4.87) - Nested parallelism - modified version"
	@echo "   $(EXE-FIG4.96) - Global data (serial version)"
	@echo "   $(EXE-FIG4.98) - Global data (threadprivate version)"
	@echo
	@echo "Targets to run individual examples:
	@echo "    run-$(EXE-FIG4.3)"
	@echo "    run-$(EXE-FIG4.10)"
	@echo "    run-$(EXE-FIG4.12)"
	@echo "    run-$(EXE-FIG4.16)"
	@echo "    run-$(EXE-FIG4.22)"
	@echo "    run-$(EXE-FIG4.26)"
	@echo "    run-$(EXE-FIG4.31)"
	@echo "    run-$(EXE-FIG4.32)"
	@echo "    run-$(EXE-FIG4.34)"
	@echo "    run-$(EXE-FIG4.36)"
	@echo "    run-$(EXE-FIG4.37)"
	@echo "    run-$(EXE-FIG4.39)"
	@echo "    run-$(EXE-FIG4.43)"
	@echo "    run-$(EXE-FIG4.47)"
	@echo "    run-$(EXE-FIG4.55)"
	@echo "    run-$(EXE-FIG4.57)"
	@echo "    run-$(EXE-FIG4.58)"
	@echo "    run-$(EXE-FIG4.61)"
	@echo "    run-$(EXE-FIG4.62)"
	@echo "    run-$(EXE-FIG4.65)"
	@echo "    run-$(EXE-FIG4.68)"
	@echo "    run-$(EXE-FIG4.70)"
	@echo "    run-$(EXE-FIG4.72)"
	@echo "    run-$(EXE-FIG4.74)"
	@echo "    run-$(EXE-FIG4.77)"
	@echo "    run-$(EXE-FIG4.79)"
	@echo "    run-$(EXE-FIG4.84)"
	@echo "    run-$(EXE-FIG4.85)"
	@echo "    run-$(EXE-FIG4.87)"
	@echo "    run-$(EXE-FIG4.96)"
	@echo "    run-$(EXE-FIG4.98)"
	@echo 
	@echo Command to remove all objects and executables:
	@echo "   "make clean

build: \
    $(EXE-FIG4.3)  \
    $(EXE-FIG4.10) \
    $(EXE-FIG4.12) \
    $(EXE-FIG4.16) \
    $(EXE-FIG4.22) \
    $(EXE-FIG4.26) \
    $(EXE-FIG4.31) \
    $(EXE-FIG4.32) \
    $(EXE-FIG4.34) \
    $(EXE-FIG4.36) \
    $(EXE-FIG4.37) \
    $(EXE-FIG4.39) \
    $(EXE-FIG4.43) \
    $(EXE-FIG4.47) \
    $(EXE-FIG4.55) \
    $(EXE-FIG4.57) \
    $(EXE-FIG4.58) \
    $(EXE-FIG4.61) \
    $(EXE-FIG4.62) \
    $(EXE-FIG4.65) \
    $(EXE-FIG4.68) \
    $(EXE-FIG4.70) \
    $(EXE-FIG4.72) \
    $(EXE-FIG4.74) \
    $(EXE-FIG4.77) \
    $(EXE-FIG4.79) \
    $(EXE-FIG4.84) \
    $(EXE-FIG4.85) \
    $(EXE-FIG4.87) \
    $(EXE-FIG4.96) \
    $(EXE-FIG4.98)

run: \
    run-$(EXE-FIG4.3)  \
    run-$(EXE-FIG4.10) \
    run-$(EXE-FIG4.12) \
    run-$(EXE-FIG4.16) \
    run-$(EXE-FIG4.22) \
    run-$(EXE-FIG4.26) \
    run-$(EXE-FIG4.31) \
    run-$(EXE-FIG4.32) \
    run-$(EXE-FIG4.34) \
    run-$(EXE-FIG4.36) \
    run-$(EXE-FIG4.37) \
    run-$(EXE-FIG4.39) \
    run-$(EXE-FIG4.43) \
    run-$(EXE-FIG4.47) \
    run-$(EXE-FIG4.55) \
    run-$(EXE-FIG4.57) \
    run-$(EXE-FIG4.58) \
    run-$(EXE-FIG4.61) \
    run-$(EXE-FIG4.62) \
    run-$(EXE-FIG4.65) \
    run-$(EXE-FIG4.68) \
    run-$(EXE-FIG4.70) \
    run-$(EXE-FIG4.72) \
    run-$(EXE-FIG4.74) \
    run-$(EXE-FIG4.77) \
    run-$(EXE-FIG4.79) \
    run-$(EXE-FIG4.84) \
    run-$(EXE-FIG4.85) \
    run-$(EXE-FIG4.87) \
    run-$(EXE-FIG4.96) \
    run-$(EXE-FIG4.98)


$(EXE-FIG4.3): $(OBJ-FIG4.3)
	$(CC) -o $(EXE-FIG4.3) $(OBJ-FIG4.3) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.10): $(OBJ-FIG4.10)
	$(CC) -o $(EXE-FIG4.10) $(OBJ-FIG4.10) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.12): $(OBJ-FIG4.12)
	$(CC) -o $(EXE-FIG4.12) $(OBJ-FIG4.12) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.16): $(OBJ-FIG4.16)
	$(CC) -o $(EXE-FIG4.16) $(OBJ-FIG4.16) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.22): $(OBJ-FIG4.22)
	$(CC) -o $(EXE-FIG4.22) $(OBJ-FIG4.22) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.31): $(OBJ-FIG4.31)
	$(CC) -o $(EXE-FIG4.31) $(OBJ-FIG4.31) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.32): $(OBJ-FIG4.32)
	$(CC) -o $(EXE-FIG4.32) $(OBJ-FIG4.32) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.34): $(OBJ-FIG4.34)
	$(CC) -o $(EXE-FIG4.34) $(OBJ-FIG4.34) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.36): $(OBJ-FIG4.36)
	$(CC) -o $(EXE-FIG4.36) $(OBJ-FIG4.36) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.37): $(OBJ-FIG4.37)
	$(CC) -o $(EXE-FIG4.37) $(OBJ-FIG4.37) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.39): $(OBJ-FIG4.39)
	$(CC) -o $(EXE-FIG4.39) $(OBJ-FIG4.39) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.43): $(OBJ-FIG4.43)
	$(CC) -o $(EXE-FIG4.43) $(OBJ-FIG4.43) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.47): $(OBJ-FIG4.47)
	$(CC) -o $(EXE-FIG4.47) $(OBJ-FIG4.47) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.55): $(OBJ-FIG4.55)
	$(CC) -o $(EXE-FIG4.55) $(OBJ-FIG4.55) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.57): $(OBJ-FIG4.57)
	$(CC) -o $(EXE-FIG4.57) $(OBJ-FIG4.57) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.58): $(OBJ-FIG4.58)
	$(CC) -o $(EXE-FIG4.58) $(OBJ-FIG4.58) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.61): $(OBJ-FIG4.61)
	$(CC) -o $(EXE-FIG4.61) $(OBJ-FIG4.61) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.62): $(OBJ-FIG4.62)
	$(CC) -o $(EXE-FIG4.62) $(OBJ-FIG4.62) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.68): $(OBJ-FIG4.68)
	$(CC) -o $(EXE-FIG4.68) $(OBJ-FIG4.68) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.70): $(OBJ-FIG4.70)
	$(CC) -o $(EXE-FIG4.70) $(OBJ-FIG4.70) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.72): $(OBJ-FIG4.72)
	$(CC) -o $(EXE-FIG4.72) $(OBJ-FIG4.72) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.74): $(OBJ-FIG4.74)
	$(CC) -o $(EXE-FIG4.74) $(OBJ-FIG4.74) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.77): $(OBJ-FIG4.77)
	$(CC) -o $(EXE-FIG4.77) $(OBJ-FIG4.77) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.85): $(OBJ-FIG4.85)
	$(CC) -o $(EXE-FIG4.85) $(OBJ-FIG4.85) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.87): $(OBJ-FIG4.87)
	$(CC) -o $(EXE-FIG4.87) $(OBJ-FIG4.87) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.96): $(OBJ-FIG4.96)
	$(CC) -o $(EXE-FIG4.96) $(OBJ-FIG4.96) $(LDFLAGS) $(C_OMP)
$(EXE-FIG4.98): $(OBJ-FIG4.98)
	$(CC) -o $(EXE-FIG4.98) $(OBJ-FIG4.98) $(LDFLAGS) $(C_OMP)

$(EXE-FIG4.26): $(OBJ-FIG4.26)
	$(FTN) -o $(EXE-FIG4.26) $(OBJ-FIG4.26) $(LDFLAGS) $(FTN_OMP)
$(EXE-FIG4.65): $(OBJ-FIG4.65)
	$(FTN) -o $(EXE-FIG4.65) $(OBJ-FIG4.65) $(LDFLAGS) $(FTN_OMP)
$(EXE-FIG4.79): $(OBJ-FIG4.79)
	$(FTN) -o $(EXE-FIG4.79) $(OBJ-FIG4.79) $(LDFLAGS) $(FTN_OMP)
$(EXE-FIG4.84): $(OBJ-FIG4.84)
	$(FTN) -o $(EXE-FIG4.84) $(OBJ-FIG4.84) $(LDFLAGS) $(FTN_OMP)

run-$(EXE-FIG4.3):
	@./$(EXE-FIG4.3)

run-$(EXE-FIG4.10):
	@./$(EXE-FIG4.10)

run-$(EXE-FIG4.12):
	@./$(EXE-FIG4.12)

run-$(EXE-FIG4.16):
	@./$(EXE-FIG4.16)

run-$(EXE-FIG4.22):
	@./$(EXE-FIG4.22)

run-$(EXE-FIG4.26):
	@./$(EXE-FIG4.26)

run-$(EXE-FIG4.31):
	@./$(EXE-FIG4.31)

run-$(EXE-FIG4.32):
	@./$(EXE-FIG4.32)

run-$(EXE-FIG4.34):
	@./$(EXE-FIG4.34)

run-$(EXE-FIG4.36):
	@./$(EXE-FIG4.36)

run-$(EXE-FIG4.37):
	@./$(EXE-FIG4.37)

run-$(EXE-FIG4.39):
	@./$(EXE-FIG4.39)

run-$(EXE-FIG4.43):
	@(OMP_SCHEDULE=static;export OMP_SCHEDULE;\
    echo "==== Results for schedule(static) ===="   ; OMP_SCHEDULE="static";    ./$(EXE-FIG4.43) | sort -n -k2,2;\
    echo "==== Results for schedule(static,2) ====" ; OMP_SCHEDULE="static,2";  ./$(EXE-FIG4.43) | sort -n -k2,2;\
    echo "==== Results for schedule(dynamic) ===="  ; OMP_SCHEDULE="dynamic";   ./$(EXE-FIG4.43) | sort -n -k2,2;\
    echo "==== Results for schedule(dynamic,2) ===="; OMP_SCHEDULE="dynamic,2"; ./$(EXE-FIG4.43) | sort -n -k2,2;\
    echo "==== Results for schedule(guided) ===="   ; OMP_SCHEDULE="guided";    ./$(EXE-FIG4.43) | sort -n -k2,2;\
    echo "==== Results for schedule(guided,2) ====" ; OMP_SCHEDULE="guided,2";  ./$(EXE-FIG4.43) | sort -n -k2,2;\
    )

run-$(EXE-FIG4.47):
	@./$(EXE-FIG4.47)

run-$(EXE-FIG4.55):
	@./$(EXE-FIG4.55)

run-$(EXE-FIG4.57):
	@./$(EXE-FIG4.57)

run-$(EXE-FIG4.58):
	@./$(EXE-FIG4.58)

run-$(EXE-FIG4.61):
	@./$(EXE-FIG4.61)

run-$(EXE-FIG4.62):
	@./$(EXE-FIG4.62)

run-$(EXE-FIG4.65):
	@./$(EXE-FIG4.65)

run-$(EXE-FIG4.68):
	@./$(EXE-FIG4.68)

run-$(EXE-FIG4.70):
	@./$(EXE-FIG4.70)

run-$(EXE-FIG4.72):
	@./$(EXE-FIG4.72)

run-$(EXE-FIG4.74):
	@(OMP_SCHEDULE=guided;export OMP_SCHEDULE;\
    ./$(EXE-FIG4.74);\
	)

run-$(EXE-FIG4.77):
	@./$(EXE-FIG4.77)

run-$(EXE-FIG4.79):
	@./$(EXE-FIG4.79)

run-$(EXE-FIG4.84):
	@./$(EXE-FIG4.84)

run-$(EXE-FIG4.85):
	@(OMP_NESTED=TRUE; export OMP_NESTED; ./$(EXE-FIG4.85))

run-$(EXE-FIG4.87):
	@(OMP_NESTED=TRUE; export OMP_NESTED; ./$(EXE-FIG4.87))

run-$(EXE-FIG4.96):
	@./$(EXE-FIG4.96)

run-$(EXE-FIG4.98):
	@./$(EXE-FIG4.98)

.c.o: 
	$(CC) -c $(CFLAGS) $(C_OMP) $*.c
.f90.o:
	$(FTN) -c $(FFLAGS) $(FTN_OMP) $*.f90

clean:
	@/bin/rm -f $(OBJ-FIG4.3)  $(EXE-FIG4.3)
	@/bin/rm -f $(OBJ-FIG4.10) $(EXE-FIG4.10)
	@/bin/rm -f $(OBJ-FIG4.12) $(EXE-FIG4.12)
	@/bin/rm -f $(OBJ-FIG4.16) $(EXE-FIG4.16)
	@/bin/rm -f $(OBJ-FIG4.22) $(EXE-FIG4.22)
	@/bin/rm -f $(OBJ-FIG4.26) $(EXE-FIG4.26)
	@/bin/rm -f $(OBJ-FIG4.31) $(EXE-FIG4.31)
	@/bin/rm -f $(OBJ-FIG4.32) $(EXE-FIG4.32)
	@/bin/rm -f $(OBJ-FIG4.34) $(EXE-FIG4.34)
	@/bin/rm -f $(OBJ-FIG4.36) $(EXE-FIG4.36)
	@/bin/rm -f $(OBJ-FIG4.37) $(EXE-FIG4.37)
	@/bin/rm -f $(OBJ-FIG4.39) $(EXE-FIG4.39)
	@/bin/rm -f $(OBJ-FIG4.43) $(EXE-FIG4.43)
	@/bin/rm -f $(OBJ-FIG4.47) $(EXE-FIG4.47)
	@/bin/rm -f $(OBJ-FIG4.55) $(EXE-FIG4.55)
	@/bin/rm -f $(OBJ-FIG4.57) $(EXE-FIG4.57)
	@/bin/rm -f $(OBJ-FIG4.58) $(EXE-FIG4.58)
	@/bin/rm -f $(OBJ-FIG4.61) $(EXE-FIG4.61)
	@/bin/rm -f $(OBJ-FIG4.62) $(EXE-FIG4.62)
	@/bin/rm -f $(OBJ-FIG4.65) $(EXE-FIG4.65)
	@/bin/rm -f $(OBJ-FIG4.68) $(EXE-FIG4.68)
	@/bin/rm -f $(OBJ-FIG4.70) $(EXE-FIG4.70)
	@/bin/rm -f $(OBJ-FIG4.72) $(EXE-FIG4.72)
	@/bin/rm -f $(OBJ-FIG4.74) $(EXE-FIG4.74)
	@/bin/rm -f $(OBJ-FIG4.77) $(EXE-FIG4.77)
	@/bin/rm -f $(OBJ-FIG4.79) $(EXE-FIG4.79)
	@/bin/rm -f $(OBJ-FIG4.84) $(EXE-FIG4.84)
	@/bin/rm -f $(OBJ-FIG4.85) $(EXE-FIG4.85)
	@/bin/rm -f $(OBJ-FIG4.87) $(EXE-FIG4.87)
	@/bin/rm -f $(OBJ-FIG4.96) $(EXE-FIG4.96)
	@/bin/rm -f $(OBJ-FIG4.98) $(EXE-FIG4.98)
