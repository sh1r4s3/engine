SRC := wndsys.cpp xlib/xlib.cpp
CFLAGS := -fpic

libwndsys.so: $(SRC:.cpp=.o)
	mkdir -p $(OUTDIR)
	$(CC) -shared -o $(OUTDIR)/$@ $^ -I$(TOPSRCDIR) -L$(OUTDIR) -lX11 -lGL -lGLU

clean:
	rm -vf wndsys.o xlib/xlib.o
