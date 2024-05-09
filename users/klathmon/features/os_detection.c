#include "../klathmon.h"
#include "os_detection.h"

WEAK bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            layer_move(_MAIN_MAC);
#ifdef GSB_GPIO_LEDS_ENABLE
            gpio_write_pin_high(RED_LED);
#endif
            break;
        case OS_LINUX:
        case OS_WINDOWS:
        case OS_UNSURE:
            layer_move(_MAIN_WIN);
#ifdef GSB_GPIO_LEDS_ENABLE
            gpio_write_pin_low(RED_LED);
#endif
            break;
    }
    return true;
}
