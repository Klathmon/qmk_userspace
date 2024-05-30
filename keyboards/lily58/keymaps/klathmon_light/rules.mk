USER_NAME := klathmon
BOOTLOADER = atmel-dfu

ENCODER_ENABLE    = yes # Enable rotary encoder
OLED_ENABLE       = yes # OLED display
RGBLIGHT_ENABLE   = no  # Enable WS2812 RGB underlight.

include ../users/klathmon/rules.mk # This is only included here is to make the generate-compile-database command work properly.
