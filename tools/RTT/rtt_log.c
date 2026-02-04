//
// Created by 69566 on 25-8-14.
//
#define ENABLE_DEBUG_LOG
#ifdef ENABLE_DEBUG_LOG
#include "SEGGER_RTT.h"
#include <stdarg.h>

#define BUFFER_INDEX 0

void log(const char *sFormat, ...)
{
    va_list ParamList;
    va_start(ParamList, sFormat);
    SEGGER_RTT_vprintf(BUFFER_INDEX, sFormat, &ParamList);
    va_end(ParamList);
}

#else
// Release 模式下什么也不做
#define print_log(...)  ((void)0)
#endif