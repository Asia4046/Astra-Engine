#include <core/logger.h>
#include <core/asserts.h>

int main(void){
    KFATAL("TEST MESSAGE %f", 3.14f);
    KERROR("TEST MESSAGE %f", 3.14f);
    KWARN("TEST MESSAGE %f", 3.14f);
    KINFO("TEST MESSAGE %f", 3.14f);
    KDEBUG("TEST MESSAGE %f", 3.14f);
    KTRACE("TEST MESSAGE %f", 3.14f);

    KASSERT(1 == 0);

    return 0;
}