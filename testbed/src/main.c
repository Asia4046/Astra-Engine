#include <core/logger.h>

int main(void){
    KFATAL("TEST MESSAGE %f", 3.14f);
    KERROR("TEST MESSAGE %f", 3.14f);
    KWARN("TEST MESSAGE %f", 3.14f);
    KINFO("TEST MESSAGE %f", 3.14f);
    KDEBUG("TEST MESSAGE %f", 3.14f);
    KTRACE("TEST MESSAGE %f", 3.14f);
    return 0;
}