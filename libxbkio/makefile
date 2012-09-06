LIBVERSION=1
LIBSUBVERSION=0.0

all:
	cd src; \
	c++ -fPIC -Wall -g -c xbkio.cpp; \
	c++ -g -shared -WL,-soname,libxbkio.so.${LIBVERSION} -o libxbkio.so.${LIBVERSION}.${LIBSUBVERSION} xbkio.o -lc; \
	strip lib*; \
	cp lib* /usr/local/lib;
	-ln -sf /usr/local/lib/libxbkio.so.${LIBVERSION}.${LIBSUBVERSION} /usr/lib/libxbkio.so.${LIBVERSION};
	ln -sf /usr/lib/libxbkio.so.${LIBVERSION} /usr/lib/libxbkio${LIBVERSION}.so
	-mkdir /usr/include/xbk
	-cp include/*.h /usr/include/xbk	
	
