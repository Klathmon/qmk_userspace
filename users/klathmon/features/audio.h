#pragma once

#include "../klathmon.h" // IWYU pragma: keep

#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

bool process_record_audio_handler(uint16_t keycode, keyrecord_t *record);
