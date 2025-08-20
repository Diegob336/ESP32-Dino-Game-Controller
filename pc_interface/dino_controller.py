import serial;

import keyboard;


ser = serial.Serial("/dev/ttyUSB0", 115200, serial.EIGHTBITS, serial.PARITY_NONE, timeout = None);


while 1:
    bytes_read = ser.read(1);
    
    if  bytes_read[0] == 0xAA:
        print("start bit recevied");
        bytes_read = ser.read(1);
        if bytes_read[0] == 1:
            keyboard.press_and_release("space");
            print("jump");
        elif bytes_read[0] == 2:
            keyboard.press_and_release("down");
            print("duck");
        
        ser.read(2);
        
     

