#include "./audio.h"

float coin_song[][2]    = SONG(E__NOTE(_A5), HD_NOTE(_E6), );
float oneup_song[][2]   = SONG(Q__NOTE(_E6), Q__NOTE(_G6), Q__NOTE(_E7), Q__NOTE(_C7), Q__NOTE(_D7), Q__NOTE(_G7), );
float mario_song[][2]   = SONG(Q__NOTE(_E5), H__NOTE(_E5), H__NOTE(_E5), Q__NOTE(_C5), H__NOTE(_E5), W__NOTE(_G5), Q__NOTE(_G4), );
float mariogo_song[][2] = SONG(HD_NOTE(_C5), HD_NOTE(_G4), H__NOTE(_E4), H__NOTE(_A4), H__NOTE(_B4), H__NOTE(_A4), H__NOTE(_AF4), H__NOTE(_BF4), H__NOTE(_AF4), WD_NOTE(_G4), );
float disney_song[][2]  = SONG(H__NOTE(_G3), H__NOTE(_G4), H__NOTE(_F4), H__NOTE(_E4), H__NOTE(_CS4), H__NOTE(_D4), W__NOTE(_A4), H__NOTE(_B3), H__NOTE(_B4), H__NOTE(_A4), H__NOTE(_G4), H__NOTE(_FS4), H__NOTE(_G4), W__NOTE(_C5), H__NOTE(_D5), H__NOTE(_C5), H__NOTE(_B4), H__NOTE(_A4), H__NOTE(_G4), H__NOTE(_F4), H__NOTE(_E4), H__NOTE(_D4), W__NOTE(_A4), W__NOTE(_B3), W__NOTE(_C4), );

WEAK bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case M_HESCW:
        case M_HESCM:
            return false;
        default:
            return true;
    }
}

bool process_record_audio_handler(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COINS:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(coin_song);
            }
            return false;
        case MARIOT:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(mario_song);
            }
            return false;
        case MARIOG:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(mariogo_song);
            }
            return false;
        case DISNEY:
            if (record->event.pressed) {
                stop_all_notes();
                PLAY_SONG(disney_song);
            }
            return false;
    }
    return true;
}
