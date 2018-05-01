ALL: all-redirect

# This makefile simplifies the task of checking the full programs
CC = mpicc
CFLAGS = @DEFS@ @CFLAGS@

PROGRAMS = cvars cvarset pvars pvarsread
OBJECTS  = safedup.o
SOURCES = cvars.c cvarset.c pvars.c pvarsread.c testp.c safedup.c \
	cvargetindex.c pvargetindex.c
# pvars

all-redirect: $(PROGRAMS) $(OBJECTS)

cvarset: cvarset.o @CVARGETINDEX_O@
	$(CC) -o cvarset cvarset.o @CVARGETINDEX_O@

pvarsread: pvarsread.o testp.o @PVARGETINDEX_O@
	$(CC) -o pvarsread pvarsread.o testp.o @PVARGETINDEX_O@
.c:
	$(CC) $(CFLAGS) -o $* $*.c
.c.o:
	$(CC) $(CFLAGS) -c $*.c

sources:
	@echo "${SOURCES}"
clean:
	-rm -f *.o $(PROGRAMS)

.SUFFIXES:
.SUFFIXES: .o .c .f .f90

.PHONY: all-redirect clean sources
