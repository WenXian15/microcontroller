Docs to refer to 
1. https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf
2. https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf

Memory
1. ROM
2. SRAM
3. Boot RAM
4. External Flash and PSRAM
5. OTP

High level boot sequence
Entry -> Core 1 Wait -> Boot Path Start -> Await Rescue -> Generate Boot Random -> Check POWMAN Vector -> Check Watchdog Vector -> Prepare for Image Boot
-> Try RAM Image Boot
   -> Check BOOTSEL 
     -> Try OTP Boot 
       -> Try Flash Boot 
     -> Prepare for BOOTSEL 
       -> Enter USB Boot 
       -> Enter UART Boot 
     -> Boot Failure


The default openocd does not works with pico2, raspberrypi version of openocd is required.
Build openocd
$ git clone https://github.com/raspberrypi/openocd.git
$ sudo apt install libhidapi-dev && sudo apt-get install libusb-1.0-0-dev (Lib dependencies)
$ cd openocd
$ ./bootstrap
$ ./configure --disable-werror --enable-buspirate --enable-cmsis-dap
$ make -j4

$ sudo openocd -f pico/interface/cmsis-dap.cfg -f pico2/target/rp2345.cfg -c "adapter speed 5000"
