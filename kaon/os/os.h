/*
 * Author: Nikita Ermakov (coffe92@gmail.com)
 *
 * SPDX-License-Identifier: MIT
 */

#ifdef __linux__
# define ENTRY_GOOD_RETURN_VALUE 0
# define ENTRY_RETURN_TYPE int
# define ENTRY_TYPEARGS int argc, const char **argv
# define ENTRY_ARGS argc, argv
# define ENTRY_FUNCNAME main

# define ENTRY_POINT \
    ENTRY_RETURN_TYPE \
    ENTRY_FUNCNAME(ENTRY_TYPEARGS)
#endif

struct os_window
{
    int width, height;
    const char *name;
};

struct os_window *os_create_window(const char *name, int width, int height);

void os_loop();

int os_kill_window();
