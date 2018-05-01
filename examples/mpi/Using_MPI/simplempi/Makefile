SHELL    = /bin/sh
CC       = mpicc
FC       = mpifort
LDFLAGS  = 
CPPFLAGS = 

all: all-redirect

PROGRAMS = pi3 cpi pit matvec matmat monte-ex
SOURCES  = pi3.f90 cpi.c pit.f90 matvec.f90 matmat.f90 matmatlog.f90 \
	monte-ex.c monte.c
# matmatlog and monte require the MPE library
EXTRA_PROGRAMS = matmatlog monte

all-redirect: ${PROGRAMS}

clean:
	rm -rf *.o ${PROGRAMS} ${EXTRA_PROGRAMS} *~ pmatmat.log.*

.SUFFIXES:
.SUFFIXES: .o .c .f .cc .f90
.c:
	${CC} ${CPPFLAGS} ${CFLAGS} -o $* $< ${LDFLAGS} ${LIBS}
.c.o:
	${CC} ${CPPFLAGS} ${CFLAGS} -c $<
.f:
	${FC} ${FCFLAGS} -o $* $< ${LDFLAGS} ${LIBS}
.f.o:
	${FC} ${FCFLAGS} -c $<
.f90.o:
	${FC} ${FCFLAGS} -c $<
.f90:
	${FC} ${FCFLAGS} -o $* $< ${LDFLAGS} ${LIBS}

matmatlog: matmatlog.o
	${FC} ${FFLAGS} -o matmatlog matmatlog.o ${LDFLAGS} -lmpe ${LIBS}
monte: monte.o
	${CC} ${CFLAGS} -o monte monte.o ${LDFLAGS} -lmpe ${LIBS}

sources:
	@echo ${SOURCES}
