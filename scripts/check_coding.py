#! python3
import serial
import time

# Configure the serial port
port = "/dev/tty.usbserial-A50285BI"  # Change this to the correct port for your system
baudrate = 1200  # Set the baud rate to match your device
timeout = 30  # Timeout for the serial read/write (in seconds)

# Open the serial port
ser = serial.Serial(port, baudrate, timeout=timeout)

# Check if the port is opened successfully
if not ser.is_open:
    print(f"Failed to open serial port: {port}")
    exit(1)

try:
    while True:
        val = ser.read()
        print([int(b) for b in val])

        time.sleep(0.1)  # Optional delay to avoid overwhelming the serial port

finally:
    ser.close()
    print(f"Serial port {port} closed.")
