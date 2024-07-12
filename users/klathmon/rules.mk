CONSOLE_ENABLE         = no  # Console for debug

# Stuff that I want enabled on all of my keyboards
DYNAMIC_MACRO_ENABLE   = yes # Enable Dynamic Macros
EXTRAKEY_ENABLE        = yes # Audio control and System control
KEY_OVERRIDE_ENABLE    = yes # Enable key override
MOUSEKEY_ENABLE        = yes # Mouse keys
NKRO_ENABLE            = yes # Enable N-Key Rollover
OS_DETECTION_ENABLE    = yes # Enable OS detection for keymap
COMBO_ENABLE           = no  # Enable chording "combos"

# save some space in the firmware where possible
SPACE_CADET_ENABLE     = no
GRAVE_ESC_ENABLE       = no
MAGIC_ENABLE           = no
AVR_USE_MINIMAL_PRINTF = yes
LTO_ENABLE             = yes # Enable LTO

# my own custom feature flags
GSB_SHOW_KEYLOGGER_DURING_MACRO = yes # Enables showing the typed text while recording a macro
GSB_KVM_ENABLE                  = yes # Enable KVM-management keybindings and features
OLED_WPM_GRAPH                  = no  # Enable WPM graph animation on the secondary OLED
OLED_STATIC_BUILDUP             = no  # Enable static buildup "animation" on the secondary OLED

SRC += ./klathmon.c \
       ./custom_keycodes.c \
       ./key_overrides.c \

ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
  SRC += ./features/os_detection.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
  SRC += ./oled/oled.c \
         ./oled/oled_print_funcs.c \
         ./oled/oled_timeout_handler.c \
         ./oled/customized_font_reader.c

  ifeq ($(strip $(DYNAMIC_MACRO_ENABLE)), yes)
    ifeq ($(strip $(GSB_SHOW_KEYLOGGER_DURING_MACRO)), yes)
      OPT_DEFS += -DGSB_SHOW_KEYLOGGER_DURING_MACRO
      SRC += ./oled/keylogger.c
    endif
  endif

  ifeq ($(strip $(OLED_WPM_GRAPH)), yes)
    WPM_ENABLE = yes # Enable WPM counter utils as they're needed for this feature
    OPT_DEFS += -DOLED_WPM_GRAPH
    SRC += ./oled/wpm_animation_graph.c
  endif
  ifeq ($(strip $(OLED_STATIC_BUILDUP)), yes)
    OPT_DEFS += -DOLED_STATIC_BUILDUP
    SRC += ./oled/wpm_animation_static.c
  endif
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

ifeq ($(strip $(BOOTLOADER)), atmel-dfu)
  OPT_DEFS += -DGSB_ATMEL_DFU_BOOTLOADER
else ifeq ($(strip $(BOOTLOADER)), caterina)
  OPT_DEFS += -DGSB_CATERINA_BOOTLOADER
endif

ifeq ($(strip $(GSB_KVM_ENABLE)), yes)
  OPT_DEFS += -DGSB_KVM_ENABLE
  SRC += ./features/kvm_manager.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
  VPATH += keyboards/gboards
endif
