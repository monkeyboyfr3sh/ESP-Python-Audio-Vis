#include "unit_test_def.h"

#include <stdarg.h>
#include "stdio.h"

void proxy_log(const char *fmt, ...)
{
    va_list arg;

    /* Write the error message */
    va_start(arg, fmt);
    printf(fmt, arg);
    va_end(arg);
}