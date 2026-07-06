#include "./kvm_manager.h"
#include "_wait.h"
#include "quantum.h"

static bool pseudo_leader_key_pressed;
/** used for determining what os has "focus" */
static uint16_t last_activated_kvm_machine;
static uint16_t last_screen_split_target_machine;

static bool kvm_follow_screen_assignment_requested(void) {
    return pseudo_leader_key_pressed && !(get_mods() & (MOD_MASK_CTRL | MOD_MASK_GUI));
}

static uint8_t kvm_suspend_mods(void) {
    const uint8_t saved_mods = get_mods();
    if (saved_mods) {
        clear_mods();
        send_keyboard_report();
    }
    return saved_mods;
}

static void kvm_restore_mods(uint8_t saved_mods) {
    if (saved_mods) {
        set_mods(saved_mods);
        send_keyboard_report();
    }
}

static void kvm_swap_keyboard_mouse(void) {
    const uint8_t saved_mods = kvm_suspend_mods();

    SEND_STRING_DELAY(SS_TAP(X_RALT) SS_TAP(X_RALT), GSB_KVM_TAP_CODE_DELAY);

    kvm_restore_mods(saved_mods);

    if (last_activated_kvm_machine == KVM_MA2 || last_screen_split_target_machine == KVM_MA2) {
        layer_invert(_MAIN_MAC);
    }

    if (active_kvm_machine == last_activated_kvm_machine) {
        active_kvm_machine = last_screen_split_target_machine;
    } else {
        active_kvm_machine = last_activated_kvm_machine;
    }
}

static bool kvm_should_play_pause_remote(uint16_t keycode) {
    return keycode == KC_MPLY && (get_mods() & MOD_MASK_GUI) && (IS_LAYER_ON(_HYPR_WIN) || IS_LAYER_ON(_HYPR_MAC));
}

static void kvm_play_pause_remote(void) {
    const uint8_t saved_mods = kvm_suspend_mods();

    kvm_swap_keyboard_mouse();
    tap_code(KC_MPLY);
    kvm_swap_keyboard_mouse();

    kvm_restore_mods(saved_mods);
}

void kvm_switch_machine(uint16_t kvm_machine_keycode) {
    const uint8_t saved_mods = kvm_suspend_mods();

    if (!pseudo_leader_key_pressed) {
        SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL), GSB_KVM_TAP_CODE_DELAY);
    }

    switch (kvm_machine_keycode) {
        case KVM_MA1:
            tap_code(KC_P1);
            if (!pseudo_leader_key_pressed) {
                layer_move(_MAIN_WIN);
                layer_on(_HYPR_WIN);
            }
            break;
        case KVM_MA2:
            tap_code(KC_P2);
            if (!pseudo_leader_key_pressed) {
                layer_move(_MAIN_MAC);
                layer_on(_HYPR_MAC);
            }
            break;
        case KVM_MA3:
            tap_code(KC_P3);
            if (!pseudo_leader_key_pressed) {
                layer_move(_MAIN_WIN);
                layer_on(_HYPR_WIN);
            }
            break;
        case KVM_MA4:
            tap_code(KC_P4);
            if (!pseudo_leader_key_pressed) {
                layer_move(_MAIN_WIN);
                layer_on(_HYPR_WIN);
            }
            break;
    }

    if (!pseudo_leader_key_pressed) {
        active_kvm_machine = kvm_machine_keycode;
    }

    if (pseudo_leader_key_pressed) {
        pseudo_leader_key_pressed = false;
    }

    // just take up some time doing nothing to avoid repeat quick presses from wreaking havoc
    wait_ms(GSB_KVM_TAP_CODE_DELAY * 4);

    kvm_restore_mods(saved_mods);
}
bool process_record_kvm_manager(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MPLY:
            if (record->event.pressed && kvm_should_play_pause_remote(keycode)) {
                kvm_play_pause_remote();
                return false;
            }
            return true;
        case M_HESCW:
        case M_HESCM:
            if (!record->event.pressed) {
                layer_off(_HYPR_WIN);
                layer_off(_HYPR_MAC);
            }
            return true;
        case KVM_MA1:
        case KVM_MA2:
        case KVM_MA3:
        case KVM_MA4:
            if (record->event.pressed) {
                const bool follow_screen_assignment = kvm_follow_screen_assignment_requested();
                if (pseudo_leader_key_pressed) {
                    last_screen_split_target_machine = keycode;
                } else {
                    last_activated_kvm_machine = keycode;
                }
                kvm_switch_machine(keycode);
                if (follow_screen_assignment) {
                    kvm_swap_keyboard_mouse();
                }
            }
            return false;
        case KVM_KBM:
            if (record->event.pressed) {
                kvm_swap_keyboard_mouse();
            }
            return false;
        case KVM_SCA:
            if (record->event.pressed) {
                SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL), GSB_KVM_TAP_CODE_DELAY);
                tap_code(KC_LEFT);
                pseudo_leader_key_pressed = true;
            }
            return false;
        case KVM_SCB:
            if (record->event.pressed) {
                SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL), GSB_KVM_TAP_CODE_DELAY);
                tap_code(KC_DOWN);
                pseudo_leader_key_pressed = true;
            }
            return false;
        case KVM_SCC:
            if (record->event.pressed) {
                SEND_STRING_DELAY(SS_TAP(X_RCTL) SS_TAP(X_RCTL), GSB_KVM_TAP_CODE_DELAY);
                tap_code(KC_RGHT);
                pseudo_leader_key_pressed = true;
            }
            return false;
    }
    return true;
}
