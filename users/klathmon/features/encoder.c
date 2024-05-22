#include "../klathmon.h"

// Rotary Encoder Processing
WEAK bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (biton32(layer_state)) {
        // scroll through space!
        case _MVMT_WIN:
        case _MVMT_MAC: {
            if (clockwise) {
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
            }
            break;
        }
        case _NUMP: {
            // scroll through time!
            if (is_mac_mode()) {
                if (clockwise) {
                    tap_code16(LGUI(LSFT(KC_Z)));
                } else {
                    tap_code16(LGUI(KC_Z));
                }
            } else {
                if (clockwise) {
                    tap_code16(LCTL(KC_Y));
                } else {
                    tap_code16(LCTL(KC_Z));
                }
            }
            break;
        }
#ifdef OLED_ENABLE
        case _HYPR_WIN:
        case _HYPR_MAC: {
            // TODO: pull this out into helper functions in an oled file
            uint8_t current_brightness = oled_get_brightness();
            if (clockwise) {
                if (current_brightness < 191) { // 255 - 64 = 191
                    oled_set_brightness(current_brightness + 64);
                } else {
                    oled_set_brightness(255);
                }
            } else {
                if (current_brightness > 64) {
                    oled_set_brightness(current_brightness - 64);
                } else {
                    oled_set_brightness(0);
                }
            }
            break;
        }
#endif // OLED_ENABLE
        default: {
#ifdef GSB_USE_FINE_VOLUME_CONTROL_ON_MACOS
            if (is_mac_mode()) {
                if (clockwise) {
                    tap_code16(LSFT(LALT(KC_VOLU)));
                } else {
                    tap_code16(LSFT(LALT(KC_VOLD)));
                }
            } else {
#endif
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
#ifdef GSB_USE_FINE_VOLUME_CONTROL_ON_MACOS
            }
#endif
            break;
        }
    }
    return false;
}
