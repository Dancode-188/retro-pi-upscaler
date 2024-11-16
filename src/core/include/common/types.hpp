#pragma once

#include <cstdint>

namespace retro {
    // Common types for emulation
    using Byte = uint8_t;      // 8-bit unsigned
    using Word = uint16_t;     // 16-bit unsigned
    using Address = uint16_t;  // Memory address

    // System states
    enum class SystemState {
        IDLE,
        RUNNING,
        PAUSED,
        ERROR
    };

    // Frame data structure
    struct Frame {
        uint32_t* data;
        uint32_t width;
        uint32_t height;
        uint64_t timestamp;
    };
}