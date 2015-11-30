AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_tcp.la

libvmod_tcp_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_tcp_la_SOURCES = \
	vmod_tcp.c

nodist_libvmod_tcp_la_SOURCES = \
	vcc_if.c \
	vcc_if.h

dist_man_MANS = vmod_tcp.3

vmod_tcp.3: vmod_tcp.man.rst
	${RST2MAN} $< $@


vmod_tcp.lo vmod_tcp.man.rst: vcc

vcc: @VMODTOOL@ $(top_srcdir)/src/vmod_tcp.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_tcp.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS) vcc

$(top_srcdir)/src/tests/*.vtc: libvmod_tcp.la
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_tcp.vcc \
	$(VMOD_TESTS)

CLEANFILES = \
	$(builddir)/vcc_if.c \
	$(builddir)/vcc_if.h \
	$(builddir)/vmod_tcp.rst \
	$(builddir)/vmod_tcp.man.rst \
	$(dist_man_MANS)
