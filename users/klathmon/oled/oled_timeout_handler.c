#include "./oled_timeout_handler.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// #define USE_16_BIT_TIMER // When defined it will use 16 bit timers instead of 32 bit timers, saving a bit of space and stack size

#ifdef USE_16_BIT_TIMER
#    define OLED_TIMER_SIZE uint16_t
#    define TIMER_READ_FN timer_read
#    define TIMER_ELAPSED_FN timer_elapsed
#else
#    define OLED_TIMER_SIZE uint32_t
#    define TIMER_READ_FN timer_read32
#    define TIMER_ELAPSED_FN timer_elapsed32
#endif

static OLED_TIMER_SIZE oled_timer  = 0;
static bool            oled_active = true; // Added flag to track the OLED state

bool oled_handle_timeout(void) {
    if (oled_timer == 0) {
        oled_timer = TIMER_READ_FN(); // Initialize timer at first use
    }

    // Update the timer if there's activity, or timeout the screen if there's no activity
    if (TIMER_ELAPSED_FN(last_input_activity_time()) < OLED_TIMEOUT) {
        oled_timer = TIMER_READ_FN();
        if (!oled_active) { // If the OLED was off, turn it back on due to activity
#ifdef CONSOLE_ENABLE
            // Log the time elapsed for debugging
            print("Enabling OLED due to activity\n");
#endif
            oled_on();
            oled_active = true;
        }
    } else if (TIMER_ELAPSED_FN(oled_timer) >= OLED_TIMEOUT) {
        if (oled_active) { // Only turn off the OLED if it is currently on
            oled_off();
#ifdef CONSOLE_ENABLE
            // Log the time elapsed for debugging
            uprintf("Disabling OLED after %d ms\n", TIMER_ELAPSED_FN(oled_timer));
#endif
            oled_active = false;
        }
    }

    return oled_active;
}
