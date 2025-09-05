USER_NAME := klathmon
BOOTLOADER = rp2040

OLED_ENABLE       = no # OLED display

include ../users/klathmon/rules.mk # This is only included here is to make the generate-compilation-database command work properly.
