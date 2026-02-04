# version.cmake - 每次编译时生成 version.h

# Get git hash
execute_process(
    COMMAND git rev-parse --short=8 HEAD
    WORKING_DIRECTORY ${SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

# Get git branch
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

# Check if dirty
execute_process(
    COMMAND git diff --quiet HEAD
    WORKING_DIRECTORY ${SOURCE_DIR}
    RESULT_VARIABLE GIT_DIRTY_RESULT
)
if(GIT_DIRTY_RESULT EQUAL 0)
    set(GIT_DIRTY 0)
else()
    set(GIT_DIRTY 1)
endif()

# Defaults
if(NOT GIT_HASH)
    set(GIT_HASH "unknown")
endif()
if(NOT GIT_BRANCH)
    set(GIT_BRANCH "unknown")
endif()

# Build time
string(TIMESTAMP BUILD_TIME "%H:%M:%S")
string(TIMESTAMP BUILD_DATE "%Y-%m-%d")

# Generate
configure_file(
    ${SOURCE_DIR}/app/version.h.in
    ${SOURCE_DIR}/app/version.h
    @ONLY
)
