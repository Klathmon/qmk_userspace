#pragma once
#include "../klathmon.h" // IWYU pragma: keep

const char *read_logo(void);

#ifdef DYNAMIC_MACRO_ENABLE
extern bool is_recording_macro;
#endif

#ifdef GSB_FLASH_INVERT_ON_KEYPRESS
extern bool should_flash_inverted;
#endif

bool process_record_oled_handler(uint16_t keycode, keyrecord_t *record);
