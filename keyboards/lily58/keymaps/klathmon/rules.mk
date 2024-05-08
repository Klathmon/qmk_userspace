USER_NAME := klathmon
BOOTLOADER = atmel-dfu

BOOTMAGIC_ENABLE  = no  # Enable Bootmagic Lite
BACKLIGHT_ENABLE  = no  # Enable keyboard backlight functionality
AUDIO_ENABLE      = no  # Audio output
RGBLIGHT_ENABLE   = no  # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no  # Enable one-hand typing
ENCODER_ENABLE    = yes # Enable rotary encoder
OLED_ENABLE       = yes # OLED display

SRC += ./lib/logo_reader.c
