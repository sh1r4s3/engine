#include <GL/glu.h>

class RenderBackend {
protected:
  int width;
  int height;
public:
  RenderBackend(int width, int height);
  void Compute();
};
