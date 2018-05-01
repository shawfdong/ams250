AC_DEFUN([PAC_PROG_MPICC],[
# Find the compilers, if they aren't set with the environment variables
if test -z "$MPICC" ; then
    AC_MSG_CHECKING([for MPI compile wrappers for C])
    # First look for the wrappers
    if test -n "$MPI_DIR" ; then
        for w in mpicc bin/mpicc mpcc bin/mpcc ; do
            if test -x $MPI_DIR/$w ; then
	        MPICC=$MPI_DIR/$w
                break
            fi
        done
    fi
    # Still not found
    if test -z "$MPICC" ; then
        # Try looking in the path
        saveIFS=$IFS
        IFS=":"
	for dir in $PATH ; do
	    for w in mpicc mpcc ; do
	        if test -x $dir/$w ; then
		    MPICC=$dir/$w
		    break 2
		fi
            done
	done
	IFS=$saveIFS
    fi
    if test -n "$MPICC" ; then
        AC_MSG_RESULT($MPICC)
    else
        AC_MSG_RESULT([none found])
    fi
fi
AC_SUBST([MPICC])
])

AC_DEFUN([PAC_PROG_MPIFORT],[
if test -z "$MPIFORT" ; then
    AC_MSG_CHECKING([for MPI compile wrappers for Fortran])
    if test -x $MPI_DIR/mpifort ; then
        MPIFORT=$MPI_DIR/mpifort
    elif test -x $MPI_DIR/bin/mpif90 ; then
        MPIFORT=$MPI_DIR/bin/mpiff90
    elif test -x $MPI_DIR/mpxlf ; then
        MPIFORT=$MPIDIR/mpxlf
    elif test -x $MPI_DIR/bin/mpxlf90 ; then
        MPIFORT=$MPIDIR/bin/mpxlf90
    else
        saveIFS=$IFS
        IFS=":"
	for dir in $PATH ; do
	    if test -x $dir/mpifort ; then
                MPIFORT=$dir/mpifort
		break
            elif test -x $dir/mpif90 ; then
                MPIFORT=$dir/mpif90
		break
            elif test -x $dir/mpxlf ; then
                MPIFORT=$dir/mpxlf
		break
            fi
	done
	IFS=$saveIFS
    fi
    if test -n "$MPIFORT" ; then
        AC_MSG_RESULT($MPIFORT)
    else
        AC_MSG_RESULT([none found])
    fi
fi
AC_SUBST([MPIFORT])
])

AC_DEFUN([PAC_PROG_MPIEXEC],[
if test -z "$MPIEXEC" ; then
    AC_MSG_CHECKING([for how to run MPI programs])
    if test -x $MPI_DIR/mpiexec ; then
        MPIEXEC=$MPI_DIR/mpiexec
	MPIEXEC_NP=-n
    elif test -x $MPI_DIR/bin/mpiexec ; then
        MPIEXEC=$MPI_DIR/bin/mpiexec
	MPIEXEC_NP=-n
    elif test -x $MPI_DIR/mpirun ; then
        MPIEXEC=$MPI_DIR/mpirun
	MPIEXEC_NP=-np
    elif test -x $MPI_DIR/bin/mpirun ; then
        MPIEXEC=$MPI_DIR/bin/mpirun
	MPIEXEC_NP=-np
    else
        saveIFS=$IFS
        IFS=":"
	for dir in $PATH ; do
	    if test -x $dir/mpiexec ; then
                MPIEXEC=$dir/mpiexec
		MPIEXEC_NP=-n
		break
            elif test -x $dir/mpirun ; then
                MPIEXEC=$dir/mpirun
		MPIEXEC_NP=-np
		break
            elif test -x $dir/llrun ; then
                MPIEXEC=$dir/llrun
		MPIEXEC_NP=-p
                break
            fi
	done
	IFS=$saveIFS
    fi
    if test -n "$MPIEXEC" ; then
        AC_MSG_RESULT($MPIEXEC $MPIEXEC_NP)
    else
        AC_MSG_RESULT([cannot determine])
    fi
fi
AC_SUBST([MPIEXEC])
AC_SUBST([MPIEXEC_NP])
])

AC_DEFUN([PAC_MPI_LIB],[
# ToDo.  Check for MPI_Init_thread available.  Use specified language,
# either C or Fortran (1st arg).  Default is to test C
])

## Add a check for whether the C compiler can handle MPI programs
## as on the Cray.
AC_DEFUN([PAC_MPI_CCWORKS],[
  AC_SEARCH_LIBS(MPI_Init,$MPILIB mpi mpich)
  if test "$ac_cv_search_MPI_Init" = "no" ; then
    ifelse($2,,
    AC_MSG_ERROR([Could not find MPI library]),[$2])
  fi
  AC_CHECK_HEADER(mpi.h,pac_have_mpi_h="yes",pac_have_mpi_h="no")
  if test $pac_have_mpi_h = "no" ; then
    ifelse($2,,
    AC_MSG_ERROR([Could not find mpi.h include file]),[$2])
  fi
])
