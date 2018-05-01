ALL: all-redirect

##### User configurable options #####

CC     = mpicc
FC     = mpifort
CFLAGS =
FFLAGS =
LIBS   = 

### End User configurable options ###
PROFLIBS = $(LIBDIR)/mpe_proff.o $(LIBDIR)/mpe_prof.o $(LIBDIR)/libmpe.a
EXECS = oned onedsync onedsandr onedpair onednb twod \
	onedpr onedsyncpr onedsandrpr onedpairpr onednbpr twodpr
SOURCES = oned.f90 sweep.f90 exchng1.f90 diff.f90 onedbase.f90 decomp.f90 \
	exbsend.f90 exchng1nb.f90 expair1d.f90 exchng2.f90 exsandr1d.f90 \
	exsync1d.f90 fndnbr2d.f90 sweep2.f90 twod.f90 twodbase.f90 diff2d.f90

default: oned twod
all-redirect: oned twod onedsync onedsandr onednb onedpair

oned: oned.o sweep.o exchng1.o diff.o onedbase.o decomp.o
	$(FC) -o oned oned.o sweep.o exchng1.o \
		diff.o onedbase.o decomp.o $(LIBS)
onedsync: oned.o sweep.o exsync1d.o diff.o onedbase.o decomp.o
	$(FC) -o onedsync oned.o sweep.o exsync1d.o \
		diff.o onedbase.o decomp.o $(LIBS)
onedsandr: oned.o sweep.o exsandr1d.o diff.o onedbase.o decomp.o
	$(FC) -o onedsandr oned.o sweep.o exsandr1d.o \
		diff.o onedbase.o decomp.o $(LIBS)
onedpair: oned.o sweep.o expair1d.o diff.o onedbase.o decomp.o
	$(FC) -o onedpair oned.o sweep.o expair1d.o \
		diff.o onedbase.o decomp.o $(LIBS)
onednb: oned.o sweep.o exchng1nb.o diff.o onedbase.o decomp.o
	$(FC) -o onednb oned.o sweep.o exchng1nb.o \
		diff.o onedbase.o decomp.o $(LIBS)
twod: twod.o sweep2.o exchng2.o diff2d.o twodbase.o decomp.o fndnbr2d.o
	$(FC) -o twod twod.o sweep2.o exchng2.o \
		diff2d.o twodbase.o decomp.o fndnbr2d.o $(LIBS)

# Profiling versions
onedpr: oned.o sweep.o exchng1.o diff.o onedbase.o decomp.o
	$(FC) -o onedpr oned.o sweep.o exchng1.o \
		diff.o onedbase.o decomp.o $(PROFLIBS)
onedsyncpr: oned.o sweep.o exsync1d.o diff.o onedbase.o decomp.o
	$(FC) -o onedsyncpr oned.o sweep.o exsync1d.o \
		diff.o onedbase.o decomp.o $(PROFLIBS)
onedsandrpr: oned.o sweep.o exsandr1d.o diff.o onedbase.o decomp.o
	$(FC) -o onedsandrpr oned.o sweep.o \
		exsandr1d.o diff.o onedbase.o decomp.o $(PROFLIBS)
onedpairpr: oned.o sweep.o expair1d.o diff.o onedbase.o decomp.o
	$(FC) -o onedpairpr oned.o sweep.o expair1d.o \
		diff.o onedbase.o decomp.o $(PROFLIBS)
onednbpr: oned.o sweep.o exchng1nb.o diff.o onedbase.o decomp.o
	$(FC) -o onednbpr oned.o sweep.o exchng1nb.o \
		diff.o onedbase.o decomp.o $(PROFLIBS)
twodpr: twod.o sweep2.o exchng2.o diff2d.o twodbase.o decomp.o fndnbr2d.o
	$(FC) -o twodpr twod.o sweep2.o exchng2.o \
		diff2d.o twodbase.o decomp.o fndnbr2d.o $(PROFLIBS)

.SUFFIXES:
.SUFFIXES: .c .f90 .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

.f90.o:
	$(FC) $(FFLAGS) -c $*.f90

clean:
	rm -f *.o *~ PI* $(EXECS)

.PHONY: clean all-redirect default sources

sources:
	@echo ${SOURCES}
