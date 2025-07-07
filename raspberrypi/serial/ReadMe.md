# BCM2711 UART to /dev/tty Device Mapping

## Overview

The BCM2711 device (found in Raspberry Pi 4 and similar boards) features six UARTs:
- **1x Mini UART** (UART1) - Simplified implementation
- **5x PL011 UARTs** (UART0, UART2, UART3, UART4, UART5) - Full-featured ARM UART implementation

## Device Mapping

### Primary UART (UART0 - PL011)
- **Device**: `/dev/ttyAMA0`
- **Type**: PL011 UART (high-quality, full-featured)
- **GPIO Pins**: 14/15 (TXD/RXD)
- **Features**: Hardware flow control, stable clock
- **Usage**: Often used as primary serial console

### Mini UART (UART1)
- **Device**: `/dev/ttyS0`
- **Type**: Mini UART (simplified implementation)
- **GPIO Pins**: 14/15 (when primary UART is disabled)
- **Limitations**: 
  - No hardware flow control
  - Shares clock with GPU (baud rate can vary)
  - Lower quality than PL011

### Additional PL011 UARTs (UART2-5)
- **Devices**: `/dev/ttyAMA1` through `/dev/ttyAMA4`
- **Type**: PL011 UART (same quality as UART0)
- **GPIO Pins**: Various (model-dependent)
- **Note**: Not all may be accessible on standard Pi headers

## System Discovery

### Check Available Devices
```bash
# List all tty devices
ls -la /dev/tty*

# Check UART-specific devices
ls -la /dev/ttyAMA* /dev/ttyS*

# View UART detection in kernel log
dmesg | grep -i uart
```

### Verify Current Configuration
```bash
# Check serial console services
systemctl status serial-getty@ttyAMA0.service
systemctl status serial-getty@ttyS0.service

# View active serial ports
cat /proc/tty/driver/serial
```

## Configuration

### Enable Additional UARTs
Add to `/boot/config.txt`:
```bash
# Enable UART2
dtoverlay=uart2

# Enable UART3
dtoverlay=uart3

# Enable UART4
dtoverlay=uart4

# Enable UART5
dtoverlay=uart5
```

### Disable Console on Primary UART
If you want to use the primary UART for applications instead of console:

1. Edit `/boot/cmdline.txt` and remove `console=ttyAMA0,115200`
2. Disable getty service:
   ```bash
   sudo systemctl disable serial-getty@ttyAMA0.service
   ```

### Switch Primary UART
To use PL011 as primary instead of mini UART:
```bash
# Add to /boot/config.txt
dtoverlay=disable-bt
enable_uart=1
```

## Usage Examples

### Basic Serial Communication
```bash
# Send data to UART
echo "Hello UART" > /dev/ttyAMA0

# Read from UART (blocking)
cat /dev/ttyAMA0

# Configure baud rate
stty -F /dev/ttyAMA0 115200
```

### Programming Example (Python)
```python
import serial

# Open PL011 UART
ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=1)

# Send data
ser.write(b'Hello UART\n')

# Read response
response = ser.readline()
print(f"Received: {response}")

ser.close()
```

## Troubleshooting

### Common Issues

**Device not found:**
- Check if UART is enabled in device tree
- Verify GPIO pin configuration
- Ensure proper permissions (`sudo` or add user to `dialout` group)

**Permission denied:**
```bash
# Add user to dialout group
sudo usermod -a -G dialout $USER
# Log out and back in
```

**Baud rate issues with mini UART:**
- Mini UART baud rate depends on GPU frequency
- Use PL011 UARTs for stable communication
- Consider fixing GPU frequency in config.txt

### Debugging Commands
```bash
# Check UART hardware info
cat /sys/class/tty/ttyAMA0/device/amba_device/id

# View current serial port settings
stty -F /dev/ttyAMA0 -a

# Monitor UART activity
sudo cat /dev/ttyAMA0 | hexdump -C
```
