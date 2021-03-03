/*
 * Author: Nikita Ermakov (sh1r4s3@mail.si-head.nl)
 *
 * SPDX-License-Identifier: MIT
 *
 * Description: This is a XCB back-end for the Kaon engine. It is using for
 * communication with X11 window system. A little bit of documentation could
 * be found at these refs [0,1,2,3]
 *
 * [Mon 08 Jun 2020]
 * - Currently it is not possible to solely use XCB with OpenGL [4]. It is
 *   still needed to use Xlib. But it is possible to use it with Vulkan and
 *   probably something else?
 *
 * Refs:
 * [0] https://xcb.freedesktop.org/manual/modules.html
 * [1] https://xcb.freedesktop.org/PublicApi/
 * [2] https://xcb.freedesktop.org/ProtocolStubApi/
 * [3] https://xcb.freedesktop.org/ProtocolExtensionApi/
 * [4] https://xcb.freedesktop.org/opengl/
 */

#include "os/x11xcb/x11xcb.h"
#include <xcb/xcb.h>
#include <stdlib.h>
#include <string.h>

static xcb_connection_t *connection;
static xcb_window_t window;
static xcb_gcontext_t foreground, background;

int create_window(int width, int height)
{
    // Make a connection to the X11 server.
    if (!(connection = xcb_connect(NULL, NULL)))
        return 0;

    // TODO: Make a check of the return value.
    // Get the first screen and window.
    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_iterator_t root_iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t *screen = root_iter.data;
    window = screen->root;

    // Create graphic context (GC) for the white foreground.
    foreground = xcb_generate_id(connection);
    uint32_t val[2] = {screen->white_pixel, 0};
    xcb_create_gc (connection, \
                   foreground, \
                   window, \
                   XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES, \
                   val);

    // Create graphic context (GC) for the black background.
    background = xcb_generate_id(connection);
    val[0] = screen->black_pixel;
    xcb_create_gc (connection, \
                   foreground, \
                   window, \
                   XCB_GC_BACKGROUND | XCB_GC_GRAPHICS_EXPOSURES, \
                   val);

    // Create a window.
    window = xcb_generate_id(connection);
    val[0] = screen->white_pixel;
    val[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
    xcb_create_window(connection,
                      XCB_COPY_FROM_PARENT,
                      window,
                      screen->root,
                      0, 0,
                      width, height,
                      10,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK,
                      val);

    // Map the window.
    xcb_map_window (connection, window);

    return 1;
}

void loop()
{
    // This is a test message.
    const char *hello_msg = "Hello Kaon!";

    // Do sync JIC.
    xcb_flush(connection);

    // Main loop.
    xcb_generic_event_t *event;
    while (event = xcb_wait_for_event(connection))
    {
        switch (event->response_type & ~0x80)
        {
            case XCB_EXPOSE:
                xcb_image_text_8(connection, strlen(hello_msg), window, foreground, 20, 20, hello_msg);
                xcb_flush(connection);
                break;
            case XCB_KEY_PRESS:
                return;
        }
        free(event);
    }
}

int kill_window()
{
    // TODO: Make a check of the return value.
    xcb_disconnect(connection);
    return 1;
}
