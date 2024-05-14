#pragma once
#include "../klathmon.h" // IWYU pragma: keep

void oled_print_layer_state_string(bool write_os);
void oled_print_boot_message(bool bootloader);

#ifdef GSB_MAC_WIN_MODE_ICON
// where to render the logo as constants
#    define GSB_MAC_WIN_MODE_ICON_COL 19
#    define GSB_MAC_WIN_MODE_ICON_ROW 0
void oled_print_mode_icon(void);
#endif // GSB_MAC_WIN_MODE_ICON

#ifdef DYNAMIC_MACRO_ENABLE
void oled_print_recording_macro(void);
#endif // DYNAMIC_MACRO_ENABLE
