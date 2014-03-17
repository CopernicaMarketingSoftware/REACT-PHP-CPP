EXTENSION_DIR	= /usr/lib/php5/20090626/
CONFIG_DIR      = /etc/php5/conf.d/

all:
		$(MAKE) -C core all

clean:
		$(MAKE) -C core clean

install:
		cp -f core/react.so ${EXTENSION_DIR}
		cp -f react.ini ${CONFIG_DIR}
