AC_INIT([bibliotheque graphique iut], [1.1], [monnerat@u-pec.fr])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AM_PROG_AR
AC_PROG_LIBTOOL

if test "x$prefix" = "xNONE" ; then
  prefix="/usr"
  fi
if test "x$exec_prefix" = "xNONE" ; then
  exec_prefix=$prefix
fi
if test "x$datadir" = "xNONE" ; then
  datadir="/usr/share/" 
fi


PREFIX=$prefix
EXEMPLES_IMAGES_DIR="${datadir}/libgraph/images/"
AC_SUBST(EXEMPLES_IMAGES_DIR)
AC_SUBST(PREFIX)

AC_ARG_ENABLE(
	exemples,
	AS_HELP_STRING(
	[--enable-exemples],
	[construit les exemples (default is no)]
	),
	[ if test "x$enableval" = "xyes" ; then
    exemples="yes"
	else 
		exemples="no"
	fi
	],
	[ exemples="no" ]
)

have_xpm=no          
AC_ARG_ENABLE(xpm,   
  AC_HELP_STRING([--enable-xpm], [enable xpm support @<:@default=detect@:>@]),
  [want_xpm=$enableval],                                                              
  [want_xpm=auto]    
)       
AC_CHECK_HEADERS(X11/Xlib.h,, AC_MSG_ERROR([Cannot find Xlib.h. Make sure your CFLAGS environment variable contains include lines for the location of this file]))
AC_CHECK_HEADERS(X11/cursorfont.h,, AC_MSG_ERROR([Cannot find cursorfont.h. Make sure your CFLAGS environment variable contains include lines for the location of this file]))
AC_CHECK_HEADERS(X11/Xatom.h,, AC_MSG_ERROR([Cannot find Xatom.h. Make sure your CFLAGS environment variable contains include lines for the location of this file]))
AC_CHECK_HEADERS(X11/Xutil.h,, AC_MSG_ERROR([Cannot find Xutil.h. Make sure your CFLAGS environment variable contains include lines for the location of this file]))
AC_CHECK_HEADERS(X11/keysym.h,, AC_MSG_ERROR([Cannot find keysym.h. Make sure your CFLAGS environment variable contains include lines for the location of this file]))

             
if test "x$want_xpm" != "xno" ; then
  AC_CHECK_HEADERS(X11/xpm.h, [
    LIBS="$LIBS -lXpm"
    have_xpm=yes     
    AC_DEFINE(HAVE_XPM, 1, [XPM Support des images xpm ])])
    if test "x$want_xpm$have_xpm" = "xyesno" ; then
      AC_MSG_ERROR([XPM support est demandé mais pas trouvé])
    fi               
fi   
#AC_CHECK_HEADERS(X11/xpm.h,, AC_MSG_ERROR([Cannot find xpm.h. Make sure your CFLAGS environment variable contains include lines for the location of this file]))


AC_CONFIG_HEADERS([config.h])
AM_CONDITIONAL([COND_EXPLES], [test "$exemples" = yes])

AC_CONFIG_FILES([Makefile src/Makefile src/lib/Makefile src/include/Makefile src/exemples/Makefile])
AC_OUTPUT
AC_MSG_CHECKING([exemples construits])
AC_MSG_RESULT([${exemples}])
AC_MSG_CHECKING([support xpm])
AC_MSG_RESULT([${have_xpm}])
