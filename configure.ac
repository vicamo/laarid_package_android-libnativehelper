# android-nativehelper versioning
# -------------------------------
# To make new release:
#
#   nativehelper_micro_version += 1
#   nativehelper_interface_revision += 1
#
# if any functions have been added:
#
#   nativehelper_micro_version += 1
#   nativehelper_interface_revision = 0
#
#   or
#
#   nativehelper_minor_version += 1
#   nativehelper_micro_version = 0
#   nativehelper_interface_revision = 0
#
# if backwards compatibility has been broken:
#
#   nativehelper_major_version += 1
#   nativehelper_minor_version = 0
#   nativehelper_micro_version = 0
#   nativehelper_interface_revision = 0
m4_define([nativehelper_major_version], [0])
m4_define([nativehelper_minor_version], [0])
m4_define([nativehelper_micro_version], [3])
m4_define([nativehelper_interface_revision], [0])
m4_define([nativehelper_api_version], [nativehelper_major_version.0])
m4_define([nativehelper_release_number], [nativehelper_major_version])
m4_define([nativehelper_version],
  [nativehelper_major_version.nativehelper_minor_version.nativehelper_micro_version])

AC_INIT([android-libnativehelper], [nativehelper_version],
  [https://github.com/laarid/package_android-libnativehelper/issues], [],
  [https://github.com/laarid/package_android-libnativehelper])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([include/nativehelper/jni.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects no-define tar-ustar])
AM_MAINTAINER_MODE([enable])
AM_SILENT_RULES([yes])

NATIVEHELPER_MAJOR_VERSION=nativehelper_major_version
NATIVEHELPER_MINOR_VERSION=nativehelper_minor_version
NATIVEHELPER_MICRO_VERSION=nativehelper_micro_version
NATIVEHELPER_API_VERSION=nativehelper_api_version
NATIVEHELPER_RELEASE_NUMBER=nativehelper_release_number
AC_SUBST([NATIVEHELPER_MAJOR_VERSION])
AC_SUBST([NATIVEHELPER_MINOR_VERSION])
AC_SUBST([NATIVEHELPER_MICRO_VERSION])
AC_SUBST([NATIVEHELPER_API_VERSION])
AC_SUBST([NATIVEHELPER_RELEASE_NUMBER])

# Define _GNU_SOURCE etc. where appropriate, e.g. for strptime() on glibc
AC_USE_SYSTEM_EXTENSIONS

AM_PROG_AR
AC_PROG_CC
AC_PROG_CXX

# libtool versioning
# ------------------
LT_INIT

LT_RELEASE="nativehelper_api_version"
AC_SUBST(LT_RELEASE)

m4_define([nativehelper_binary_age], [m4_eval(100 * nativehelper_minor_version + nativehelper_micro_version)])
m4_define([lt_current], [m4_eval(nativehelper_binary_age - nativehelper_interface_revision)])
m4_define([lt_revision], [nativehelper_interface_revision])
# Whenever backward compatibility is broken, we generate libraries of different
# release number. That follows the library files of the same release are always
# compatible, and they have their lt_age equal to lt_current.
m4_define([lt_age], [lt_current])
LT_VERSION_INFO="lt_current:lt_revision:lt_age"
AC_SUBST(LT_VERSION_INFO)

# System dlloader
# ---------------
LT_LIB_DLLOAD

LT_OUTPUT

# Required libraries
# ------------------
BIONIC_API_VERSION=0.0
BIONIC_REQUIRED_VERSION=0.1.4
AC_SUBST([BIONIC_API_VERSION])
AC_SUBST([BIONIC_REQUIRED_VERSION])

PKG_CHECK_MODULES([BIONIC], [android-bionic-$BIONIC_API_VERSION >= $BIONIC_REQUIRED_VERSION])
AC_SUBST([BIONIC_CFLAGS])
AC_SUBST([BIONIC_LIBS])

SYSTEMCORE_API_VERSION=0.0
SYSTEMCORE_REQUIRED_VERSION=0.0.12
AC_SUBST([SYSTEMCORE_API_VERSION])
AC_SUBST([SYSTEMCORE_REQUIRED_VERSION])

PKG_CHECK_MODULES([SYSTEMCORE], [
  android-cutils-$SYSTEMCORE_API_VERSION >= $SYSTEMCORE_REQUIRED_VERSION
  android-log-$SYSTEMCORE_API_VERSION >= $SYSTEMCORE_REQUIRED_VERSION
])
AC_SUBST([SYSTEMCORE_CFLAGS])
AC_SUBST([SYSTEMCORE_LIBS])

# Thread implementation
# ---------------------
AX_PTHREAD(
  [AC_DEFINE([HAVE_PTHREAD], [1],
    [Define if you have POSIX threads libraries and header files.])
  AC_DEFINE([HAVE_PTHREADS], [1],
    [Define if you have POSIX threads libraries and header files.])],
  [AC_MSG_FAILURE([pthread not available.])])

# GTest
# -----
AC_LANG_PUSH([C++])
AC_ARG_WITH([gtest],
  [AS_HELP_STRING([--with-gtest],
    [Build with Google Test Frameworks based tests @<:@default=check@:>@])],
  [], [])
AS_IF([test "x${with_gtest}" != xno],
  [GTEST_SRCDIR="/usr/src/gtest"
  AS_IF([test "x${with_gtest}" != xyes],
    [AS_IF([test -e "${with_gtest}/include/gtest/gtest.h"],
      [GTEST_SRCDIR="${with_gtest}"])])
  CPPFLAGS_save="$CPPFLAGS"
  GTEST_CPPFLAGS="-I ${GTEST_SRCDIR}/include"
  GTEST_LIBS="libgtest.la libgtest_main.la"
  CPPFLAGS="${GTEST_CPPFLAGS}"
  AC_CHECK_HEADER([gtest/gtest.h], [],
    [AS_IF([test "x${with_gtest}" != xyes],
      [AC_MSG_ERROR([Google Test Frameworks source folder not found])],
      [with_gtest=no])])
  CPPFLAGS="$CPPFLAGS_save"])
AC_SUBST([GTEST_CPPFLAGS])
AC_SUBST([GTEST_LIBS])
AC_SUBST([GTEST_SRCDIR])
AC_LANG_POP()
AM_CONDITIONAL([HAVE_GTEST], [test "x${with_gtest}" != xno])

# Configure output
# ----------------
AC_CONFIG_FILES([
  Makefile
  android-nativehelper-$NATIVEHELPER_API_VERSION.pc
])
AC_OUTPUT
