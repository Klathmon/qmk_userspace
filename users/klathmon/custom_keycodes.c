#include "./custom_keycodes.h"

#ifdef SPLIT_KEYBOARD
#    include "split_util.h" // IWYU pragma: keep
#endif

#ifdef GSB_KVM_ENABLE
#    include "./features/kvm_manager.h"
#endif

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
#        else
#            ifdef GSB_RP2040_BOOTLOADER
        if (isLeftHand) {
            SEND_STRING(" -bl uf2-split-left");
        } else {
            SEND_STRING(" -bl uf2-split-right");
        }
#            endif
#        endif
#    endif
#endif
        SEND_STRING(SS_TAP(X_ENTER));
    }
}

/** Should be called from the keyboard's process_record_user function */
bool process_record_custom_keycode_handler(uint16_t keycode, keyrecord_t *record) {
#ifdef GSB_KVM_ENABLE
    if (!process_record_kvm_manager(keycode, record)) {
        return false;
    }
#endif

    switch (keycode) {
        case KQ_FLSH:
            if (record->event.pressed) {
                send_flash_string();
            }
            return false;
    }
    return true;
}
