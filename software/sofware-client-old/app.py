# import the necessary packages
import cv2 as cv 
import numpy as np
from pyzbar.pyzbar import decode
# import pyzbar
import time
import AiPhile

import utils

import serial 
import threading 
from threading import Thread 

from math import atan2, pi, ceil

# Identify angle of QR code (orientation)
# Parameter 'qrcode' is 'frame'


#ref_point = []
#click = False
#points 
################### Rapoo Camera 


############# variable - uart ###############
### global variable
BACK = [0,0]
HEAD = [1,1]
# LEFT = [1,0]
# RIGHT = [0,1]
LEFT = [0, 1]
RIGHT = [1, 0]

pNONE = 0
pRUN = 1
pCALIB1 = 2
pCALIB2 = 3
pCALIB3 = 4
pROTATELEFT = 5
pROTATERIGHT = 6
pBACK = 7
pDONE = 8

ReadyFlag= 0
angle_point = 0 # goc giua 2 diem T-G vs duong thang ve phia truoc
d = 0 
angle = 0

i = 0 # bien check hanh dong tiep theo giua 2 QR code lien tiep 
list_process = [pRUN, pROTATELEFT, pRUN]

# Init pNONE 
tProcess = pNONE

########### function - uart  ###################
ser = serial.Serial(
	port = '/dev/ttyS0',
	baudrate = 115200,
	parity = serial.PARITY_NONE,
	stopbits = serial.STOPBITS_ONE,
	bytesize = serial.EIGHTBITS,
	timeout = 1
)


def doAngle():
    global angle_point, d, angle
    global tProcess, list_process, i
    global pRUN, pROTATELEFT, pCALIB1, pCALIB2, pCALIB3
    print(round(angle_point * 4))
    print(f"{d} in do")
    # Xoay sang trai 
    if angle_point > 0:
        angle_point = round(angle_point * 4)
        tProcess = pCALIB2
        SendData(angle_point, 20, 15, LEFT[0], LEFT[1])

    # Xoay sang phai
    else:
        angle_point = angle_point * 4
        angle_point = round(abs(angle_point))
        tProcess = pCALIB2
        SendData(angle_point, 20, 15, RIGHT[0], RIGHT[1])
    
   

def doDistance():
    global angle_point, d, angle
    global tProcess, list_process, i
    global pRUN, pROTATELEFT, pCALIB1, pCALIB2, pCALIB3
    # Quy do d thanh <do xung>
    # d = d * hehe (thuc nghiem de tim duoc gia tri)
    d = round(d * 5.0 / 3)
    print(f"do distance {d}")
    # SendData(d, 30, 15, HEAD[0], HEAD[1])
    tProcess = pCALIB3
    SendData(d, 30, 15, 1, 1)
    

def doCorrect():
    global angle_point, d, angle
    global tProcess, list_process, i
    global pRUN, pROTATELEFT, pCALIB1, pCALIB2, pCALIB3
    '''
    angle > 0: xoay sang trai (0->180)
    angle < 0: xoay sang phai (0->-180)
    '''
    
    if angle > 0:  
        angle = angle * 4
        angle = round(angle)
        print(f"do angle {angle}")
        tProcess = list_process[i]
        SendData(angle, 30, 30, 0, 1)
    else: 
        # angle = angle * K
        angle = angle * 4
        angle = round(angle)
        angle = abs(angle)
        tProcess = list_process[i]
        SendData(angle, 30, 30, 1, 0)

    
    #time.sleep(2)# list_process = [pHead, pRotateLeft]
    i += 1 
    if i == 3: 
        i = 0 
        tProcess = pDONE 
    
def doHead():
    global angle_point, d, angle
    global tProcess, list_process, i
    global pRUN, pROTATELEFT, pCALIB1, pCALIB2, pCALIB3
    SendData(710, 45, 45, HEAD[0], HEAD[1])
    tProcess = pRUN
    

