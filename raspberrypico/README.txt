
Refer to Debug with a second Pico or Pico 2 section of https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf
$ sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000"
