#pragma once

#include "../klathmon.h" // IWYU pragma: keep

void kvm_switch_machine(uint16_t kvm_input_keycode);

bool process_record_kvm_manager(uint16_t keycode, keyrecord_t *record);
