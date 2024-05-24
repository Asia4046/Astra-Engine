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

typedef struct internal_state 
{
    Display *display;
    xcb_connection_t* connection;
    xcb_window_t window;
    xcb_screen_t *screen;
    xcb_atom_t wm_protocols;
    xcb_atom_t wm_delete_win;
} internal_state;

b8 platform_startup(
    platform_state* plat_state,
    const char* application_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height
)
{
    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state *state = (internal_state *)plat_state->internal_state;
}

void platform_shutdown(platform_state* plat_state)
{

}

b8 platform_pump_messages(platform_state* plat_state)
{

}

void* platform_allocate(u64 size, b8 aligned)
{

}

void platform_free(void* block, b8 aligned)
{

}

void* platform_zero_memory(void* block, u64 size)
{

}

void* platform_copy_memory(void* dest, const void* source, u64 size)
{

}

void* platform_set_memory(void* dest, i32 value, u64 size)
{

}

void platform_console_write(const char* message, u8 colour)
{

}

void platform_console_write_error(const char* message, u8 colour)
{

}

f64 platform_get_absolute_time()
{

}

void platform_sleep(u64 ms)
{

}

#endif