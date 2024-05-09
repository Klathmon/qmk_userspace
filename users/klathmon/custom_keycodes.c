#include "custom_keycodes.h"

// Macro Functions
/** Switches the KVM to Macos */
void kvm_mac(void) {
    layer_move(_MAIN_MAC);
    SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL) SS_TAP(X_P1), GSB_KVM_TAP_CODE_DELAY);
    // wait a bit, then slap an escape in there to make sure the macbook is woken up when switching to it
    wait_ms(500);
    tap_code(KC_ESC);
}
/** Switches the KVM to Windows */
void kvm_win(void) {
    layer_move(_MAIN_WIN);
    SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL) SS_TAP(X_P2), GSB_KVM_TAP_CODE_DELAY);
}

/** Switches the KVM to main screen Macos, secondary screen Windows */
void kvm_hybrid_mmac_swin(void) {
    kvm_mac();
    wait_ms(GSB_KVM_TAP_CODE_DELAY);
    SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL) SS_TAP(X_LEFT), GSB_KVM_TAP_CODE_DELAY);
}
/** Switches the KVM to main screen Windows, secondary screen Macos */
void kvm_hybrid_mwin_smac(void) {
    kvm_win();
    wait_ms(GSB_KVM_TAP_CODE_DELAY);
    SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL) SS_TAP(X_LEFT), GSB_KVM_TAP_CODE_DELAY);
}

/** Swaps the keyboard and mouse between windows and macos machines */
void kbm_swap_kbm(void) {
    layer_invert(_MAIN_MAC);
    SEND_STRING_DELAY(SS_TAP(X_RALT) SS_TAP(X_RALT), GSB_KVM_TAP_CODE_DELAY);
}

/** Sends the qmk flash command for this keyboard */
void send_flash_string(void) {
    const bool is_ctrl_cmd_held = get_mods() & (is_mac_mode() ? MOD_MASK_GUI : MOD_MASK_CTRL);

    if (is_ctrl_cmd_held) {
        unregister_mods(is_mac_mode() ? MOD_MASK_GUI : MOD_MASK_CTRL);
        SEND_STRING("qmk generate-compilation-database -kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER));
    } else {
        SEND_STRING("qmk flash -j 0 -kb " QMK_KEYBOARD " -km " QMK_KEYMAP SS_TAP(X_ENTER));
    }
}

/** Should be called from the keyboard's process_record_user function */
bool process_record_custom_keycode_handler(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case K_WIN:
            if (record->event.pressed) {
                kvm_win();
            }
            return false;
        case K_MAC:
            if (record->event.pressed) {
                kvm_mac();
            }
            return false;
        case K_MW_SM:
            if (record->event.pressed) {
                kvm_hybrid_mwin_smac();
            }
            return false;
        case K_MM_SW:
            if (record->event.pressed) {
                kvm_hybrid_mmac_swin();
            }
            return false;
        case K_S_KBM:
            if (record->event.pressed) {
                kbm_swap_kbm();
            }
            return false;
        case KQ_FLSH:
            if (record->event.pressed) {
                send_flash_string();
            }
            return false;
    }
    return true;
}
