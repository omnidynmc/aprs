#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([aprs], [1.0.0.1], [gcarter@openaprs.net])
AC_CONFIG_SRCDIR([src/APRS.cpp])
AC_CONFIG_HEADERS([include/aprs/config.h])
AM_INIT_AUTOMAKE
LT_INIT
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_LANG([C++])

prefix="/usr/local"

#bindir="`pwd`"
#libdir="`pwd`/lib"
#includedir="`pwd`/include"
ofincludedir="/usr/local/include/openframe"
oflibdir="/usr/local/lib"

local_include="`pwd`/include/aprs"

CPPFLAGS="$CPPFLAGS -I/usr/include -I$local_include"
CXXFLAGS="-Wall -pipe -g -I$includedir -I$ofincludedir -I$local_include"
CXX="g++"
LIBS="$LIBS"

# Checks for libraries.

AC_CHECK_LIB([pthread], [pthread_create], [], [
               echo "pthread library is required for this program"
               exit 1
             ])

AC_CHECK_LIB([ossp-uuid++], [uuid_version], [], [
               echo "ossp-uuid++ library is required for this program"
               exit 1
             ])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_SUBST(bindir)
AC_SUBST(LIBTOOL_DEPS)

LIBS="$LIBS -L`pwd`/lib $DEPS_LIBS -L$oflibdir -lopenframe"

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 include/aprs/Makefile
                 test/Makefile
               ])
AC_OUTPUT
