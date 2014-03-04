TOOLCHAIN=/opt/arm-2010q1/bin
ARCH=arm
CC=arm-none-linux-gnueabi-g++
CXX=arm-none-linux-gnueabi-g++
PATH:=$(TOOLCHAIN):${PATH}
CROSS_COMPILE=arm-none-linux-gnueabi
STDLIBS=-lstdc++
AR=arm-none-linux-gnueabi-ar
RANLIB=arm-none-linux-gnueabi-ranlib

PROJECTDIR:=$(shell pwd)
PACKAGENAME:=
DESCRIPTION:=
SECTION:=Utilities
LIBFILES:=
BINFILES:=
ETCFILES:=
RECFILES:=


all:: build
install:: package

build::
	@export PATH=${PATH} && \
	export CC=${CC} && \
	cd src && \
	make
clean::
	cd src && \
	make clean

filecopy::
	@mkdir -p $(DEVELROOT)/CDI/bin
	@cp src/tempsensormonitor $(DEVELROOT)/CDI/bin/.

package::
	@${PROJECTROOT}/createpackage.sh "${PROJECTDIR}" "${PACKAGENAME}" "${LIBFILES}" "${BINFILES}" "${ETCFILES}" "${RECFILES}" "${DESCRIPTION}" "${SECTION}" "${CONTROLDIR}" "${PACKAGEDIR}" "${CDI_MAJOR_VERSION_NUMBER}" "${SVN_DATE}" "${ARCH}"
