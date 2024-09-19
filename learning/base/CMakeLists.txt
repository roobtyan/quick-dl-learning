add_library(base_lib
    memory_tool.cpp
)

target_include_directories(base_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})