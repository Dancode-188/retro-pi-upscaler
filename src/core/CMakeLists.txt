# src/core/CMakeLists.txt
add_library(retro_core
    src/emulator/memory.cpp
)

target_include_directories(retro_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)