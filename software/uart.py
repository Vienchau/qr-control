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

def FixLength(value):
    if len(str(value)) == 1:
        return "000" + str(value)
    elif len(str(value)) == 2:
        return "00" + str(value)
    elif len(str(value)) == 3:
        return "0" + str(value)
    else: 
        return str(value)
    
def FormatData(Pos, Vel, Acc, Dir1, Dir2):
    PosStr = FixLength(Pos)
    VelStr = FixLength(Vel)
    AccStr = FixLength(Acc)
    Dir1Str = str(Dir1)
    Dir2Str = str(Dir2)
    result = "{},{},{},{},{}".format(PosStr, VelStr, AccStr, Dir1Str, Dir2Str)
    return result

def SendData(Pos, Vel, Acc, Dir1, Dir2):
    
    while 1:
        # print("arg send: ",Pos1, Vel1, Acc1, Dir1, Pos2, Vel2, Acc2, Dir2)
        data2Send  = FormatData(Pos, Vel, Acc, Dir1, Dir2)
        print(data2Send)
        print("into the send_data")
        ser.write(bytes(data2Send, 'utf-8'))
        time.sleep(3)

def ReceiveData():
    while 1:
        print("into the receive_data")
        s = ser.readline()
        data = s.decode('utf-8')			
        data = data.rstrip()	
        print(data)	
        time.sleep(1)
        
SendData(360,45,45,1,0)

# try:
#     t = time.time()
#     t1 = threading.Thread(target=ReceiveData)
#     t2 = threading.Thread(target=SendData, args=(360,45,45,1,0,))
#     t1.start()
#     t2.start()
#     t1.join()
#     t2.join()
#     print("All thread join!")




# except KeyboardInterrupt:
# 	ser.close()

