#!/usr/bin/python3
import time
import serial
from threading import Thread
import threading

i = 0

BACK = [0,0]
HEAD = [1,1]
LEFT = [1,0]
RIGHT = [0,1]

pNONE = 0
pcTOPLEFT = 1
pcTOPRIGHT = 2
pcBACK = 3
pcHEAD = 4
pcMIDLEFT = 5 
pcMIDRIGHT = 6
pcBOTTOMLEFT = 7
pcBOTTOMRIGHT = 8


tProcess = pcBOTTOMRIGHT

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

# 5 -> 2
def docHead():
    global tProcess 
    SendData(65,20,20,HEAD[0],HEAD[1])
    tProcess = pNone

# 5 -> 8
def docBack():
    global tProcess 
    SendData(65,20,20,BACK[0],BACK[1])
    tProcess = pNone

# 5 -> 1
def docTopLeft(i):
    global tProcess
    if i == 0:
        SendData(170,20,20,LEFT[0],LEFT[1])
        i = 1
    elif i == 1:
        SendData(120,20,20,HEAD[0],HEAD[1])
        i+= 1 
    elif i == 2:
        SendData(170,20,20,RIGHT[0],RIGHT[1])
        i = 0 
        tProcess = pNONE

# 5 -> 3
def docTopRight(i):
    global tProcess
    if i == 0:
        SendData(170,20,20,RIGHT[0],RIGHT[1])
        i = 1
    elif i == 1:
        SendData(120,20,20,HEAD[0],HEAD[1])
        i+= 1 
    elif i == 2:
        SendData(170,20,20,LEFT[0],LEFT[1])
        i = 0 
        tProcess = pNONE

# 5 -> 3
def docBottomLeft(i):
    global tProcess
    if i == 0:
        SendData(170,20,20,RIGHT[0],RIGHT[1])
        i = 1
    elif i == 1:
        SendData(120,20,20,BACK[0],BACK[1])
        i+= 1 
    elif i == 2:
        SendData(170,20,20,LEFT[0],LEFT[1])
        i = 0 
        tProcess = pNONE

# 5 -> 3
def docBottomRight(i):
    global tProcess
    if i == 0:
        SendData(170,20,20,LEFT[0],LEFT[1])
        i = 1
    elif i == 1:
        SendData(120,20,20,BACK[0],BACK[1])
        i+= 1 
    elif i == 2:
        SendData(170,20,20,RIGHT[0],RIGHT[1])
        i = 0 
        tProcess = pNONE

# 5 -> 4
def docMidLeft(): 
    global tProcess
    SendData(65,20,20,BACK[0],BACK[1])
    tProcess = pcTOPLEFT

# 5 -> 4
def docMidRight(): 
    global tProcess
    SendData(65,20,20,BACK[0],BACK[1])
    tProcess = pcTOPRIGHT


    

def SendData(Pos, Vel, Acc, Dir1, Dir2):
    data2Send  = FormatData(Pos, Vel, Acc, Dir1, Dir2)
    # print(data2Send)
    print("into the send_data")
    ser.write(bytes(data2Send, 'utf-8'))
    time.sleep(3)

def ReceiveData():
    global tProcess
    i = 0
    while 1:
        # print("into the receive_data")
        s = ser.readline()
        data = s.decode('utf-8')			
        data = data.rstrip()	
        print(data)
        if(data == "OK"):
            print(tProcess)
            if tProcess == pNONE:
                pass
            elif tProcess == pcTOPLEFT:
                docTopLeft(i)
                i+= 1
            elif tProcess == pcTOPRIGHT: 
                docTopRight(i)
                i += 1 
            elif tProcess == pcBACK: 
                docBack()
            elif tProcess == pcHEAD: 
                docHead()
            elif tProcess == pcMIDLEFT:
                docMidLeft()
            elif tProcess == pcMIDRIGHT:
                docMidRight()
            elif tProcess == pcBOTTOMLEFT:
                docBottomLeft(i)
                i += 1 
            elif tProcess == pcBOTTOMRIGHT:
                docBottomRight(i)
                i += 1 

        # time.sleep(1)
        
# SendData(360,45,45,1,0)


try:

    t = time.time()
    t1 = threading.Thread(target=ReceiveData)
    t2 = threading.Thread(target=SendData, args=(1111,1111,1111,1,1,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    print("All thread join!")

except KeyboardInterrupt:
	ser.close()


