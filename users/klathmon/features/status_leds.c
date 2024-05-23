#include "../klathmon.h"

#ifndef GREEN_LED
#    define GREEN_LED 0
#endif
#ifndef RED_LED
#    define RED_LED 0
#endif

WEAK void housekeeping_task_user(void) {
    if (is_mac_mode()) {
        gpio_write_pin_high(RED_LED);
    } else {
        gpio_write_pin_low(RED_LED);
    }
}

WEAK void suspend_power_down_user(void) {
    gpio_write_pin_low(GREEN_LED);
}

WEAK void suspend_wakeup_init_user(void) {
    gpio_write_pin_high(GREEN_LED);
}

WEAK bool shutdown_user(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        // Green off red on for bootloader
        gpio_write_pin_low(GREEN_LED);
        gpio_write_pin_high(RED_LED);
    }
    return true;
}
