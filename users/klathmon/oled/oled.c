#include "./oled.h"
#include "./oled_print_funcs.h"
#include "./keylogger.h"
#include "./oled_timeout_handler.h"
#include "./customized_font_reader.h"
#include "./wpm_animation.h"

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
#    ifdef GSB_SHOW_KEYLOGGER_DURING_MACRO
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
#    endif
#endif // DYNAMIC_MACRO_ENABLE

/** Handles the custom OLED processing when needed, should be called from process_record_user in the keymap.c file */
WEAK bool process_record_oled_handler(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_STATIC_BUILDUP
        wpm_graph_key_pressed();
#endif
#ifdef DYNAMIC_MACRO_ENABLE
#    ifdef GSB_SHOW_KEYLOGGER_DURING_MACRO
        if (is_recording_macro) {
            set_keylog(keycode, record);
        }
#    endif
#endif // DYNAMIC_MACRO_ENABLE

#ifdef GSB_FLASH_INVERT_ON_KEYPRESS
        should_flash_inverted = true;
#endif
    }

    return true;
}

/** flips the display 180 degrees if offhand */
#ifndef OLED_WPM_GRAPH
WEAK oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}
#endif

/** The actual update loop for the OLED */
WEAK bool oled_task_user(void) {
#ifdef OLED_TIMEOUT
    if (!oled_handle_timeout()) {
        return false;
    }
#endif

#if defined(OLED_SECONDARY_BORING_IMAGE)
    if (!is_keyboard_master()) {
        oled_print_secondary_logo();

#    ifdef GSB_FLASH_INVERT_ON_KEYPRESS
        // if enabled, invert the display for a single frame
        oled_invert(should_flash_inverted);
        should_flash_inverted = false;
#    endif

        return false;
    }
#elif defined(OLED_WPM_GRAPH) || defined(OLED_STATIC_BUILDUP)
    if (!is_keyboard_master()) {
        print_wpm_graph();
#    ifdef GSB_FLASH_INVERT_ON_KEYPRESS
        // if enabled, invert the display for a single frame
        oled_invert(should_flash_inverted);
        should_flash_inverted = false;
#    endif
    }
#endif

#ifdef DYNAMIC_MACRO_ENABLE
    if (is_recording_macro) {
        oled_print_recording_macro();
#    ifdef GSB_FLASH_INVERT_ON_KEYPRESS
        // if enabled, invert the display for a single frame
        oled_invert(should_flash_inverted);
        should_flash_inverted = false;
#    endif
        return false;
    }
#endif // DYNAMIC_MACRO_ENABLE

#ifdef GSB_MAC_WIN_MODE_ICON
    oled_print_layer_state_string(false);
    oled_set_cursor(0, 2);              // move to the third line
    oled_write_P(read_logo_P(), false); // write the logo first (leaving room for the icon)
    oled_print_mode_icon();
#else
    oled_print_layer_state_string(true);
    oled_set_cursor(0, 1);              // move to the second line
    oled_write_P(read_logo_P(), false); // write the logo

#endif // GSB_MAC_WIN_MODE_ICON

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
