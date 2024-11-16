#pragma once

#include "common/types.hpp"
#include <array>
#include <bitset>
#include <memory>

namespace retro {

// Button states for standard controller
enum class Button {
    A,
    B,
    SELECT,
    START,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    TOTAL_BUTTONS  // Used for array sizing
};

// Input device types
enum class InputDevice {
    KEYBOARD,
    GAMEPAD,
    CUSTOM
};

class InputManager {
public:
    static constexpr size_t MAX_PLAYERS = 4;
    static constexpr size_t BUTTON_COUNT = static_cast<size_t>(Button::TOTAL_BUTTONS);

    InputManager();

    // Device management
    bool addDevice(uint8_t playerIndex, InputDevice deviceType);
    bool removeDevice(uint8_t playerIndex);
    bool isDeviceConnected(uint8_t playerIndex) const;

    // Input state
    bool isButtonPressed(uint8_t playerIndex, Button button) const;
    void updateButtonState(uint8_t playerIndex, Button button, bool pressed);
    std::bitset<BUTTON_COUNT> getPlayerState(uint8_t playerIndex) const;

    // Configuration
    bool mapButton(uint8_t playerIndex, Button button, uint32_t deviceButton);
    void clearMappings(uint8_t playerIndex);

    // System events
    void update();  // Process input events
    void reset();   // Reset all states

private:
    struct PlayerInput {
        bool active;
        InputDevice deviceType;
        std::bitset<BUTTON_COUNT> buttonStates;
        std::array<uint32_t, BUTTON_COUNT> buttonMappings;
    };

    std::array<PlayerInput, MAX_PLAYERS> players;

    // Input processing helpers
    void processKeyboardInput(uint8_t playerIndex);
    void processGamepadInput(uint8_t playerIndex);
};

} // namespace retro