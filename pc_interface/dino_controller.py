import serial;
import time;
from pynput.keyboard import Key, Controller


ser = serial.Serial("/dev/ttyUSB0", 115200, serial.EIGHTBITS, serial.PARITY_NONE, timeout = None);


keyboard = Controller();

while 1:
    bytes_read = ser.read(1);
    
    if  bytes_read[0] == 0xAA:
        print("start bit recevied");
        bytes_read = ser.read(1);
        if bytes_read[0] == 1:
            keyboard.press(Key.space); 
            time.sleep(0.01);
            keyboard.release(Key.space);
            print("jump");
        elif bytes_read[0] == 2:
            keyboard.press(Key.down);      
            time.sleep(0.01);
            keyboard.release(Key.down);    
            print("duck");
        
        ser.read(2);
        
     

