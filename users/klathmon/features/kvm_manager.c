#include "./kvm_manager.h"

void kvm_switch_machine(uint16_t kvm_machine_keycode) {
    SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL), GSB_KVM_TAP_CODE_DELAY);

    switch (kvm_machine_keycode) {
        case KVM_MA1:
            tap_code(KC_P1);
            layer_move(_MAIN_WIN);
            break;
        case KVM_MA2:
            tap_code(KC_P2);
            layer_move(_MAIN_MAC);
            break;
        case KVM_MA3:
            tap_code(KC_P3);
            layer_move(_MAIN_WIN);
            break;
    }
}

bool process_record_kvm_manager(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KVM_MA1:
        case KVM_MA2:
        case KVM_MA3:
            if (record->event.pressed) {
                kvm_switch_machine(keycode);
            }
            return false;
    }
    return true;
}
