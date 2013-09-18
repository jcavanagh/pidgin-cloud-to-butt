#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([pidgin-cloud-to-butt], [1.0], [joe@jlcavanagh.com])
AC_CONFIG_SRCDIR([src/pidgin-cloud-to-butt.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR

# Checks for programs.
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AC_PROG_CC
AC_SYS_LARGEFILE

# Checks for libraries.
# PKG_CHECK_MODULES([PIDGIN], [pidgin])
PKG_CHECK_MODULES([PURPLE], [purple])

# Checks for header files.
AC_CHECK_HEADERS([locale.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale strdup])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT