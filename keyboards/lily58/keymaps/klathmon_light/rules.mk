USER_NAME := klathmon
BOOTLOADER = atmel-dfu

ENCODER_ENABLE    = yes # Enable rotary encoder
OLED_ENABLE       = yes # OLED display
DYNAMIC_MACRO_ENABLE = yes # Enable Dynamic Macros
RGBLIGHT_ENABLE   = no # Enable WS2812 RGB underlight.

SRC += ./lib/logo_reader.c
