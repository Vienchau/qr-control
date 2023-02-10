#!/usr/bin/python3
import time
import serial
from threading import Thread
import threading

ser = serial.Serial(
	port = '/dev/ttyS0',
	baudrate = 115200,
	parity = serial.PARITY_NONE,
	stopbits = serial.STOPBITS_ONE,
	bytesize = serial.EIGHTBITS,
	timeout = 1
)

ser2 = serial.Serial(
	port = '/dev/ttyS0',
	baudrate = 115200,
	parity = serial.PARITY_NONE,
	stopbits = serial.STOPBITS_ONE,
	bytesize = serial.EIGHTBITS,
	timeout = 1
)


def send_data():
    i = 0
    while True:
        print("into the send_data")
        test_str = '0360,0045,0045,1,0360,0045,0045,0'
        test_str_2 = '0360,0075,0045,0,0360,0095,0045,0'
        # test_str = '0360'
        # test_str_2 = '0361'
        if i % 2 :
            ser.write(bytes(test_str, 'utf-8'))
            i+=1
        else :
            ser.write(bytes(test_str_2, 'utf-8'))
            i+=1
        
        
        time.sleep(3)

def receive_data():
    while True:
        print("into the recieve_data")
                #print received data
        s = ser.readline()
        data = s.decode('utf-8')			# decode s
        data = data.rstrip()			# cut "\r\n" at last of string
        print(data)	
        
    
try:
    t = time.time()
    t1 = threading.Thread(target=receive_data)
    t2 = threading.Thread(target=send_data)
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    print("All thread join!")

except KeyboardInterrupt:
	ser.close()