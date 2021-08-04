SRC := os.cpp glxlib/glxlib.cpp
CFLAGS := -fpic

libos.so: $(SRC:.cpp=.o)
	mkdir -p $(OUTDIR)
	$(CC) -shared -o $(OUTDIR)/$@ $^ -I$(TOPSRCDIR) -L$(OUTDIR) -lX11 -lGL -lGLU

clean:
	rm -vf os.o glxlib/glxlib.o
