#include "klathmon.h"
#ifdef OLED_ENABLE
#    include "./oled/oled.h"
#endif
#ifdef AUDIO_ENABLE
#    include "./features/audio.h"
#endif

/* Returns true if the keyboard is in mac mode */
bool is_mac_mode(void) {
    return IS_LAYER_ON(_MAIN_MAC) || IS_LAYER_ON(_MVMT_MAC) || IS_LAYER_ON(_HYPR_MAC);
}

bool     is_autocorrecting_t_typo = false;
uint16_t previous_keycode         = 0;

bool process_autocorrect_user(uint16_t *keycode, keyrecord_t *record, uint8_t *typo_buffer_size, uint8_t *mods) {
    if (*typo_buffer_size <= 1) {
        is_autocorrecting_t_typo = false;
    }

    switch (*keycode) {
        case KC_SPC:
            if (previous_keycode == KC_T) {
                is_autocorrecting_t_typo = true;
                *keycode                 = KC_Z;
            }
            break;
        case KC_BSPC:
            if (is_autocorrecting_t_typo) {
                is_autocorrecting_t_typo = false;
                *typo_buffer_size        = 0;
            }
            break;
    }

    previous_keycode = *keycode;

    oled_clear();
    oled_set_cursor(0, 0); // move to the second line
    oled_write_ln(get_u8_str(*typo_buffer_size, ' '), false);
    oled_write_ln(is_autocorrecting_t_typo ? "is autocorrecting" : " ", false);

    return true;
}

bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    for (uint8_t i = 0; i < backspaces; ++i) {
        tap_code(KC_BSPC);
    }

    if (is_autocorrecting_t_typo) {
        is_autocorrecting_t_typo = false;
        SEND_STRING(" t");
    }

    send_string_P(str);

    return false;
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
