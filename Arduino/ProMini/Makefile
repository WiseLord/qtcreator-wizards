# Output file name
TARG     = %{ProjectName}

# MCU name and frequency
MCU      = atmega328p
F_CPU    = 16000000

# Source files
SRCS     = main.c

# Defines
DEFINES = -D_$(MCU)

# Build directory
BUILDDIR = build

# Compiler options
OPTIMIZE = -Os -mcall-prologues -fshort-enums -ffunction-sections -fdata-sections -ffreestanding -flto
WARNLEVEL = -Wall -Werror
CFLAGS = $(WARNLEVEL) -lm $(OPTIMIZE) -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS += -MMD -MP -MT $(BUILDDIR)/$(*F).o -MF $(BUILDDIR)/$(*D)/$(*F).d
LDFLAGS = $(WARNLEVEL) -mmcu=$(MCU) -Wl,--gc-sections -Wl,--relax

# AVR toolchain
CC       = avr-gcc
OBJCOPY  = avr-objcopy
OBJDUMP  = avr-objdump

# Avrdude parameters
AVRDUDE  = avrdude
AD_MCU   = -p $(MCU)
#AD_PROG = -c stk500v2
#AD_PORT = -P avrdoper

AD_CMDLINE = $(AD_MCU) $(AD_PROG) $(AD_PORT) -V -B 0.5

OBJS = $(addprefix $(BUILDDIR)/, $(SRCS:.c=.o))
ELF = $(BUILDDIR)/$(TARG).elf
HEX = flash/$(TARG).hex

all: $(HEX) size

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram $(ELF) $(HEX)

$(ELF): $(OBJS)
	@mkdir -p $(BUILDDIR) flash
	$(CC) $(LDFLAGS) -o $(ELF) $(OBJS)
	$(OBJDUMP) -h -S $(ELF) > $(BUILDDIR)/$(TARG).lss

size: $(ELF)
	@sh ./size.sh $(ELF)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFINES) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

.PHONY: flash
flash: $(ELF)
	$(AVRDUDE) $(AD_CMDLINE) -U flash:w:$(HEX):i

fuse:
	$(AVRDUDE) $(AD_CMDLINE) -U lfuse:w:0xFF:m -U hfuse:w:0xD8:m -U efuse:w:0xCB:m

# Dependencies
-include $(OBJS:.o=.d)
