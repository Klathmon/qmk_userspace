#pragma once

#include "../klathmon.h" // IWYU pragma: keep

void kvm_switch_machine(uint16_t kvm_input_keycode);

uint16_t active_kvm_machine;

bool process_record_kvm_manager(uint16_t keycode, keyrecord_t *record);
