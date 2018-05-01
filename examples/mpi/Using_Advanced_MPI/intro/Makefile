ALL: all-redirect

##### User configurable options #####

CC      = mpicc
FC      = mpifort
CFLAGS  =
FCFLAGS =
LIBS    = 

# Programs or objects
PROGRAMS =
OBJECTS  = exchng1nb.o
SOURCES  = exchng1nb.f90 exchng1nb.c

all-redirect: $(PROGRAMS) $(OBJECTS)

# Rules
.SUFFIXES:
.SUFFIXES: .c .f .f90 .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c
.f90.o:
	$(FC) $(FCFLAGS) -c $*.f90
.f.o:
	$(FC) $(FCFLAGS) -c $*.f
sources:
	@echo ${SOURCES}
clean:
	rm -f *.o *~ $(PROGRAMS)

.PHONY: clean all-redirect default sources
