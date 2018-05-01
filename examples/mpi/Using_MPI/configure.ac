AC_PREREQ(2.63)
AC_INIT([using-mpi-examples],
        [3,0],
        [wgropp@illinois.edu],
        [usingmpi3rd],
        [http://www.cs.illinois.edu/~wgropp])
AC_CONFIG_MACRO_DIR([confdb])

AC_ARG_ENABLE([echo],
    [AS_HELP_STRING([--enable-echo],
    [Turn on verbose shell echo when running configure])],
    [set -x],
    [set +x])
#
# Specify the location of MPI compilation scripts, or MPI install
# directory.  Not necessary in most cases (e.g., scripts in the
# search path)
AC_ARG_WITH([mpi],
   [AS_HELP_STRING([--with-mpi=dir],
                   [location of MPI compilation and run scripts])],
   [],
   [with_mpi=/usr/local/bin])
#
# Optional packages.  An location can be provided (directory)
# Not all of the packages may ship with the baseenv package
AC_ARG_WITH([fpmpi2],
   [AS_HELP_STRING([--with-fpmpi2=dir],
                   [location of FPMPI2 libraries])],
   [if test "x$with_fpmpi2" = "x" ; then with_fpmpi2=fpmpi2 ; fi],
   [with_fpmpi2=no])
#
AC_ARG_WITH([mpe],
   [AS_HELP_STRING([--with-mpe=dir],
                   [location of MPE libraries])],
   [if test "x$with_mpe" = "x" ; then with_mpe=mpe ; fi],
   [with_mpe=no])

#
# Try to find the compiler
if test "x$with_mpi" != "x" ; then
    if test -d "$with_mpi" -a -x "$with_mpi/mpicc" ; then
        MPI_DIR=$with_mpi
    elif test -d "$with_mpi/bin" ; then
        MPI_DIR="$with_mpi/bin"
    fi
fi

PAC_PROG_MPICC

# Now, make sure that we have something that we can use
if test -n "$MPICC" ; then
    # Note that this may make CC a cross compiler
    CC=$MPICC
fi

# Basic properties of the C compiler.  Small components that don't
# have separate builds can use these values
AC_PROG_CC
AC_C_VOLATILE
AC_C_RESTRICT
AC_C_INLINE

PAC_PROG_MPIFORT
if test -n "$MPIFORT" ; then
   FC=$MPIFORT
fi

AC_PROG_FC
# We use .f90 for modern Fortran programs
AC_FC_SRCEXT([f90])
# And we use free format
AC_FC_FREEFORM()

# Find how to build libraries
AC_PROG_RANLIB
#
# Find the MPI location
PAC_MPI_CCWORKS

# Check for mpi.h (needed for some of the other tests)
AC_CHECK_HEADERS([mpi.h])

# Check for the optional packages.  Make sure that that are present if selected
if test "$with_fpmpi2" != no ; then
    FPMPI2_DIR=$with_fpmpi2
    if test "$FPMPI2_DIR" = fpmpi2 ; then
        if test -d fpmpi2 ; then
            AC_CONFIG_SUBDIRS([fpmpi2])
        fi
    elif test -d "$FPMPI2_DIR" ; then
        # This is much harder.  Keep track of these; we'll handle them
	# later
	externalDirs="$externalDirs $FPMPI2_DIR"
    else
        AC_MSG_ERROR([Directory $with_fpmpi2 for fpmpi2 does not exist])
    fi
fi

if test "$with_mpe" != no ; then
    MPE_DIR=$with_mpe
    if test "$MPE_DIR" = mpe ; then
        if test -d mpe ; then
            AC_CONFIG_SUBDIRS([mpe])
        fi
    elif test -d "$MPE_DIR" ; then
        # This is much harder.  Keep track of these; we'll handle them
	# later
	externalDirs="$externalDirs $MPE_DIR"
    else
        AC_MSG_ERROR([Directory $with_mpe for MPE does not exist])
    fi
    if test -f $MPE_DIR/lib/libmpe.a ; then
        LDFLAGS="-L$MPE_DIR/lib $LDFLAGS"
    fi
    if test -f $MPE_DIR/include/mpe.h ; then
	CPPFLAGS="-I$MPE_DIR/include $CPPFLAGS"
    fi
fi


MPICC=$CC

AC_SUBST([MPI_DIR])
AC_SUBST([FPMPI2_DIR])
AC_SUBST([MPE_DIR])
AC_SUBST([MPICC])
AC_SUBST([MPIFORT])
AC_CONFIG_FILES([Makefile simplempi/Makefile intermediate/Makefile
       advmsg/Makefile libraries/Makefile advanced/Makefile])
AC_OUTPUT
