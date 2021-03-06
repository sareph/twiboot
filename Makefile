CC	:= avr-gcc
LD	:= avr-ld
OBJCOPY	:= avr-objcopy
OBJDUMP	:= avr-objdump
SIZE	:= avr-size

TARGET = twiboot
SOURCE = $(wildcard *.c)

# select MCU
MCU = atmega328p

AVRDUDE_PROG := -c usbasp
#AVRDUDE_PROG := -c dragon_isp -P usb

# ---------------------------------------------------------------------------

ifeq ($(MCU), atmega8)
# (8Mhz internal RC-Osz., 2.7V BOD)
AVRDUDE_MCU=m8
AVRDUDE_FUSES=lfuse:w:0x84:m hfuse:w:0xda:m

BOOTLOADER_START=0x1C00
endif

ifeq ($(MCU), atmega88)
# (8Mhz internal RC-Osz., 2.7V BOD)
AVRDUDE_MCU=m88
AVRDUDE_FUSES=lfuse:w:0xc2:m hfuse:w:0xdd:m efuse:w:0xfa:m

BOOTLOADER_START=0x1C00
endif

ifeq ($(MCU), atmega168)
# (8Mhz internal RC-Osz., 2.7V BOD)
AVRDUDE_MCU=m168 -F
AVRDUDE_FUSES=lfuse:w:0xc2:m hfuse:w:0xdd:m efuse:w:0xfa:m

BOOTLOADER_START=0x3C00
endif

ifeq ($(MCU), atmega328p)
# (8Mhz internal RC-Osz., 2.7V BOD, EEPROMSAVE)
AVRDUDE_MCU=m328p -F
AVRDUDE_FUSES=lfuse:w:0xe2:m hfuse:w:0xd0:m efuse:w:0xfd:m -Y 0 

BOOTLOADER_START=0x7000
endif

# ---------------------------------------------------------------------------

CFLAGS = -pipe -g -Os -mmcu=$(MCU) -Wall -fdata-sections -ffunction-sections
CFLAGS += -Wa,-adhlns=$(*F).lst -DBOOTLOADER_START=$(BOOTLOADER_START)
LDFLAGS = -Wl,-Map,$(@:.elf=.map),--cref,--relax,--gc-sections,--section-start=.text=$(BOOTLOADER_START)

# ---------------------------------------------------------------------------

$(TARGET): $(TARGET).elf
	@$(SIZE) -C -d --mcu=$(MCU) $<

$(TARGET).elf: $(SOURCE:.c=.o)
	@echo " Linking file:  $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(OBJDUMP) -h -S $@ > $(@:.elf=.lss)
	@$(OBJCOPY) -j .text -j .data -O ihex $@ $(@:.elf=.hex)
	@$(OBJCOPY) -j .text -j .data -O binary $@ $(@:.elf=.bin)

%.o: %.c $(MAKEFILE_LIST)
	@echo " Building file: $<"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(SOURCE:.c=.o) $(SOURCE:.c=.lst) $(addprefix $(TARGET), .elf .map .lss .hex .bin)

program: $(TARGET).elf
	avrdude $(AVRDUDE_PROG) -p $(AVRDUDE_MCU) -U flash:w:$(<:.elf=.hex) -y

fuses:
	avrdude $(AVRDUDE_PROG) -p $(AVRDUDE_MCU) $(patsubst %,-U %, $(AVRDUDE_FUSES))
