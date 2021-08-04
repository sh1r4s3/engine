/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
 *
 * SPDX-License-Identifier: MIT
 */

#include "os/os.hpp"

int main(int argc, char **argv)
{
  {
    Os os(800, 600, "kaon");
    os.Loop();
  }

  return 0;
}
