import cv2 as cv 
import numpy as np
from pyzbar.pyzbar import decode
import time
import AiPhile

import queue 
import utils
import serial 
import threading 
from math import atan2, pi, ceil

############# variable - uart ###############
### global variable
BACK            = [0, 0]
HEAD            = [1, 1]
LEFT            = [0, 1]
RIGHT           = [1, 0]

pNONE           = 0
pCALIB1         = 1
pCALIB2         = 2
pCALIB3         = 3
pCALIB4         = 4
pCALIBDONE      = 5

pRUN            = 6
pROTATELEFT     = 7
pROTATERIGHT    = 8

pBACK           = 9
pDONE           = 10

BackFlag        = 50
HeadFlag        = 51



Head_doing      = 100 
Calib3_doing    = 101

tProcess        = pNONE

q = queue.Queue() # Init empty queue 

########### function - uart  ###################
ser = serial.Serial(
	port        = '/dev/ttyS0',
	baudrate    = 115200,
	parity      = serial.PARITY_NONE,
	stopbits    = serial.STOPBITS_ONE,
	bytesize    = serial.EIGHTBITS,
	timeout     = 1
)

# param: angle_point
def doAngle(q):
    global tProcess
    if q.qsize() == 3: 
        angle_point = q.get()
    angle_point = angle_point * 4

    if angle_point > 0:
        # goc (duong) be hon 90 -> xoay trai 
        if angle_point <= 90 * 4:
            angle_point = round(angle_point)
            tProcess = pCALIB2
            SendData(angle_point, 20, 15, LEFT[0], LEFT[1])
        # goc (duong) lon hon 90 -> xoay trai
        else: 
            angle_point = 180 * 4 - round(angle_point)
            tProcess    = pCALIB2 
            SendData(angle_point, 20, 15, RIGHT[0], RIGHT[1])
    # angle_point < 0 
    else: 
        angle_point = round(abs(angle_point))
        if angle_point <= 90 * 4: 
            tProcess = pCALIB2
            SendData(angle_point, 20, 15, RIGHT[0], RIGHT[1])
        else: 
            tProcess = pCALIB2 
            angle_point = 180 * 4 - angle_point 
            SendData(angle_point, 20, 15, LEFT[0], LEFT[1])
# param: distance    
def doDistance(q):
    global tProcess
    if q.qsize() == 2:
        Flag = q.get()
        distance = q.get()
    # 1000 -> go back 
    if Flag == BackFlag:
        distance = round(distance * 3.0 / 5)
        tProcess = pCALIB3
        SendData(distance, 20, 15, 0, 0)
    # 1001 -> go head 
    elif Flag == HeadFlag:
        distance = round(distance * 1.0 / 5 )
        tProcess = pCALIB3
        SendData(distance, 20, 15, 1, 1)
# param: angle    
def doCorrect(q): 
    print(f'into doCorrect function and size of q = {q.qsize()}')
    global tProcess
    if q.qsize() == 1:
        angle = q.get()
    angle = round(angle * 4)
    '''
    angle > 0: xoay sang trai (0->180)
    angle < 0: xoay sang phai (0->-180)
    '''
    if angle > 0:
        tProcess = pCALIB4
        SendData(abs(angle-20), 20, 15, 0, 1)
    else: 
        angle = abs(angle)
        tProcess = pCALIB4
        SendData(abs(angle-20), 20, 15, 1, 0)

def doCorrectDistance(q):
    global tProcess 
    print(f'into doCorrectDistance function and the size of q is {q.qsize()}') 
    if q.qsize() == 2: 
        Flag = q.get()
    print(f"Flag is {Flag}")
    if q.qsize() == 1: 
        distance = q.get()
    distance = round(distance * 3.0 / 5)
    
    if Flag == 50:
        tProcess = pCALIBDONE 
        SendData(distance, 20, 15, 0, 0)
    else:
        tProcess = pCALIBDONE 
        SendData(distance, 20, 15, 1, 1)

