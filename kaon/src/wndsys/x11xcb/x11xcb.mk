libx11xcb.so:
	mkdir -p $(OUTDIR)
	$(CC) -I$(TOPSRCDIR) -shared -fPIC -lxcb -o $(OUTDIR)/$@ x11xcb.c
