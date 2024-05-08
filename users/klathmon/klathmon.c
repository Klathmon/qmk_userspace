#include "klathmon.h"
#ifdef OLED_ENABLE
#    include "./oled/oled.h"
#endif

/* Returns true if the keyboard is in mac mode */
bool is_mac_mode(void) {
    return IS_LAYER_ON(_MAIN_MAC) || IS_LAYER_ON(_MVMT_MAC) || IS_LAYER_ON(_HYPR_MAC);
}

/** The default process_record_user, i'm going to try and get this to work the same on all my boards */
WEAK bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (!process_record_oled_handler(keycode, record)) {
        return false;
    }
#endif

    if (!process_record_custom_keycode_handler(keycode, record)) {
        return false;
    }

    switch (keycode) {
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
