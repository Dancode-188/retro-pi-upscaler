// tests/test_core/test_memory.cpp

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "emulator/memory.hpp"

namespace retro {

TEST_CASE("MemoryManager initialization", "[memory]") {
    SECTION("Default construction") {
        MemoryManager memory;
        REQUIRE_NOTHROW(memory.read(0x0000));  // First RAM address
        REQUIRE_NOTHROW(memory.read(0x1FFF));  // Last RAM address
    }

    SECTION("Custom sizes") {
        MemoryManager memory(0x1000, 0x1000, 0x4000);  // Smaller sizes
        REQUIRE_NOTHROW(memory.read(0x0000));
    }
}

TEST_CASE("Memory read/write operations", "[memory]") {
    MemoryManager memory;

    SECTION("RAM operations") {
        REQUIRE_NOTHROW(memory.write(0x0000, 0x42));
        REQUIRE(memory.read(0x0000) == 0x42);
    }

    SECTION("VRAM operations") {
        REQUIRE_NOTHROW(memory.write(0x2000, 0x42));
        REQUIRE(memory.read(0x2000) == 0x42);
    }

    SECTION("ROM write protection") {
        REQUIRE_THROWS(memory.write(0x4000, 0x42));
    }
}

TEST_CASE("ROM loading", "[memory]") {
    MemoryManager memory;
    std::vector<Byte> testRom(0x4000, 0x42);

    SECTION("Valid ROM loading") {
        REQUIRE_NOTHROW(memory.loadROM(testRom));
        REQUIRE(memory.read(0x4000) == 0x42);
    }

    SECTION("Oversized ROM") {
        std::vector<Byte> bigRom(0x9000, 0x42);  // Too big
        REQUIRE_THROWS(memory.loadROM(bigRom));
    }
}

TEST_CASE("Save states", "[memory]") {
    MemoryManager memory;

    SECTION("Save and load state") {
        // Write some test data
        memory.write(0x0000, 0x42);  // RAM
        memory.write(0x2000, 0x43);  // VRAM

        // Save state
        auto state = memory.saveState();

        // Modify memory
        memory.write(0x0000, 0x00);
        memory.write(0x2000, 0x00);

        // Load state back
        REQUIRE_NOTHROW(memory.loadState(state));
        REQUIRE(memory.read(0x0000) == 0x42);
        REQUIRE(memory.read(0x2000) == 0x43);
    }

    SECTION("Invalid state loading") {
        std::vector<Byte> invalidState(100, 0);  // Wrong size
        REQUIRE_THROWS(memory.loadState(invalidState));
    }
}

TEST_CASE("Memory mapping and regions", "[memory]") {
    MemoryManager memory;

    SECTION("Memory regions") {
        REQUIRE(memory.getRegion(0x0000) == MemoryManager::Region::RAM);
        REQUIRE(memory.getRegion(0x2000) == MemoryManager::Region::VRAM);
        REQUIRE(memory.getRegion(0x4000) == MemoryManager::Region::ROM);
    }

    SECTION("Invalid addresses") {
        REQUIRE_THROWS(memory.read(0xFFFF));  // Beyond memory space
        REQUIRE_THROWS(memory.write(0xFFFF, 0x42));
    }
}

} // namespace retro