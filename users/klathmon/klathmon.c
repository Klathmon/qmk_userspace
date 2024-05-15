#include "./klathmon.h"
#ifdef OLED_ENABLE
#    include "./oled/oled.h"
#endif
#ifdef AUDIO_ENABLE
#    include "./features/audio.h"
#endif

#ifdef CONSOLE_ENABLE
static bool last_is_mac_mode = false;
#endif

/* Returns true if the keyboard is in mac mode */
bool is_mac_mode(void) {
    bool on_mac_layer = IS_LAYER_ON(_MAIN_MAC) || IS_LAYER_ON(_MVMT_MAC) || IS_LAYER_ON(_HYPR_MAC);
#ifdef CONSOLE_ENABLE
    if (last_is_mac_mode != on_mac_layer) {
        // Log the switch of mac mode for debugging
        uprintf("Is mac mode: %s\n", on_mac_layer ? "true" : "false");
        last_is_mac_mode = on_mac_layer;
    }
#endif
    return on_mac_layer;
}

/** The default process_record_user, i'm going to try and get this to work the same on all my boards */
WEAK bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (!process_record_oled_handler(keycode, record)) {
        return false;
    }
#endif

#ifdef AUDIO_ENABLE
    if (!process_record_audio_handler(keycode, record)) {
        return false;
    }
#endif

    if (!process_record_custom_keycode_handler(keycode, record)) {
        return false;
    }

    switch (keycode) {
        // this is dumb, but LCTL_T can't send the LGUI(KC_SPC) keycode, so we have to intercept and do it manually here
        case LCTL_T(LGUI(KC_SPC)): {
            if (record->tap.count && record->event.pressed) {
                tap_code16(LGUI(KC_SPC));
                return false;
            }
        }
        default: {
            return true; // Process all other keycodes normally
        }
    }
}

// if we disable this, then replacing these (also weak) functions with our own can save 500 bytes
#ifdef GSB_DISABLE_MAGIC_KEYCODES
WEAK uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}
WEAK uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif
