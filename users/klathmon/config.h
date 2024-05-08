#pragma once

/// settings I want configured on most/all of my keyboards ///

#define QUICK_TAP_TERM 0          // we only use quick tap for escape keys and others that we don't want to repeat, so this makes it nicer
#define TAPPING_TERM 100          // this is the default, but I like to have it here to make it easier to tweak if needed
#define USB_POLLING_INTERVAL_MS 5 // reduces latency a tiny bit

#ifdef MOUSEKEY_ENABLE
#    define MK_3_SPEED             // Manages scrolling speed for my encoder mouse wheel scrolling feature
#    define MK_W_OFFSET_UNMOD 16   // Manages scrolling speed for my encoder mouse wheel scrolling feature
#    define MK_W_INTERVAL_UNMOD 40 // Manages scrolling speed for my encoder mouse wheel scrolling feature
#endif

#ifdef OS_DETECTION_ENABLE
#    define OS_DETECTION_DEBOUNCE 500 // debounce time for os detection to settle down before picking
#endif

#ifdef OLED_ENABLE
#    define OLED_BRIGHTNESS 64       // 0-255 keep this low to help prevent burn-in
#    define OLED_TIMEOUT 15000       // time after touching the keyboard that the OLED will turn off, keep this low to help prevent burn-in
#    define SPLIT_OLED_ENABLE        // on split boards, when the master oled turns off, the slave will as well
#    define SPLIT_LAYER_STATE_ENABLE // makes sure that the slave half knows about the layer states of the master half
#    define SPLIT_TRANSPORT_MIRROR   // mirror most/all states across the split halves
#endif

#ifdef DYNAMIC_MACRO_ENABLE
#    define DYNAMIC_MACRO_NO_NESTING // I don't use nesting, so this saves a tiny bit of memory
#    define DYNAMIC_MACRO_SIZE 128   // putting this at 256 causes eeprom corruption, but 128 works. I haven't bothered trying anything inbetween
#endif

/// space saving stuff ///

#define LAYER_STATE_8BIT      // I'm only using 8 layers so I can fit it all in 8 bits and save a tiny bit of memory
#undef LOCKING_SUPPORT_ENABLE // we don't have lock keys, so disabling this can save a tad
#undef LOCKING_RESYNC_ENABLE  // we don't have lock keys, so disabling this can save a tad
#define NO_ACTION_ONESHOT     // i'm not using oneshot keys

/// My own custom options below here ///

#define GSB_DISABLE_MAGIC_KEYCODES // I'm not currently using any magic keycodes, so this saves a bit of memory

// time between keypresses in KVM related macros (as it misses quicker keypresses)
#define GSB_KVM_TAP_CODE_DELAY 100

// invert the OLED for one frame every time a key is pressed, helps prevent burn-in
#define GSB_FLASH_INVERT_ON_KEYPRESS

// define this to enable showing the macos/windows icon in the top right of the OLED
// #define MAC_WIN_MODE_ICON
