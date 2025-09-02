import serial

import keyboard

START_BYTE = 0xAA       # UART_COMM_START_BYTE
END_BYTE   = 0x67      # UART_COMM_END_BYTE

def compute_checksum(data_bytes):

    return sum(data_bytes) & 0xFF


ser = serial.Serial("/dev/ttyUSB0", 115200, serial.EIGHTBITS, serial.PARITY_NONE, timeout = None)


while 1:
    bytes_read = ser.read(1)
    
    if  bytes_read[0] == START_BYTE:
        print("start bit recevied")

        bytes_read = ser.read(3)
        cmd = bytes_read[0]
        rec_check = bytes_read[1]
        end_byte = bytes_read[2]

        if end_byte != END_BYTE:
            print("Received end byte did not match correct end byte")
            continue

        calc_check = compute_checksum([cmd])
        if rec_check != calc_check:
            print("Received checksum and calculated checksum did not match")
            continue

        if cmd == 1:
            keyboard.press_and_release("space")
            print("jump")
        elif cmd == 2:
            keyboard.press_and_release("down")
            print("duck")


        
         

