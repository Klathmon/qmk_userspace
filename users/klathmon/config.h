#pragma once

/// My own custom options here ///

#define GSB_DISABLE_MAGIC_KEYCODES   /* I'm not currently using any magic keycodes, so this saves a bit of memory */
#define GSB_KVM_TAP_CODE_DELAY 100   /* time between keypresses in KVM related macros (as it misses quicker keypresses) */
#define GSB_FLASH_INVERT_ON_KEYPRESS /* invert the OLED for one frame every time a key is pressed, helps prevent burn-in */
#define GSB_MAC_WIN_MODE_ICON        /* define this to enable showing the macos/windows icon in the top right of the OLED */
#define GSB_USE_CUSTOM_FONT          /* use the custom font for the OLED */
// #define GSB_USE_FINE_VOLUME_CONTROL_ON_MACOS /* if defined, finer volume control is used for macos */

/// settings I want configured on most/all of my keyboards ///

#define RETRO_TAPPING_PER_KEY     /* only used for the M_NUMRD key */
#define QUICK_TAP_TERM_PER_KEY    /* only allow quick-tap for the M_NUMRD key */
#define TAPPING_TERM 100          /* tweak the difference between when a *tap key is pressed vs a hold version of the key. defaults to 100ms */
#define USB_POLLING_INTERVAL_MS 5 /* reduces latency a tiny bit, but we could run out of CPU time and drop keys if we push this too low */

/// per feature settings which are pretty universal ///

#ifdef MOUSEKEY_ENABLE
#    define MK_3_SPEED             /* Manages scrolling speed for my encoder mouse wheel scrolling feature */
#    define MK_W_OFFSET_UNMOD 16   /* Manages scrolling speed for my encoder mouse wheel scrolling feature */
#    define MK_W_INTERVAL_UNMOD 40 /* Manages scrolling speed for my encoder mouse wheel scrolling feature */
#endif

#ifdef KEY_OVERRIDE_ENABLE
#    define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18
#    define MODS_TO_NEUTRALIZE \
        { MOD_BIT(KC_LEFT_GUI) }
#endif

#ifdef OS_DETECTION_ENABLE
#    define OS_DETECTION_DEBOUNCE 500   /* debounce time for os detection to settle down before picking */
#    define OS_DETECTION_KEYBOARD_RESET /* reset the keyboard when the os changes (seemingly avoids the master OLED from crashing) */
#endif

#ifdef OLED_ENABLE
#    define OLED_BRIGHTNESS 64       /* 0-255 keep this low to help prevent burn-in */
#    define OLED_TIMEOUT 15000       /* time after touching the keyboard that the OLED will turn off, keep this low to help prevent burn-in */
#    define SPLIT_OLED_ENABLE        /* on split boards, when the master oled turns off, the slave will as well */
#    define SPLIT_LAYER_STATE_ENABLE /* makes sure that the slave half knows about the layer states of the master half */
#    define SPLIT_TRANSPORT_MIRROR   /* mirror most/all states across the split halves */
#    ifdef GSB_USE_CUSTOM_FONT
#        undef OLED_FONT_H                             /* remove the default font */
#        define OLED_FONT_H "./oled/customized_font.c" /* use a customized font */
#    endif
#    ifdef WPM_ENABLE
#        define SPLIT_WPM_ENABLE
#    endif
#endif

#ifdef DYNAMIC_MACRO_ENABLE
#    define DYNAMIC_MACRO_NO_NESTING /* I don't use nesting, so this saves a tiny bit of memory */
#    define DYNAMIC_MACRO_SIZE 128   /* putting this at 256 causes eeprom corruption, but 128 works. I haven't bothered trying anything inbetween */
#endif

/// space saving stuff ///

#define LAYER_STATE_8BIT      /* I'm only using 8 layers so I can fit it all in 8 bits and save a tiny bit of memory */
#undef LOCKING_SUPPORT_ENABLE /* we don't have lock keys, so disabling this can save a tad */
#undef LOCKING_RESYNC_ENABLE  /* we don't have lock keys, so disabling this can save a tad */
#define NO_ACTION_ONESHOT     /* i'm not using oneshot keys */
