#!/usr/bin/env bash

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

if [ -x "$SCRIPT_DIR/.venv/bin/qmk" ]; then
    PATH="$SCRIPT_DIR/.venv/bin:$PATH"
fi

for dir in \
    "/opt/homebrew/opt/arm-none-eabi-gcc@8/bin" \
    "/opt/homebrew/opt/arm-none-eabi-binutils/bin" \
    "/opt/homebrew/opt/avr-gcc@8/bin" \
    "/opt/homebrew/opt/avr-binutils/bin" \
    "/opt/homebrew/bin"; do
    if [ -d "$dir" ]; then
        PATH="$dir:$PATH"
    fi
done
export PATH

# Use QMK MSYS's shell for make to avoid Windows command line length limits
# that break ARM builds (CONVERT_TO=elite_pi) with Git Bash's /usr/bin/sh
SHELL_OVERRIDE=""
if [ -x "/c/QMK_MSYS/usr/bin/sh.exe" ]; then
    SHELL_OVERRIDE="-e SHELL=/c/QMK_MSYS/usr/bin/sh.exe"
fi

qmk clean -a
qmk userspace-compile -j 0 $SHELL_OVERRIDE
