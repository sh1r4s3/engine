/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
 *
 * SPDX-License-Identifier: MIT
 */

struct os_window
{
    int width, height;
    const char *name;
};

struct os_window *os_create_window(const char *name, int width, int height);

void os_loop();

int os_kill_window();
