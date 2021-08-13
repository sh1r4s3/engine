SRC := wndsys.cpp xlib/xlib.cpp render/render.cpp render/gl/RenderBackend.cpp
CXXFLAGS := -fpic

libwndsys.so: $(SRC:.cpp=.o)
	mkdir -p $(OUTDIR)
	$(CC) -shared $(CXXFLAGS) -o $(OUTDIR)/$@ $^ -I$(TOPSRCDIR) -L$(OUTDIR) -lX11 -lGL -lGLU

clean:
	find . -name "*.o" -delete
