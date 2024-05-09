CONSOLE_ENABLE         = no  # Console for debug

AUTOCORRECT_ENABLE     = yes

# Stuff that I want enabled on all of my keyboards
DYNAMIC_MACRO_ENABLE   = yes # Enable Dynamic Macros
EXTRAKEY_ENABLE        = yes # Audio control and System control
KEY_OVERRIDE_ENABLE    = yes # Enable key override
MOUSEKEY_ENABLE        = yes # Mouse keys
NKRO_ENABLE            = yes # Enable N-Key Rollover
OS_DETECTION_ENABLE    = yes # Enable OS detection for keymap

# save some space in the firmware where possible
SPACE_CADET_ENABLE     = no
GRAVE_ESC_ENABLE       = no
AVR_USE_MINIMAL_PRINTF = yes
LTO_ENABLE             = yes # Enable LTO

SRC += ./klathmon.c \
       ./custom_keycodes.c \
       ./key_overrides.c \

ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
  SRC += ./features/os_detection.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
  SRC += ./oled/oled.c \
         ./oled/oled_print_funcs.c \
         ./oled/keylogger.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
  SRC += ./features/encoder.c
endif

ifeq ($(strip $(AUDIO_ENABLE)), yes)
  SRC += ./features/audio.c
endif

ifeq ($(strip $(GSB_GPIO_LEDS_ENABLE)), yes)
  OPT_DEFS += -DGSB_GPIO_LEDS_ENABLE
  SRC += ./features/status_leds.c
endif
