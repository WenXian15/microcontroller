Docs to refer to 
1. https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf
2. https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf

Memory
1. ROM
2. SRAM
3. Boot RAM
4. External Flash and PSRAM
5. OTP


The bootrom decides the boot outcome based on the following system state:
  • The contents of the attached QSPI memory device on chip select 0, if any
  • The contents of POWMAN registers BOOT0 through BOOT3
  • The contents of watchdog registers SCRATCH4 through SCRATCH7
  • The contents of OTP, particularly CRIT1, BOOT_FLAGS0 and BOOT_FLAGS1
  • The QSPI CSn pin being driven low externally (to select BOOTSEL)
  • The QSPI SD1 pin being driven high externally (to select UART boot in BOOTSEL mode)

Based on these, the outcome of the boot sequence may be to:
  • Call code via a vector specified in SCRATCH or BOOT registers prior to the most recent reboot
    ◦ e.g. into code retained in RAM following a power-up from a low-power state.
  • Run an image from external flash
    ◦ either in-place, or loaded into RAM during the boot sequence
    ◦ in-package flash on RP2354 is external for boot purposes: it is a separate silicon die, and the RP2350 die
      does not implicitly trust it
  • Run an image preloaded into SRAM (distinct from the vector case)
  • Load and run an image from OTP into SRAM
  • Enter the USB bootloader
  • Enter the UART bootloader
  • Perform a one-shot operation requested via the reboot() API, such as a flash update boot
    ◦ this may be requested by the user, or by the UART or UF2 bootloaders
  • Refuse to boot, due to lack of suitable images and the UART and USB bootloaders being disabled via OTP

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

POWMAN Boot Vector
• BOOT0: magic number 0xb007c0d3
• BOOT1: Entry point XORed with magic -0xb007c0d3 (0x4ff83f2d)
• BOOT2: Stack pointer
• BOOT3: Entry point

Watchdog Boot Vector
• SCRATCH4: magic number 0xb007c0d3
• SCRATCH5: entry point XORed with magic -0xb007c0d3 (0x4ff83f2d)
• SCRATCH6: stack pointer
• SCRATCH7: entry point


The default openocd does not works with pico2, raspberrypi version of openocd is required.
Build openocd
$ git clone https://github.com/raspberrypi/openocd.git
$ sudo apt install libhidapi-dev && sudo apt-get install libusb-1.0-0-dev (Lib dependencies)
$ cd openocd
$ ./bootstrap
$ ./configure --disable-werror --enable-buspirate --enable-cmsis-dap
$ make -j4

$ sudo openocd -f pico/interface/cmsis-dap.cfg -f pico2/target/rp2345.cfg -c "adapter speed 5000"
