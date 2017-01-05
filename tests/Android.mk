if HAVE_GTEST
check_PROGRAMS += \
	%reldir%/JniInvocation_test

TESTS += \
	%reldir%/JniInvocation_test

%canon_reldir%_JniInvocation_test_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	$(GTEST_CPPFLAGS)
%canon_reldir%_JniInvocation_test_LDADD = \
	libandroid-nativehelper.la \
	$(GTEST_LIBS)
%canon_reldir%_JniInvocation_test_DEPENDENCIES = \
	libandroid-nativehelper.la \
	$(GTEST_LIBS)
%canon_reldir%_JniInvocation_test_SOURCES = \
	%reldir%/JniInvocation_test.cpp
endif