def doHead(q):
    global tProcess 
    SendData(495, 40, 10, 1, 1)
    # Nếu gán tProcess = pNONE ngay ở đây thì ngay lập tức luồng doOpenCV sẽ thực hiện CALIB 
    tProcess = pDONE 
    if q.qsize() == 0: 
        q.put(Head_doing)

def doRotateLeft(q):
    global tProcess 
    tProcess = pCALIBDONE
    SendData(360, 20, 15, 0, 1)

def doRotateRight(q): 
    global tProcess 
    SendData(360, 20, 15, 1, 0)
    tProcess = pCALIBDONE 

def SendData(Pos, Vel, Acc, Dir1, Dir2):
    data2Send = utils.FormatData(Pos, Vel, Acc, Dir1, Dir2)
    print(data2Send)
    print("into the send_data")
    ser.write(bytes(data2Send, 'utf-8'))

def ReceiveData(q):
    print('into RecieveData thread')
    global tProcess 
    while True:
        s = ser.readline() # s is an bytes object 
        data = s.decode('utf-8') # bytes object b'\xe2\x82\xac100' -> after using decode() method -> data: €100
        data = data.rstrip() # remove trailing whitespace ('\n')
        print(data) 
        if "OK" in data:
            print('into OK condition')
            print(f"tProcess = {tProcess}")
            if tProcess == pNONE:
                pass
            elif tProcess == pDONE: 
                if q.get() == Head_doing: 
                    tProcess = pCALIB1 
                           
            elif tProcess == pCALIB1: # pCALIB1 = 2 
                print(f'into tProcess == pCALIB1 condition and size of q = {q.qsize()}')
                if q.qsize() == 3: 
                    doAngle(q)
                else: 
                    break 
            elif tProcess == pCALIB2: # pCALIB2 = 3 
                print(f'into tProcess == pCALIB2 condition and size of q = {q.qsize()}')
                if q.qsize() == 2:
                    doDistance(q)
                else: 
                    break 
            elif tProcess == pCALIB3: # pCALIB3 = 4 
                print(f'into tProcess == pCALIB3 condition and size of q = {q.qsize()}') 
                if q.qsize() == 1:
                    doCorrect(q)
                else:  
                    print(f"RecieveData into tProcess == pCALIB3 but can't do function doCorrect(q) because q.qsize()={q.qsize()}")
                    continue  
            elif tProcess == pCALIB4: # pCALIB4 = 9 
                print(f'into tProcess == pCALIB4 condition and size of q = {q.qsize()}')
                if q.qsize() == 2:
                    doCorrectDistance(q)
                else: 
                    break
            elif tProcess == pRUN:
                print(f'into tProcess == pRUN condition and size of q = {q.qsize()}')
                if q.qsize() == 0:
                    doHead(q)
                else: 
                    break 
            elif tProcess == pROTATELEFT: 
                print(f"into tProcess == pROTATELEFT condition and size of q = {q.qsize()}")
                if q.qsize() == 0:
                    doRotateLeft(q)
                else: 
                    break 
            

