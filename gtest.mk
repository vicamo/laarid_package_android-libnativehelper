if HAVE_GTEST
check_LTLIBRARIES = \
	libgtest.la \
	libgtest_main.la

libgtest_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	$(PTHREAD_CFLAGS) \
	$(GTEST_CPPFLAGS) \
	-I $(GTEST_SRCDIR)
nodist_libgtest_la_SOURCES = \
	$(top_builddir)/gtest-all.cc
libgtest_la_LIBADD = \
	$(PTHREAD_CFLAGS)

$(top_builddir)/gtest-all.cc: $(top_builddir)
	@-rm -f $@; $(LN_S) $(GTEST_SRCDIR)/src/gtest-all.cc $@

libgtest_main_la_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	$(PTHREAD_CFLAGS) \
	$(GTEST_CPPFLAGS)
nodist_libgtest_main_la_SOURCES = \
	$(top_builddir)/gtest_main.cc
libgtest_main_la_LIBADD = \
	$(PTHREAD_CFLAGS)

$(top_builddir)/gtest_main.cc: $(top_builddir)
	@-rm -f $@; $(LN_S) $(GTEST_SRCDIR)/src/gtest_main.cc $@

BUILT_SOURCES += \
	$(top_builddir)/gtest-all.cc \
	$(top_builddir)/gtest_main.cc
endif # HAVE_GTEST
