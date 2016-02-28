TARGET := %ProjectName%

lc = $(shell echo $1 | tr '[:upper:]' '[:lower:]')

STM32_DEV  := STM32F10X_MD
SPL_NAME   := $(call lc,$(STM32_DEV))

SPL_PATH   := %StdPeriph_Lib%

CMSIS_LIB  := $(SPL_PATH)/Libraries/CMSIS
SPL_DRIVER := $(SPL_PATH)/Libraries/STM32F10x_StdPeriph_Driver

OPENOCD    := openocd
OOCD_CFG   := extra/stm32f10x_openocd.cfg

OUT_DIR    := out

TOOLCHAIN  := %ToolChain%
CC         := $(TOOLCHAIN)/../bin/arm-none-eabi-gcc
AS         := $(TOOLCHAIN)/../bin/arm-none-eabi-as
OBJCOPY    := $(TOOLCHAIN)/../bin/arm-none-eabi-objcopy
OBJDUMP    := $(TOOLCHAIN)/../bin/arm-none-eabi-objdump
SIZE       := $(TOOLCHAIN)/../bin/arm-none-eabi-size

CFLAGS     := -Wall -g -std=c99 -Os
CFLAGS     += -mlittle-endian -mthumb -mcpu=cortex-m3 -march=armv7-m
CFLAGS     += -ffunction-sections -fdata-sections
CFLAGS     += -Wl,--gc-sections -Wl,-Map=$(OUT_DIR)/$(TARGET).map

CFLAGS     += -I $(CMSIS_LIB)/CM3/DeviceSupport/ST/STM32F10x
CFLAGS     += -I $(CMSIS_LIB)/CM3/CoreSupport
CFLAGS     += -I $(SPL_DRIVER)/inc
CFLAGS     += -I SPL/

vpath %.c src
SRCS := $(notdir $(wildcard src/*.c))

SRCS      += $(CMSIS_LIB)/CM3/CoreSupport/core_cm3.c
SRCS      += $(CMSIS_LIB)/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
SRCS      += $(CMSIS_LIB)/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_ld.s

OBJS      := $(SRCS:.c=.o)

SPL_AR    := SPL/lib$(SPL_NAME).a

all: $(OUT_DIR) $(SPL_AR) $(TARGET)

$(SPL_AR):
	$(MAKE) -C SPL/ SPL_PATH=$(SPL_PATH) STM32_DEV=$(STM32_DEV)

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -DUSE_STDPERIPH_DRIVER -D$(STM32_DEV) $^ -o $(OUT_DIR)/$@.elf -L SPL/ -l$(SPL_NAME) -Lextra -Tstm32f103x8_flash.ld
	$(OBJCOPY) -O binary $(OUT_DIR)/$@.elf $(OUT_DIR)/$@.bin
	$(OBJCOPY) -O ihex $(OUT_DIR)/$@.elf $(OUT_DIR)/$@.hex
	$(OBJDUMP) -St $(OUT_DIR)/$@.elf > $(OUT_DIR)/$@.lst
	$(SIZE) $(OUT_DIR)/$@.elf

flash: all
	#$(OPENOCD) -f $(OOCD_CFG) -c "stm_flash `pwd`/$(OUT_DIR)/$(TARGET).bin" -c shutdown
	stm32flash -w "`pwd`/$(OUT_DIR)/$(TARGET).bin" /dev/ttyUSB0
	stm32flash -g 0x00000000 /dev/ttyUSB0

erase:
	#$(OPENOCD) -f $(OOCD_CFG) -c "stm_erase" -c shutdown
	stm32flash -o /dev/ttyUSB0

clean:
	$(RM) -r ./$(OUT_DIR)

distclean: clean
	$(MAKE) -C SPL/ clean
