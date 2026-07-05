#!/usr/bin/env bash

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

. "$SCRIPT_DIR/setup-qmk-env.sh"

# Use QMK MSYS's shell for make to avoid Windows command line length limits
# that break ARM builds (CONVERT_TO=elite_pi) with Git Bash's /usr/bin/sh
SHELL_OVERRIDE=""
if [ -x "/c/QMK_MSYS/usr/bin/sh.exe" ]; then
    SHELL_OVERRIDE="-e SHELL=/c/QMK_MSYS/usr/bin/sh.exe"
fi

qmk clean -a
qmk userspace-compile -j 0 $SHELL_OVERRIDE
