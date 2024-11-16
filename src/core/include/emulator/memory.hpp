#pragma once

#include "common/types.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

namespace retro {

class MemoryException : public std::runtime_error {
public:
    explicit MemoryException(const char* message) : std::runtime_error(message) {}
};

class MemoryManager {
public:
    // Memory regions
    enum class Region {
        RAM,    // Main RAM
        VRAM,   // Video RAM
        ROM,    // Game ROM
        SAVE    // Save state
    };

    // Constructor with memory size configuration
    explicit MemoryManager(Address ramSize = 0x2000,    // 8KB RAM
                         Address vramSize = 0x2000,      // 8KB VRAM
                         Address romSize = 0x8000);      // 32KB ROM

    // Memory operations
    Byte read(Address address);
    void write(Address address, Byte value);

    // Memory state management
    bool loadROM(const std::vector<Byte>& romData);
    std::vector<Byte> saveState();
    bool loadState(const std::vector<Byte>& state);

    // Memory info
    Region getRegion(Address address) const;
    bool isValidAddress(Address address) const;

private:
    std::vector<Byte> ram;
    std::vector<Byte> vram;
    std::vector<Byte> rom;

    const Address ramSize;
    const Address vramSize;
    const Address romSize;

    // Memory mapping helpers
    Address mapAddress(Address address) const;
    bool isReadOnly(Address address) const;
};

} // namespace retro