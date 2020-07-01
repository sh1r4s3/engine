SRC := os.c glxlib/glxlib.c
CFLAGS := -fpic

libos.so: $(SRC:.c=.o)
	mkdir -p $(OUTDIR)
	$(CC) -shared -o $(OUTDIR)/$@ $^ -I$(TOPSRCDIR) -L$(OUTDIR) -lX11 -lGL -lGLU

clean:
	rm -vf os.o glxlib/glxlib.o
