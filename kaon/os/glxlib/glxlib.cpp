/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
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

#include "glxlib.hpp"

WindowSystem::WindowSystem(int width, int height, const char *name) :
  mWidth(width), mHeight(height), mName(name) {

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

  mGlc = glXCreateContext(mDisplay, mVisInfo, nullptr, GL_TRUE);
  glXMakeCurrent(mDisplay, mWnd, mGlc);
  glEnable(GL_DEPTH_TEST);
}

WindowSystem::~WindowSystem() {
  glXMakeCurrent(mDisplay, None, nullptr);
  glXDestroyContext(mDisplay, mGlc);
  XDestroyWindow(mDisplay, mWnd);
  XCloseDisplay(mDisplay);
}

void WindowSystem::DrawQuad() {
 glClearColor(1.0, 1.0, 1.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-1., 1., -1., 1., 1., 20.);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

 glBegin(GL_QUADS);
  glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
  glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
  glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
  glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
  glEnd();
}

void WindowSystem::RefreshWindow() {
  while (1) {
    XNextEvent(mDisplay, &mXev);
    if (mXev.type == Expose) {
      XGetWindowAttributes(mDisplay, mWnd, &mGwa);
      glViewport(0, 0, mGwa.width, mGwa.height);
      DrawQuad();
      glXSwapBuffers(mDisplay, mWnd);
    }

    else if(mXev.type == KeyPress) {
      return;
    }
  }
}

bool WindowSystem::IsWindowOk() {
  return mDisplay != nullptr;
}
