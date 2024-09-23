add_library(base_lib
        memory_tool.cpp
        utils.cpp
)

target_link_libraries(base_lib stdc++fs)
target_link_libraries(base_lib absl::strings absl::base absl::time absl::status absl::statusor)
target_include_directories(base_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
