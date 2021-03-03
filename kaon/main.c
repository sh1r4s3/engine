/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
 *
 * SPDX-License-Identifier: MIT
 */

#include "os/os.h"

ENTRY_POINT
{
    os_create_window("kaon", 800, 600);
    os_loop();
    os_kill_window();
    return ENTRY_GOOD_RETURN_VALUE;
}
