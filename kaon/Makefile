# TODO: This is just a simple sample Makefile.
# We need to rewrite it later or more specifically generate it automatically.

export CC = g++
export TOPSRCDIR = $(PWD)
export OUTDIR = $(TOPSRCDIR)/objs
export CPPFLAGS = -DK_GL_RNDR

all: wndsys
	$(CC) $(CPPFLAGS) -Llibs/ -I. src/main.cpp objs/libwndsys.a -o kaon -lX11 -lGL -lGLU

wndsys:
	$(MAKE) -C src/wndsys/ -f wndsys.mk

clean:
	rm -vrf kaon objs
	$(MAKE) -C src/wndsys/ -f wndsys.mk clean
