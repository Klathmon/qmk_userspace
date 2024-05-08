#pragma once
#include "quantum.h"         // IWYU pragma: keep
#include "config.h"          // IWYU pragma: keep
#include "custom_keycodes.h" // IWYU pragma: keep

/** allows a keymap file to optionally overwrite a function defined with this if needed */
#define WEAK __attribute__((weak))

// My Layers - these should be consistent across all of my keyboards
// clang-format off
enum my_layers {
    _MAIN_WIN, // Main layer for Windows
    _MVMT_WIN, // Movement layer for Windows
    _MAIN_MAC, // Main layer for MacOS
    _MVMT_MAC, // Movement layer for MacOS
    _NUMR,     // Number row delete layer tap
    _NUMP,     // Numpad layer
    _HYPR_WIN, // Hyper layer for Windows
    _HYPR_MAC  // Hyper layer for MacOS
};
// clang-format on

bool is_mac_mode(void);
