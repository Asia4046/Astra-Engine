// LOCAL HEADERS
#include "logger.h"

// GLOBAL HEADERS
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 initialize_logging() {
    // TODO: create a log file
    return true;
}

void shutdown_logging() {
    // TODO: IMPLEMENT LOGIC
}

KAPI void log_output(log_level level, const char* message, ...) {
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    // b8 is_error = level < 2;

    // ! DOING THIS IS REALLY BAD!!, IT IMPOSES A 32K CHAR LIMIT ON A SINGLE LOG ENTRY, BUT ANYWAYS ..
    char out_message[32000];
    memset(out_message, 0, sizeof(out_message));

    // FORMAT ORIGINAL MESSAGE
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[32000];
    sprintf(out_message2, "%s%s\n", level_strings[level], out_message);

    printf("%s", out_message2);
}