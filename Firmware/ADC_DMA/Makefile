#======================================================================#
#Output files
EXECUTABLE=stm32_executable.elf
BIN_IMAGE=stm32_bin_image.bin

#======================================================================#
#Cross Compiler
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

#======================================================================#
#Flags
CFLAGS=-g -mlittle-endian -mthumb
CFLAGS+=-mcpu=cortex-m4
CFLAGS+=-mfpu=fpv4-sp-d16 -mfloat-abi=softfp
CFLAGS+=-ffreestanding
CFLAGS+=-D USE_STDPERIPH_DRIVER
CFLAGS+=-I./


#stm32-flash
CFLAGS+=-Wl,-T,stm32_flash.ld

#======================================================================#
#Libraries

#Stm32 libraries
ST_LIB=../Libraries/STM32F4xx_StdPeriph_Driver
CFLAGS+=-I../Libraries/CMSIS/ST/STM32F4xx/Include

#CMSIS libraries
CFLAGS+=-I../Libraries/CMSIS/Include

#StdPeriph includes
CFLAGS+=-I$(ST_LIB)/inc

#Std C Lib
CFLAGS+=-I./stdlib/

#======================================================================#
#Source code
SRC=../Libraries/CMSIS/system_stm32f4xx.c

#StdPeriph
SRC+=$(ST_LIB)/src/misc.c \
	$(ST_LIB)/src/stm32f4xx_rcc.c \
	$(ST_LIB)/src/stm32f4xx_dma.c \
	$(ST_LIB)/src/stm32f4xx_flash.c \
	$(ST_LIB)/src/stm32f4xx_gpio.c \
	$(ST_LIB)/src/stm32f4xx_usart.c \
	$(ST_LIB)/src/stm32f4xx_tim.c \
	$(ST_LIB)/src/stm32f4xx_spi.c \
	$(ST_LIB)/src/stm32f4xx_i2c.c \
	$(ST_LIB)/src/stm32f4xx_dma.c \
	$(ST_LIB)/src/stm32f4xx_adc.c

#Std C Lib
SRC+=./stdlib/*.c

#Major programs
SRC+=./main.c

#======================================================================#
#STM32 startup file
STARTUP=./startup_stm32f4xx.s

#======================================================================#
#Make rules

#Make all
all:$(BIN_IMAGE)

$(BIN_IMAGE):$(EXECUTABLE)
	$(OBJCOPY) -O binary $^ $@

STARTUP_OBJ = startup_stm32f4xx.o

$(STARTUP_OBJ): $(STARTUP) 
	$(CC) $(CFLAGS) $^ -c $(STARTUP)

$(EXECUTABLE):$(SRC) $(STARTUP_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

#Make clean
clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(BIN_IMAGE)
#Make flash
flash:
	st-flash write $(BIN_IMAGE) 0x8000000

#======================================================================
.PHONY:all clean flash
