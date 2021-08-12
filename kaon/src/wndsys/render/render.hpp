
#ifdef K_GL_RNDR
# include "gl/RenderBackend.hpp"
#endif

class Render : public RenderBackend {
public:
  Render(int width, int height);
};
