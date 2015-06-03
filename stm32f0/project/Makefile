TARGET := %ProjectName%

STM32F0_DEV := %STM32F0Dev%

SPL_PATH := %StdPeriph_Lib%

CMSIS_LIB := $(SPL_PATH)/Libraries/CMSIS
STDPERIPH_DRIVER := $(SPL_PATH)/Libraries/STM32F0xx_StdPeriph_Driver

LDSCRIPT_INC := extra/ldscripts
OPENOCD_BOARD_DIR := /usr/share/openocd/scripts/board
OPENOCD_PROC_FILE := extra/stm32f0-openocd.cfg
OUT_DIR := out

vpath %.c src
SRCS := $(notdir $(wildcard src/*.c))

OPENOCD := openocd
TOOLCHAIN_PREFIX := %ToolChain%/bin/
CC := $(TOOLCHAIN_PREFIX)arm-none-eabi-gcc
OBJCOPY := $(TOOLCHAIN_PREFIX)arm-none-eabi-objcopy
OBJDUMP := $(TOOLCHAIN_PREFIX)arm-none-eabi-objdump
SIZE := $(TOOLCHAIN_PREFIX)arm-none-eabi-size

CFLAGS := -Wall -g -std=c99 -Os
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m0 -march=armv6s-m
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -Wl,-Map=$(OUT_DIR)/$(TARGET).map

CFLAGS += -I $(CMSIS_LIB)/Device/ST/STM32F0xx/Include
CFLAGS += -I $(CMSIS_LIB)/Include
CFLAGS += -I $(STDPERIPH_DRIVER)/inc
CFLAGS += -I SPL/

# Filename (lowercase) of library from objects archive
lc = $(shell echo $1 | tr '[:upper:]' '[:lower:]')
SPL_NAME = $(call lc,$(STM32F0_DEV))
STDPERIPH_AR = SPL/lib$(SPL_NAME).a

# Startup files
SRCS += $(SPL_PATH)/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/TrueSTUDIO/startup_$(SPL_NAME).s
SRCS += $(SPL_PATH)/Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.c

OBJS := $(SRCS:.c=.o)

all: $(OUT_DIR) $(STDPERIPH_AR) $(TARGET)

$(STDPERIPH_AR):
	$(MAKE) -C SPL/ SPL_PATH=$(SPL_PATH) STM32F0_DEV=$(STM32F0_DEV)

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -DUSE_STDPERIPH_DRIVER -D$(STM32F0_DEV) $^ -o $(OUT_DIR)/$@.elf -L SPL/ -l$(SPL_NAME) -L$(LDSCRIPT_INC) -Tstm32f0.ld
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
