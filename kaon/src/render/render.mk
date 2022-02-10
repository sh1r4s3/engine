SRC := render.cpp gl/RenderBackend.cpp
OBJ := $(SRC:.cpp=.o)
CPPFLAGS := -I$(TOPSRCDIR)
TARGET := librender.a

${TARGET}: ${OBJ}
	mkdir -p $(OBJDIR)
	ar ru $(OBJDIR)/${TARGET} $(OBJ)
	ranlib $(OBJDIR)/${TARGET}

clean:
	find . -name "*.o" -delete
