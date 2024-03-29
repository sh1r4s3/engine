SRC := wndsys.cpp xlib/xlib.cpp
OBJ := $(SRC:.cpp=.o)
CPPFLAGS := -I$(TOPSRCDIR)/src
TARGET := libwndsys.a

${TARGET}: ${OBJ}
	mkdir -p $(OBJDIR)
	ar ru $(OBJDIR)/${TARGET} $(OBJ)
	ranlib $(OBJDIR)/${TARGET}

clean:
	find . -name "*.o" -delete
