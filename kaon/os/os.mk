libos.so:
	mkdir -p $(OUTDIR)
	$(CC) -I$(TOPSRCDIR) -L$(OUTDIR) -lx11xcb -shared -fPIC  -o $(OUTDIR)/$@ os.c
