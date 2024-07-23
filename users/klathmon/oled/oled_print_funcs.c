#include "./oled_print_funcs.h"
#include "./keylogger.h"
#include "./customized_font_reader.h"
#ifdef GSB_KVM_ENABLE
#    include "./features/kvm_manager.h"
#endif

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

#ifdef GSB_KVM_ENABLE
    oled_set_cursor(0, 1);
    switch (active_kvm_machine) {
        case KVM_MA1:
            oled_write_ln_P(PSTR("Focus: 1 Personal"), false);
            break;
        case KVM_MA2:
            oled_write_ln_P(PSTR("Focus: 2 Macbook"), false);
            break;
        case KVM_MA3:
            oled_write_ln_P(PSTR("Focus: 3 Win x64"), false);
            break;
        case KVM_MA4:
            oled_write_ln_P(PSTR("Focus: 4 Win ARM"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Focus: ? Unknown"), false);
            break;
    }
#endif
}

#ifdef GSB_MAC_WIN_MODE_ICON
// the logos itself pulled from the font image
static const char PROGMEM macWinLogo[][2][3] = {{{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}};

// for some reason using this causes the OLED timeout to break and i'm not sure why...
void oled_print_mode_icon(void) {
    oled_set_cursor(GSB_MAC_WIN_MODE_ICON_COL, GSB_MAC_WIN_MODE_ICON_ROW);
    oled_write_P(macWinLogo[(int)!is_mac_mode()][0], false);

    oled_set_cursor(GSB_MAC_WIN_MODE_ICON_COL, GSB_MAC_WIN_MODE_ICON_ROW + 1);
    oled_write_P(macWinLogo[(int)!is_mac_mode()][1], false);
}
#endif // GSB_MAC_WIN_MODE_ICON

#ifdef DYNAMIC_MACRO_ENABLE
void oled_print_recording_macro(void) {
    oled_clear();
#    ifdef GSB_SHOW_KEYLOGGER_DURING_MACRO
    oled_write_ln_P(PSTR("Recording Macro:"), false);
    oled_write(read_keylogs(), false);
#    else
    oled_write_ln_P(PSTR("Recording Macro"), false);
#    endif
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

#ifdef OLED_SECONDARY_BORING_IMAGE
static float line_to_paint   = 0;
static float column_to_paint = 0;

void oled_print_secondary_logo(void) {
    if (!is_keyboard_master()) {
        line_to_paint += 0.02;
        column_to_paint += 0.02;

        oled_clear();
        oled_set_cursor((abs((int)column_to_paint) % 4), (abs((int)line_to_paint) % 4));
        oled_write_P(read_logo_P(), false);
    }
}
#endif
