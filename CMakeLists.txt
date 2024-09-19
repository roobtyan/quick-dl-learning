cmake_minimum_required(VERSION 3.29)
project(learning)

set(ABSL_PROPAGATE_CXX_STD ON)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        absl
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
        GIT_TAG master
)

FetchContent_MakeAvailable(absl)

add_subdirectory(learning)