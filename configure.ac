#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT
AC_CONFIG_SRCDIR([Makefile.am])
AM_INIT_AUTOMAKE([mph], [0.1], [brad.heller@gmail.com])
AC_CONFIG_HEADERS([config.h])
LT_INIT
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

# Checks for libraries.
# FIXME: Add other functions in `-lcmph`
AC_CHECK_LIB([cmph], [cmph_new])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
