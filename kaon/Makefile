# TODO: This is just a simple sample Makefile.
# We need to rewrite it later or more specifically generate it automatically.

export CC = g++
export TOPSRCDIR = $(PWD)
export OUTDIR = $(TOPSRCDIR)/libs
export CPPFLAGS = -DK_GL_RNDR

all: libwndsys.so
	$(CC) $(CPPFLAGS) -Llibs/ -I. src/main.cpp -lwndsys -o kaon

libwndsys.so:
	$(MAKE) -C src/wndsys/ -f wndsys.mk

clean:
	rm -vrf libs/ kaon
	$(MAKE) -C src/wndsys/ -f wndsys.mk clean
