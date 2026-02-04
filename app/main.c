/**
 * @file main.c
 * @brief 应用程序入口 (与CubeMX解耦)
 */

#include "main.h"
#include "gpio.h"
#include "auto_init.h"
#include "rtt_log.h"

/**
 * @brief 应用程序入口
 */
int main(void)
{


    while (1)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
        LOG_D("LED toggle");
        HAL_Delay(1000);
    }
}
