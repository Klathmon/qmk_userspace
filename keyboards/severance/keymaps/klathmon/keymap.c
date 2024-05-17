// this is my disgusting hack to get clangd to cooperate and not throw a fit about the macros that QMK handles in python
#ifndef QMK_KEYBOARD_H
// for vscode
#    define MATRIX_ROWS 999
#    define MATRIX_COLS 999
#    define LAYOUT(...) \
        {}
#    include "../../../../users/klathmon/klathmon.h"
#else
// for qmk
#    include QMK_KEYBOARD_H
#    include "klathmon.h"
#    include "custom_keycodes.h"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                                            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,                        KC_PSCR, KC_SCRL, KC_PAUS,
                 KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_PGDN, KC_INS, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,             KC_UP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,     KC_LEFT, KC_ENT,  KC_RGHT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RGUI, KC_END,              KC_DOWN,
                                                              KC_SPC,                                                                    KC_HOME, KC_DEL,  KC_END,
    )
};
// clang-format on
