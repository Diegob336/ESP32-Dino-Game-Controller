import serial;

ser = serial.Serial("/dev/ttyUSB0", 115200, serial.EIGHTBITS, serial.PARITY_NONE, timeout = None);

while 1:
    bytes_read = ser.read(4);

    if len(bytes_read) == 4:
        print("packet received");
    else:
        print(f"Error sending packet, only sent {len(bytes_read)} bits")
