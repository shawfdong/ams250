#! /bin/sh
#
M4SRC=/Users/gropp/baseenv/confdb
# Make sure that configure is built properly
if [ ! -f confdb/aclocal_mpi.m4 ] ; then
    if [ ! -d confdb ] ; then mkdir confdb ; fi
    if [ -s $M4SRC/aclocal_mpi.m4 ] ; then
        cp $M4SRC/aclocal_mpi.m4 confdb
    else
	echo "Could not find aclocal_mpi.m4!"
	exit 1
    fi
fi
autoreconf -ifv -Iconfdb
if grep PAC_ configure >/dev/null 2>&1 ; then
     echo "configure script contains unresolved local macros"
     echo "Check confdb/aclocal_mpi.m4"
     exit 1
fi
