## STM32F4 Examples

Some example programs of STM32F4 for beginners, where [STM32F4DISCOVERY](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) board is used.

<img src="stm32f4-discovery.jpg" height="354px" width="392px" />

**Required platform:**

* GNU/Linux
* GNU Arm Embedded Toolchain

## Provided Examples

**Peripheral manipulation examples:**

* GPIO output (LED)
* GPIO input (button)
* PWM
* UART read / write with pooling
* UART write with DMA
* SysTick
* CRC
* Flash 
* USB VCP (Virtual COM Port)

**FreeRTOS examples:**
* Task
* Semaphore
* Queue

## Development Tools

1. Prerequisites:

```
sudo apt install build-essential git zlib1g-dev libsdl1.2-dev automake* autoconf* \
         libtool libpixman-1-dev lib32gcc1 lib32ncurses5 libc6:i386 libncurses5:i386 \
         libstdc++6:i386 libusb-1.0.0-dev ninja-build
```

2. OpenOCD:

```
git clone git://git.code.sf.net/p/openocd/code openocd
cd openocd
git submodule update --init --recursive
./bootstrap
./configure --prefix=/usr/local --enable-jlink --enable-amtjtagaccel --enable-buspirate \
            --enable-stlink --disable-libftdi
echo -e "all:\ninstall:" > doc/Makefile
make -j4
sudo make install
```

3. ARM GCC toolchain 9:

```
wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2
tar jxf ./gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2
rm gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2
```

4. QEMU:

```
git clone git://git.qemu.org/qemu.git
cd qemu
git submodule init
git submodule update --recursive
mkdir build
cd build
../configure
make -j $(nproc)
```

5. Edit `~/.bashrc` and append the following instructions:

```
PATH=$PATH:${YOUR_PATH}/qemu/build
PATH=$PATH:${YOUR_PATH}/gcc-arm-none-eabi-9-2019-q4-major/bin
```

6. Restart the terminal

## Build and run

1. Build:

```
make
```

2. Upload binary:

```
make flash
```

3. To observe the UART examples, type:

```
sudo screen /dev/ttyUSB0 9600
```

## Troubleshooting

**Resolve premission denied error of the GNU screen:**

```
sudo gpasswd --add username dialout
```

## References

* NCKU Wikipedia: http://wiki.csie.ncku.edu.tw/embedded/Lab25
