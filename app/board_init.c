/**
 * @file board_init.c
 * @brief 板级初始化 (从CubeMX的main.c中提取)
 */

#include "main.h"
#include "gpio.h"
#include "auto_init.h"

/* 由 CubeMX 生成的时钟配置函数 (声明) */
extern void SystemClock_Config(void);

/**
 * @brief 板级硬件初始化
 */
static int board_init(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    return 0;
}
INIT_BOARD_EXPORT(board_init);
