USER_NAME := klathmon
BOOTLOADER = atmel-dfu

ENCODER_ENABLE    = yes # Enable rotary encoder
OLED_ENABLE       = yes # OLED display

include ../users/klathmon/rules.mk # This is only included here is to make the generate-compilation-database command work properly.
