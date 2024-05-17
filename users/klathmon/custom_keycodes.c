#include "./custom_keycodes.h"
#include "split_util.h" // IWYU pragma: keep

// Macro Functions
void kvm_switch_input(uint8_t kvm_input_number) {
    SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL), GSB_KVM_TAP_CODE_DELAY);
    switch (kvm_input_number) {
        case KVM_INPUT_1:
            tap_code(KC_P1);
            layer_move(_MAIN_MAC);
            break;
        case KVM_INPUT_2:
            tap_code(KC_P2);
            layer_move(_MAIN_WIN);
            break;
    }
}

/** Switches the KVM to main screen Macos, secondary screen Windows */
void kvm_hybrid_mmac_swin(void) {
    kvm_switch_input(KVM_INPUT_1);
    wait_ms(GSB_KVM_TAP_CODE_DELAY);
    SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL) SS_TAP(X_LEFT), GSB_KVM_TAP_CODE_DELAY);
}
/** Switches the KVM to main screen Windows, secondary screen Macos */
void kvm_hybrid_mwin_smac(void) {
    kvm_switch_input(KVM_INPUT_2);
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
        SEND_STRING("qmk flash -j 0 -kb " QMK_KEYBOARD " -km " QMK_KEYMAP);
#ifdef EE_HANDS
// if we are on a split keyboard with ee_hands, we also want to flash the correct handedness bootloader command to flash the correct EEPROM
#    ifdef GSB_ATMEL_DFU_BOOTLOADER
        if (isLeftHand) {
            SEND_STRING(" -bl dfu-split-left");
        } else {
            SEND_STRING(" -bl dfu-split-right");
        }
#    else
#        ifdef GSB_CATERINA_BOOTLOADER
        if (isLeftHand) {
            SEND_STRING(" -bl avrdude-split-left");
        } else {
            SEND_STRING(" -bl avrdude-split-right");
        }
#        endif
#    endif
#endif
        SEND_STRING(SS_TAP(X_ENTER));
    }
}

/** Should be called from the keyboard's process_record_user function */
bool process_record_custom_keycode_handler(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KVM_C2:
            if (record->event.pressed) {
                kvm_switch_input(KVM_INPUT_2);
            }
            return false;
        case KVM_C1:
            if (record->event.pressed) {
                kvm_switch_input(KVM_INPUT_1);
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
