#!/usr/bin/env python3
"""
自动扫描 CubeMX 生成的头文件，提取 MX_xxx_Init 函数，生成 board_init.c
"""

import re
import os
from pathlib import Path

# 配置
CORE_INC_DIR = "Core/Inc"
OUTPUT_FILE = "app/board_init.c"

# 需要排除的函数（这些不是外设初始化）
EXCLUDE_FUNCTIONS = {"MX_GPIO_Init"}  # GPIO 单独处理，因为要最先调用

# 固定顺序的初始化函数（按顺序调用）
FIXED_ORDER = ["MX_GPIO_Init"]


def find_mx_init_functions(inc_dir: str) -> list:
    """扫描头文件，提取 MX_xxx_Init 函数声明"""
    functions = []
    includes = []
    
    pattern = re.compile(r"void\s+(MX_\w+_Init)\s*\(void\)\s*;")
    
    inc_path = Path(inc_dir)
    if not inc_path.exists():
        print(f"Warning: {inc_dir} not found")
        return [], []
    
    for header in inc_path.glob("*.h"):
        # 跳过 main.h 和一些系统头文件
        if header.name in ["main.h", "stm32f4xx_it.h", "stm32f4xx_hal_conf.h"]:
            continue
        
        content = header.read_text(encoding="utf-8", errors="ignore")
        matches = pattern.findall(content)
        
        if matches:
            includes.append(header.name)
            for func in matches:
                if func not in functions:
                    functions.append(func)
    
    return functions, includes


def generate_board_init(functions: list, includes: list, output_file: str):
    """生成 board_init.c 文件"""
    
    # 分离固定顺序和其他函数
    fixed = [f for f in FIXED_ORDER if f in functions]
    others = [f for f in functions if f not in FIXED_ORDER]
    
    # 按字母排序其他函数
    others.sort()
    
    # 合并：固定顺序在前
    ordered_functions = fixed + others
    
    code = '''/**
 * @file board_init.c
 * @brief 板级初始化 (自动生成，请勿手动修改)
 * @note  由 scripts/gen_board_init.py 自动生成
 */

#include "main.h"
'''
    
    # 添加外设头文件
    for inc in sorted(includes):
        code += f'#include "{inc}"\n'
    
    code += '#include "auto_init.h"\n\n'
    code += '/* CubeMX 生成的时钟配置 */\n'
    code += 'extern void SystemClock_Config(void);\n\n'
    
    code += '''/**
 * @brief 板级硬件初始化
 */
static int board_init(void)
{
    HAL_Init();
    SystemClock_Config();
    
'''
    
    # 添加初始化调用
    for func in ordered_functions:
        code += f"    {func}();\n"
    
    code += '''    
    return 0;
}
INIT_BOARD_EXPORT(board_init);
'''
    
    # 写入文件
    output_path = Path(output_file)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(code, encoding="utf-8")
    print(f"Generated: {output_file}")
    print(f"  Functions: {', '.join(ordered_functions)}")


def main():
    # 获取项目根目录
    script_dir = Path(__file__).parent
    project_root = script_dir.parent
    os.chdir(project_root)
    
    print("Scanning CubeMX headers...")
    functions, includes = find_mx_init_functions(CORE_INC_DIR)
    
    if not functions:
        print("No MX_xxx_Init functions found!")
        return 1
    
    generate_board_init(functions, includes, OUTPUT_FILE)
    return 0


if __name__ == "__main__":
    exit(main())
