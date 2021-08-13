/*
 * Author: Nikita Ermakov <sh1r4s3@mail.si-head.nl>
 *
 * SPDX-License-Identifier: MIT
 */

#include "wndsys/wndsys.hpp"

int main(int argc, char **argv)
{
  bool run = true;
  {
    WndSys wndsys(800, 600, "kaon");
    while (run) {
      WndSysEvents::event ev = wndsys.GetEvent();
      switch (ev) {
      case WndSysEvents::draw:
        wndsys.Draw();
        break;
      case WndSysEvents::keyPress:
        run = true;
        break;
      }
    }
  }

  return 0;
}
