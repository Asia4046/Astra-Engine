#pragma once

#include "defines.h"

enum {

    DARRAY_CAPACITY,
    DARRAY_LENGTH,
    DARRAY_STRIDE,
    DARRAY_FIELD_LENGTH

};

KAPI void* _darray_create(u64 length, u64 stride);
KAPI void* _darray_destroy(void* array);

KAPI u64 _darray_field_get(void* array, u64 field);