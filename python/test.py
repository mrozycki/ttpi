#! python3
import json
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

ALL_CHARACTERS = '1234567890!":?%+_()=ż`qwertzuiopóasdfghjklłyxcvbnm.,- $~|*śńćęąźŻ\n\tQWERTYUIOPASDFGHJKLZXCVBNMŁ'

MAP = {
    "1": 47,
    "2": 45,
    "3": 43,
    "4": 41,
    "5": 39,
    "6": 37,
    "7": 35,
    "8": 33,
    "9": 31,
    "0": 29,
    "!": 61,
    '"': 63,
    ":": 2,
    "?": 55,
    "%": 51,
    "+": 27,
    "_": 1,
    "(": 59,
    ")": 57,
    "=": 26,
    "`": 14,
    "q": 87,
    "w": 95,
    "e": 82,
    "r": 80,
    "t": 78,
    "z": 96,
    "u": 75,
    "i": 86,
    "o": 76,
    "p": 89,
    "a": 81,
    "s": 90,
    "d": 85,
    "f": 94,
    "g": 79,
    "h": 91,
    "j": 92,
    "k": 83,
    "l": 88,
    "y": 97,
    "x": 73,
    "c": 84,
    "v": 74,
    "n": 77,
    "m": 93,
    ".": 100,
    ",": 99,
    "-": 22,
    " ": 113,
    "$": 187,
    "~": 253,
    "|": 19,
    "*": 187,
    "\u017c": 24,
    "\u00f3": 101,
    "\u0142": 18,
    "b": 72,
    "\u015b": 102,
    "\u0144": 103,
    "\u0107": 104,
    "\u0119": 20,
    "\u0105": 15,
    "\u017a": 105,
    "\u017b": 23,
    "\n": 119,
    "\t": 121,
    "Q": 52,
    "W": 64,
    "E": 70,
    "R": 28,
    "T": 50,
    "Y": 60,
    "U": 48,
    "I": 65,
    "O": 46,
    "P": 69,
    "A": 44,
    "S": 67,
    "D": 38,
    "F": 68,
    "G": 42,
    "H": 40,
    "J": 32,
    "K": 66,
    "L": 30,
    "Z": 71,
    "X": 58,
    "C": 36,
    "V": 62,
    "B": 34,
    "N": 54,
    "M": 56,
    "\u0141": 11,
}
REVERSE_MAP = {}

for ch, val in MAP.items():
    REVERSE_MAP[val] = ch
# for val in sorted(REVERSE_MAP):
# print(f"value {val} is {REVERSE_MAP[val]}")
try:
    # Loop through all ASCII values from 0 to 255
    # for i in range(60,256):
    # for i in [0, 27, 45, 43, 41, 39, 37, 35, 33, 31, 29]:
    for ch in ALL_CHARACTERS:
        if ch in MAP:
            continue
        print(f"type: {ch}, hex: {ord(ch):02x}")
        # Send each ASCII byte without line endings
        # ser.write(bytes([i]))  # Send byte by byte (ASCII value)
        val = ser.read()
        if len(val) != 1:
            print("WARNING, got more bytes than expected:", val)
        MAP[ch] = val[0]

        time.sleep(0.1)  # Optional delay to avoid overwhelming the serial port

    for ch in "What is your name?":
        ser.write(MAP[ch].to_bytes())
        time.sleep(0.1)
    ser.write(MAP["\n"].to_bytes())
    val = ser.read_until(MAP["\n"].to_bytes())
    print("Got bytes:", val)
    print(ser.dsrdtr)
    ret = "Hello, "
    for ch in ret:
        ser.write(MAP[ch].to_bytes())
        time.sleep(0.1)
    for ch in val[:-1]:
        print("Writing:", REVERSE_MAP[ch])
        ser.write(ch.to_bytes())
        time.sleep(0.1)
    ser.flush()
    for ch in ". My name is Tom Marvolo Riddle.":
        ser.write(MAP[ch].to_bytes())
        time.sleep(0.3)
    ser.write(MAP["\n"].to_bytes())

    print("All ASCII values sent.")

finally:
    # Close the serial port when done
    print(json.dumps(MAP, indent=4))
    ser.close()
    print(f"Serial port {port} closed.")
