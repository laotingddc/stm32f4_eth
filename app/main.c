/**
 * @file main.c
 * @brief 应用程序入口
 */

#include "main.h"
#include "gpio.h"
#include "rtt_log.h"
int main(void)
{
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
        HAL_Delay(1000);
    }
}
