#pragma once

#include "../klathmon/config.h" // IWYU pragma: keep

#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_EFFECT_BREATHING
#    undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#    undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    undef RGBLIGHT_EFFECT_SNAKE
#    undef RGBLIGHT_EFFECT_KNIGHT
#    undef RGBLIGHT_EFFECT_CHRISTMAS
#    undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#    undef RGBLIGHT_EFFECT_RGB_TEST
#    undef RGBLIGHT_EFFECT_ALTERNATING
#    undef RGBLIGHT_EFFECT_TWINKLE

#    define RGBLIGHT_DEFAULT_SAT 0
#    define RGBLIGHT_DEFAULT_VAL 16
#    define RGBLIGHT_DEFAULT_SPD 120
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_SLEEP //  the RGB lighting will be switched off when the host goes to sleep
#endif
