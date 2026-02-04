/**
 * @file version.c
 * @brief 版本信息存储 (确保编译进bin)
 */

#include "version.h"

/* 放入独立section，防止被优化掉 */
__attribute__((used, section(".version_info")))
const char VERSION_INFO[] = VERSION_FULL " " BUILD_DATE " " BUILD_TIME;
