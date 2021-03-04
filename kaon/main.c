/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
 *
 * SPDX-License-Identifier: MIT
 */

#include "os/os.h"

int main(int argc, char **argv)
{
    os_create_window("kaon", 800, 600);
    os_loop();
    os_kill_window();
    return 0;
}
