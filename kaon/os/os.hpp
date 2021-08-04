/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
 *
 * SPDX-License-Identifier: MIT
 */

#ifdef __linux__
#  include "glxlib/glxlib.hpp"
#endif

class Os : public WindowSystem {
public:
  Os(int width, int height, const char *name);
  void Loop();
};
