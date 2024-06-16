#include "containers/darray.h"
#include "kmemory.h"

void* _darray_create(u64 length, u64 stride){
    u64 header_size = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 array_size = length * stride;
    u64* new_array = kallocate(header_size + array_size, MEMORY_TAG_DARRAY);
    kset_memory(new_array, 0, header_size + array_size);
    new_array[DARRAY_CAPACITY] = length;
    new_array[DARRAY_LENGTH] = 0;
    new_array[DARRAY_STRIDE] = stride;
    return (void*)(new_array + DARRAY_FIELD_LENGTH);
}

void _darray_destroy(void* array){
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    u64 header_size = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 total_size = header_size + header[DARRAY_CAPACITY] * header[DARRAY_STRIDE];
    kfree(header, total_size, MEMORY_TAG_DARRAY);
}

u64 _darray_field_get(void* array, u64 field){
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    return header[field];
}

u64 _darray_field_set(void* array, u64 field, u64 value){
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    header[field]= value;
}

void* _darray_resize(void* array){
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);
    void* temp = _darray_create(
        (DARRAY_RESIZE_FACTOR * darray_capacity(array)),
        stride);
    kcopy_memory(temp, array, length * stride);

    _darray_field_set(temp, DARRAY_LENGTH, length);
    _darray_destroy(array);
    return temp;
}