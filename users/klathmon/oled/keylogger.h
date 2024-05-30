#pragma once
#include "action.h"

extern char               keylogs_str[21];
extern int                keylogs_str_idx;
extern const char PROGMEM code_to_name[60];

void set_keylog(uint16_t keycode, keyrecord_t *record);

const char *read_keylogs(void);