def doRotateLeft():
    global angle_point, d, angle
    global tProcess, list_process, i
    global pRUN, pROTATELEFT, pCALIB1, pCALIB2, pCALIB3
    # quay 90
    SendData(360, 30, 30, LEFT[0], LEFT[1])
    pre_tProcess = tProcess
    tProcess = pDONE
    #time.sleep(2)
    #SendData(1111,1111,1111,1,1)
    
def SendData(Pos, Vel, Acc, Dir1, Dir2):
    data2Send  = utils.FormatData(Pos, Vel, Acc, Dir1, Dir2)
    print(data2Send)
    print("into the send_data")
    ser.write(bytes(data2Send, 'utf-8'))
    #time.sleep(1)


def ReceiveData():
    global angle_point, d, angle
    global list_process
    global i
    global tProcess
    global pRUN, pROTATELEFT, pCALIB1, pCALIB2, pCALIB3
    global ReadyFlag
    
    while 1:
        # print("into the receive_data")
        s = ser.readline() # s is an bytes object 
        data = s.decode('utf-8') # bytes object b'\xe2\x82\xac100' -> after using decode() method -> data: €100
        data = data.rstrip() # remove trailing whitespace ('\n')
        print(data)
        '''
        + Thread doOpenCV va thread ReceiveData chay song song
        + STM32F4 nhan duoc data "1111,1111,1111,1,1" -> gui len Raspberry pi 4 "OK"
        + data == "OK" -> Tinh toan hien tai nhu the nao, tuong lai mong muon -> SendData phu hop xuong STM32F4
        + Cac buoc dieu khien: 
            - "Tinh toan hien tai nhu the nao, tuong lai mong muon" xu ly trong doOpenCV 
            - Tu do, cai dat tProcess 
        '''
        if(data == "OK"):
            print(tProcess)
            if tProcess == pNONE or tProcess == pDONE:
                #if(tProcess == pDONE):
                    #tProcess = pNONE
                pass
            elif tProcess == pCALIB1: 
                doAngle()
            elif tProcess == pCALIB2:
               
                doDistance()
            elif tProcess == pCALIB3: 
                doCorrect()
            elif tProcess == pRUN: 
                doHead()
            elif tProcess == pROTATELEFT:
                doRotateLeft()

