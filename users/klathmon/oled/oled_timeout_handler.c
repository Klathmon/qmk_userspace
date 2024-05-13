#include "./oled_timeout_handler.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

static uint32_t oled_timer  = 0;
static bool     oled_active = true; // Added flag to track the OLED state

bool oled_handle_timeout(void) {
    if (oled_timer == 0) {
        oled_timer = timer_read32(); // Initialize timer at first use
    }

    // Update the timer if there's activity, or timeout the screen if there's no activity
    if (timer_elapsed32(last_input_activity_time()) < OLED_TIMEOUT) {
        oled_timer = timer_read32();
        if (!oled_active) { // If the OLED was off, turn it back on due to activity
#ifdef CONSOLE_ENABLE
            // Log the time elapsed for debugging
            print("Enabling OLED due to activity\n");
#endif
            oled_on();
            oled_active = true;
        }
    } else if (timer_elapsed32(oled_timer) >= OLED_TIMEOUT) {
        if (oled_active) { // Only turn off the OLED if it is currently on
            oled_off();
#ifdef CONSOLE_ENABLE
            // Log the time elapsed for debugging
            uprintf("Disabling OLED after %d ms\n", timer_elapsed32(oled_timer));
#endif
            oled_active = false;
        }
    }

    return oled_active;
}
