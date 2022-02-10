SRC := wndsys.cpp xlib/xlib.cpp render/render.cpp render/gl/RenderBackend.cpp
OBJ := $(SRC:.cpp=.o)
CPPFLAGS := -I$(TOPSRCDIR)

wndsys.o: ${OBJ}
	mkdir -p $(OUTDIR)
	ar ru $(OUTDIR)/libwndsys.a $(OBJ)
	ranlib $(OUTDIR)/libwndsys.a

clean:
	find . -name "*.o" -delete