def doOpenCV():
    
    # Can uoc tinh lai, 200 chi la gia tri gia dinh
    T_x = 315 
    T_y = 245
    global angle_point, d, angle
    global list_process
    global i
    global tProcess
    global pRUN, pROTATELEFT, pCALIB1, pCALIB2, pCALIB3
    cap = cv.VideoCapture(-1)
    _, frame = cap.read()
    old_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    lk_params = dict(winSize=(20, 20),
                    maxLevel=4,
                    criteria=(cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.01))
    cv.circle(frame, (265, 177), radius = 0, color = (255, 0, 0), thickness = 4)
    old_points = np.array([[]])
    qr_detected= False
    # stop_code=False
    frame_counter = 0
    starting_time = time.time()
    
    counter = 0 
    pre_angle = 500
    count_send = 0
    print("hehe")
    # SendData(1111,1111,1111,1,1)
    
    while 1:
        
        counter += 1
        frame_counter += 1
        ret, frame = cap.read()
        cv.line(frame, (65, 70), (565, 70), (255, 255, 0), 2)
        cv.line(frame, (565, 70), (565, 420), (255, 255, 0), 2)
        cv.line(frame, (565, 420), (65, 420), (255, 255, 0), 2)
        cv.line(frame, (65, 420), (65, 70), (255, 255, 0), 2)
        img = frame.copy()
        barcodes = decode(frame) 

        # cv.line(frame, (213, 0), (213, 479), (0, 255, 255), 1)

        for barcode in barcodes: 
            (x, y, w, h) = barcode.rect

            barcodeData = barcode.data.decode("utf-8") 
            barcodeType = barcode.type
            
            if len(barcode.polygon) != 4: 
                pass 
            else:
                p1_x = barcode.polygon[0].x
                p1_y = barcode.polygon[0].y
                
                p2_x = barcode.polygon[1].x 
                p2_y = barcode.polygon[1].y

                p3_x = barcode.polygon[2].x 
                p3_y = barcode.polygon[2].y

                p4_x = barcode.polygon[3].x 
                p4_y = barcode.polygon[3].y
            
            (rv, points, straight_qrcode) = cv.QRCodeDetector().detectAndDecode(frame)
            #print(points)
            if rv:
                points = points[0]

                # Toa do dung cua ma QR
                pt1 = points[0] 
                pt2 = points[1]
                pt3 = points[2]
                pt4 = points[3]
                a = int(pt2[1])
                b = int(pt1[1])
                c = int(pt2[0])
                d = int(pt1[0])

                angle = atan2(a - b, c - d)
                angle = (angle * 180 / pi)
                angle = int(angle)
            
                # send uart 
                if pre_angle > angle - 2 or pre_angle < angle + 2: 
                    
                    count_send += 1 
                    print(angle, count_send)
                pre_angle = angle
                print(tProcess)
                
                
                
                
                G_x = (p2_x + p4_x) / 2.0
                G_y = (p2_y + p4_y) / 2.0
                # print(G_x, G_y)
                if count_send == 20:
                    count_send = 0
            
                    if tProcess == pRUN or tProcess == pROTATELEFT:
                        print("into if tprocess == 2 cai ")
                        SendData(1111,1111,1111,1,1)
                    
                    elif tProcess == pNONE:
                        print('into tprocess == pNONE')
                        tProcess = pCALIB1
                        angle_point = round(utils.ComputeAngle(p2_x, p2_y, p4_x, p4_y, T_x, T_y))
                        d = round(utils.ComputeDistance(p2_x, p2_y, p4_x, p4_y, T_x, T_y))
                        SendData(1111,1111,1111,1,1)
                 
                    # tProcess = pcHEAD
                    # tProcess = utils.CheckCase(p1_x, p1_y, p2_x, p2_y, p3_x, p3_y, p4_x, p4_y)
                    
                    
              
             
        img = cv.resize(img, None, fx=2, fy=2,interpolation=cv.INTER_CUBIC)

        gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        stop_code = False
        if qr_detected and stop_code == False:
            # print('detecting')
            new_points, status, error = cv.calcOpticalFlowPyrLK(old_gray, gray_frame, old_points, None, **lk_params)
            old_points = new_points 
            new_points = new_points.astype(int)
            n = (len(new_points))
            frame = AiPhile.fillPolyTrans(frame, new_points, AiPhile.GREEN, 0.4)
            AiPhile.textBGoutline(frame, f'Detection: Optical Flow', (30,80), scaling=0.5,text_color=AiPhile.GREEN)
            cv.circle(frame, (new_points[0]), 3,AiPhile.GREEN, 2)

        old_gray = gray_frame.copy()
        # press 'r' to reset the window
        key = cv.waitKey(1)
        if key == ord("s"):
            cv.imwrite(f'reference_img/Ref_img{frame_counter}.png', img)

        # if the 'c' key is pressed, break from the loop
        if key == ord("q"):
            break
        fps = frame_counter/(time.time()-starting_time)
        AiPhile.textBGoutline(frame, f'FPS: {round(fps,1)}', (30,40), scaling=0.6)
        cv.imshow("Streaming", frame) # chỉ cần comment dòng này thì sẽ không show UI 

            # close all open windows
    cv.destroyAllWindows()
    cap.release()

try:
    t = time.time()
    t1 = threading.Thread(target=ReceiveData)
    t2 = threading.Thread(target=doOpenCV)
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    print("All thread join!")
except KeyboardInterrupt:
    ser.close()