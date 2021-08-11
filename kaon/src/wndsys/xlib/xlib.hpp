/*
 * Author: Nikita Ermakov <sh1r4s3@mail.si-head.nl>
 *
 * SPDX-License-Identifier: MIT
 */

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include "../events.hpp"

class WndSysBackend {
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
  // Please refer to the /usr/include/X11/X.h
  static constexpr int mNevents = LASTEvent - KeyPress;
  WndSysEvents::event mEvents[mNevents];

  void SetEvent(int xevent, WndSysEvents::event event);
protected:
  int mWidth, mHeight;
  const char *mName;

  WndSysBackend(int width, int height, const char *name);
  ~WndSysBackend();
public:
  WndSysEvents::event GetEvent();
  bool IsWindowOk();
};
