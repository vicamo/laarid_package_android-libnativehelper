ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# Distribution
# ------------
EXTRA_DIST =
BUILT_SOURCES =
CLEANFILES =
DISTCLEANFILES =
MAINTAINERCLEANFILES = \
	$(GITIGNORE_MAINTAINERCLEANFILES_TOPLEVEL) \
	$(GITIGNORE_MAINTAINERCLEANFILES_M4_LIBTOOL) \
	$(GITIGNORE_MAINTAINERCLEANFILES_MAKEFILE_IN)

# We're running CI in docker, which reports host architecture as host,
# not the docker image architecture as we expected, so specifying the
# host/build information is necessary here.
DISTCHECK_CONFIGURE_FLAGS = \
	--host=$(host) \
	--build=$(build) \
	--disable-dependency-tracking \
	--disable-maintainer-mode

GITIGNOREFILES = \
	build \
	debian \
	$(DIST_ARCHIVES)

# Common/global flags
# -------------------
AM_CPPFLAGS = \
	-include config.h \
	-I$(top_srcdir)/include

AM_CXXFLAGS = \
	-Wall -Werror \
	-std=gnu++11 \
	-fvisibility=protected

libtool_opts = \
	-version-info $(LT_VERSION_INFO) \
	-export-dynamic \
	-rpath $(libdir)

check_PROGRAMS =
TESTS =

include $(srcdir)/gtest.mk

# Installable libraries
# ---------------------
lib_LTLIBRARIES = \
	libandroid-nativehelper.la

# libandroid-nativehelper.la
# --------------------------
libandroid_nativehelper_la_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	$(SYSTEMCORE_CFLAGS)
libandroid_nativehelper_la_LDFLAGS = \
	$(libtool_opts)
libandroid_nativehelper_la_LIBADD = \
	$(LIBADD_DLOPEN) \
	$(SYSTEMCORE_LIBS)
libandroid_nativehelper_la_SOURCES = \
	JNIHelp.cpp \
	JniConstants.cpp \
	JniInvocation.cpp \
	toStringArray.cpp

# HEADERS: android/nativehelper
# -----------------------------
incdir = $(includedir)/android/nativehelper-$(NATIVEHELPER_API_VERSION)/nativehelper
inc_HEADERS = \
	include/nativehelper/JNIHelp.h \
	include/nativehelper/JniConstants.h \
	include/nativehelper/JniInvocation.h \
	include/nativehelper/ScopedBytes.h \
	include/nativehelper/ScopedFd.h \
	include/nativehelper/ScopedLocalFrame.h \
	include/nativehelper/ScopedLocalRef.h \
	include/nativehelper/ScopedPrimitiveArray.h \
	include/nativehelper/ScopedStringChars.h \
	include/nativehelper/ScopedUtfChars.h \
	include/nativehelper/UniquePtr.h \
	include/nativehelper/jni.h \
	include/nativehelper/toStringArray.h

# PKG-CONFIG data files
# ---------------------
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	android-nativehelper-$(NATIVEHELPER_API_VERSION).pc

$(pkgconfig_DATA): config.status

EXTRA_DIST += $(pkgconfig_DATA:.pc=.pc.in)
DISTCLEANFILES += \
	$(pkgconfig_DATA)

include $(srcdir)/tests/Android.mk

CLEANFILES += $(BUILT_SOURCES)
GITIGNOREFILES += $(BUILT_SOURCES)

-include $(top_srcdir)/git.mk
