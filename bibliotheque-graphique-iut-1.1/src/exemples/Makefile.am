exemplesdir = $(exec_prefix)/bin/

AM_CPPFLAGS = \
-I. \
-I$(top_srcdir)/src/include \
-I$(top_builddir)/src/include\
-DEXEMPLES_IMAGES_DIR=\"@EXEMPLES_IMAGES_DIR@\"

LDADD = $(top_builddir)/src/lib/libgraph.la

AM_LDFLAGS = -lm

SRCS = \
ExempleGraphique.c \
ExempleSouris.c \
ExempleMandelbrot.c \
ExempleSprite.c
exemples_PROGRAMS = ExempleGraphique\
			   ExempleSouris \
			   ExempleMandelbrot \
			   ExempleSprite

filesdir = $(datadir)/libgraph/images
files_DATA = \
./images/walk-0.png \
./images/walk-1.png \
./images/walk-2.png \
./images/walk-3.png \
./images/walk-4.png\
./images/walk-5.png \
./images/walks-0.png \
./images/walks-1.png \
./images/walks-2.png \
./images/walks-3.png \
./images/walks-4.png \
./images/walks-5.png \
./images/arctis2.jpg \
./images/nouveau0.xpm \
./images/nouveau1.xpm \
./images/nouveau2.xpm \
./images/nouveau3.xpm \
./images/nouveau4.xpm \
./images/nouveau5.xpm \
./images/nouveauinverse0.xpm \
./images/nouveauinverse1.xpm \
./images/nouveauinverse2.xpm \
./images/nouveauinverse3.xpm \
./images/nouveauinverse4.xpm \
./images/nouveauinverse5.xpm 



EXTRA_DIST = $(files_DATA)
