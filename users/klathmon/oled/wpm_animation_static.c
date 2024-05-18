#include "./wpm_animation.h"

static int keys_pressed_last_frame_counter = 0;

void wpm_graph_key_pressed(void) {
    keys_pressed_last_frame_counter++;
}

void print_wpm_graph(void) {
    for (int i = keys_pressed_last_frame_counter * 10; i > 0; i--) {
        oled_write_pixel(random() % OLED_DISPLAY_WIDTH, random() % OLED_DISPLAY_HEIGHT, i % 2);
    }
    keys_pressed_last_frame_counter = 0;
}
