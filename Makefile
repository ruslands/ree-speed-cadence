PROJECT_NAME := cycling_sensor
TARGETS := main
OUTPUT_DIRECTORY := build

SDK_ROOT := ../nRF5_SDK
TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc

C_SOURCE_FILES += \
  $(wildcard src/**/*.c)

CFLAGS += -DBOARD_PCA10040 -DCONFIG_GPIO_AS_PINRESET -DNRF52
include $(TEMPLATE_PATH)/Makefile.common