TARG = %ProjectName%

MCU = %MCU%
F_CPU = %F_CPU%

# Source files
SRCS = $(wildcard *.c)

# Build directory
BUILDDIR = build

# Compiler options
OPTIMIZE = -Os -mcall-prologues -fshort-enums -ffunction-sections -fdata-sections
DEBUG = -g -Wall -Werror
CFLAGS = $(DEBUG) -lm $(OPTIMIZE) -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS += -MMD -MP -MT $(BUILDDIR)/$(*F).o -MF $(BUILDDIR)/$(@F).d
LDFLAGS = $(DEBUG) -mmcu=$(MCU) -Wl,-gc-sections

# AVR toolchain and flasher
CC       = avr-gcc
OBJCOPY  = avr-objcopy

AVRDUDE  = avrdude
AD_MCU = -p $(MCU)
#AD_PROG = -c stk500v2
#AD_PORT = -P avrdoper

AD_CMDLINE = $(AD_MCU) $(AD_PROG) $(AD_PORT) -V

OBJS = $(addprefix $(BUILDDIR)/, $(SRCS:.c=.o))
ELF = $(BUILDDIR)/$(TARG).elf

all: $(ELF) size

$(ELF): $(OBJS)
	@mkdir -p $(BUILDDIR) flash
	$(CC) $(LDFLAGS) -o $(ELF) $(OBJS) -lm
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram $(ELF) flash/$(TARG).hex

size:
	@sh ./size.sh $(ELF)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

flash: $(TARG)
	$(AVRDUDE) $(AD_CMDLINE) -U flash:w:flash/$(TARG).hex:i

fuse:
	$(AVRDUDE) $(AD_CMDLINE) %FUSEBIT_STRING%

# Other dependencies
-include $(wildcard $(BUILDDIR)/*.d)
