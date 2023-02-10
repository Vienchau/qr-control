# import the necessary packages
import cv2 as cv 
import numpy as np
from pyzbar.pyzbar import decode
# import pyzbar
import time
import AiPhile

from math import atan2, pi

# QR code detector function 
# def detectQRcode(image):
#     # convert the color image to gray scale image
#     Gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)

#     # create QR code object
#     objectQRcode = pyzbar.pyzbar.decode(Gray)
#     for obDecoded in objectQRcode: 
#         x, y, w, h = obDecoded.rect
#         # cv.rectangle(image, (x,y), (x+w, y+h), ORANGE, 4)
#         points = obDecoded.polygon
#         if len(points) > 4:
#             hull = cv.convexHull(   
#                 np.array([points for point in points], dtype=np.float32))
#             hull = list(map(tuple, np.squeeze(hull)))
#         else:
#             hull = points

#         return hull

# Identify angle of QR code (orientation)
# Parameter 'qrcode' is 'frame'
def get_angle(qrcode):
    barcode = decode(qrcode)
    poly = barcode[0].polygon
    angle = atan2(poly[2].y - poly[3].y, poly[2].x - poly[3].x)
    return 180*angle/pi 


#ref_point = []
#click = False
#points =()
################### Rapoo Camera 
cap = cv.VideoCapture(2)
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

while 1: 
   
    frame_counter += 1
    ret, frame = cap.read()
    
    img = frame.copy()

    # hull_points = detectQRcode(frame)
    # if hull_points:
    #     pt1, pt2, pt3, pt4 = hull_points
    #     angle = atan2(pt3.y - pt4.y, pt3.x - pt4.x)
    #     angle = 180 * angle / pi
    # # decode data in QR code
    barcodes = decode(frame) 



    flag = 1 # default flag
    xi = 253
    yi = 204 
    wi = 110  
    hi = 110 

    xo = 200 
    yo = 150
    wo = 200 
    ho = 200

    x_g = 0
    y_g = 0
    w_g = 639 
    h_g = 479

    cv.rectangle(frame, (x_g, y_g), (x_g + w_g, y_g + h_g), (0, 255, 0), 2)
    # cv.rectangle(frame, (xi, yi), (xi + wi, yi + hi), (0, 0, 255), 2)
    cv.rectangle(frame, (xo, yo), (xo + wo, yo + ho), (255, 0, 0), 2)
    # cv.rectangle(frame, (x1 - 100, y1 - 100), (x1 + w1 + 200, y1 + h1 + 200), (0, 255, 0), 2)
    for barcode in barcodes: 
        (x, y, w, h) = barcode.rect
        cv.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 255), 2)
        """ 
        roi: region of interest
        x' = 
        y' = 
        w' = 
        h' = 
        (x', y') & (x' + w', y' + h')
        """


        barcodeData = barcode.data.decode("utf-8") 
        barcodeType = barcode.type
        # print(barcode.polygon)
        
        p1_x = barcode.polygon[0].x
        p1_y = barcode.polygon[0].y
        
        p2_x = barcode.polygon[1].x 
        p2_y = barcode.polygon[1].y

        p3_x = barcode.polygon[2].x 
        p3_y = barcode.polygon[2].y

        p4_x = barcode.polygon[3].x 
        p4_y = barcode.polygon[3].y


        if (p1_x >= xo and p1_y >= yo) and (p2_x <= xo + wo and p2_y >= yo) and (p3_x >= xo and p3_y <= yo+ho) and (p4_x <= xo+wo and p4_y <= yo+hols'):

            (rv, points, straight_qrcode) = cv.QRCodeDetector().detectAndDecode(frame)
            #print(points)
            if rv:
                points = points[0]

                pt1 = points[0]
                pt2 = points[1]
                pt3 = points[2]
                pt4 = points[3]


                a = pt2[1]
                b = pt1[1]

                c = pt2[0]
                d = pt1[0]

                angle_2 = atan2(a - b, c - d)
                angle_2  = angle_2*180/pi
                text = "\"[{}] [{}] [{}]\"".format(barcodeData, angle_2, flag, barcodeType) 
                #print(angle_2)
                # print(text)
                #print(angle_2)
                print(points)
                if angle_2 == 0 or angle_2 == 90 or angle_2 == -90:
                    print("Send data")
                
                # cv.putText(frame, text, (x-10, y-10), cv.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 1)
    img = cv.resize(img, None, fx=2, fy=2,interpolation=cv.INTER_CUBIC)
    
    #angle = get_angle(frame)
    #print(angle)

    #cv.imshow('old frame ', old_gray)
    #cv.imshow('img', img)

    gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    # display the image and wait for a keypress
    clone = frame.copy()
    
    # hull_points = detectQRcode(frame)
    # if hull_points != None:
    #     print(hull_points)


    # print(old_points.size)
    stop_code = False
    # if hull_points:
    #     pt1, pt2, pt3, pt4 = hull_points
    #     # angle = atan2(pt2.y - pt1.y, pt2.x - pt1.x)
    #     # angle = 180 * angle / pi
    #     # print(angle) 
    #     qr_detected = True
    #     stop_code = True
    #     old_points = np.array([pt1, pt2, pt3, pt4], dtype=np.float32)
    #     frame = AiPhile.fillPolyTrans(frame, hull_points, AiPhile.MAGENTA, 0.4)
    #     AiPhile.textBGoutline(frame, f'Detection: Pyzbar', (30,80), scaling=0.5,text_color=(AiPhile.MAGENTA))
    #     cv.circle(frame, pt1, 3, AiPhile.GREEN, 3)
    #     cv.circle(frame, pt2, 3, (255, 0, 0), 3)
    #     cv.circle(frame, pt3, 3,AiPhile.YELLOW, 3)
    #     cv.circle(frame, pt4, 3, (0, 0, 255), 3)

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
    # AiPhile.textBGoutline(frame, f'FPS: {round(fps,1)}', (30,40), scaling=0.6)
    cv.imshow("Streaming", frame) # chỉ cần comment dòng này thì sẽ không show UI 

        # close all open windows
cv.destroyAllWindows()
cap.release()
