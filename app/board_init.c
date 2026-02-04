/**
 * @file board_init.c
 * @brief 板级初始化 (自动生成，请勿手动修改)
 * @note  由 scripts/gen_board_init.py 自动生成
 */

#include "main.h"
#include "gpio.h"
#include "auto_init.h"

/* CubeMX 生成的时钟配置 */
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
