/*
 * Author: Nikita Ermakov <sh1r4s3@mail.si-head.nl>
 *
 * SPDX-License-Identifier: MIT
 *
 * Description: This is a Xlib back-end for the Kaon engine. It is using for
 * communication with X11 window system. The extensive documentation about
 * Xlib is available there [0].
 *
 * Refs:
 * [0] https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#Introduction_to_Xlib
 */

#include "xlib.hpp"
#include <X11/X.h>

WndSysBackend::WndSysBackend(int width, int height, const char *name)
    : mWidth(width), mHeight(height), mName(name),
      /*
       * The first event number in the list of events from X11/X.h is KeyPress
       * The last event number in the list is LASTevent
       */
      mEvHashTbl(LASTEvent - KeyPress, [](const int& e) { return e - KeyPress + 1; } ) {

  // Connect to the X server. We're using a DISPLAY environment
  // variable here, so set the first argument to NULL.
  if (!(mDisplay = XOpenDisplay(nullptr)))
    return;

  // Get the root window.
  mRootWnd = DefaultRootWindow(mDisplay);

  // Get visual for given attributes
  GLint visAtt[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
  mVisInfo = glXChooseVisual(mDisplay, 0, visAtt);

  // Create colormap for the window
  mCMap = XCreateColormap(mDisplay, mRootWnd, mVisInfo->visual, AllocNone);

  // Create window
  mSwa.colormap = mCMap;
  mSwa.event_mask = ExposureMask | KeyPressMask;
  mWnd = XCreateWindow(mDisplay,
                      mRootWnd,
                      0, 0,             // (x, y) position of the window
                      600, 600,         // width and height of the window
                      0,                // border width
                      mVisInfo->depth,
                      InputOutput,
                      mVisInfo->visual,
                      CWColormap | CWEventMask, &mSwa);

  XMapWindow(mDisplay, mWnd);
  XStoreName(mDisplay, mWnd, "K engine");

#ifdef K_GL_RNDR
  mGlc = glXCreateContext(mDisplay, mVisInfo, nullptr, GL_TRUE);
  glXMakeCurrent(mDisplay, mWnd, mGlc);
#endif

  mEvHashTbl[KeyPress] = WndSysEvents::keyPress;
  mEvHashTbl[Expose] = WndSysEvents::draw;
}

WndSysBackend::~WndSysBackend() {
#ifdef K_GL_RNDR
  glXMakeCurrent(mDisplay, None, nullptr);
  glXDestroyContext(mDisplay, mGlc);
#endif
  XDestroyWindow(mDisplay, mWnd);
  XCloseDisplay(mDisplay);
}

WndSysEvents::event WndSysBackend::GetEvent() {
  XNextEvent(mDisplay, &mXev);

  if (mXev.type == Expose) {
    XGetWindowAttributes(mDisplay, mWnd, &mGwa);
  }

  return mEvHashTbl[mXev.type];
}

void WndSysBackend::RefreshWindow() {
#ifdef K_GL_RNDR
  glXSwapBuffers(mDisplay, mWnd);
#endif
}

bool WndSysBackend::IsWindowOk() {
  return mDisplay != nullptr;
}
