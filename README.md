# STM32F4 Ethernet Project

基于 STM32F407 的嵌入式项目模板，采用 CMake 构建，与 CubeMX 生成代码解耦。

## 项目结构

```
├── app/                 # 用户应用代码
├── Core/                # CubeMX 生成代码
├── Drivers/             # HAL 驱动
└── tools/               # 功能模块
    ├── auto_Init/       # 自动初始化框架
    └── RTT/             # RTT 日志
```

## 功能模块

### Auto Init - 自动初始化框架

类似 RT-Thread 的自动初始化机制，按优先级自动执行初始化函数。
```c
#include "auto_init.h"

static int xxx_init(void) {
    // 初始化代码
    return 0;
}
INIT_DEVICE_EXPORT(xxx_init);  // 注册为设备级初始化
```

**优先级（从高到低）：**
| 宏 | 用途 |
|---|---|
| `INIT_BOARD_EXPORT` | 板级初始化 (时钟、GPIO) |
| `INIT_PREV_EXPORT` | 预初始化 |
| `INIT_DEVICE_EXPORT` | 设备驱动 |
| `INIT_COMPONENT_EXPORT` | 组件 |
| `INIT_ENV_EXPORT` | 环境配置 |
| `INIT_APP_EXPORT` | 应用层 |

---

### RTT Log - 日志系统

基于 SEGGER RTT 的多级别日志，支持彩色输出。

```c
#include "rtt_log.h"

LOG_E("error: %d", code);   // 红色 - 错误
LOG_W("warning");           // 黄色 - 警告
LOG_I("info");              // 绿色 - 信息
LOG_D("debug: %s", str);    // 青色 - 调试
```

**配置 (rtt_log.h)：**
```c
#define LOG_ENABLE  1                // 0=关闭所有日志
#define LOG_LEVEL   LOG_LEVEL_DEBUG  // 日志级别
```

## 构建

```bash
cmake --preset Release
cmake --build build/Release
```

 
