## Makefile.am for gtk+/modules/input

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

INCLUDES = @STRIP_BEGIN@ \
	-I$(top_srcdir) 				\
	-I$(top_srcdir)/gdk				\
	-I$(top_builddir)/gdk				\
	-DG_DISABLE_DEPRECATED	 			\
	-DGDK_PIXBUF_DISABLE_DEPRECATED			\
	-DGDK_DISABLE_DEPRECATED			\
	-DGTK_DISABLE_DEPRECATED 			\
	@GTK_DEBUG_FLAGS@				\
	@GTK_XIM_FLAGS@					\
	@GTK_DEP_CFLAGS@				\
@STRIP_END@

DEPS = \
	$(top_builddir)/gdk-pixbuf/libgdk_pixbuf-$(GTK_API_VERSION).la	\
	$(top_builddir)/gdk/@gdktargetlib@ 				\
	$(top_builddir)/gtk/@gtktargetlib@

LDADDS = @STRIP_BEGIN@ 							\
	$(top_builddir)/gdk-pixbuf/libgdk_pixbuf-$(GTK_API_VERSION).la	\
	$(top_builddir)/gdk/@gdktargetlib@        			\
	$(top_builddir)/gtk/@gtktargetlib@ 				\
	@GTK_DEP_LIBS@							\
@STRIP_END@

moduledir = $(libdir)/gtk-2.0/$(GTK_BINARY_VERSION)/immodules

im_xim_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_xim_la_SOURCES = 		\
	gtkimcontextxim.c 	\
	gtkimcontextxim.h	\
	imxim.c
im_xim_la_LIBADD = $(LDADDS)
if USE_X11
IM_XIM_MODULE=im-xim.la 
endif

im_am_et_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_am_et_la_SOURCES = imam-et.c
im_am_et_la_LIBADD = $(LDADDS)

im_cedilla_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_cedilla_la_SOURCES = imcedilla.c
im_cedilla_la_LIBADD = $(LDADDS)

im_cyrillic_translit_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_cyrillic_translit_la_SOURCES = imcyrillic-translit.c
im_cyrillic_translit_la_LIBADD = $(LDADDS)

im_ti_er_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_ti_er_la_SOURCES = imti-er.c
im_ti_er_la_LIBADD = $(LDADDS)

im_ti_et_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_ti_et_la_SOURCES = imti-et.c
im_ti_et_la_LIBADD = $(LDADDS)

im_thai_broken_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_thai_broken_la_SOURCES = imthai-broken.c
im_thai_broken_la_LIBADD = $(LDADDS)

im_viqr_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_viqr_la_SOURCES = imviqr.c
im_viqr_la_LIBADD = $(LDADDS)

im_inuktitut_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_inuktitut_la_SOURCES = iminuktitut.c
im_inuktitut_la_LIBADD = $(LDADDS)

im_ipa_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_ipa_la_SOURCES = imipa.c
im_ipa_la_LIBADD = $(LDADDS)

im_hangul_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module $(no_undefined)
im_hangul_la_SOURCES = imhangul.c imhangul-defs.h
im_hangul_la_LIBADD = $(LDADDS)

if CROSS_COMPILING
RUN_QUERY_IMMODULES_TEST=false
else
RUN_QUERY_IMMODULES_TEST=test -z "$(DESTDIR)"
endif

# Running this if cross compiling or if DESTDIR is set is going to
# not work at all, so skip it.
install-data-local:
	@if $(RUN_QUERY_IMMODULES_TEST) ; then \
	  echo $(mkinstalldirs) $(DESTDIR)$(sysconfdir)/gtk-2.0 ; \
	  $(mkinstalldirs) $(DESTDIR)$(sysconfdir)/gtk-2.0 ; \
	  echo "$(top_builddir)/gtk/gtk-query-immodules-2.0 > $(DESTDIR)$(sysconfdir)/gtk-2.0/gtk.immodules" ; \
	  $(top_builddir)/gtk/gtk-query-immodules-2.0 > $(DESTDIR)$(sysconfdir)/gtk-2.0/gtk.immodules ; \
	else \
	  echo "***" ; \
	  echo "*** Warning: gtk.immodules not built" ; \
	  echo "***" ; \
	  echo "*** Generate this file manually on host" ; \
	  echo "*** system using gtk-query-immodules-2.0" ; \
	  echo "***" ; \
        fi

module_LTLIBRARIES =				\
	$(IM_XIM_MODULE)			\
	im-am-et.la				\
	im-cedilla.la				\
	im-cyrillic-translit.la			\
	im-hangul.la				\
	im-inuktitut.la				\
	im-ipa.la				\
	im-thai-broken.la			\
	im-ti-er.la				\
	im-ti-et.la				\
	im-viqr.la

gtk.immodules: Makefile.am $(module_LTLIBRARIES)
	$(top_builddir)/gtk/gtk-query-immodules-2.0 *.la > gtk.immodules

if CROSS_COMPILING
else
all-local: gtk.immodules
endif
