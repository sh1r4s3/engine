/*
 * Author: Nikita Ermakov <sh1r4s3@mail.si-head.nl>
 *
 * SPDX-License-Identifier: MIT
 */

#ifdef __linux__
#  include "xlib/xlib.hpp"
#endif
#include "render/render.hpp"

class WndSys : public WndSysBackend, public Render {
public:
  WndSys(int width, int height, const char *name);
  void Draw();
};
