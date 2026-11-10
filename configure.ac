# Process this file with autoconf to produce a configure script.
AC_INIT(m17n-docs, 1.8.4, bugs-m17n-lib@m17n.org)
AM_INIT_AUTOMAKE([-Wno-portability])

AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_AWK

if test $USE_MAINTAINER_MODE = yes; then

# Checks for source program files.
AC_ARG_WITH(m17nlib,
  [  --with-m17nlib=DIR     directory of m17n-lib source files],
  M17NLIB="$withval")

if test "x$M17NLIB" = "x"; then
  if test -d ../m17n-lib; then
    M17NLIB=../m17n-lib
  elif test -d /usr/local/src/m17n-lib; then
    M17NLIB=/usr/local/src/m17n-lib
  else
    M17NLIB=.
  fi
else :
fi
AC_SUBST(M17NLIB)

# Checks for the m17n database files.
AC_ARG_WITH(m17ndb,
  [  --with-m17ndb=DIR     directory of m17n-db source files],
  M17NDB="$withval")

if test "x$M17NDB" = "x"; then
  if test -d ../m17n-db; then
    M17NDB=../m17n-db
  elif test -d /usr/local/src/m17n-db; then
    M17NDB=/usr/local/src/m17n-db
  else
    M17NDB=.
  fi
else :
fi
AC_SUBST(M17NDB)

PKG_CHECK_MODULES(M17N, m17n-shell)
AC_SUBST(M17N_CFLAGS)
AC_SUBST(M17N_LIBS)

AC_CHECK_PROG(HAVEDOXYGEN, doxygen, yes, no)
AC_CHECK_PROG(RUBY, ruby, yes, no)
AC_CHECK_PROG(PDFLATEX, pdflatex, yes, no)
AC_CHECK_PROG(MAGICK, magick, yes, no)

OK=yes
if test "$HAVEDOXYGEN" = "no"; then
  echo "Can't find a program \"doxygen\"!"
  OK=no
fi
if test "$RUBY" = "no"; then
  echo "Can't find a program \"ruby\"!"
  OK=no
fi
if test "$PDFLATEX" = "no"; then
  echo "Can't find a program \"pdflatex\"!"
  OK=no
fi
if test "$MAGICK" = "no"; then
  echo "Can't find a program \"pdflatex\"!"
  OK=no
fi
if test "$OK" = "no"; then
  exit 1
fi

fi

AC_CONFIG_FILES([Makefile utils/Makefile])
AC_OUTPUT

# Print configuration message.
if test $USE_MAINTAINER_MODE = yes; then
  AC_MSG_NOTICE([Find documentation source in "$M17NLIB"])
  AC_MSG_NOTICE([Find m17n database source in "$M17NDB"])
fi

eval dir=${datadir}
AC_MSG_NOTICE([-------------------------------------------])
AC_MSG_NOTICE([Install documentations in these directories])
AC_MSG_NOTICE([-------------------------------------------])
AC_MSG_NOTICE([  m17n-lib.pdf:  ${dir}/m17n/docs])
AC_MSG_NOTICE([  html files:    ${dir}/m17n/docs/html])
eval dir=${mandir}
AC_MSG_NOTICE([  man files:     ${dir}])
