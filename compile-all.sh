#!/usr/bin/env bash

set -eEuo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
arm_gcc8_dir="/usr/local/opt/arm-none-eabi-gcc@8/bin"
if [ -x "$arm_gcc8_dir/arm-none-eabi-gcc" ]; then
    export PATH="$arm_gcc8_dir:$PATH"
fi

qmk="${QMK:-}"
if [ -z "$qmk" ]; then
    if [ -x "$script_dir/.venv/bin/qmk" ]; then
        qmk="$script_dir/.venv/bin/qmk"
    else
        qmk="qmk"
    fi
fi

# Use QMK MSYS's shell for make to avoid Windows command line length limits
# that break ARM builds (CONVERT_TO=elite_pi) with Git Bash's /usr/bin/sh
"$qmk" clean -a
if [ -x "/c/QMK_MSYS/usr/bin/sh.exe" ]; then
    "$qmk" userspace-compile -j 0 -e "SHELL=/c/QMK_MSYS/usr/bin/sh.exe"
else
    "$qmk" userspace-compile -j 0
fi
