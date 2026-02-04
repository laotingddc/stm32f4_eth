/**
 * @file auto_init.h
 * @brief 自动初始化框架 (类似RT-Thread)
 */
#ifndef __AUTO_INIT_H__
#define __AUTO_INIT_H__

typedef int (*init_fn_t)(void);

/* 初始化函数优先级定义 */
#define INIT_BOARD_EXPORT(fn)       INIT_EXPORT(fn, "1")      /* 板级初始化 */
#define INIT_PREV_EXPORT(fn)        INIT_EXPORT(fn, "2")      /* 预初始化 */
#define INIT_DEVICE_EXPORT(fn)      INIT_EXPORT(fn, "3")      /* 设备初始化 */
#define INIT_COMPONENT_EXPORT(fn)   INIT_EXPORT(fn, "4")      /* 组件初始化 */
#define INIT_ENV_EXPORT(fn)         INIT_EXPORT(fn, "5")      /* 环境初始化 */
#define INIT_APP_EXPORT(fn)         INIT_EXPORT(fn, "6")      /* 应用初始化 */

/* GCC编译器下的section定义 */
#define INIT_EXPORT(fn, level) \
    __attribute__((used)) const init_fn_t __init_##fn \
    __attribute__((section(".init_fn." level))) = fn

void auto_init(void);

#endif /* __AUTO_INIT_H__ */
