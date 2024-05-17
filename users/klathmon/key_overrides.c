#include "./klathmon.h"

// Key Overrides
#ifdef KEY_OVERRIDE_ENABLE
const key_override_t redo_windows        = ko_make_with_layers(MOD_MASK_CTRL, KC_Y, LCTL(LSFT(KC_Z)), 1 << _MAIN_WIN);    // Windows:  CTRL+Y -> CTRL+SHIFT+Z
const key_override_t redo_macos          = ko_make_with_layers(MOD_MASK_GUI, KC_Y, LGUI(LSFT(KC_Z)), 1 << _MAIN_MAC);     // Macos:    CMD+Y  -> CMD+SHIFT+Z
const key_override_t open_devtools_macos = ko_make_with_layers(MOD_MASK_SG, KC_J, LALT(LGUI(KC_J)), 1 << _MAIN_MAC);      // Macos:    CMD+J  -> OPT+CMD+J
const key_override_t goto_line_macos     = ko_make_with_layers(MOD_BIT(KC_LGUI), KC_G, LCTL(KC_G), 1 << _MAIN_MAC);       // Macos:    CMD+G  -> CTRL+G
const key_override_t video_recording     = ko_make_with_layers(MOD_BIT(KC_LCTL), KC_G, LALT(LSFT(KC_R)), 1 << _MAIN_MAC); // Macos:    CTRL+G -> ALT+SHIFT+R
// clang-format off
WEAK const key_override_t **key_overrides = (const key_override_t *[]){
    &redo_windows,
    &redo_macos,
    &open_devtools_macos,
    &goto_line_macos,
    &video_recording,
    NULL // Null terminate
};
// clang-format on
#endif // KEY_OVERRIDE_ENABLE
