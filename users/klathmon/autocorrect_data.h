// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

#pragma once
// this is my disgusting hack to get clangd to cooperate and not throw a fit about the macros that QMK handles in python
#ifndef QMK_KEYBOARD_H
// for vscode
#    include "./klathmon.h" // IWYU pragma: keep
#endif

// Autocorrection dictionary (10 entries):
//   tzhe:   -> the
//   tzhat:  -> that
//   tzhis:  -> this
//   tzhey:  -> they
//   tzheir: -> their
//   tzhere: -> there
//   tzhen:  -> then
//   tzhem:  -> them
//   tzhose: -> those
//   thsi:   -> this

#define AUTOCORRECT_MIN_LENGTH 5 // "tzhe:"
#define AUTOCORRECT_MAX_LENGTH 7 // "tzheir:"
#define DICTIONARY_SIZE 136

// clang-format off
static const uint8_t autocorrect_data[DICTIONARY_SIZE] PROGMEM = {
    0x2C, 0x00, 0x48, 0x1B, 0x00, 0x0C, 0x42, 0x00, 0x10, 0x4A, 0x00, 0x11, 0x54, 0x00, 0x15, 0x5E,
    0x00, 0x16, 0x6A, 0x00, 0x17, 0x74, 0x00, 0x1C, 0x7E, 0x00, 0x00, 0x4B, 0x25, 0x00, 0x15, 0x2C,
    0x00, 0x16, 0x37, 0x00, 0x00, 0x1D, 0x17, 0x00, 0x83, 0x68, 0x65, 0x00, 0x08, 0x0B, 0x1D, 0x17,
    0x00, 0x85, 0x68, 0x65, 0x72, 0x65, 0x00, 0x12, 0x0B, 0x1D, 0x17, 0x00, 0x85, 0x68, 0x6F, 0x73,
    0x65, 0x00, 0x16, 0x0B, 0x17, 0x00, 0x82, 0x69, 0x73, 0x00, 0x08, 0x0B, 0x1D, 0x17, 0x00, 0x84,
    0x68, 0x65, 0x6D, 0x00, 0x08, 0x0B, 0x1D, 0x17, 0x00, 0x84, 0x68, 0x65, 0x6E, 0x00, 0x0C, 0x08,
    0x0B, 0x1D, 0x17, 0x00, 0x85, 0x68, 0x65, 0x69, 0x72, 0x00, 0x0C, 0x0B, 0x1D, 0x17, 0x00, 0x84,
    0x68, 0x69, 0x73, 0x00, 0x04, 0x0B, 0x1D, 0x17, 0x00, 0x84, 0x68, 0x61, 0x74, 0x00, 0x08, 0x0B,
    0x1D, 0x17, 0x00, 0x84, 0x68, 0x65, 0x79, 0x00
};
// clang-format on
