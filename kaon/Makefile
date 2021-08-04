# TODO: This is just a simple sample Makefile.
# We need to rewrite it later or more specifically generate it automatically.

export CC = g++
export TOPSRCDIR = $(PWD)
export OUTDIR = $(TOPSRCDIR)/libs

all: libos.so
	$(CC) -Llibs/ -I. main.cpp -los -o kaon

libos.so:
	$(MAKE) -C os/ -f os.mk

clean:
	rm -vrf libs/ kaon
	$(MAKE) -C os/ -f os.mk clean
