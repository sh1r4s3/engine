/*
 * vim:sw=2:et:ts=2
 *
 * Author: Nikita Ermakov <sh1r4s3@mail.si-head.nl>
 *
 * SPDX-License-Identifier: MIT
 */

#include "wndsys.hpp"

WndSys::WndSys(int width, int height, const char *name)
  : WndSysBackend(width, height, name), Render(width, height) {

}

void WndSys::Draw() {
  Compute();
  RefreshWindow();
}
