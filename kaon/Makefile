# TODO: This is just a simple sample Makefile.
# We need to rewrite it later or more specifically generate it automatically.

export CC = g++
export TOPSRCDIR = $(PWD)
export OBJDIR = $(TOPSRCDIR)/objs

TARGETS := libwndsys.a librender.a
LIBS := -lX11 -lGL -lGLU

all: $(TARGETS)
	$(CC) $(CPPFLAGS) -Isrc src/main.cpp $(patsubst %,objs/%,$^) -o kaon $(LIBS)

%.a:
	$(MAKE) -C src/$(patsubst lib%.a,%,$@)/ -f $(patsubst lib%.a,%.mk,$@)

clean:
	rm -vrf kaon ${OBJDIR}
	find src/ -name "*.o" -delete
	$(MAKE) -C src/wndsys/ -f wndsys.mk clean
