STM32F0_DEV := %STM32F0Dev%

SPL_PATH := %StdPeriph_Lib%

CMSIS_LIB := $(SPL_PATH)/Libraries/CMSIS
STDPERIPH_DRIVER := $(SPL_PATH)/Libraries/STM32F0xx_StdPeriph_Driver
STM32F0XX_TEMPLATE := stm32f0xx_conf.h

TOOLCHAIN_PREFIX := %ToolChain%/bin/
CC := $(TOOLCHAIN_PREFIX)arm-none-eabi-gcc
AR := $(TOOLCHAIN_PREFIX)arm-none-eabi-ar

CFLAGS := -g -O2 -Wall
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m0 -march=armv6s-m
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -ffreestanding -nostdlib

CFLAGS += -I $(CMSIS_LIB)/Device/ST/STM32F0xx/Include
CFLAGS += -I $(CMSIS_LIB)/Include
CFLAGS += -I $(STDPERIPH_DRIVER)/inc
CFLAGS += -include $(STM32F0XX_TEMPLATE)

SRCS := $(notdir $(wildcard $(STDPERIPH_DRIVER)/src/*.c))
OBJS = $(SRCS:.c=.o)

# Filename (lowercase) of objects archive
lc = $(shell echo $1 | tr '[:upper:]' '[:lower:]')
SPL_NAME = $(call lc,$(STM32F0_DEV))
STDPERIPH_AR = lib$(SPL_NAME).a

%.o: $(STDPERIPH_DRIVER)/src/%.c
	$(CC) $(CFLAGS) -D$(STM32F0_DEV) -c -o $@ $^

all: $(OBJS)
	$(AR) -r $(STDPERIPH_AR) $(OBJS)
	$(RM) $(OBJS)

clean:
	$(RM) $(STDPERIPH_AR)
