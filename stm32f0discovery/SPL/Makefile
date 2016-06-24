lc = $(shell echo $1 | tr '[:upper:]' '[:lower:]')

STM32_DEV  := STM32F051
SPL_NAME   := $(call lc,$(STM32_DEV))

SPL_PATH   := %{StdPeriph_Lib}

CMSIS_LIB  := $(SPL_PATH)/Libraries/CMSIS
SPL_DRIVER := $(SPL_PATH)/Libraries/STM32F0xx_StdPeriph_Driver

TOOLCHAIN  := %{ToolChain}
CC         := $(TOOLCHAIN)/../bin/arm-none-eabi-gcc
AR         := $(TOOLCHAIN)/../bin/arm-none-eabi-ar

CFLAGS     := -g -O2 -Wall
CFLAGS     += -mlittle-endian -mthumb -mcpu=cortex-m0 -march=armv6s-m
CFLAGS     += -ffunction-sections -fdata-sections
CFLAGS     += -ffreestanding -nostdlib

CFLAGS     += -I $(CMSIS_LIB)/Include
CFLAGS     += -I $(CMSIS_LIB)/Device/ST/STM32F0xx/Include
CFLAGS     += -I $(SPL_DRIVER)/inc
CFLAGS     += -I .

SRCS       := $(notdir $(wildcard $(SPL_DRIVER)/src/*.c))

OBJS       := $(SRCS:.c=.o)

SPL_AR     := lib$(SPL_NAME).a

%.o: $(SPL_DRIVER)/src/%.c
	$(CC) $(CFLAGS) -DUSE_STDPERIPH_DRIVER -D$(STM32_DEV) -c -o $@ $^

all: $(OBJS)
	$(AR) -r $(SPL_AR) $(OBJS)
	$(RM) $(OBJS)

clean:
	$(RM) $(OBJS) $(SPL_AR)
