## stm32f4_examples

Some example code of STM32F4 for beginners.

## Development platform and hardware

GNU/Linux and GCC toolchain are used, and the code have been tested on STM32F407-Discovery board.

<img src="stm32f4-discovery.jpg" height="354px" width="392px" />

### For Peripheral manipulation examples:
1. GPIO Output (LED)
2. PWM
3. UART read and write
  * Type command **sudo screen /dev/ttyUSB0 9600** to test the program
4. DMA (using UART as example)
5. Systick
6. USB VCP (Virtual COM Port)

### For FreeRTOS examples:
1. Task creation
2. Semaphore
3. Queue

## Fixing USB device premission denied error for GNU screen

```
sudo gpasswd --add username dialout
```

## Developement environment setup

Here we provide a brief tutorial of setting up the environment (i.e., GCC toolchain, debugger, flash tool)

### 0.Prerequisite

```
sudo apt install build-essential git zlib1g-dev libsdl1.2-dev automake* autoconf* libtool libpixman-1-dev lib32gcc1 lib32ncurses5 libc6:i386 libncurses5:i386 libstdc++6:i386 libusb-1.0.0-dev
```

### 1.OpenOCD

```
git clone git://git.code.sf.net/p/openocd/code openocd
cd openocd
./bootstrap
./configure --prefix=/usr/local  --enable-jlink --enable-amtjtagaccel --enable-buspirate  --enable-stlink   --disable-libftdi
echo -e "all:\ninstall:" > doc/Makefile
make -j4
sudo make install
```

### 2. ST-LINK

```
git clone http://github.com/texane/stlink.git
cd stlink
mkdir build
cd build
cmake ..
make -j4
sudo make install
#sudo cp 49-stlinkv2.rules /etc/udev/rules.d/
```

### 3. ARM GCC toolchain 5.4

```
wget https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
tar -jxf gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
rm gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
```

edit "~/.bashrc" and append the following instruction:

```
PATH=$PATH:~/workspace/tools/gcc-arm-none-eabi-5_4-2016q3/bin
```

### 4. Restart the terminal

### References

* NCKU Wikipedia: http://wiki.csie.ncku.edu.tw/embedded/Lab25
