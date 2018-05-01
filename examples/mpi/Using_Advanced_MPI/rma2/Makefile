ALL: all-redirect

CC   = mpicc
LIBS = 

.SUFFIXES:
.SUFFIXES: .o .c

OLDOBJECTS =

BPUT_SOURCES = bput.c
MUTEXOBJS = mutex-acquire.o mutex-release.o mutex-create.o
MUTEX_SOURCES = mutex-acquire.c mutex-release.c mutex-create.c
SLISTOBJS = insertelm.o printelm.o slistmain.o
SLIST_SOURCES = insertelm.c printelm.c slistmain.c list.h
MCSOBJS   = mcs-lock.o
MCS_SOURCES = mcs-lock.c

NEWOBJECTS = $(MUTEXOBJS) $(SLISTOBJS) $(MCSOBJS)

NEWPROGRAMS = slist

SOURCES = $(MUTEX_SOURCES) $(SLIST_SOURCES) $(MCS_SOURCES) $(GA_SOURCES) \
	$(BPUT_SOURCES) dlistinit.c

LIBRARIES = libga.a libnxtval.a

GAOBJS = ga_create.o ga_free.o ga_put.o ga_acc.o ga-read-inc.o ga_mutex1.o
GA_SOURCES = ga_create.c ga_free.c ga_put.c ga_acc.c ga-read-inc.c \
	ga_mutex1.c ga.h

NXTVALOBJS = nxtval.o

all-redirect: $(NEWPROGRAMS) $(NEWOBJECTS) $(LIBRARIES)

slist: $(SLISTOBJS) $(MUTEXOBJS)
	$(CC) -o slist $(SLISTOBJS) $(MUTEXOBJS)

mcs-lock.o: mcs-lock-init.c mcs-lock-acquire.c mcs-lock-release.c

libga.a: $(GAOBJS)
	ar cr libga.a $(GAOBJS)
libnxtval.a: $(NXTVALOBJS)
	ar cr libnxtval.a $(NXTVALOBJS)

.c:
	$(CC) $(CFLAGS) -o $* $*.c
.c.o:
	$(CC) $(CFLAGS) -c $*.c
.o:
	$(CC) $(CFLAGS) -o $* $*.o

sources:
	@echo "${SOURCES}"

clean:
	rm -f *.o $(NEWPROGRAMS) $(LIBRARIES)

.PHONY: all all-redirect clean sources
