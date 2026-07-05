#!/usr/bin/env sh

# Source this file to make the local QMK CLI and Homebrew QMK toolchain
# available in the current shell:
#
#   . ./setup-qmk-env.sh

if [ -n "${BASH_SOURCE:-}" ]; then
    QMK_USERSPACE_SCRIPT="${BASH_SOURCE[0]}"
elif [ -n "${ZSH_VERSION:-}" ]; then
    QMK_USERSPACE_SCRIPT="${(%):-%N}"
else
    QMK_USERSPACE_SCRIPT="$0"
fi

QMK_USERSPACE_DIR="$(CDPATH= cd -- "$(dirname -- "$QMK_USERSPACE_SCRIPT")" && pwd)"

qmk_userspace_prepend_path() {
    if [ -d "$1" ]; then
        case ":$PATH:" in
            *":$1:"*) ;;
            *) PATH="$1:$PATH" ;;
        esac
    fi
}

qmk_userspace_prepend_path "$QMK_USERSPACE_DIR/.venv/bin"
qmk_userspace_prepend_path "/opt/homebrew/opt/arm-none-eabi-gcc@8/bin"
qmk_userspace_prepend_path "/opt/homebrew/opt/arm-none-eabi-binutils/bin"
qmk_userspace_prepend_path "/opt/homebrew/opt/avr-gcc@8/bin"
qmk_userspace_prepend_path "/opt/homebrew/opt/avr-binutils/bin"
qmk_userspace_prepend_path "/opt/homebrew/bin"

export PATH

unset QMK_USERSPACE_SCRIPT
unset QMK_USERSPACE_DIR
unset -f qmk_userspace_prepend_path 2>/dev/null || true