def doOpenCV(q):
    
    global tProcess
    print('into doOpenCV thread')

    list_process    = [pRUN, pRUN, pROTATELEFT, pRUN]
    list_i          = range(len(list_process)) # [0, 1, 2, 3]
    i               = 0 
    angle_point     = 0 
    distance        = 0     
    angle           = 0
    T_x             = 315 
    T_y             = 245
    counter         = 0 
    pre_angle       = 500
    count_send      = 0

    cap = cv.VideoCapture(-1)
    _, frame = cap.read()
    old_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    lk_params = dict(winSize=(20, 20),
                    maxLevel=4,
                    criteria=(cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.01))
    cv.circle(frame, (265, 177), radius = 0, color = (255, 0, 0), thickness = 4)
    old_points = np.array([[]])
    qr_detected= False
    frame_counter = 0
    starting_time = time.time()
    
    while True:
        counter += 1
        frame_counter += 1
        _, frame = cap.read()
        cv.line(frame, (65, 70), (565, 70), (255, 255, 0), 2)
        cv.line(frame, (565, 70), (565, 420), (255, 255, 0), 2)
        cv.line(frame, (565, 420), (65, 420), (255, 255, 0), 2)
        cv.line(frame, (65, 420), (65, 70), (255, 255, 0), 2)
        img = frame.copy()
        barcodes = decode(frame) 
        for barcode in barcodes: 

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
                angle = atan2(b - a, c - d)
                angle = (angle * 180 / pi) 

                G_x = (p2_x + p4_x) / 2.0
                G_y = (p2_y + p4_y) / 2.0
                
                if pre_angle > angle - 2 or pre_angle < angle + 2: 
                    
                    count_send += 1 
                pre_angle = angle
                # print(f"count_send = {count_send}")
                if count_send == 2:
                    count_send = 0

                    if tProcess == pNONE:
                        print('doOpenCV into tprocess == pNONE')
                        tProcess = pCALIB1

                    elif tProcess == pCALIB1:
                        print('doOpenCV into tProcess == pCALIB1')
                        angle_point = round(utils.ComputeAngle(p2_x, p2_y, p4_x, p4_y, T_x, T_y))
                        distance = round(utils.ComputeDistance(p2_x, p2_y, p4_x, p4_y, T_x, T_y))
                        if q.qsize() == 0:
                            q.put(angle_point)   
                            if abs(angle_point) >= 90:
                                q.put(BackFlag) # di lui, goc lon hon 90
                            elif abs(angle_point) < 90: 
                                q.put(HeadFlag) # di toi, goc nho hon 90 
                            q.put(distance) 
                        SendData(1111,1111,1111,1,1)       
                    
                    elif tProcess == pCALIB3:
                        print("doOpenCV into tProcess == pCALIB3")
                        print(f"doOpenCV tProcess = {tProcess} and angle = {angle} and size of q = {q.qsize()}")
                        if q.qsize() == 0: 
                            q.put(angle)
                        if q.qsize() == 1: 
                            SendData(1111,1111,1111,1,1)  
                    
                    elif tProcess == pCALIB4:
                        print("doOpenCV into tProcess == pCALIB4")
                        distance = round(utils.ComputeDistance(p2_x, p2_y, p4_x, p4_y, T_x, T_y))
                        if G_y > 245.0:
                            if q.qsize() == 0: 
                                q.put(BackFlag) # 50 is BackFlag
                        else:
                            if q.qsize() == 0:
                                q.put(HeadFlag) # 51 is HeadFlag 
                        # distance
                        if q.qsize() == 1: 
                            q.put(distance)
                    
                    # Giữa hai hành động trong list_process là quá trình calib
                    elif tProcess == pCALIBDONE and i == 0:
                        tProcess = list_process[i] # pRUN 
                        i += 1 # 0 -> 1 
                    elif tProcess == pCALIBDONE and i == 1: 
                        tProcess = list_process[i] # pRUN 
                        i += 1 # 1 -> 2 
                    elif tProcess == pCALIBDONE and i == 2:
                        tProcess = list_process[i] # pROTATELEFT 
                        i += 1 # 2 -> 3 
                    elif tProcess == pCALIBDONE and i == 3: 
                        tProcess = list_process[i]
                        i = 0                  
                                                    

        img = cv.resize(img, None, fx=2, fy=2,interpolation=cv.INTER_CUBIC)
        gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        stop_code = False
        if qr_detected and stop_code == False:
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
        if key == ord("q"):
            break
        fps = frame_counter/(time.time()-starting_time)
        AiPhile.textBGoutline(frame, f'FPS: {round(fps,1)}', (30,40), scaling=0.6)
        # cv.imshow("Streaming", frame)
    # cv.destroyAllWindows()
    # cap.release()
try:
    t = time.time()
    t1 = threading.Thread(target=ReceiveData, args=(q, ))
    t2 = threading.Thread(target=doOpenCV, args=(q, ))
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    print("All thread join!")
except KeyboardInterrupt:
    ser.close()