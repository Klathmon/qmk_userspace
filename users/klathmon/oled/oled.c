#include "oled.h"
#include "oled_print_funcs.h"
#include "keylogger.h"

#ifdef DYNAMIC_MACRO_ENABLE
bool is_recording_macro = false;
#endif

#ifdef GSB_FLASH_INVERT_ON_KEYPRESS
bool should_flash_inverted = false;
#endif

#ifdef SPLIT_TRANSPORT_MIRROR
// used to get the fully mirrored OLED working with some split configuration stuff
WEAK bool should_process_keypress(void) {
    return true;
}
#endif // SPLIT_TRANSPORT_MIRROR

#ifdef DYNAMIC_MACRO_ENABLE
/** Handle clearing out the previous recording and setting the index to 0 when we start recording a new dynamic macro */
WEAK void dynamic_macro_record_start_user(int8_t direction) {
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
        keylogs_str[i] = ' ';
    }
    keylogs_str_idx = 0;

    is_recording_macro = true;
}
/** Handles setting the bool flag when we are done recording a macro */
WEAK void dynamic_macro_record_end_user(int8_t direction) {
    is_recording_macro = false;
}
#endif // DYNAMIC_MACRO_ENABLE

/** Handles the custom OLED processing when needed, should be called from process_record_user in the keymap.c file */
WEAK bool process_record_oled_handler(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef DYNAMIC_MACRO_ENABLE
        if (is_recording_macro) {
            set_keylog(keycode, record);
        }
#endif // DYNAMIC_MACRO_ENABLE

#ifdef GSB_FLASH_INVERT_ON_KEYPRESS
        should_flash_inverted = true;
#endif
    }

    return true;
}

/** flips the display 180 degrees if offhand */
WEAK oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

/** The actual update loop for the OLED */
WEAK bool oled_task_user(void) {
#ifdef DYNAMIC_MACRO_ENABLE
    if (is_recording_macro) {
        oled_print_recording_macro();
        return false;
    }
#endif // DYNAMIC_MACRO_ENABLE

#ifdef MAC_WIN_MODE_ICON
    oled_print_layer_state_string(false);
    oled_print_mode_icon();
#else
    oled_print_layer_state_string(true);
    oled_set_cursor(0, 1);          // move to the second line
    oled_write(read_logo(), false); // write the logo

#endif // MAC_WIN_MODE_ICON

#ifdef GSB_FLASH_INVERT_ON_KEYPRESS
    // if enabled, invert the display for a single frame
    oled_invert(should_flash_inverted);
    should_flash_inverted = false;
#endif

    return false;
}

/** shutdown user function, just defining it here for convenience, overwrite if necessary */
WEAK bool shutdown_user(bool jump_to_bootloader) {
    oled_print_boot_message(jump_to_bootloader);
    return true;
}
