ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# Distribution
# ------------
EXTRA_DIST =
DISTCLEANFILES =

# Common/global flags
# -------------------
AM_CPPFLAGS = \
	-include config.h \
	-I$(top_srcdir)/include

AM_CXXFLAGS = \
	-Wall -Werror \
	-std=gnu++98 \
	-fvisibility=protected \
	$(SYSTEMCORE_CFLAGS)

LIBS = \
	$(LIBADD_DLOPEN) \
	$(SYSTEMCORE_LIBS)

libtool_opts = \
	-version-info $(LT_VERSION_INFO) \
	-export-dynamic \
	-rpath $(libdir)

# Installable libraries
# ---------------------
lib_LTLIBRARIES = \
	libandroid-nativehelper-0.la

# libandroid-nativehelper.la
# --------------------------
libandroid_nativehelper_0_la_LDFLAGS = \
	$(libtool_opts)
libandroid_nativehelper_0_la_SOURCES = \
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
	include/nativehelper/jni.h \
	include/nativehelper/toStringArray.h

# PKG-CONFIG data files
# ---------------------
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = \
	android-nativehelper-$(NATIVEHELPER_API_VERSION).pc

$(pkgconfig_DATA): config.status

DISTCLEANFILES += \
	$(pkgconfig_DATA)
