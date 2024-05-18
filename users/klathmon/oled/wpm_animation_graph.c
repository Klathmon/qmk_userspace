#include "wpm.h"
#include "./wpm_animation.h"

static int timer = 0;

void print_wpm_graph(void) {
    // get current WPM value
    const int currwpm = get_current_wpm();

    // check if it's been long enough before refreshing graph
    if (timer_elapsed(timer) > GRAPH_REFRESH_INTERVAL) {
        // main calculation to plot graph line
        int x = OLED_DISPLAY_HEIGHT - ((currwpm / GRAPH_TOP_WPM) * OLED_DISPLAY_HEIGHT);

        // first draw actual value line
        for (int i = 0; i <= GRAPH_LINE_THICKNESS - 1; i++) {
            oled_write_pixel(1, x + i, true);
        }

        // then fill in area below the value line
#ifdef VERT_LINE
        static int vert_count = 0;
        if (vert_count == VERT_INTERVAL) {
            vert_count = 0;
            while (x <= OLED_DISPLAY_HEIGHT) {
                oled_write_pixel(1, x, true);
                x++;
            }
        } else {
            for (int i = OLED_DISPLAY_HEIGHT; i > x; i--) {
                if (i % GRAPH_AREA_FILL_INTERVAL == 0) {
                    oled_write_pixel(1, i, true);
                }
            }
            vert_count++;
        }
#else
        for (int i = OLED_DISPLAY_HEIGHT; i > x; i--) {
            if (i % GRAPH_AREA_FILL_INTERVAL == 0) {
                oled_write_pixel(1, i, true);
            }
        }
#endif

        // then move the entire graph one pixel to the right
        oled_pan(false);

        // refresh the timer for the next iteration
        timer = timer_read();
    }

#ifdef SHOW_WPM_TEXT
    char wpm_text[5];
    // format current WPM value into a printable string
    sprintf(wpm_text, "%i", currwpm);

    // formatting for triple digit WPM vs double digits, then print WPM readout
    if (currwpm >= 100) {
        oled_set_cursor(14, 3);
        oled_write("WPM: ", false);
        oled_set_cursor(18, 3);
        oled_write(wpm_text, false);
    } else if (currwpm >= 10) {
        oled_set_cursor(15, 3);
        oled_write("WPM: ", false);
        oled_set_cursor(19, 3);
        oled_write(wpm_text, false);
    } else if (currwpm > 0) {
        oled_set_cursor(16, 3);
        oled_write("WPM: ", false);
        oled_set_cursor(20, 3);
        oled_write(wpm_text, false);
    }
#endif
}
