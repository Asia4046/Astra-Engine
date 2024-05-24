#include "application.h"
#include "platform/platform.h"
#include "logger.h"

typedef struct application_state {

    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    f64 last_time;

} application_state;

static b8 initialized = false;
static application_state app_state;

b8 application_create(application_config* config)
{
    if(initialized)
    {
        KERROR("application_create called more than once");
        return false;
    }

    initialize_logging();

    KFATAL("TEST MESSAGE %f", 3.14f);
    KERROR("TEST MESSAGE %f", 3.14f);
    KWARN("TEST MESSAGE %f", 3.14f);
    KINFO("TEST MESSAGE %f", 3.14f);
    KDEBUG("TEST MESSAGE %f", 3.14f);
    KTRACE("TEST MESSAGE %f", 3.14f);

    app_state.is_running = true;
    app_state.is_suspended = false;

    if(!platform_startup(&app_state.platform, config->name, config->start_pos_x, config->start_pos_y, config->start_width, config->start_height)) {
       return false;
    }

    initialized = true;

    return true;
   
}

b8 application_run()
{
     while(app_state.is_running) {
            if(!platform_pump_messages(&app_state.platform))
            {
                app_state.is_running = false;
            }
        }

    app_state.is_running = false;

    platform_shutdown(&app_state.platform);

    return true;
}