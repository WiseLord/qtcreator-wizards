TARGET := %ProjectName%

STM32F10X_DEV := %STM32F10xDev%

SPL_PATH := %StdPeriph_Lib%

CMSIS_LIB := $(SPL_PATH)/Libraries/CMSIS
STDPERIPH_DRIVER := $(SPL_PATH)/Libraries/STM32F10x_StdPeriph_Driver

LDSCRIPT_INC := extra/ldscripts
OPENOCD_BOARD_DIR := /usr/share/openocd/scripts/board
OPENOCD_PROC_FILE := extra/stm32f0-openocd.cfg
OUT_DIR := out

vpath %.c src
SRCS := $(notdir $(wildcard src/*.c))

OPENOCD := openocd
TOOLCHAIN_PREFIX := %ToolChain%/
CC := $(TOOLCHAIN_PREFIX)arm-none-eabi-gcc
OBJCOPY := $(TOOLCHAIN_PREFIX)arm-none-eabi-objcopy
OBJDUMP := $(TOOLCHAIN_PREFIX)arm-none-eabi-objdump
SIZE := $(TOOLCHAIN_PREFIX)arm-none-eabi-size

CFLAGS := -Wall -g -std=c99 -Os
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -march=armv7-m
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -Wl,-Map=$(OUT_DIR)/$(TARGET).map

CFLAGS += -I $(CMSIS_LIB)/CM3/DeviceSupport/ST/STM32F10x
CFLAGS += -I $(CMSIS_LIB)/CM3/CoreSupport
CFLAGS += -I $(STDPERIPH_DRIVER)/inc
CFLAGS += -I SPL/

# Filename (lowercase) of library from objects archive
lc = $(shell echo $1 | tr '[:upper:]' '[:lower:]')
SPL_NAME = $(call lc,$(STM32F10X_DEV))
STDPERIPH_AR = SPL/lib$(SPL_NAME).a

# Startup files
SRCS += $(CMSIS_LIB)/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_$(SPL_NAME).s
SRCS += $(CMSIS_LIB)/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c

OBJS := $(SRCS:.c=.o)

all: $(OUT_DIR) $(STDPERIPH_AR) $(TARGET)

$(STDPERIPH_AR):
	$(MAKE) -C SPL/ SPL_PATH=$(SPL_PATH) STM32F10X_DEV=$(STM32F10X_DEV)

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -DUSE_STDPERIPH_DRIVER -D$(STM32F10X_DEV) $^ -o $(OUT_DIR)/$@.elf -L SPL/ -l$(SPL_NAME) -L$(LDSCRIPT_INC) -T$(STM32F10X_DEV)_FLASH.ld
	$(OBJCOPY) -O binary $(OUT_DIR)/$@.elf $(OUT_DIR)/$@.bin
	$(OBJCOPY) -O ihex $(OUT_DIR)/$@.elf $(OUT_DIR)/$@.hex
	$(OBJDUMP) -St $(OUT_DIR)/$@.elf > $(OUT_DIR)/$@.lst
	$(SIZE) $(OUT_DIR)/$@.elf

flash: all
	$(OPENOCD) -f $(OPENOCD_BOARD_DIR)/stm32f0discovery.cfg -f $(OPENOCD_PROC_FILE) -c "stm_flash `pwd`/$(OUT_DIR)/$(TARGET).bin" -c shutdown

erase:
	$(OPENOCD) -f $(OPENOCD_BOARD_DIR)/stm32f0discovery.cfg -f $(OPENOCD_PROC_FILE) -c "stm_erase" -c shutdown

clean:
	$(RM) -r ./$(OUT_DIR)

distclean: clean
	$(MAKE) -C SPL/ clean
