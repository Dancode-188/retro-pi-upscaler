#pragma once

#include "emulator/memory.hpp"
#include "emulator/input.hpp"
#include "common/types.hpp"
#include <string>
#include <functional>
#include <memory>

namespace retro {

// System configuration
struct SystemConfig {
    uint32_t frameRate;        // Target frame rate
    uint32_t resolution[2];    // Width, Height
    bool audioEnabled;
    std::string saveDirectory;
};

// Frame callback for rendering/AI upscaling
using FrameCallback = std::function<void(const Frame&)>;

class System {
public:
    explicit System(const SystemConfig& config);
    ~System();

    // System control
    bool initialize();
    void shutdown();
    bool loadGame(const std::string& romPath);
    void run();
    void pause();
    void reset();

    // State management
    bool saveState(const std::string& filename);
    bool loadState(const std::string& filename);
    
    // Frame management
    void setFrameCallback(FrameCallback callback);
    Frame getCurrentFrame() const;

    // System state
    SystemState getState() const;
    float getFPS() const;
    
    // Sub-system access
    MemoryManager& getMemory();
    InputManager& getInput();

private:
    // Core components
    std::unique_ptr<MemoryManager> memoryManager;
    std::unique_ptr<InputManager> inputManager;
    SystemConfig config;
    SystemState state;

    // Frame handling
    Frame currentFrame;
    FrameCallback frameCallback;
    
    // Timing
    uint64_t frameCount;
    float currentFPS;

    // Internal methods
    void processFrame();
    void updateTiming();
    bool validateConfig(const SystemConfig& config);
};

} // namespace retro