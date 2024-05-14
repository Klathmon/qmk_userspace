#include "./oled_print_funcs.h"
#include "./keylogger.h"

/** Prints the current layer and optionally the OS mode on the top line of the OLED */
void oled_print_layer_state_string(bool write_os) {
    oled_set_cursor(0, 0);
    switch (biton32(layer_state)) {
        case _MAIN_WIN:
        case _MAIN_MAC:
            oled_write_ln_P(PSTR("Layer: Main"), false);
            break;
        case _MVMT_WIN:
        case _MVMT_MAC:
            oled_write_ln_P(PSTR("Layer: Movement"), false);
            break;
        case _HYPR_WIN:
        case _HYPR_MAC:
            oled_write_ln_P(PSTR("Layer: Hyper"), false);
            break;
        case _NUMR:
            oled_write_ln_P(PSTR("Layer: Number Row"), false);
            break;
        case _NUMP:
            oled_write_ln_P(PSTR("Layer: Numpad"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: ???"), false);
    }

    if (write_os) {
        oled_set_cursor(oled_max_chars() - 3, 0);
        if (is_mac_mode()) {
            oled_write_ln_P(PSTR("Mac"), false);
        } else {
            oled_write_ln_P(PSTR("Win"), false);
        }
    }
}

#ifdef MAC_WIN_MODE_ICON
// the logos itself pulled from the font image
static const char PROGMEM macWinLogo[][2][3] = {{{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}};

// for some reason using this causes the OLED timeout to break and i'm not sure why...
void oled_print_mode_icon(void) {
    oled_set_cursor(MAC_WIN_MODE_ICON_COL, MAC_WIN_MODE_ICON_ROW);
    oled_write_P(macWinLogo[(int)!is_mac_mode()][0], false);

    oled_set_cursor(MAC_WIN_MODE_ICON_COL, MAC_WIN_MODE_ICON_ROW + 1);
    oled_write_P(macWinLogo[(int)!is_mac_mode()][1], false);
}
#endif // MAC_WIN_MODE_ICON

#ifdef DYNAMIC_MACRO_ENABLE
void oled_print_recording_macro(void) {
    oled_clear();
    oled_write_ln_P(PSTR("Recording Macro:"), false);
    oled_write(read_keylogs(), false);
    oled_invert(false);
}
#endif // DYNAMIC_MACRO_ENABLE

/** OLED shutdown/bootloader message, only works on the master OLED */
void oled_print_boot_message(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 5; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
#ifdef GSB_FLASH_INVERT_ON_KEYPRESS
            oled_invert(false);
#endif
        } else {
            oled_write_P(PSTR("Rebooting "), false);
#ifdef GSB_FLASH_INVERT_ON_KEYPRESS
            oled_invert(false);
#endif
        }
    }

    oled_render_dirty(true);
}
