#include "../klathmon.h"

WEAK bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            layer_move(_MAIN_MAC);
            break;
        case OS_LINUX:
        case OS_WINDOWS:
        case OS_UNSURE:
            layer_move(_MAIN_WIN);
            break;
    }
    return true;
}
