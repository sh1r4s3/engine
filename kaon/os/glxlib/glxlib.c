/*
 * Author: Nikita Ermakov (coffe92@gmail.com)
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

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "glxlib.h"

Display *display;
Window root_wnd;

GLint vis_att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
XVisualInfo *vis_info;
Colormap cmap;
XSetWindowAttributes swa;
Window wnd;
GLXContext glc;
XWindowAttributes gwa;
XEvent xev;

int create_window(int width, int height)
{
  // Connect to the X server. We're using a DISPLAY environment
  // variable here, so set the first argument to NULL.
  if (!(display = XOpenDisplay(NULL)))
    return -1;

  // Get the root window.
  root_wnd = DefaultRootWindow(display);

  // Get visual for given attributes
  vis_info = glXChooseVisual(display, 0, vis_att);

  // Create colormap for the window
  cmap = XCreateColormap(display, root_wnd, vis_info->visual, AllocNone);

  // Create window
  swa.colormap = cmap;
  swa.event_mask = ExposureMask | KeyPressMask;
  wnd = XCreateWindow(display,
                      root_wnd,
                      0, 0,             // (x, y) position of the window
                      600, 600,         // width and height of the window
                      0,                // border width
                      vis_info->depth,
                      InputOutput,
                      vis_info->visual,
                      CWColormap | CWEventMask, &swa);

  XMapWindow(display, wnd);
  XStoreName(display, wnd, "K engine");

  glc = glXCreateContext(display, vis_info, NULL, GL_TRUE);
  glXMakeCurrent(display, wnd, glc);
  glEnable(GL_DEPTH_TEST);

  return 0;
}

void DrawAQuad() {
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

void loop() {
  while (1) {
    XNextEvent(display, &xev);
    if (xev.type == Expose) {
      XGetWindowAttributes(display, wnd, &gwa);
      glViewport(0, 0, gwa.width, gwa.height);
      DrawAQuad();
      glXSwapBuffers(display, wnd);
    }

    else if(xev.type == KeyPress) {
      return;
    }
  }
}

int kill_window() {
  glXMakeCurrent(display, None, NULL);
  glXDestroyContext(display, glc);
  XDestroyWindow(display, wnd);
  XCloseDisplay(display);
  return 0;
}
