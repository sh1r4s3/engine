/*
 * Author: Nikita Ermakov <sh1r4s3@mail.si-head.nl>
 *
 * SPDX-License-Identifier: MIT
 */

#include "wndsys/wndsys.hpp"

int main(int argc, char **argv)
{
  {
    WndSys wndsys(800, 600, "kaon");
    while (1) {
      WndSysEvets::events ev = wndsys.GetEvent();
    }
  }

  return 0;
}
