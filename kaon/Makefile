# TODO: This is just a simple sample Makefile.
# We need to rewrite it later or more specifically generate it automatically.

export CC = gcc
export TOPSRCDIR = $(PWD)
export OUTDIR = $(TOPSRCDIR)/libs

all: libos.so
	$(CC) -Llibs/ -I. -los -lx11xcb main.c -o kaon

libos.so: libx11xcb.so
	$(MAKE) -C os/ -f os.mk

libx11xcb.so:
	$(MAKE) -C os/x11xcb/ -f x11xcb.mk

clean:
	rm -vrf libs/ kaon
