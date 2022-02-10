#include <GL/glu.h>

class RenderBackend {
protected:
  int mWidth;
  int mHeight;
  float mRatio;
public:
  RenderBackend(int width, int height);
  void Compute();
};
