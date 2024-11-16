# tests/test_core/CMakeLists.txt
add_executable(test_memory
    test_memory.cpp
)

target_link_libraries(test_memory
    PRIVATE
        retro_core
        Catch2::Catch2
)