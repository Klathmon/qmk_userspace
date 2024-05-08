#pragma once
#include "klathmon.h" // IWYU pragma: keep

enum my_keycodes {
    K_WIN = SAFE_RANGE, // KVM: switch to windows PC
    K_MAC,              // KVM: switch to macbook
    K_MW_SM,            // KVM: hybrid view | main: windows  secondary: mac
    K_MM_SW,            // KVM: hybrid view | main: mac      secondary: windows
    K_S_KBM,            // KVM: swap keyboard and mouse
    KQ_FLSH,            // type out qmk flash command for this keyboard
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
#define M_SSHTM LGUI(LSFT(KC_5))      // Macos screenshot key
#define M_R_PLA RGB_MODE_PLAIN        // RGB Lighting
#define M_R_BRE RGB_MODE_BREATHE      // RGB Lighting
#define M_R_RAI RGB_MODE_RAINBOW      // RGB Lighting
#define M_R_SWI RGB_MODE_SWIRL        // RGB Lighting
#define M_R_SNA RGB_MODE_SNAKE        // RGB Lighting
#define M_R_KNI RGB_MODE_KNIGHT       // RGB Lighting

// Macro Functions
void kvm_mac(void);
void kvm_hybrid_mmac_swin(void);
void kvm_hybrid_mwin_smac(void);
void kvm_win(void);
void kbm_swap_kbm(void);
void send_flash_string(void);

bool process_record_custom_keycode_handler(uint16_t keycode, keyrecord_t *record);
