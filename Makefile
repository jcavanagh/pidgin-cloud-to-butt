LIBDIR ?= ~/.purple/plugins
DATADIR ?= /usr/share
CC = gcc

LIBPURPLE_CFLAGS = -I/usr/include/libpurple -DPURPLE_PLUGINS -DENABLE_NLS
GLIB_CFLAGS = $(shell pkg-config --cflags glib-2.0)

#Standard stuff here
SOURCES =     \
    src/pidgin-cloud_to_butt.c

all:	release

ifdef DESTDIR

install:
	install -d -m 0755    ${DESTDIR}${LIBDIR}
	install pidgin-cloud_to_butt.so     ${DESTDIR}${LIBDIR}

uninstall:
	rm -f ${DESTDIR}${LIBDIR}/pidgin-cloud_to_butt.so

else

install:
	install -d -m 0755    ${LIBDIR}
	install pidgin-cloud_to_butt.so     ${LIBDIR}

uninstall:
	rm -f ${LIBDIR}/pidgin-cloud_to_butt.so

endif

clean:
	rm -f pidgin-cloud_to_butt.so

pidgin-cloud_to_butt.so:	${SOURCES}
	${CC} ${LIBPURPLE_CFLAGS} -Wall -pthread ${GLIB_CFLAGS} -I. -g3 -O2 -pipe ${SOURCES} -o pidgin-cloud_to_butt.so -shared -fPIC -DPIC -D_GNU_SOURCE

release:	pidgin-cloud_to_butt.so