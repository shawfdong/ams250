SHELL = /bin/sh
CC    = mpicc
FC    = mpifort
LIBS  = 
#FCFLAGS =
#CFLAGS  =

all: all-redirect

PROGRAMS = oned

oned_SOURCES = onedbase.f90 sweep.f90 diff.f90 nbr1drma.f90 decomp.f90 oned.f90
oned_OBJECTS = onedbase.o sweep.o diff.o nbr1drma.o decomp.o oned.o

twod_SOURCES = nbr2dsetup.f90 nbr2dputex.f90
twod_OBJECTS = nbr2dsetup.o nbr2dputex.o

alt_SOURCES = 	nbr1daltrma.f90
alt_OBJECTS = 	nbr1daltrma.o

pt2pt_SOURCES = nbr1dpt2pt.f90

oned: ${oned_OBJECTS}
	${FC} -o oned ${oned_OBJECTS} ${LIBS}

all-redirect: ${PROGRAMS}

SOURCES = ${oned_SOURCES} ${twod_SOURCES} ${pt2pt_SOURCES} ${alt_SOURCES}

clean:
	rm -f *.o ${PROGRAMS} *~ PI*

.SUFFIXES:
.SUFFIXES: .o .c .f90
.c:
	${CC} ${CFLAGS} -o $* $< ${LIBS}
.c.o:
	${CC} ${CFLAGS} -c $<
.f90:
	${FC} ${FCFLAGS} -o $* $< ${LIBS}
.f90.o:
	${FC} ${FCFLAGS} -c $<

sources:
	@echo ${SOURCES}
