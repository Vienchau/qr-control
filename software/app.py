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
#points =()
################### Rapoo Camera 


############# variable - uart ###############
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
pRUN = 9

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

# 5 -> 2
def docHead():
    global tProcess 
    SendData(65,20,20,HEAD[0],HEAD[1])
    tProcess = pNONE
# 5 -> 8
def docBack():
    global tProcess 
    SendData(65,20,20,BACK[0],BACK[1])
    tProcess = pNONE
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

def doHeadVaiLoz(): 
    global tProcess 
    SendData(700, 45, 45, HEAD[0], HEAD[1])
    tProcess = pNONE 

def SendData(Pos, Vel, Acc, Dir1, Dir2):
    data2Send  = utils.FormatData(Pos, Vel, Acc, Dir1, Dir2)
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
            elif tProcess == pRUN: 
                doHeadVaiLoz()




def doOpenCV():
    global tProcess

    cap = cv.VideoCapture(-1)
    _, frame = cap.read()
    old_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    lk_params = dict(winSize=(20, 20),
                    maxLevel=4,
                    criteria=(cv.TERM_CRITERIA_EPS | cv.TERM_CRITERIA_COUNT, 10, 0.01))
    
    #cap = cv.VideoCapture(0) 
    point_selected = False
    #points = [()]
    old_points = np.array([[]])
    qr_detected= False
    # stop_code=False

    frame_counter = 0
    starting_time = time.time()
    # keep looping until the 'q' key is pressed

    counter = 0 
    pre_text = None 
    pre_angle = 500
    flag = None
    
    tmp = None
    count_send = 0
    SendData(1111,1111,1111,1,1)
    while 1: 
        counter += 1
        frame_counter += 1
        ret, frame = cap.read()
        
        img = frame.copy()

        barcodes = decode(frame) 

   

      
        # cv.rectangle(frame, (x_g, y_g), (x_g + w_g, y_g + h_g), (0, 255, 0), 1)
        # cv.rectangle(frame, (xi, yi), (xi + wi, yi + hi), (0, 0, 255), 2)
        # cv.rectangle(frame, (xo, yo), (xo + wo, yo + ho), (255, 0, 0), 1)
        
        #### vertical line ###
        cv.line(frame, (213, 0), (213, 479), (0, 255, 255), 1)
        cv.line(frame, (426, 0), (426, 479), (0, 255, 255), 1)
        ### horizontal line ### 
        cv.line(frame, (0, 159), (639, 159), (0, 255, 255), 1)
        cv.line(frame, (0, 318), (639, 318), (0, 255, 255), 1)
   
        
        
       
        for barcode in barcodes: 
            (x, y, w, h) = barcode.rect

            barcodeData = barcode.data.decode("utf-8") 
            barcodeType = barcode.type
            

            # this block fixes bug "IndexError: list index out of range"
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
            # print(barcode.polygon)
            # if (p1_x >= xo2 and p1_y >= yo2) and (p2_x <= xo2 + wo2 and p2_y >= yo2) and (p3_x >= xo2 and p3_y <= yo2+ho2) and (p4_x <= xo2+wo2 and p4_y <= yo2+ho2):
            
            # print(angle_revise)
            (rv, points, straight_qrcode) = cv.QRCodeDetector().detectAndDecode(frame)
            #print(points)
            if rv:
                points = points[0]

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
                if pre_angle > angle + 2 or pre_angle < angle - 2: 
                    
                    count_send += 1 
                    print(angle, count_send)
                if count_send == 20:
                    count_send = 0 
                    # tProcess = pcHEAD
                    tProcess = utils.CheckCase(p1_x, p1_y, p2_x, p2_y, p3_x, p3_y, p4_x, p4_y)
                    SendData(1111,1111,1111,1,1)
                    
                     


                angle_revise = atan2(p2_y - p1_y, p2_x - p1_x)
                # angle_revise = angle_revise * 180 / pi
                
                text = "{}, {}".format(angle, angle_revise, barcodeType)
        img = cv.resize(img, None, fx=2, fy=2,interpolation=cv.INTER_CUBIC)

        gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
        # display the image and wait for a keypress
        clone = frame.copy()

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