#======================================================================#

#Output files

EXECUTABLE=firmware.elf
BIN_IMAGE=firmware.bin

#======================================================================#

#Toolchain

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
GDB=arm-none-eabi-gdb

#======================================================================#

#Flags

CFLAGS=-g -mlittle-endian -mthumb \
	-mcpu=cortex-m4 \
	-mfpu=fpv4-sp-d16 -mfloat-abi=hard \
	--specs=nano.specs \
	--specs=nosys.specs
CFLAGS+=-D USE_STDPERIPH_DRIVER
CFLAGS+=-D STM32F4xx
CFLAGS+=-D __FPU_PRESENT=1 \
        -D ARM_MATH_CM4 \
	-D __FPU_USED=1
CFLAGS+=-I./


#stm32-flash
CFLAGS+=-Wl,-T,stm32_flash.ld

#======================================================================#

#Source code

CFLAGS+=-I./lib/CMSIS/Include
SRC=./lib/CMSIS/system_stm32f4xx.c

#StdPeriph
ST_LIB=./lib/STM32F4xx_StdPeriph_Driver

CFLAGS+=-I$(ST_LIB)/inc
CFLAGS+=-I./lib/CMSIS/ST/STM32F4xx/Include
SRC+=$(ST_LIB)/src/misc.c \
	$(ST_LIB)/src/stm32f4xx_rcc.c \
	$(ST_LIB)/src/stm32f4xx_dma.c \
	$(ST_LIB)/src/stm32f4xx_flash.c \
	$(ST_LIB)/src/stm32f4xx_gpio.c \
	$(ST_LIB)/src/stm32f4xx_usart.c \
	$(ST_LIB)/src/stm32f4xx_tim.c\
	$(ST_LIB)/src/stm32f4xx_spi.c\
	$(ST_LIB)/src/stm32f4xx_i2c.c

#FreeRTOS
ARCH=CM4F
FREERTOS=./lib/FreeRTOSV8.2.3/FreeRTOS

CFLAGS+=-I$(FREERTOS)/Source/include \
	-I$(FREERTOS)/Source/portable/GCC/ARM_$(ARCH)
SRC+=$(FREERTOS)/Source/croutine.c \
	$(FREERTOS)/Source/list.c \
	$(FREERTOS)/Source/queue.c \
	$(FREERTOS)/Source/tasks.c \
	$(FREERTOS)/Source/timers.c \
	$(FREERTOS)/Source/portable/MemMang/heap_4.c \
	$(FREERTOS)/Source/portable/GCC/ARM_$(ARCH)/port.c

#STM32 startup file
STARTUP=./startup_stm32f4xx.s

#Major programs
SRC+=./main.c

#======================================================================#

#Make rules

#Compile
all:$(BIN_IMAGE)

$(BIN_IMAGE):$(EXECUTABLE)
	$(OBJCOPY) -O binary $^ $@

STARTUP_OBJ = startup_stm32f4xx.o

$(STARTUP_OBJ): $(STARTUP) 
	$(CC) $(CFLAGS) $^ -c $(STARTUP)

$(EXECUTABLE):$(SRC) $(STARTUP_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

#clean
clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(BIN_IMAGE)

#Flash
flash:
	st-flash write $(BIN_IMAGE) 0x8000000

#OpenOCD GDB server
openocd:
	openocd -f ./openocd.cfg

#GNU Debugger
gdbauto:
	cgdb -d $(GDB) -x ./openocd_gdb.gdb

#======================================================================
.PHONY:all clean flash
