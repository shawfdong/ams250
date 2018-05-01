SHELL = /bin/sh
CC    = mpicc
FC    = mpifort
LIBS  = 

all: all-redirect

PROGRAMS = matvec-master matvec-worker matvec-master-universe \
	   pcp-spawn-master pcp-spawn-worker

SOURCES = matvec-master.f90 matvec-worker.f90 matvec-master-universe.f90 \
	pcp-spawn-master.c pcp-spawn-worker.c

all-redirect: ${PROGRAMS}

clean:
	rm -f *.o ${PROGRAMS} *~

.SUFFIXES:
.SUFFIXES: .o .c .f .f90
.c:
	${CC} ${CFLAGS} -o $* $< ${LIBS}
.c.o:
	${CC} ${CFLAGS} -c $<
.f:
	${FC} ${FCFLAGS} -o $* $< ${LIBS}
.f.o:
	${FC} ${FCFLAGS} -c $<
.f90:
	${FC} ${FCFLAGS} -o $* $< ${LIBS}
.f90.o:
	${FC} ${FCFLAGS} -c $<

sources:
	@echo ${SOURCES}

.PHONY: sources clean
