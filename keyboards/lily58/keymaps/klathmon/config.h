#pragma once

#define SPLIT_USB_DETECT       // enables split USB detection
#define SPLIT_USB_TIMEOUT 1000 // time to wait before timing out trying to detect primary/secondary half
#define EE_HANDS               // enables storing the handedness in eeprom

// Encoders
#ifndef ENCODERS_PAD_A
#    define ENCODERS_PAD_A \
        { F5 }
#    define ENCODERS_PAD_B \
        { F4 }
#endif
