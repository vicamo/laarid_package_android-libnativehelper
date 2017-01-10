# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# Installable libraries
# ---------------------
lib_LTLIBRARIES = \
	libandroid-nativehelper.la

# libandroid-nativehelper.la
# --------------------------
libandroid_nativehelper_la_CXXFLAGS = \
	$(AM_CXXFLAGS) \
	$(SYSTEMCORE_CFLAGS) \
	-fvisibility=protected
libandroid_nativehelper_la_LDFLAGS = \
	$(libtool_opts)
libandroid_nativehelper_la_LIBADD = \
	$(LIBADD_DLOPEN) \
	$(SYSTEMCORE_LIBS)
libandroid_nativehelper_la_SOURCES = \
	AsynchronousCloseMonitor.cpp \
	JNIHelp.cpp \
	JniConstants.cpp \
	JniInvocation.cpp \
	toStringArray.cpp

# HEADERS: android/nativehelper
# -----------------------------
incdir = $(includedir)/android/nativehelper-$(NATIVEHELPER_API_VERSION)/nativehelper
inc_HEADERS = \
	include/nativehelper/AsynchronousCloseMonitor.h \
	include/nativehelper/JNIHelp.h \
	include/nativehelper/JniConstants.h \
	include/nativehelper/JniInvocation.h \
	include/nativehelper/ScopedBytes.h \
	include/nativehelper/ScopedFd.h \
	include/nativehelper/ScopedLocalFrame.h \
	include/nativehelper/ScopedLocalRef.h \
	include/nativehelper/ScopedPrimitiveArray.h \
	include/nativehelper/ScopedPthreadMutexLock.h \
	include/nativehelper/ScopedStringChars.h \
	include/nativehelper/ScopedUtfChars.h \
	include/nativehelper/UniquePtr.h \
	include/nativehelper/jni.h \
	include/nativehelper/toStringArray.h

# PKG-CONFIG data files
# ---------------------
pkgconfig_DATA = \
	android-nativehelper-$(NATIVEHELPER_API_VERSION).pc

#
# Tests.
#

include $(srcdir)/tests/Android.mk
