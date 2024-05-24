#include <core/logger.h>
#include <core/asserts.h>
#include <platform/platform.h>
#include "defines.h"

int main(void){
    KFATAL("TEST MESSAGE %f", 3.14f);
    KERROR("TEST MESSAGE %f", 3.14f);
    KWARN("TEST MESSAGE %f", 3.14f);
    KINFO("TEST MESSAGE %f", 3.14f);
    KDEBUG("TEST MESSAGE %f", 3.14f);
    KTRACE("TEST MESSAGE %f", 3.14f);

    platform_state state;
    if(platform_startup(&state, "Astra Engine Testbed", 100, 100, 1280, 720)) {
        while(true) {
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);

    return 0;
}