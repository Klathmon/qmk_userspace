#pragma once

#include "../klathmon.h" // IWYU pragma: keep

#ifdef OLED_WPM_GRAPH
// #    define SHOW_WPM_TEXT              /* if defined, the WPM text will be printed on the screen, disabling this saves a lot of space */
#    define GRAPH_TOP_WPM 110.0f       /* WPM value at the top of the graph window */
#    define GRAPH_REFRESH_INTERVAL 100 /* in milliseconds */
#    define GRAPH_AREA_FILL_INTERVAL 3 /* determines how dense the horizontal lines under the graph line are; lower = more dense */
#    define VERT_INTERVAL 3            /* determines frequency of vertical lines under the graph line */
// #    define VERT_LINE                  /* if defined, it will draw vertical lines, disabling this saves a small amount of firmware space */
#    define GRAPH_LINE_THICKNESS 3 /* determines thickness of graph line in pixels */
#endif

#ifdef OLED_STATIC_BUILDUP
void wpm_graph_key_pressed(void);
#endif
void print_wpm_graph(void);
