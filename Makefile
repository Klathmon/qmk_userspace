.SILENT:

MAKEFLAGS += --no-print-directory

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

QMK ?= $(if $(wildcard $(QMK_USERSPACE)/.venv/bin/qmk),$(QMK_USERSPACE)/.venv/bin/qmk,qmk)
ARM_GCC8_DIR := /usr/local/opt/arm-none-eabi-gcc@8/bin
ifneq ($(wildcard $(ARM_GCC8_DIR)/arm-none-eabi-gcc),)
    export PATH := $(ARM_GCC8_DIR):$(PATH)
endif

QMK_FIRMWARE_ROOT = $(shell $(QMK) config -ro user.qmk_home | cut -d= -f2 | sed -e 's@^None$$@@g')
ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location. `$(QMK) config -ro user.qmk_home` is not set)
endif

%:
	+$(MAKE) -C $(QMK_FIRMWARE_ROOT) $(MAKECMDGOALS) QMK_USERSPACE=$(QMK_USERSPACE)
