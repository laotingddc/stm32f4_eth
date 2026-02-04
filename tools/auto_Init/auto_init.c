/**
 * @file auto_init.c
 * @brief 自动初始化框架实现
 */
#include "auto_init.h"

/* 定义初始化段的起始和结束符号 */
extern const init_fn_t __init_fn_start;
extern const init_fn_t __init_fn_end;

/**
 * @brief 执行所有自动初始化函数
 */
void auto_init(void)
{
    const init_fn_t *fn_ptr;
    
    for (fn_ptr = &__init_fn_start; fn_ptr < &__init_fn_end; fn_ptr++)
    {
        if (*fn_ptr)
        {
            (*fn_ptr)();
        }
    }
}
