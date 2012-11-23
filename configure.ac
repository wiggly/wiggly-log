AC_INIT(wiggly-log,0.0.6,wiggly@wiggly.org)
AM_INIT_AUTOMAKE

AC_CONFIG_HEADERS(config.h)

AC_CONFIG_MACRO_DIR([m4])

AC_LIBTOOL_WIN32_DLL

AC_PROG_LIBTOOL

AC_PROG_MAKE_SET

AC_PROG_CXX

AC_PROG_CPP

AC_PROG_INSTALL

AC_FUNC_STRFTIME

AC_ARG_WITH(pthread,
[  --with-pthread          Build thread-safe version using posix threads],
[with_pthread=1])

if test "$with_pthread" = 1;
then
	ACX_PTHREAD
fi

AC_OUTPUT(Makefile Doxyfile example/Makefile)
