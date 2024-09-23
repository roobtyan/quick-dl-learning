cmake_minimum_required(VERSION 3.20)
project(learning)

set(ABSL_PROPAGATE_CXX_STD ON)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
include(CPack)

FetchContent_Declare(
        absl
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(absl)

add_subdirectory(learning)

install(TARGETS learning
        RUNTIME DESTINATION bin)  # RUNTIME 表示可执行文件

# 软件信息
set(CPACK_PACKAGE_NAME "learning")

# 软件版本
set(CPACK_PACKAGE_VERSION_MAJOR 0)

# 软件作者
set(CPACK_PACKAGE_VENDOR "roobtyan")