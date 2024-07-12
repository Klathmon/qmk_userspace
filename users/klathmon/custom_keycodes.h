#pragma once
#include "./klathmon.h" // IWYU pragma: keep

enum my_keycodes {
    KQ_FLSH = SAFE_RANGE, // type out qmk flash command for this keyboard

    KVM_MA1, // KVM: switch to machine 1
    KVM_MA2, // KVM: switch to machine 2
    KVM_MA3, // KVM: switch to machine 3
    KVM_MA4, // KVM: switch to machine 4
    KVM_KBM, // KVM: switch to keyboard/mouse machine when running in split-host mode
    KVM_SCA, // KVM: switch screen A, triggers a leader key and waits for the machine to be pressed next
    KVM_SCB, // KVM: switch screen B, triggers a leader key and waits for the machine to be pressed next
    KVM_SCC, // KVM: switch screen C, triggers a leader key and waits for the machine to be pressed next

    // audio stuff
    COINS,
    MARIOT,
    MARIOG,
    DISNEY,
};

// Keycode Aliases
#define M_NUMP MO(_NUMP)              // numpad
#define M_NUMRD LT(_NUMR, KC_DEL)     // number row delete layer tap
#define M_LALTE LALT_T(KC_ESC)        // alt/esc hybrid
#define M_TGLM TG(_MAIN_MAC)          // switch win/mac mode
#define M_BAKM LOPT(KC_LEFT)          // Macos back
#define M_FWDM LOPT(KC_RGHT)          // Macos forward
#define M_MVMTW MO(_MVMT_WIN)         // Windows movement layer
#define M_MVMTM MO(_MVMT_MAC)         // Macos movement layer
#define M_MSPOT LCTL_T(LGUI(KC_SPC))  // Macos Spotlight/ctrl mod-tap
#define M_HESCW LT(_HYPR_WIN, KC_ESC) // Windows hyper/escape hybrid
#define M_HESCM LT(_HYPR_MAC, KC_ESC) // Macos hyper/escape hybrid
#define M_LWRDW LCTL(KC_LEFT)         // Windows left one word
#define M_LWRDM LALT(KC_LEFT)         // Macos left one word
#define M_RWRDW LCTL(KC_RIGHT)        // Windows right one word
#define M_RWRDM LALT(KC_RIGHT)        // Macos right one word
#define M_HOMEW KC_HOME               // Windows home
#define M_HOMEM LGUI(KC_LEFT)         // Macos home
#define M_ENDW KC_END                 // Windows end
#define M_ENDM LGUI(KC_RGHT)          // Macos end
#define M_LOCKW LGUI(KC_L)            // Windows lock
#define M_LOCKM LGUI(LCTL(KC_Q))      // Macos lock
#define M_SLEPW KC_SLEP               // Windows sleep
#define M_SLEPM LGUI(LALT(KC_PWR))    // Macos sleep
#define M_SSHTW LGUI(LSFT(KC_S))      // Windows screenshot key
#define M_SSHTM LALT(LSFT(KC_S))      // Macos screenshot key
#define M_R_PLA RGB_MODE_PLAIN        // RGB Lighting
#define M_R_BRE RGB_MODE_BREATHE      // RGB Lighting
#define M_R_RAI RGB_MODE_RAINBOW      // RGB Lighting
#define M_R_SWI RGB_MODE_SWIRL        // RGB Lighting
#define M_R_SNA RGB_MODE_SNAKE        // RGB Lighting
#define M_R_KNI RGB_MODE_KNIGHT       // RGB Lighting

// Macro Functions
void send_flash_string(void);

bool process_record_custom_keycode_handler(uint16_t keycode, keyrecord_t *record);
