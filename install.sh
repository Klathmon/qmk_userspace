#!/usr/bin/env bash

set -eEuo pipefail

userspace_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
qmk_home="${QMK_HOME:-"$userspace_dir/qmk_firmware"}"
qmk_repo="${QMK_REPO:-Klathmon/qmk_firmware}"
qmk_ref="${QMK_REF:-klathmon_external_userspace}"
venv_dir="$userspace_dir/.venv"
arm_gcc8_dir="/usr/local/opt/arm-none-eabi-gcc@8/bin"
case "$qmk_repo" in
    http* | /* | ./* | ../*) qmk_remote_url="$qmk_repo" ;;
    *) qmk_remote_url="https://github.com/$qmk_repo" ;;
esac

if [ -x "$arm_gcc8_dir/arm-none-eabi-gcc" ]; then
    export PATH="$arm_gcc8_dir:$PATH"
fi

if [ ! -x "$venv_dir/bin/qmk" ]; then
    python3 -m venv "$venv_dir"
    "$venv_dir/bin/python" -m pip install --upgrade pip qmk
fi

qmk="$venv_dir/bin/qmk"

if [ ! -d "$qmk_home/.git" ]; then
    "$qmk" setup -H "$qmk_home" "$qmk_repo" -b "$qmk_ref" -y
else
    "$qmk" config user.qmk_home="$qmk_home"
fi

if [ "$qmk_home" = "$userspace_dir/qmk_firmware" ]; then
    if git -C "$qmk_home" remote get-url userspace-firmware >/dev/null 2>&1; then
        git -C "$qmk_home" remote set-url userspace-firmware "$qmk_remote_url"
    else
        git -C "$qmk_home" remote add userspace-firmware "$qmk_remote_url"
    fi

    git -C "$qmk_home" fetch userspace-firmware "$qmk_ref"
    git -C "$qmk_home" checkout -B "$qmk_ref" "userspace-firmware/$qmk_ref"
fi

"$qmk" config user.overlay_dir="$userspace_dir"
"$qmk" git-submodule
