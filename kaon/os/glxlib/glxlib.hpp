/*
 * Author: Nikita Ermakov <sh1r4s3@mail.si-head.nl>
 *
 * SPDX-License-Identifier: MIT
 */

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/glu.h>

class WindowSystem {
private:
  Display *mDisplay;
  Window mRootWnd;
  XVisualInfo *mVisInfo;
  Colormap mCMap;
  XSetWindowAttributes mSwa;
  Window mWnd;
  GLXContext mGlc;
  XWindowAttributes mGwa;
  XEvent mXev;

  void DrawQuad();
protected:
  int mWidth, mHeight;
  const char *mName;

  WindowSystem(int width, int height, const char *name);
  ~WindowSystem();

public:
  void RefreshWindow();
  bool IsWindowOk();
};

int create_window(int width, int height);

void loop();

int kill_window();
