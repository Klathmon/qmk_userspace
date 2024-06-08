#include "./klathmon.h"
#include "action.h"

// Key Overrides
#ifdef KEY_OVERRIDE_ENABLE

// vscode_complete_import_win is a special little one, cause ko isn't working well with the GUI key for some reason
bool complete_import_win_custom_action(bool key_down, void *layer) {
    if (key_down) {
        tap_code(KC_F18);
        unregister_code(KC_LGUI);

        tap_code16(LCTL(KC_SPC));
    }
    return false;
}
const key_override_t vscode_complete_import_win = {.trigger_mods    = MOD_MASK_GUI,                      //
                                                   .layers          = 1 << _MAIN_WIN,                    //
                                                   .suppressed_mods = MOD_BIT(KC_LGUI),                  //
                                                   .options         = ko_option_no_reregister_trigger,   //
                                                   .custom_action   = complete_import_win_custom_action, //
                                                   .trigger         = KC_SPC,                            //
                                                   .replacement     = LCTL(KC_SPC),                      //
                                                   .enabled         = NULL};
// vscode_complete_import_win is a special little one, cause ko isn't working well with the GUI key for some reason
bool complete_win_c_ctrl_c(bool key_down, void *layer) {
    if (key_down) {
        tap_code(KC_F18);
        unregister_code(KC_LGUI);

        tap_code16(LCTL(KC_C));
    }
    return false;
}
const key_override_t stop_process_windows = {.trigger_mods    = MOD_MASK_GUI,                    //
                                             .layers          = 1 << _MAIN_WIN,                  //
                                             .suppressed_mods = MOD_BIT(KC_LGUI),                //
                                             .options         = ko_option_no_reregister_trigger, //
                                             .custom_action   = complete_win_c_ctrl_c,           //
                                             .trigger         = KC_C,                            //
                                             .replacement     = LCTL(KC_C),                      //
                                             .enabled         = NULL};

//                                                ko_make_with_layers(MOD_BIT(*)/MOD_MASK_*, KC_* keycode, KC_* override to send, 1 << _layer_to_be_active_on_goes_here)
const key_override_t redo_windows        = ko_make_with_layers(MOD_MASK_CTRL, KC_Y, LCTL(LSFT(KC_Z)), 1 << _MAIN_WIN); // Windows: CTRL+Y    -> CTRL+SHIFT+Z
const key_override_t redo_macos          = ko_make_with_layers(MOD_MASK_GUI, KC_Y, LGUI(LSFT(KC_Z)), 1 << _MAIN_MAC);  // Macos:   CMD+Y     -> CMD+SHIFT+Z
const key_override_t open_devtools_macos = ko_make_with_layers(MOD_MASK_SG, KC_J, LALT(LGUI(KC_J)), 1 << _MAIN_MAC);   // Macos:   CMD+J     -> OPT+CMD+J
const key_override_t goto_line_macos     = ko_make_with_layers(MOD_MASK_GUI, KC_G, LCTL(KC_G), 1 << _MAIN_MAC);        // Macos:   CMD+G     -> CTRL+G
const key_override_t video_recording     = ko_make_with_layers(MOD_MASK_CTRL, KC_G, LALT(LSFT(KC_R)), 1 << _MAIN_MAC); // Macos:   CTRL+G    -> ALT+SHIFT+R

// clang-format off
WEAK const key_override_t **key_overrides = (const key_override_t *[]){
    &vscode_complete_import_win,
    &stop_process_windows,
    &redo_windows,
    &redo_macos,
    &open_devtools_macos,
    &goto_line_macos,
    &video_recording,
    NULL // Null terminate
};
// clang-format on
#endif // KEY_OVERRIDE_ENABLE
