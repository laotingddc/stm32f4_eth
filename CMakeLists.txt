cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME stm32f4_eth)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Auto generate board_init.c from CubeMX headers
find_package(Python3 COMPONENTS Interpreter REQUIRED)
execute_process(
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/gen_board_init.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# =============================================================================
# Version info (Git hash + build time) - 每次编译更新
# =============================================================================
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# 创建自定义target，每次编译前生成version.h
add_custom_target(version_header ALL
    COMMAND ${CMAKE_COMMAND}
        -DVERSION_MAJOR=${VERSION_MAJOR}
        -DVERSION_MINOR=${VERSION_MINOR}
        -DVERSION_PATCH=${VERSION_PATCH}
        -DSOURCE_DIR=${CMAKE_SOURCE_DIR}
        -P ${CMAKE_SOURCE_DIR}/cmake/version.cmake
    BYPRODUCTS ${CMAKE_SOURCE_DIR}/app/version.h
    COMMENT "Generating version.h"
)

# version.c 依赖 version.h，确保每次都重新编译
set_source_files_properties(${CMAKE_SOURCE_DIR}/app/version.c
    PROPERTIES OBJECT_DEPENDS ${CMAKE_SOURCE_DIR}/app/version.h
)

# Auto collect all sources under tools/
file(GLOB_RECURSE TOOLS_SOURCES
    ${CMAKE_SOURCE_DIR}/tools/*/*.c
    ${CMAKE_SOURCE_DIR}/tools/*/*.S
)
file(GLOB TOOLS_INCLUDE_DIRS LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/tools/*)

# Auto collect all sources under app/
file(GLOB_RECURSE APP_SOURCES
    ${CMAKE_SOURCE_DIR}/app/*.c
)
file(GLOB APP_INCLUDE_DIRS LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/app)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${TOOLS_SOURCES}
    ${APP_SOURCES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${TOOLS_INCLUDE_DIRS}
    ${APP_INCLUDE_DIRS}
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

# Generate bin and hex files
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMENT "Generating bin and hex files"
)
