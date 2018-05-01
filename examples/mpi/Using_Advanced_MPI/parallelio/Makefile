all: all-redirect

SHELL   = /bin/sh
CC      = mpicc
FC      = mpifort
LIBS    = 

PROGRAMS = read read_at read_all query shared
ROUTINES = irreg.o

SOURCES = astro-align.c astro.c darray.c ghost.c hints.c interop.c \
	  levels-darray.c query.c read.c read_all.c subarray.c view.c \
	  irreg.f90 read_at.f90

all-redirect: ${PROGRAMS} ${ROUTINES}

clean:
	rm -f *.o ${PROGRAMS} *~

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

.PHONY: sources all-redirect
