PREFIX                  = /usr
INCLUDE_DIR             = ${PREFIX}/include
LIBRARY_DIR             = ${PREFIX}/lib

all:
		$(MAKE) -C core all

clean:
		$(MAKE) -C core clean

install:
		cp -f src/libreactcpp.a ${LIBRARY_DIR}
