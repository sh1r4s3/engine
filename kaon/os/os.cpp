/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
 *
 * SPDX-License-Identifier: MIT
 */

#include "os.hpp"

Os::Os(int width, int height, const char *name)
  : WindowSystem(width, height, name) {

}

void Os::Loop() {
  RefreshWindow();
}
