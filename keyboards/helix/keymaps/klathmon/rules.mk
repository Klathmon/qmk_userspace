USER_NAME := klathmon

CONVERT_TO = elite_pi

OLED_ENABLE       = no  # no screen
RGBLIGHT_ENABLE   = no  # no RGB underglow
RGB_MATRIX_ENABLE = no  # no RGB matrix
ENCODER_ENABLE    = no  # no rotary encoder

include $(QMK_USERSPACE)/users/klathmon/rules.mk # This is only included here is to make the generate-compilation-database command work properly.
