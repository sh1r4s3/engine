/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
 *
 * SPDX-License-Identifier: MIT
 */

#include "os.h"

#ifdef __linux__
# include "glxlib/glxlib.h"
#endif

static struct os_window window;

struct os_window *os_create_window(const char *name, int width, int height)
{
    // Fill the window structure.
    window.width = width;
    window.height = height;
    window.name = name;
    // Create a window.
    if (!create_window(width, height))
        return 0;
    return &window;
}

void os_loop()
{
    loop();
}

int os_kill_window()
{
    return kill_window();
}
