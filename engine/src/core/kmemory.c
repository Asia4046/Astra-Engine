#include "kmemory.h"
#include "core/logger.h"
#include "platform/platform.h"

struct memory_stats {

    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];

};

static struct memory_stats stats;

void initialize_memory()
{
    platform_zero_memory(&stats, sizeof(stats));
}

void* kallocate(u64 size, memory_tag tag)
{
    if(tag == MEMORY_TAG_UNKNOWN)
    {
        KWARN("kallocate called using MEMORY_TAG_UNKOWN. Re class this allocation!");
    }

    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    void* block = platform_allocate(size, false);
    platform_zero_memory(block, size);
    return block;
}

void kfree(void* block, u64 size, memory_tag tag)
{
    if(tag == MEMORY_TAG_UNKNOWN)
    {
        KWARN("kallocate called using MEMORY_TAG_UNKOWN. Re class this allocation!");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;
    platform_free(block, false);
}

void* kzero_memory(void* block, u64 size)
{
    return platform_zero_memory(block, size);
}

KAPI void* kcopy_memory(void* dest, const void* source, u64 size)
{   
    return platform_copy_memory(dest, source, size);
}

KAPI void* kset_memory(void* dest, i32 value, u64 size)
{
    return platform_set_memory(dest, value, size);
}