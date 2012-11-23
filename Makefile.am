
ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = COPYING

lib_LTLIBRARIES = libwlog.la

libwlog_la_SOURCES = detail.hpp \
log.cpp logger.cpp log_exc.cpp log_level.cpp \
appender.cpp appender_factory.cpp console_appender.cpp file_appender.cpp \
simple_layout.cpp log_format_xml.cpp log_format_simple.cpp \
properties.cpp test.cpp

nobase_include_HEADERS = wiggly/*.hpp wiggly/log/*.hpp

SUBDIRS = . example
