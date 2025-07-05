import RPi.GPIO as GPIO
import time

# GPIO2 - EN
# GPIO3 - IO0
# GPIO14 - Uart TX
# GPIO15 - Uart RX

# ls -l /dev/serial*
# demesg | grep -i serial

# Required to enable uart thru GPIO
# sudo nano /boot/firmware/config.txt

# Pin definitions
IO0_PIN = 2    # RPi GPIO2 -> WT32 IO0
EN_PIN = 3     # RPi GPIO3 -> WT32 EN
IO4_PIN = 4    # RPi GPIO4 -> WT32 IO4

# Setup GPIO
def setup_gpio():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)

    # Setup pins as outputs
    GPIO.setup(IO0_PIN, GPIO.OUT)
    GPIO.setup(EN_PIN, GPIO.OUT)
    GPIO.setup(IO4_PIN, GPIO.OUT)

    # Initial states
    GPIO.output(IO0_PIN, GPIO.HIGH)  # Default to normal boot mode
    GPIO.output(EN_PIN, GPIO.HIGH)   # EN high (not in reset)
    GPIO.output(IO4_PIN, GPIO.LOW)   # IO4 default state

# Enter programming mode
def enter_program_mode():
    print("Entering programming mode...")

    # Set IO0 low for programming mode
    GPIO.output(IO0_PIN, GPIO.LOW)

    # Reset sequence
    GPIO.output(EN_PIN, GPIO.LOW)    # Put into reset
    time.sleep(0.1)                  # Wait for 100ms
    GPIO.output(EN_PIN, GPIO.HIGH)   # Release reset
    time.sleep(0.5)                  # Wait for device to stabilize

    print("Device should now be in programming mode")

# Exit programming mode and enter normal boot
def exit_program_mode():
    print("Exiting programming mode...")

    # Set IO0 high for normal boot
    GPIO.output(IO0_PIN, GPIO.HIGH)

    # Reset sequence
    GPIO.output(EN_PIN, GPIO.LOW)    # Put into reset
    time.sleep(0.1)                  # Wait for 100ms
    GPIO.output(EN_PIN, GPIO.HIGH)   # Release reset
    time.sleep(0.5)                  # Wait for device to stabilize

    print("Device should now boot normally")

# Clean up GPIO
def cleanup():
    GPIO.cleanup()

if __name__ == "__main__":
    try:
        setup_gpio()

        # Example usage:
        enter_program_mode()
        input("Press Enter when programming is complete...")
        exit_program_mode()

    except KeyboardInterrupt:
        print("Program interrupted by user")
    finally:
        cleanup()
        print("GPIO cleanup completed")
