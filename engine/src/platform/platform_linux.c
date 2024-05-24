#include "platform.h"

// * Linux Platform Layer
#if KPLATFORM_LINUX

#include "core/logger.h"

#include <xcb/xcb.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <X11/Xlib-xcb.h>
#include <X11/Xlib.h>
#include <sys/time.h>

#if _POSIX_C_SOURCE >= 199309L
#include <time.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct internal_state {
    Display* display;
    xcb_connection_t* connection;
    xcb_window_t window;
    xcb_screen_t* screen;
    xcb_atom_t wm_protocols;
    xcb_atom_t wm_delete_win;
} internal_state;

b8 platform_startup(
    platform_state* plat_state,
    const char* application_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height) {
    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state* state = (internal_state*)plat_state->internal_state;

    state->display = XOpenDisplay(NULL);

    XAutoRepeatOff(state->display);

    state->connection = XGetXCBConnection(state->display);

    if (xcb_connection_has_error(state->connection)) {
        KFATAL("Failed to connect to X server via XCB");
        return False;
    }

    const struct xcb_setup_t* setup = xcb_get_setup(state->display);

    xcb_screen_iterator_t it = xcb_setup_roots_iterator(setup);
    int screen_p = 0;
    for (i32 s = screen_p; s > 0; s--) {
        xcb_screen(&it);
    }

    state->screen = it.data;

    state->window = xcb_generate_id(state->connection);

    u32 event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

    u32 event_values = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
                       XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
                       XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
                       XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY;

    u32 value_list[] = {state->screen->black_pixel, event_values};

    xcb_void_cookie_t cookie = xcb_create_window(
        state->connection,
        XCB_COPY_FROM_PARENT,
        state->window,
        state->screen->root,
        x,
        y,
        width,
        height,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        state->screen->root_visual,
        event_mask,
        value_list);

    xcb_change_property(
        state->connection,
        XCB_PROP_MODE_REPLACE,
        state->window,
        XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING,
        8,
        strlen(application_name),
        application_name);

    xcb_intern_atom_cookie_t wm_delete_cookie = xcb_intern_atom(
        state->connection,
        0,
        strlen("WM_DELETE_WINDOW"),
        "WM_DELETE_WINDOW");

    xcb_intern_atom_cookie_t wm_protocols_cookie = xcb_intern_atom(
        state->connection,
        0,
        strlen("WM_PROTOCOLS"),
        "WM_PROTOCOLS");

    xcb_intern_atom_reply_t* wm_delete_reply = xcb_intern_atom_reply(
        state->connection,
        wm_delete_cookie,
        NULL);

    xcb_intern_atom_reply_t* wm_protocols_reply = xcb_intern_atom_reply(
        state->connection,
        wm_protocols_cookie,
        NULL);

    state->wm_delete_win = wm_delete_reply->atom;
    state->wm_protocols = wm_protocols_reply->atom;

    xcb_change_property(
        state->connection,
        XCB_PROP_MODE_REPLACE,
        state->window,
        wm_protocols_reply->atom,
        4,
        32,
        1,
        &wm_delete_reply->atom
    );

    xcb_map_window(state->connection, state->window);

    i32 stream_result = xcb_flush(state->connection);
    if(stream_result <= 0){
        KFATAL("An Error Occured When Flushing The Stream: %d", stream_result);
        return False;
    }

    return True;
}

void platform_shutdown(platform_state* plat_state) {
    internal_state *state = (internal_state *)plat_state->internal_state;

    XAutoRepeatOn(state->display);

    xcb_destroy_window(state->connection, state->window);
}

b8 platform_pump_messages(platform_state* plat_state) {
     internal_state *state = (internal_state *)plat_state->internal_state;

     xcb_generic_event_t *event;
     xcb_client_message_event_t *cm;

     b8 quit_flagged = False;
}

void* platform_allocate(u64 size, b8 aligned) {
}

void platform_free(void* block, b8 aligned) {
}

void* platform_zero_memory(void* block, u64 size) {
}

void* platform_copy_memory(void* dest, const void* source, u64 size) {
}

void* platform_set_memory(void* dest, i32 value, u64 size) {
}

void platform_console_write(const char* message, u8 colour) {
}

void platform_console_write_error(const char* message, u8 colour) {
}

f64 platform_get_absolute_time() {
}

void platform_sleep(u64 ms) {
}

#endif