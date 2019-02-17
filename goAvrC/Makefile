MCU     = atmega328
OUTPUT  = $(shell basename "`pwd`")
AVRDUDE = /home/varun/exe/arduino/avrdude
CC      = avr-gcc
OBJCPY  = avr-objcopy
CFLAGS  = -g -Os -I./src 
DFLAGS  = -MM
LFLAGS  = -g
DEPS    = 
TMP     = tmp
SRC     = src
BIN     = bin
SRCS    = $(wildcard $(SRC)/*.c)
HEADERS = $(wildcard $(SRC)/*.h)
OBJS    = $(patsubst $(SRC)/%.c,$(TMP)/%.o,$(SRCS))

all: $(BIN)/$(OUTPUT).hex


$(TMP)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -mmcu=$(MCU) -o $@ -c $<
	$(CC) $(DFLAGS) $<  | sed -e 's/^/$(TMP)\//'  > $(TMP)/$*.d

bin/$(OUTPUT).hex: $(OBJS)
	$(CC) $(LFLAGS) -mmcu=$(MCU) -o $(TMP)/$(OUTPUT).elf $^
	$(OBJCPY) -j .text -j .data -O ihex $(TMP)/$(OUTPUT).elf bin/$(OUTPUT).hex

upload : $(BIN)/$(OUTPUT).hex
	$(AVRDUDE)/avrdude -C$(AVRDUDE)/avrdude.conf -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:$(BIN)/$(OUTPUT).hex:i

clean:
	rm -f bin/* tmp/*

-include $(OBJS:.o=.d)
