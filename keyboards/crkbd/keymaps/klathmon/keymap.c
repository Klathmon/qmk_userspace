// this is my disgusting hack to get clangd to cooperate and not throw a fit about the macros that QMK handles in python
#ifndef QMK_KEYBOARD_H
// for vscode
#    define MATRIX_ROWS 23
#    define MATRIX_COLS 23
#    define LAYOUT_split_3x6_3_ex2(...) \
        {                               \
        }
#    include "../../../../../users/klathmon/klathmon.h"
#else
// for qmk
#    include QMK_KEYBOARD_H
#    include "klathmon.h"
#    include "custom_keycodes.h"
#endif

#ifdef COMBO_ENABLE
#    include "g/keymap_combo.h"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN_WIN] = LAYOUT_split_3x6_3_ex2(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_TRNS,RM_TOGG, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_TRNS,M_LOCKW, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   M_LALTE, KC_LCTL, KC_SPC,                   M_NUMRD,  M_MVMTW, M_NUMP
    ),
    [_MVMT_WIN] = LAYOUT_split_3x6_3_ex2(
        RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, M_LWRDW, KC_UP,   M_RWRDW, KC_MINS, KC_EQL,
        RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC, KC_RBRC,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_HOME, KC_BSLS, KC_END , KC_LCBR, KC_RCBR,
                                   KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_MAIN_MAC] = LAYOUT_split_3x6_3_ex2(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_TRNS,RM_TOGG, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        M_MSPOT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_TRNS,M_LOCKM, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   M_LALTE, KC_LGUI, KC_SPC,                   M_NUMRD,  M_MVMTM, M_NUMP
    ),
    [_MVMT_MAC] = LAYOUT_split_3x6_3_ex2(
        RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, M_LWRDM, KC_UP,   M_RWRDM, KC_MINS, KC_EQL,
        RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_LBRC, KC_RBRC,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, M_HOMEM, KC_BSLS, M_ENDM,  KC_LCBR, KC_RCBR,
                                   KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_NUMR] = LAYOUT_split_3x6_3_ex2(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_TRNS,KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_NUMP] = LAYOUT_split_3x6_3_ex2(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_P0, KC_TRNS
    ),
    [_HYPR_WIN] = LAYOUT_split_3x6_3_ex2(
        DM_REC1, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_PSCR, KVM_KBM, KVM_MA1, KVM_MA2, KVM_MA3,
        DM_PLY1, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_TRNS, KC_TRNS,M_SLEPW, M_SLEPW, KC_VOLD, KC_MUTE, KC_VOLU, KC_WBAK, KC_WFWD,
        M_SSHTW, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,                  KQ_FLSH, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, M_TGLM,
                                   KC_TRNS, KQ_FLSH, QK_BOOT,                  QK_BOOT, KQ_FLSH, KC_TRNS
    ),
    [_HYPR_MAC] = LAYOUT_split_3x6_3_ex2(
        DM_REC2, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS, KC_PSCR, KVM_KBM, KVM_MA1, KVM_MA2, KVM_MA3,
        DM_PLY2, KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_TRNS, KC_TRNS,M_SLEPM, M_SLEPM, KC_VOLD, KC_MUTE, KC_VOLU, M_BAKM,  M_FWDM,
        M_SSHTM, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,                  KQ_FLSH, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, M_TGLM,
                                   KC_TRNS, KQ_FLSH, QK_BOOT,                  QK_BOOT, KQ_FLSH, KC_TRNS
    )
};
// clang-format on

// use tri-layer-state to handle the hyper layer
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _MVMT_WIN, _NUMP, _HYPR_WIN);
    state = update_tri_layer_state(state, _MVMT_MAC, _NUMP, _HYPR_MAC);
    return state;
}
